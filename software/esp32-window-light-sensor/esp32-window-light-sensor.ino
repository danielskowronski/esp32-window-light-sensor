#include "HomeSpan.h" 
#include "Identify.h"      
#include "Sensors.h"
#include <WiFi.h>

void setup() {
  Serial.begin(115200);

  homeSpan.begin(Category::Bridges,"esp32-window-light-sensor Bridge");
  new SpanAccessory();  
    new Identify("esp32-window-light-sensor Bridge","DS",WiFi.macAddress().c_str(),"esp32-window-light-sensor Bridge","0.1",3);
    new Service::HAPProtocolInformation();
      new Characteristic::Version("1.1.0");
      
  new SpanAccessory();                                                          
    new Identify("esp32-window-light-sensor Ambient Light Sensor","DS",WiFi.macAddress().c_str(),"esp32-window-light-sensor Ambient Light Sensor","0.1",5);
    new AmbientLightSensor();
}

void loop(){
  homeSpan.poll(); 
}
