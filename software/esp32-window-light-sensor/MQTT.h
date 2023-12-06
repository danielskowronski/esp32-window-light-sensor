#include "MQTT_AUTH.h"
#include <PubSubClient.h>
#include <WiFi.h>
#include <ArduinoNvs.h>

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE	(50)
char msg[MSG_BUFFER_SIZE];

char topic_lux[48];

int mqtt_enabled=0;
String mqtt_ip;
String mqtt_user;
String mqtt_pass;


void destroyMQTT(){
  if (mqtt_enabled != 1) {
    return;
  }

  client.disconnect();
}

void readMQTTConfig(){
  destroyMQTT();

  mqtt_ip =      NVS.getString("MQTT_IP");
  mqtt_user =    NVS.getString("MQTT_USER");
  mqtt_pass =    NVS.getString("MQTT_PASS");
  mqtt_enabled = NVS.getInt("MQTT_ENABLED");

  Serial.printf("[MQTT] mqtt_enabled=%d mqtt_ip=%s mqtt_user=%s mqtt_pass=%s\n",mqtt_enabled, mqtt_ip.c_str(), mqtt_user.c_str(), mqtt_pass.c_str());
}
void configureMQTT(const char *buf){
  mqtt_enabled = 0;

  char buff[1024];
  Serial.print("enter MQTT IP:       ");
  Utils::readSerial(buff, 1000);
  String mqtt_ip = String(buff);
  Serial.print("enter MQTT username: ");
  Utils::readSerial(buff, 1000);
  String mqtt_user = String(buff);
  Serial.print("enter MQTT password: ");
  Utils::readSerial(buff, 1000);
  String mqtt_pass = String(buff);

  NVS.setString("MQTT_IP",      mqtt_ip);
  NVS.setString("MQTT_USER",    mqtt_user);
  NVS.setString("MQTT_PASS",    mqtt_pass);

  if (mqtt_ip != "" && mqtt_user != "" && mqtt_pass != ""){
    Serial.println("[MQTT] Enabling MQTT");
    mqtt_enabled=1;
  }
  else {
    Serial.println("[MQTT] Some fields are empty, disabling MQTT");
    mqtt_enabled=0;
  }
  
  NVS.setInt("MQTT_ENABLED", mqtt_enabled);
  NVS.commit();

  readMQTTConfig();
}

void setupMQTT(){
  if (mqtt_enabled != 1) {
    return;
  }

  client.setServer(mqtt_ip.c_str(), 1883);
  bool ok = client.connect("esp32-window-light-sensor", mqtt_user.c_str(), mqtt_pass.c_str());

  snprintf (topic_lux, MSG_BUFFER_SIZE, "esp32-window-light-sensor/%s/lux", WiFi.macAddress().c_str());

  if (ok) {
    Serial.printf("[MQTT] Connected, using topic: %s\n", topic_lux);
  }
  else {
    Serial.printf("[MQTT] Can't connect to: %s\n", mqtt_ip.c_str());
  }

}
void publishMQTT(){
  if (mqtt_enabled != 1) {
    return;
  }

  unsigned long now = millis();
  bool success = false;
  if (now - lastMsg > 5000) {
    lastMsg = now;
    snprintf (msg, MSG_BUFFER_SIZE, "%ld", last_lux);
    success = client.publish(topic_lux, msg);

    if (! success){
      destroyMQTT();
      setupMQTT();
      success = client.publish(topic_lux, msg);
    }

    Serial.printf("[MQTT] Publish status: %d (%s -> %d)\n",success, topic_lux, last_lux);
  }
}
