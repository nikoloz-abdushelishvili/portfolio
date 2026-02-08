# Line Following Robot

## Overview
This project is an autonomous line-following robot designed to detect and follow a predefined path on the ground using sensors and a microcontroller.

## Objective
The goal of this project was to design and implement a robot that can:
- Detect a line accurately
- Adjust its movement in real time
- Follow the path smoothly with minimal deviation

## How It Works
The robot uses infrared (IR) sensors to detect the contrast between the line and the surface.  
Sensor readings are processed by the microcontroller, which controls the motors to steer the robot left or right to stay on the line.

## Hardware Components
- Arduino
- IR line sensors
- DC motors
- Motor driver
- Chassis
- Battery pack

## Software / Logic
- Reads sensor values continuously
- Compares sensor input to threshold values
- Adjusts motor speed and direction accordingly
- Uses conditional logic (or PID control, if applicable)

## Technologies Used
- C / C++ (Arduino)
- Arduino IDE

## What I Learned
- Working with sensors and noisy data
- Motor control and hardware interfacing
- Debugging embedded systems
- Translating physical behavior into software logic

## Future Improvements
- Implement PID control for smoother motion
- Improve sensor calibration
- Add obstacle detection

