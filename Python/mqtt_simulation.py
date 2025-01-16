import sys
import os
import json
import paho.mqtt.client as mqtt
import time

# Add the path to the simulation script
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..')))

from simulation_data import simulate_temp, simulate_hum

# Set up MQTT Broker Details
broker = "localhost"
port = 1883
topic = "home/temperature"

# Create a client instance for MQTT
client = mqtt.Client()
client.connect(broker, port)

if __name__ == "__main__":
    while True:
        # Simulate data
        temp = simulate_temp()
        hum = simulate_hum()

        # Create a message in JSON format using json.dumps to ensure proper JSON formatting
        message = json.dumps({"temperature": temp, "humidity": hum})

        # Publish the message to the MQTT topic
        client.publish(topic, message)
        print(f"Published: {message} to topic: {topic}")

        # Sleep for 5 seconds before generating new data; adjust the frequency as needed
        time.sleep(5)
