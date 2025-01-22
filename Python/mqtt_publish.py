import paho.mqtt.client as mqtt
import json
import time
from simulation_data import simulate_temp, simulate_hum

client = mqtt.Client()
client.connect("localhost", 1883, 60)

client.loop_start()

while True:
    temperature = simulate_temp()
    humidity = simulate_hum()
    payload = json.dumps({"temperature": temperature, "humidity": humidity})

    client.publish("home/temperature", payload)
    print(f"Data sent to home/temperature: {payload}")

    time.sleep(5)
