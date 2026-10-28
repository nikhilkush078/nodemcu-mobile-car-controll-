# NodeMCU ESP8266 Wi-Fi Controlled Robot Car

A Wi-Fi-controlled robotic car built using the **NodeMCU ESP8266, L298N motor driver, and DC motors**. The car can be controlled wirelessly using an Android application (`application.apk`) or through a compatible web browser.

## Project Overview

This project demonstrates how to build a simple wireless robotic car using an ESP8266 microcontroller. The NodeMCU creates its own Wi-Fi access point, allowing a mobile phone to connect directly to the car and send movement commands.

The robot supports forward, backward, left, right, diagonal movement, stopping, and speed control.

## Components Required

- NodeMCU ESP8266 development board
- L298N dual H-bridge motor driver
- 2 DC geared motors
- Robot car chassis with wheels
- Battery or suitable DC power supply for the motors
- Jumper wires
- Android smartphone
- `application.apk` — Android control application

## Hardware Connections

| NodeMCU Pin | GPIO | L298N Pin |
|---|---|---|
| D5 | GPIO14 | ENA |
| D6 | GPIO12 | ENB |
| D8 | GPIO15 | IN1 |
| D7 | GPIO13 | IN2 |
| D4 | GPIO2 | IN3 |
| D3 | GPIO0 | IN4 |

### Motor Connections

| L298N Output | Connection |
|---|---|
| OUT1 and OUT2 | Right DC motor |
| OUT3 and OUT4 | Left DC motor |

### Power Connections

- Connect the motor battery to the L298N motor power input, following the driver's voltage rating.
- Connect the battery negative, L298N GND, and NodeMCU GND together.
- Power the NodeMCU using a suitable regulated supply.
- Check the L298N module's 5V jumper and regulator configuration before connecting its 5V terminal to the NodeMCU.

### Wiring Diagram

The wiring diagram below illustrates the controller, motor driver, motors, and power connections.

![NodeMCU ESP8266 Wi-Fi Robot Car Wiring Diagram](wiring-diagram.png)

**Note:** Add the wiring diagram image to the repository and name it `wiring-diagram.png`, or update the image path above to match your actual filename.

## Software Requirements

- Arduino IDE
- ESP8266 board support package
- ESP8266WiFi library
- ESP8266WebServer library
- Android control application (`application.apk`)

The ESP8266 libraries are generally included with the ESP8266 board package for Arduino IDE.

## How to Upload the Code

1. Install the Arduino IDE.
2. Install ESP8266 board support using the Boards Manager.
3. Select the appropriate NodeMCU ESP8266 board.
4. Open the robot car source code (`nodemcu_car.ino`).
5. Connect the NodeMCU to your computer using USB.
6. Select the correct COM port and upload the code.
7. Open the Serial Monitor at **115200 baud** to check the access-point IP address.

## How to Control the Robot Using `application.apk`

The repository contains an Android application named `application.apk`, which can be used to control the robot car from a smartphone.

1. Upload the program to the NodeMCU ESP8266.
2. Power on the robot car.
3. Enable Wi-Fi on your Android smartphone.
4. Connect to the Wi-Fi network named **NodeMCU Car**.
5. Install `application.apk` on your Android phone if it is not already installed.
6. Open the application and use its movement and speed controls to operate the car.

The NodeMCU creates its own Wi-Fi network, so a separate router or internet connection is not normally required.

**Important:** The application must be configured to communicate with the NodeMCU's web-server IP address and expected command format. The default access-point IP is usually `192.168.4.1`.

## Supported Commands

| Command | Function |
|---|---|
| F | Move forward |
| B | Move backward |
| L | Turn left |
| R | Turn right |
| I | Move forward-right |
| G | Move forward-left |
| J | Move backward-right |
| H | Move backward-left |
| S | Stop |
| 0–9 | Adjust motor speed |

The speed settings range from 400 to 1023 in the program.

## Repository Structure

```text
NodeMCU-WiFi-Robot-Car/
│
├── nodemcu_car.ino
├── application.apk
├── wiring-diagram.png
└── README.md
```

## Features

- Wireless control using ESP8266 Wi-Fi
- Android application support
- Forward and backward movement
- Left and right turning
- Diagonal movement
- Adjustable motor speed
- Direct Wi-Fi connection without a router
- Low-cost educational robotics platform

## Applications

- Beginner robotics projects
- Arduino and ESP8266 learning
- Wireless motor control experiments
- Embedded systems practice
- College electronics workshops
- DIY robotic vehicle development

## Safety Notes

- Verify the motor driver's current and voltage ratings before connecting the motors.
- Never power the motors directly from the NodeMCU GPIO pins.
- Ensure all grounds are connected together.
- Use a regulated power supply for the NodeMCU.
- The ESP8266 boot-configuration pins must not be forced into incompatible logic states during startup.

## Author

**Nikhil Kushwah**  
Electrical Engineering  
Samrat Ashok Technological Institute (SATI), Vidisha

## License

This project is intended for educational and DIY robotics purposes. You may adapt and improve the design for your own learning projects.
