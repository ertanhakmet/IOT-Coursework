#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// WiFi and MQTT Configuration
const char* ssid = "iPhone";           // WiFi SSID
const char* password = "ertanhak";     // WiFi password
const char* mqtt_server = "172.20.10.2";   // MQTT Broker IP
const char* mqtt_topic = "home/temperature";  // MQTT topic for publishing

WiFiClient espClient;
PubSubClient client(espClient);

// Function to setup WiFi connection
void setup_wifi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

// Function to handle MQTT connection and reconnection
void reconnect() {
  while (!client.connected()) {
    if (client.connect("ESP8266Client")) {
      Serial.println("Connected to MQTT Broker!");
    } else {
      Serial.print("MQTT connection failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(9600);  // Initialize serial
  setup_wifi();        // Setup WiFi connection
  client.setServer(mqtt_server, 1883);  // Configure MQTT server
}

void loop() {
  // Ensure MQTT connection
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Check if data is available on Serial
  if (Serial.available()) {
    String data = Serial.readStringUntil('\n');
    int separator = data.indexOf(',');
    
    if (separator != -1) {
      float humidity = data.substring(0, separator).toFloat();
      float temperature = data.substring(separator + 1).toFloat();
      
      // Create JSON payload
      String payload = "{\"humidity\":" + String(humidity) + ",\"temperature\":" + String(temperature) + "}";
      
      // Publish to MQTT
      client.publish(mqtt_topic, payload.c_str());
      
      // Debug output
      Serial.print("Published to ");
      Serial.print(mqtt_topic);
      Serial.print(": ");
      Serial.println(payload);
    }
  }
}