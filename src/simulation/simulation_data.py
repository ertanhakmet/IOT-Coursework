import random
import time

# This function simulates fake temperature data between 15 and 30 degrees
def simulate_temp():
    return round(random.uniform(15.0, 30.0), 2)

# This function simulates fake humidity data between 30 to 60 percent
def simulate_hum():
    return round(random.uniform(30.0, 60.0), 2)

if __name__ == "__main__":
    while True:
        temp = simulate_temp()
        hum = simulate_hum()
        
        print(f"Temperature: {temp} C")
        print(f"Humidity: {hum}%")
    
        time.sleep(5)
    
