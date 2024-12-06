import requests

# Replace with the ESP32's IP address
esp32_ip = "http://192.168.124.68"  # Example: "http://192.168.1.100"

# LED control pins on the ESP32
LED_PIN_FORWARD = 4  # Forward LED pin
LED_PIN_BACKWARD = 5  # Backward and Stop LED pin
LED_PIN_LEFT = 2  # Left turn LED pin
LED_PIN_RIGHT = 16  # Right turn LED pin

# Function to move the robot forward
def move_forward():
    url = f"{esp32_ip}/FORWARD"
    response = requests.get(url)
    if response.status_code == 200:
        print("Robot moving forward")
        turn_on_led(LED_PIN_FORWARD)
    else:
        print("Failed to move robot forward")

# Function to move the robot backward
def move_backward():
    url = f"{esp32_ip}/BACKWARD"
    response = requests.get(url)
    if response.status_code == 200:
        print("Robot moving backward")
        turn_on_led(LED_PIN_BACKWARD)
    else:
        print("Failed to move robot backward")

# Function to turn the robot left
def turn_left():
    url = f"{esp32_ip}/LEFT"
    response = requests.get(url)
    if response.status_code == 200:
        print("Robot turning left")
        turn_on_led(LED_PIN_LEFT)
    else:
        print("Failed to turn robot left")

# Function to turn the robot right
def turn_right():
    url = f"{esp32_ip}/RIGHT"
    response = requests.get(url)
    if response.status_code == 200:
        print("Robot turning right")
        turn_on_led(LED_PIN_RIGHT)
    else:
        print("Failed to turn robot right")

# Function to stop the robot
def stop_robot():
    url = f"{esp32_ip}/STOP"
    response = requests.get(url)
    if response.status_code == 200:
        print("Robot stopped")
        turn_on_led(LED_PIN_BACKWARD)  # Turn on LED for stop (same as backward)
    else:
        print("Failed to stop robot")

# Function to turn on the appropriate LED based on the action
def turn_on_led(led_pin):
    # Turn off all LEDs before turning on the selected one
    turn_off_all_leds()
    # Turn on the selected LED pin
    url = f"{esp32_ip}/LED/{led_pin}/ON"
    response = requests.get(url)
    if response.status_code == 200:
        print(f"LED on pin {led_pin} turned ON")
    else:
        print(f"Failed to turn on LED on pin {led_pin}")

# Function to turn off all LEDs
def turn_off_all_leds():
    for led_pin in [LED_PIN_FORWARD, LED_PIN_BACKWARD, LED_PIN_LEFT, LED_PIN_RIGHT]:
        url = f"{esp32_ip}/LED/{led_pin}/OFF"
        response = requests.get(url)
        if response.status_code == 200:
            print(f"LED on pin {led_pin} turned OFF")
        else:
            print(f"Failed to turn off LED on pin {led_pin}")

# Main loop to take user input and control the robot
def control_robot():
    while True:
        user_input = input("Enter 'FORWARD' to move forward, 'BACKWARD' to move backward, 'LEFT' to turn left, 'RIGHT' to turn right, 'STOP' to stop, or 'EXIT' to quit: ").strip().upper()

        if user_input == 'FORWARD':
            move_forward()
        elif user_input == 'BACKWARD':
            move_backward()
        elif user_input == 'LEFT':
            turn_left()
        elif user_input == 'RIGHT':
            turn_right()
        elif user_input == 'STOP':
            stop_robot()
        elif user_input == 'EXIT':
            print("Exiting...")
            break
        else:
            print("Invalid input. Please enter 'FORWARD', 'BACKWARD', 'LEFT', 'RIGHT', 'STOP', or 'EXIT'.")

# Run the program
control_robot()
