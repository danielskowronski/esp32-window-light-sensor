#define VER "0.2"
#define BMP280_I2C_ADDRESS 0x76
#define BH1750_I2C_ADDRESS 0x23

#include <Wire.h>
#include "HomeSpan.h" 
#include "Identify.h"      
#include "LightSensor.h"
#include "TemperatureSensor.h"
#include <WiFi.h>

void setup() {
  Serial.begin(115200);

  homeSpan.begin(Category::Bridges,"esp32-window-light-sensor Bridge");
  new SpanAccessory();  
    new Identify("esp32-window-light-sensor Bridge","DS",WiFi.macAddress().c_str(),"esp32-window-light-sensor Bridge", VER ,3);
    new Service::HAPProtocolInformation();
      new Characteristic::Version("1.1.0");
      
  new SpanAccessory();                                                          
    new Identify("esp32-window-light-sensor Light Sensor","DS",WiFi.macAddress().c_str(),"esp32-window-light-sensor Light Sensor", VER, 5);
    new LightSensor();

  new SpanAccessory();                                                          
    new Identify("esp32-window-light-sensor Temperature Sensor","DS",WiFi.macAddress().c_str(),"esp32-window-light-sensor Temperature Sensor", VER, 7);
    new TemperatureSensor();
}

void loop(){
  homeSpan.poll(); 
}
