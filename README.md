# AutoDocking Robot

This project demonstrates a simple **AutoDocking Robot** controlled via a web interface. The robot can move forward, backward, turn left, turn right, and stop using a web browser over a Wi-Fi network. This project is built on an **ESP32** board using the **Arduino IDE**.

## Features
- **Wi-Fi Controlled:** Control the robot remotely through a simple web interface.
- **Motor Control:** Simulates movement commands such as forward, backward, left turn, right turn, and stop.
- **LED Indicators:** LEDs light up to indicate the direction of movement.
- **Web Server:** A lightweight HTTP server built into the ESP32 to handle requests and send responses to the client (web browser).

## Components Used
- **ESP32** board (or ESP8266)
- 4x LEDs (for visual direction indicators)
- 4x motors (simulated with LEDs in this project)
- **Wi-Fi router** for network connection

## Pin Configuration
- **Motor Control Pins (Simulated with LEDs):**
  - Pin 12: Forward
  - Pin 13: Backward
  - Pin 14: Left Turn
  - Pin 15: Right Turn
- **LED Pins:**
  - Pin 4: Forward LED
  - Pin 5: Backward LED
  - Pin 2: Left Turn LED
  - Pin 16: Right Turn LED

## How to Use
1. **Connect the ESP32 to Wi-Fi:**
   - Modify the `ssid` and `password` in the code with your Wi-Fi credentials.

2. **Upload the Code:**
   - Upload the Arduino sketch to your ESP32 board using the Arduino IDE.

3. **Access the Web Interface:**
   - Once the ESP32 is connected to Wi-Fi, open the Serial Monitor to view the IP address assigned to your ESP32.
   - In a web browser, enter the IP address. You will see a simple HTML interface with links to control the robot.

4. **Control the Robot:**
   - Click on the links to move the robot:
     - **Move Forward**
     - **Move Backward**
     - **Turn Left**
     - **Turn Right**
     - **Stop**

   - The corresponding LED will light up to show the movement direction.

## Code Explanation

### Wi-Fi Connection:
```cpp
WiFi.begin(ssid, password);
