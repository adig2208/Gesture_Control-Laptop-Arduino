# Gesture Control for Laptops using Arduino

## Project Overview
This project enables users to control their laptops using simple hand gestures. By leveraging Arduino and ultrasonic sensors, it interprets physical gestures to execute commands such as adjusting the volume, scrolling through pages, and navigating web browsers.

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
Guide to the gestures recognized by the system and their corresponding actions:

- **Volume Up**: Move your hand closer to the right ultrasonic sensor to increase the volume. Ideal for quick volume adjustments without the need to reach for your laptop.
- **Volume Down**: Move your hand closer to the left ultrasonic sensor to decrease the volume. This gesture provides an effortless way to lower volume levels discreetly.
- **Scroll Up**: A swift hand motion in an upward direction over the right sensor scrolls up through documents or web pages, making reading and browsing more convenient.
- **Scroll Down**: Similarly, a downward hand gesture over the right sensor scrolls down, enhancing your navigation experience through long articles or websites.
- **Forward**: Gesture towards the right with your hand between both sensors to navigate forward in your web browser, handy for skipping through pages or tutorials.
- **Rewind**: A leftward hand gesture between both sensors acts as the "back" command in web browsers, allowing you to easily return to previous content.
- **Change Tab**: Raise your hand above the left sensor to quickly switch between open tabs, facilitating efficient multitasking and information retrieval.
- **Drop Down**: An overarching motion that briefly covers both sensors triggers dropdown menus or lists, simplifying navigation in complex applications or websites.
- **Enter**: Bringing your hand close to both sensors simultaneously simulates the "Enter" key, perfect for selecting options or confirming commands without touching the keyboard.

For the best experience, ensure your gestures are deliberate and clear, maintaining an optimal distance from the sensors as described in the calibration section.

## Calibration
Upon starting, the system will calibrate the sensors based on the initial conditions. Please ensure there is no obstruction in front of the sensors during calibration.
