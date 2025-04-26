#include "network.h"
#include "config.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

void setupWiFi() {
  WiFi.begin(wifi_ssid, wifi_pass);
  Serial.print(F("Connecting to Wi-Fi"));
  uint8_t wifi_tries = 0;
  while (WiFi.status() != WL_CONNECTED && wifi_tries < 40) {
    delay(500);
    Serial.print('.');
    wifi_tries++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println(F("\nWi-Fi Connected!"));
    Serial.print(F("IP Address: "));
    Serial.println(WiFi.localIP());
  } else {
    Serial.println(F("\nWi-Fi Connection Failed!"));
  }
}

void sendDataToThingSpeak(float t_water, float t_oil, float fan_rpm, float pump_lpm) {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println(F("WiFi disconnected. Cannot send data."));
    return;
  }

  WiFiClient client;
  HTTPClient http;

  String url = String("http://") + ts_host + "/update?api_key=" + ts_key +
               "&field1=" + String(t_water, 1) +
               "&field2=" + String(t_oil,   1) +
               "&field3=" + String(fan_rpm, 0) +
               "&field4=" + String(pump_lpm,1);

  Serial.print(F("Sending data to ThingSpeak: "));
  Serial.println(url);

  http.setTimeout(5000);
  http.begin(client, url);

  int http_code = http.GET();

  if (http_code > 0) {
    Serial.printf("[HTTP] GET... code: %d\n", http_code);
    if (http_code == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.print(F("[HTTP] Response: "));
      Serial.println(payload);
    }
  } else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(http_code).c_str());
  }

  http.end();
}
