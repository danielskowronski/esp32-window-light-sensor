#include <Wire.h>
//#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP280 HW611;

struct TemperatureSensor : Service::TemperatureSensor {
  SpanCharacteristic *temperature;
  
  TemperatureSensor() : Service::TemperatureSensor(){
    temperature=new Characteristic::CurrentTemperature(0);
    temperature->setRange(-40,85);
        
    Serial.print("Configuring Temperature");
    Serial.print("\n");

    HW611.begin(BMP280_I2C_ADDRESS); // TODO: handle initialization errors
  } 

  void loop(){
    if(temperature->timeVal()>2500){
      float celsius=HW611.readTemperature();;
      temperature->setVal(celsius); 
      LOG1("Temperature Update: ");
      LOG1(celsius);
      LOG1(" °C\n");
    }
  } 
};
