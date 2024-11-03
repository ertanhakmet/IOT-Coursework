import sys
import os

sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..')))

import paho.mqtt.client as mqtt
import time
from src.simulation.simulation_data import simulate_temp, simulate_hum

# Set up MQTT Broker Details
broker = "localhost"
port = 1883
topic = "smart_home/sensors"

# Create a client instance for MQTT
client = mqtt.Client()
client.connect(broker, port)

if __name__ == "__main__":
    while True:
        # simulate data
        temp = simulate_temp()
        hum = simulate_hum()

        # create a message in JSON format
        message = f'{{"temperature": {temp}, "humidity": {hum}}}'

        # publish the message to the MQTT topic
        client.publish(topic, message)
        print(f"Published: {message} to topic: {topic}")

        time.sleep(5) # you can change the frequency of generating new data