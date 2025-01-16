#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// WiFi and MQTT Configuration
const char* ssid = "iPhone"; // change wifi name to yours       
const char* password = "ertanhak"; // change password to yours
const char* mqtt_server = "172.20.10.2"; // change ip address to yours   
const char* mqtt_topic = "home/temperature";  

WiFiClient espClient;
PubSubClient client(espClient);

// Setup wifi connection
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

// Handle MQTT
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
  Serial.begin(9600);  
  setup_wifi();        
  client.setServer(mqtt_server, 1883);  
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  if (Serial.available()) {
    String data = Serial.readStringUntil('\n');
    int separator = data.indexOf(',');
    
    if (separator != -1) {
      float humidity = data.substring(0, separator).toFloat();
      float temperature = data.substring(separator + 1).toFloat();
      
      // Put the data in JSON format
      String payload = "{\"humidity\":" + String(humidity) + ",\"temperature\":" + String(temperature) + "}";
      
      // Publish data
      client.publish(mqtt_topic, payload.c_str());
      
      Serial.print("Published to ");
      Serial.print(mqtt_topic);
      Serial.print(": ");
      Serial.println(payload);
    }
  }
}