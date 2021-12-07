#include "FS.h"           // https://nerdyelectronics.com/upload-files-to-esp8266-spiffs/
#include <ESP8266WiFi.h>  // https://github.com/esp8266/Arduino/releases/tag/2.7.4
#include <PubSubClient.h> // https://github.com/knolleary/pubsubclient/releases/tag/v2.8
#include <NTPClient.h>    // https://github.com/arduino-libraries/NTPClient/releases/tag/3.2.0
#include <WiFiUdp.h>      // https://github.com/esp8266/Arduino/releases/tag/2.7.4
#include <WiFiManager.h>  // https://github.com/tzapu/WiFiManager

// WiFi
WiFiClientSecure espWiFiClient;
WiFiManager wifiManager;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

// MQTT
void message_received_callback(char *topic, byte *payload, unsigned int length)
{
  Serial.println("Message arrived");
  char message[50];
  for (int i = 0; i < length; i++)
  {
    message[i] = (char)payload[i];
  }
  control_light_from_json(message);
}
const char *AWS_endpoint = "a3l1l7s5ulqonx-ats.iot.eu-west-1.amazonaws.com"; // Edit your AWS Endpoint here
PubSubClient mqttClient(AWS_endpoint, 8883, message_received_callback, espWiFiClient);

// MQTT TOPIC INIT
char mac[13];
void get_mac_address()
{
  String macS = WiFi.macAddress();
  int nextIdx = 0;
  for (int i = 0; i < macS.length(); i++)
  {
    if (macS.charAt(i) == ':')
    {
      continue;
    }
    mac[nextIdx] = macS.charAt(i);
    nextIdx++;
  }
}

// Lights
uint8_t R_Pin = D1;
uint8_t G_Pin = D2;
uint8_t B_Pin = D6;

char topicPub[18];
char topicSub[18];
bool isWifiConnected = false;

void setup()
{
  Serial.begin(115200);
  Serial.setDebugOutput(false);

  setup_pins();
  WiFi.mode(WIFI_STA);
  light_red();
  isWifiConnected = wifiManager.autoConnect("NerdLight");
  if (isWifiConnected)
  {
    light_yellow();
  }
  
  setup_wifi();
  delay(1000);

  get_mac_address();
  strcpy(topicPub, mac);
  strcat(topicPub, "-PUB");
  strcpy(topicSub, mac);
  strcat(topicSub, "-SUB");
  Serial.println("My MAC Address is:");
  Serial.println(mac);

  if (!SPIFFS.begin())
  {
    Serial.println("Failed to mount file system");
    return;
  }

  load_mqtt_certificates();
}

long lastTime = 0;
void loop()
{
  while (isWifiConnected != true)
  {
    light_red();
    delay(500);
    light_off();
  }

  if (!mqttClient.connected())
  {
    Serial.println("MQTT not connected, reconnecting now");
    mqtt_reconnect();
  }
  mqttClient.loop();
  delay(500);
  if (millis() - lastTime > 5000)
  {
    send_heartbeat();
    activity_led();
    lastTime = millis();
  }
}

void print_heap()
{
  Serial.print("Heap: ");
  Serial.println(ESP.getFreeHeap());
}
