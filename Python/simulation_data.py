import random
import time

# Function to simulate temperature data between 15° to 30°
def simulate_temp():
    return round(random.uniform(15.0, 30.0), 2) 

# Function to simulate humidity data between 30% to 60%
def simulate_hum():
    return round(random.uniform(30.0, 60.0), 2) 

if __name__ == "__main__":
    while True:
        temp = simulate_temp()
        hum = simulate_hum()
        
        print(f"Temperature: {temp} C")
        print(f"Humidity: {hum}%")
    
        time.sleep(5) # new data is generated every 5 seconds
    
