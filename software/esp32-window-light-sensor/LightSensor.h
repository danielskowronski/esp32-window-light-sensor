#include <Wire.h>
#include <BH1750.h>

BH1750 GY302(BH1750_I2C_ADDRESS);

struct LightSensor : Service::LightSensor {
  SpanCharacteristic *light;
  
  LightSensor() : Service::LightSensor(){
    light=new Characteristic::CurrentAmbientLightLevel(0);
    light->setRange(0,65535);
        
    Serial.print("Configuring Light Sensor");

    Wire.begin();
    bool initialized = GY302.begin();

    if (initialized) {
      Serial.println("OK");
    }
    else {
      Serial.println("FAILED");
    }
  } 

  void loop(){
    if(light->timeVal()>2500){
      uint16_t lux = GY302.readLightLevel();
      light->setVal(lux); // Characteristic::StatusFault does not work so letting it be 65534

      LOG1("Light Update: ");
      LOG1(lux);
      LOG1(" lx\n");
    }
  } 
};
