# KeyBoard Controlled Robot

This project demonstrates a simple **KeyBoard Controlled Robot** controlled via a web interface. The robot can move forward, backward, turn left, turn right, and stop using a web browser over a Wi-Fi network. This project is built on an **ESP32** board using the **Arduino IDE**.
## Note : This Project has been configured using UBUNTU-JammyJellyfish.
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

## Instructions on How to build this project from scratch
1. **Install and configure VSCode**
2. **Download Extension "PLATFORMIO"**
   - Install the **PLATFORMIO IDE** extension.  
   [PLATFORMIO IDE Extension Link](https://platformio.org/platformio-ide)
3. **Create a new Project through PLATFORMIO Extension Interface**
   -{Picture}
4. **Name the project as per the requirement.**
5. **In boards lookup 'DOIT ESP-32 DEVKIT-V1' and Select Framework to be 'Arduino'.** {Picture}
6. **Use the Default location unless as per requirement and Click 'FINISH'.** 
7. **In your Project Folder0 look for 'platforn.ini' file and open it.**
8. **Paste the following code in the folder**
### Modify the `platformio.ini` File

In your project folder, locate the **`platformio.ini`** file. Open it and replace the content with the following configuration:

```
[env:esp32doit-devkit-v1]
platform = espressif32
board = esp32dev
framework = arduino
upload_port = /dev/ttyUSB0
monitor_speed = 115200
upload_speed = 115200
lib_deps = 
    https://github.com/micro-ROS/micro_ros_platformio/    
    WiFi
    mirs240x/micro_ros_arduino@^2.0.7-humble
build_flags = 
    -D MICROROS_WIFI_TRANSPORT
```

   **NOTE** : **The indentation is the very crucial factor for this step. The indentation of the lines according to the following image.**
9. **Head to src folder and open 'main.cpp' and paste the code present in the code block from the github files.**
10. **Create a python file 'Control.py' in the project folder and paste the code present in the github files.**
11. **Connect your 'ESP-32' to your device using a USB-B cable and make sure it is connected properly.**
12. **Open up Terminal and run the following code**
          ```sudo chmod a+rw /dev/ttyUSB0```
13. **Perform Build, Upload Operations throught your VSCODE.**
14. ** Disconnect ESP-32 and Connect it to a external Power Source and Check if it connects to the Same Network.**
15. ** After Ensuring That ESP-32 has Connected, Run "Control.py" On your device and insert commands to move the Robot.**
    
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
