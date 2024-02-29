# Gesture Control for Laptops using Arduino

## Project Overview
This project enables users to control their laptop using simple hand gestures. By leveraging Arduino and ultrasonic sensors, it interprets physical gestures to execute commands such as adjusting the volume, scrolling through pages, and navigating web browsers.

## Hardware Requirements
- Arduino Uno or any compatible microcontroller
- 2 x HC-SR04 Ultrasonic Sensors
- 1 x LED (for visual feedback)
- Breadboard and jumper wires for connections

## Software Requirements
- Arduino IDE for uploading the sketch to the Arduino board.
- Python 3.x for running the script that communicates between the Arduino and the laptop.

## Setup Instructions

### Arduino Setup
1. Connect the ultrasonic sensors and the LED to the Arduino as per the wiring diagram included in the repository.
2. Upload the `gesture_control_laptop.ino` sketch to your Arduino using the Arduino IDE.

### Python Setup
1. Ensure Python 3.x is installed on your laptop.
2. Install necessary Python libraries with `pip install pyserial pyautogui`.
3. Execute the `laptop_control.py` script to start listening to the gesture commands from the Arduino.

## Usage
Perform gestures in front of the ultrasonic sensors to control your laptop:
- Move your hand closer to the **right sensor** to increase the volume.
- Move your hand closer to the **left sensor** to decrease the volume.
- Explore more gestures and their functionality.

## Calibration
Upon starting, the system will calibrate the sensors based on the initial conditions. Please ensure there is no obstruction in front of the sensors during calibration.
