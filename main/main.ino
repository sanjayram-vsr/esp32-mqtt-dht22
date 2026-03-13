#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <time.h>

#define WIFI_SSID       "Hotspot"
#define WIFI_PASSWORD   "raghu@4567"

#define MQTT_SERVER     "mqtt-dashboard.com"
#define MQTT_PORT       1883

#define LED_PIN         4
#define DHT_PIN         5
#define DHT_TYPE        DHT22

#define TOPIC_LED       "home/led"
#define TOPIC_REQUEST   "home/command"
#define TOPIC_DATA      "home/environment"

WiFiClient espClient;
PubSubClient client(espClient);
DHT dht(DHT_PIN, DHT_TYPE);

void callback(char* topic, byte* payload, unsigned int length) {
  String msg = "";
  for (int i = 0; i < length; i++) msg += (char)payload[i];

  Serial.print("Received on ");
  Serial.print(topic);
  Serial.print(" : ");
  Serial.println(msg);

  // --- LED CONTROL ---
  if (String(topic) == TOPIC_LED) {
    if (msg == "ON") {
      digitalWrite(LED_PIN, HIGH);
      client.publish(TOPIC_DATA, "LED turned ON");
    }
    if (msg == "OFF") {
      digitalWrite(LED_PIN, LOW);
      client.publish(TOPIC_DATA, "LED turned OFF");
    }
  }

  // --- SEND SENSOR DATA WHEN REQUESTED ---
  if (String(topic) == TOPIC_REQUEST) {
    if (msg == "READ") {

      float t = dht.readTemperature();
      float h = dht.readHumidity();

      if (isnan(t) || isnan(h)) {
        client.publish(TOPIC_DATA, "Sensor Error!");
        return;
      }

      String dataMsg =
        " Temp: " + String(t) +
        "C, Hum: " + String(h) + "%";

      client.publish(TOPIC_DATA, dataMsg.c_str());
      Serial.println("Published: " + dataMsg);

    }
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");
    if (client.connect("TEST1234")) {
      Serial.println("connected!");
      client.subscribe(TOPIC_LED);
      client.subscribe(TOPIC_REQUEST);
    } else {
      Serial.println("retrying in 2 sec");
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  dht.begin();

  Serial.println("Connecting WiFi...");
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(400);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");
  Serial.println(WiFi.localIP());

  client.setServer(MQTT_SERVER, MQTT_PORT);
  client.setCallback(callback);

}

void loop() {  
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
