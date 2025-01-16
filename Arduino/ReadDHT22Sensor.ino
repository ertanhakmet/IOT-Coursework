#include <DHT.h>

// DHT22 Configuration
#define DHTPIN 2         // DHT22 connected to digital pin 2
#define DHTTYPE DHT22    // DHT 22
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);    // Start serial communication at 9600 baud
  dht.begin();          // Initialize DHT sensor
}

void loop() {
  // Wait for 2 seconds between measurements
  delay(2000);

  // Reading temperature and humidity
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Check if any reads failed
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Send data in format: humidity,temperature
  Serial.print(humidity);
  Serial.print(",");
  Serial.println(temperature);
}