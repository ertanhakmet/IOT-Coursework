#include <DHT.h>

// Temperature and Humidity Sensor Configuration
#define DHTPIN 2         
#define DHTTYPE DHT22    
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);    
  dht.begin();          
}

void loop() {
  delay(2000);

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print(humidity);
  Serial.print(",");
  Serial.println(temperature);
}