# Autonomous Smart Car Controlled via Telegram

An ESP32-based smart car featuring remote control through a Telegram Bot and autonomous obstacle avoidance.

## Project Overview

This academic project combines embedded systems, IoT communication, motor control, and ultrasonic obstacle detection.

The robot supports two operating modes:

* **Manual Mode:** Control the car remotely using Telegram commands.
* **Autonomous Mode:** Detect obstacles and automatically change direction to avoid collisions.

## Hardware Components

* ESP32 microcontroller
* HC-SR04 ultrasonic sensor
* L298N dual H-bridge motor driver
* Two DC motors and a two-wheel chassis
* Servo motor for sensor scanning

## Technologies

* Embedded C/C++
* Arduino IDE
* ESP32 Wi-Fi
* Telegram Bot API
* HTTPS communication
* Ultrasonic distance measurement

## Telegram Commands

| Command    | Function                             |
| ---------- | ------------------------------------ |
| `/start`   | Display available commands           |
| `/avancer` | Move forward                         |
| `/reculer` | Move backward                        |
| `/droite`  | Turn right                           |
| `/gauche`  | Turn left                            |
| `/stop`    | Stop the motors                      |
| `/auto`    | Enable autonomous obstacle avoidance |

## Obstacle Avoidance

The robot uses an HC-SR04 sensor mounted on a servo motor to scan its surroundings.

* **25 cm:** Autonomous obstacle-avoidance threshold.
* **15 cm:** Manual-mode safety stop threshold.

When an obstacle is detected in autonomous mode, the robot stops, reverses, scans both directions, and turns toward the direction with more available space.

## Hardware Connections

| Component    | ESP32 GPIO |
| ------------ | ---------- |
| HC-SR04 Trig | GPIO 5     |
| HC-SR04 Echo | GPIO 18    |
| L298N ENA    | GPIO 25    |
| L298N ENB    | GPIO 13    |
| L298N IN1    | GPIO 26    |
| L298N IN2    | GPIO 27    |
| L298N IN3    | GPIO 14    |
| L298N IN4    | GPIO 12    |
| Servo signal | GPIO 4     |

## Setup

1. Install Arduino IDE and the ESP32 board package.
2. Install the required libraries.
3. Configure Wi-Fi credentials and the Telegram Bot token.
4. Upload the firmware to the ESP32.
5. Start the Telegram Bot and test the commands.

## Test Results

The project presentation reports successful Wi-Fi connectivity, Telegram commands, servo scanning, and obstacle avoidance, with an approximately one-second Telegram response delay.

## Future Improvements

* ESP32-CAM video monitoring
* Faster communication for real-time control
* Improved navigation and mapping
* Battery monitoring and power management

## Academic Project

ISSAT Sousse — Embedded Systems
Academic year: 2024–2025
