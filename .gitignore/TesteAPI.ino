#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "Galvao";
const char* password = "mariaepedro";

void setup() 
{
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(1000);
    Serial.println("Connecting...");
  }
}

void loop() 
{
  if (WiFi.status() == WL_CONNECTED) 
  {
    HTTPClient http; //Object of class HTTPClient
    http.begin("http://api.openweathermap.org/data/2.5/weather?id=3397277&appid=7d103cfe921d9a5bfcf551a90513f265");
    int httpCode = http.GET();

    if (httpCode > 0) 
    {
      String payload = http.getString();
      Serial.println(httpCode);
      Serial.println(payload);
    }
    http.end(); //Close connection
  }
  delay(60000);
}
