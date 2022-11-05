#include <math.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP280 HW611;

struct TemperatureSensor : Service::TemperatureSensor {
  SpanCharacteristic *temperature;
  
  TemperatureSensor() : Service::TemperatureSensor(){
    temperature = new Characteristic::CurrentTemperature(0);
    temperature->setRange(-40,85);
        
    Serial.print("Configuring Temperature: ");

    Wire.begin();
    bool initialized = HW611.begin(BMP280_I2C_ADDRESS, BMP280_CHIPID);

    if (initialized) {
      Serial.println("OK");
    }
    else {
      Serial.println("FAILED");
    }
  } 

  void loop(){
    if(temperature->timeVal()>2500){
      float celsius=HW611.readTemperature();
      if (isnan(celsius)){
        celsius=-40; // Characteristic::StatusFault does not work so applying workaround
      }
      temperature->setVal(celsius); 

      LOG1("Temperature Update: ");
      LOG1(celsius);
      LOG1(" °C");
      LOG1("\n");
    }
  } 
};
