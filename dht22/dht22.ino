#include <WiFi.h>
#include <Ambient.h>
#include <DHT.h>

const char* ssid = "your_ssid";
const char* pass = "your_pass";
unsigned int channelId = your_channelId;
const char* writeKey = "your_writeKey";

const int dhtpin = 4;

DHT dht(dhtpin, DHT22);
WiFiClient client;
Ambient ambient;

void setup() {
  Serial.begin(115200);
  Serial.println("Initialize Wifi");
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("WiFi Connected");
  Serial.println("Ambient start");
  ambient.begin(channelId, writeKey, &client); 
  Serial.println("Initialize DHT22");
  dht.begin();
}

void loop() {
  static int count = 0;
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  Serial.print("Count = ");
  Serial.print(count);
  Serial.print(", Temperature = ");
  Serial.print(t);
  Serial.print(", Humidity = ");
  Serial.println(h);
  ambient.set(1, t);
  ambient.set(2, h);
  ambient.send();
  count++;
  delay(10000);
}
