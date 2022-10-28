struct AmbientLightSensor : Service::LightSensor {
  SpanCharacteristic *light;
  
  AmbientLightSensor() : Service::LightSensor(){
    light=new Characteristic::CurrentAmbientLightLevel(0);
    light->setRange(0,2048);
        
    Serial.print("Configuring Ambient Light Sensor");
    Serial.print("\n");
  } 

  void loop(){
    if(light->timeVal()>2500){
      float lux=analogRead(A3)/2;
      light->setVal(lux); 
      LOG1("Ambient Light Update: ");
      LOG1(lux);
      LOG1("\n");
    }
  } 
};
