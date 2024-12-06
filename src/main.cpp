#include <WiFi.h>

// Replace with your WiFi credentials
const char* ssid = "Wi_Fi";       // Your WiFi SSID
const char* password = "";         // Your WiFi password.. Make Sure Your Wifi Password is Blank so that ESP-32 can easily connect.

WiFiServer server(80); // Create a web server on port 80

// Define motor control pins (LEDs for simulation)
const int motorPin1 = 12; // Motor 1 control pin (Forward) - LED 1
const int motorPin2 = 13; // Motor 2 control pin (Backward) - LED 2
const int motorPin3 = 14; // Motor 3 control pin (Left turn) - LED 3
const int motorPin4 = 15; // Motor 4 control pin (Right turn) - LED 4

// Define LED control pins (additional LEDs)
const int ledPin1 = 4; // Forward LED
const int ledPin2 = 5; // Backward LED
const int ledPin3 = 2; // Left LED
const int ledPin4 = 16; // Right LED

// Function prototypes
void moveForward();
void moveBackward();
void turnLeft();
void turnRight();
void stopMotors();
void turnOffAllLeds(); // Function to turn off all LEDs

void setup() {
  Serial.begin(115200);

  // Ensure all LEDs are off at the start
  turnOffAllLeds();

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi...");
  
  // Wait for connection or timeout after 30 seconds
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 30) {
    delay(500);
    Serial.print(".");
    attempts++;
  }

  if(WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConnected to WiFi!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nFailed to connect to WiFi.");
    return;  // Abort if WiFi connection fails
  }

  // Start the server
  server.begin();
  Serial.println("Server started.");

  // Initialize motor pins (LEDs)
  pinMode(motorPin1, OUTPUT);  // LED for forward
  pinMode(motorPin2, OUTPUT);  // LED for backward
  pinMode(motorPin3, OUTPUT);  // LED for left turn
  pinMode(motorPin4, OUTPUT);  // LED for right turn

  // Initialize additional LED pins
  pinMode(ledPin1, OUTPUT);    // LED for forward
  pinMode(ledPin2, OUTPUT);    // LED for backward
  pinMode(ledPin3, OUTPUT);    // LED for left turn
  pinMode(ledPin4, OUTPUT);    // LED for right turn
}

void loop() {
  // Check if a client is connected
  WiFiClient client = server.available();
  
  if (client) {
    Serial.println("New client connected.");
    String request = "";

    // Read the client request
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        request += c;

        // Break out of loop once the request ends (after "\r\n\r\n")
        if (request.endsWith("\r\n\r\n")) {
          break;
        }
      }
    }

    // Debug: Print the request to the Serial Monitor
    Serial.println(request);

    // Parse the request for docking commands
    if (request.indexOf("/FORWARD") != -1) {
      moveForward();
      Serial.println("Moving Forward");
    } else if (request.indexOf("/BACKWARD") != -1) {
      moveBackward();
      Serial.println("Moving Backward");
    } else if (request.indexOf("/LEFT") != -1) {
      turnLeft();
      Serial.println("Turning Left");
    } else if (request.indexOf("/RIGHT") != -1) {
      turnRight();
      Serial.println("Turning Right");
    } else if (request.indexOf("/STOP") != -1) {
      stopMotors();
      Serial.println("Stopping Motors");
    }

    // Send an HTTP response to the client
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close");
    client.println();  // Blank line between headers and body
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println("<h1>AutoDocking Robot Control</h1>");
    client.println("<p><a href=\"/FORWARD\">Move Forward</a></p>");
    client.println("<p><a href=\"/BACKWARD\">Move Backward</a></p>");
    client.println("<p><a href=\"/LEFT\">Turn Left</a></p>");
    client.println("<p><a href=\"/RIGHT\">Turn Right</a></p>");
    client.println("<p><a href=\"/STOP\">Stop</a></p>");
    client.println("</html>");

    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
  }
}

void moveForward() {
  turnOffAllLeds(); // Turn off all LEDs before moving

  digitalWrite(motorPin1, HIGH);  // LED 1 for forward
  digitalWrite(motorPin2, LOW);   // LED 2 off
  digitalWrite(motorPin3, LOW);   // LED 3 off
  digitalWrite(motorPin4, LOW);   // LED 4 off

  // Turn on LED for forward motion
  digitalWrite(ledPin1, HIGH);
}

void moveBackward() {
  turnOffAllLeds(); // Turn off all LEDs before moving

  digitalWrite(motorPin1, LOW);   // LED 1 off
  digitalWrite(motorPin2, HIGH);  // LED 2 for backward
  digitalWrite(motorPin3, LOW);   // LED 3 off
  digitalWrite(motorPin4, LOW);   // LED 4 off

  // Turn on LED for backward motion
  digitalWrite(ledPin2, HIGH);
}

void turnLeft() {
  turnOffAllLeds(); // Turn off all LEDs before turning

  digitalWrite(motorPin1, LOW);   // LED 1 off
  digitalWrite(motorPin2, LOW);   // LED 2 off
  digitalWrite(motorPin3, HIGH);  // LED 3 for left turn
  digitalWrite(motorPin4, LOW);   // LED 4 off

  // Turn on LED for left turn
  digitalWrite(ledPin3, HIGH);
}

void turnRight() {
  turnOffAllLeds(); // Turn off all LEDs before turning

  digitalWrite(motorPin1, LOW);   // LED 1 off
  digitalWrite(motorPin2, LOW);   // LED 2 off
  digitalWrite(motorPin3, LOW);   // LED 3 off
  digitalWrite(motorPin4, HIGH);  // LED 4 for right turn

  // Turn on LED for right turn
  digitalWrite(ledPin4, HIGH);
}

void stopMotors() {
  turnOffAllLeds(); // Turn off all LEDs before stopping

  digitalWrite(motorPin1, LOW);  // Turn off LED 1 (forward)
  digitalWrite(motorPin2, LOW);  // Turn off LED 2 (backward)
  digitalWrite(motorPin3, LOW);  // Turn off LED 3 (left turn)
  digitalWrite(motorPin4, LOW);  // Turn off LED 4 (right turn)
}

void turnOffAllLeds() {
  // Turn off all motor LEDs
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);

  // Turn off all status LEDs
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin3, LOW);
  digitalWrite(ledPin4, LOW);
}
