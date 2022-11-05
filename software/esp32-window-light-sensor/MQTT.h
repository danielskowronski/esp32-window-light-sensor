#include "MQTT_AUTH.h"
#include <PubSubClient.h>
#include <WiFi.h>



WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE	(50)
char msg[MSG_BUFFER_SIZE];

char topic_lux[48];

void setupMQTT(){
  client.setServer(mqtt_ip, 1883);
  client.connect("esp32-window-light-sensor", mqtt_user,mqtt_pass);

  snprintf (topic_lux, MSG_BUFFER_SIZE, "esp32-window-light-sensor/%s/lux", WiFi.macAddress().c_str());
  Serial.print("MQTT topic: ");
  Serial.println(topic_lux);
}
void publishMQTT(){
  unsigned long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    snprintf (msg, MSG_BUFFER_SIZE, "%ld", last_lux);
    client.publish(topic_lux, msg);
  }
}
