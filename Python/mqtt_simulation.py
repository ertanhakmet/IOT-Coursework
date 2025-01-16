import sys
import os
import json
import paho.mqtt.client as mqtt
import time

# Include the path for the simulation
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..')))

from simulation_data import simulate_temp, simulate_hum

# MQTT Broker Details
broker = "localhost"
port = 1883
topic = "home/temperature"

client = mqtt.Client()
client.connect(broker, port)

if __name__ == "__main__":
    while True:
        temp = simulate_temp()
        hum = simulate_hum()

        message = json.dumps({"temperature": temp, "humidity": hum})

        # Publish the data
        client.publish(topic, message)
        print(f"Published: {message} to topic: {topic}")

        time.sleep(5)
