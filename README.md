# ESP32 Telegram Robot Car 🤖

An ESP32-based robotic car controlled remotely through Telegram, featuring ultrasonic obstacle detection and servo-assisted navigation.

## Overview

This project implements a smart robotic car using an ESP32 microcontroller. The robot receives movement commands through a Telegram bot and includes an automatic mode that detects obstacles and selects a direction to avoid them.

## Features

* 📱 Remote control through Telegram
* ⬆️ Forward and backward movement
* ↪️ Left and right steering
* 🛑 Manual stop command
* 📡 Ultrasonic distance measurement
* 🤖 Automatic obstacle avoidance
* 🔄 Servo-assisted ultrasonic sensor scanning
* 📶 Wi-Fi connectivity

## Hardware Components

* ESP32 development board
* L298N dual H-bridge motor driver
* DC motors and robot car chassis
* HC-SR04 ultrasonic distance sensor
* SG90 or compatible servo motor
* Battery and power supply
* Jumper wires

## Software and Libraries

* Arduino IDE
* ESP32 Arduino Core
* UniversalTelegramBot
* ArduinoJson
* ESP32Servo

## Telegram Commands

| Command    | Function                            |
| ---------- | ----------------------------------- |
| `/start`   | Display available commands          |
| `/avancer` | Move forward                        |
| `/reculer` | Move backward                       |
| `/droite`  | Turn right                          |
| `/gauche`  | Turn left                           |
| `/stop`    | Stop the robot                      |
| `/auto`    | Enable automatic obstacle avoidance |

## Installation

1. Install the Arduino IDE.
2. Install the ESP32 board support package.
3. Install the required libraries.
4. Create a private `secrets.h` file containing your Wi-Fi credentials and Telegram bot configuration.
5. Open `RobotTelegram.ino`.
6. Select the correct ESP32 board and serial port.
7. Upload the program to the ESP32.
8. Connect the robot to a suitable power supply and test the Telegram commands.

**Security:** Never publish Wi-Fi passwords, Telegram bot tokens, or other private credentials.

## Pin Configuration

| Component        | ESP32 GPIO |
| ---------------- | ---------- |
| Ultrasonic TRIG  | GPIO 5     |
| Ultrasonic ECHO  | GPIO 18    |
| Motor driver ENA | GPIO 25    |
| Motor driver ENB | GPIO 13    |
| Motor driver IN1 | GPIO 26    |
| Motor driver IN2 | GPIO 27    |
| Motor driver IN3 | GPIO 14    |
| Motor driver IN4 | GPIO 12    |
| Servo signal     | GPIO 4     |

Check the electrical compatibility of the ultrasonic sensor's ECHO output with the ESP32's 3.3 V GPIO inputs before powering the circuit.

## How It Works

The ESP32 connects to Wi-Fi and communicates with a Telegram bot. In manual mode, users control the motors with Telegram commands. In automatic mode, the ultrasonic sensor measures the distance to nearby obstacles. When an obstacle is detected, the robot stops, reverses, scans both directions using the servo, and turns toward the side with more available space.

## Future Improvements

* Add battery voltage monitoring.
* Implement non-blocking motor control.
* Improve obstacle avoidance and distance filtering.
* Add command authorization using the Telegram chat ID.
* Include a wiring diagram and demonstration video.

## Author

Embedded Systems / Electrical Engineering Student

## License

This project is intended for educational and personal development purposes. A license can be added to define reuse and distribution permissions.
