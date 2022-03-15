// Change this to your unique names
#define PROTOTYPE_NAME "MyDevice"
#define SERVER_NAME "MyServer"
// Change this to your server PC IP
#define HOST_SERVER "143.248.109.205"

// Change this value to control data sending frequency
// e.g., 50: once every 50ms
const long interval = 50; 
unsigned long previousMillis = 0;

#include <SocketIoClient.h>
#include <ArduinoJson.h>
SocketIoClient socket;

// Include libraries and declare global variables BELOW



void setup() {
  Serial.begin(115200);      
  while(smartWiFi(PROTOTYPE_NAME));  
  launchWeb(1);
  socket.on(SERVER_NAME, event);
  socket.begin(HOST_SERVER);
  
  // Pin setup HERE
  pinMode(13, OUTPUT);

}


void loop() {  
  mdns_setup();  
  unsigned long currentMillis = millis();  

  // Sending data to web
  if (currentMillis - previousMillis >= interval) {    
    previousMillis = currentMillis;
    
    DynamicJsonDocument data_to_web(1024);

    // configure the json array of data HERE
    // i.e., data_to_web["data_name"] = data    
    // e.g., data_to_web["button"] = digitalRead(13);
    
    String jsonData;
    serializeJson(data_to_web, jsonData);    
    socket.emit(PROTOTYPE_NAME, jsonData.c_str());
  }
  socket.loop();  
  
  // Loop code HERE (NO DELAYS ALLOWED)    
  
}


// Receiving data from web
void event(const char * data, size_t length) {
  DynamicJsonDocument data_from_web(1024);
  deserializeJson(data_from_web, data);

  // Parse your received json data from here
  // i.e., data = data_from_web["data_name"];
  // e.g., 
  bool buttonState = data_from_web["button"];

  // Use your parsed data HERE (NO DELAYS ALLOWED)   
  // e.g.,

  digitalWrite(13,buttonState);
}
