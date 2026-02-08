# Plant Watering System

## Overview
This project is an **automatic plant watering system** designed to monitor soil moisture and water plants without manual intervention. It uses sensors and a microcontroller to ensure plants receive the right amount of water at the right time.

## Objective
The goal of this project was to design and implement a system that can:  
- Detect soil dryness accurately  
- Automatically turn on a water pump when needed  
- Maintain optimal soil moisture for healthy plant growth  

## How It Works
The system uses a **soil moisture sensor** to measure the water content in the soil.  
The sensor readings are processed by an **Arduino microcontroller**, which controls a water pump to deliver water whenever the soil is dry.  
The system stops watering once the soil reaches the desired moisture level.  

## Hardware Components
- Arduino  
- Soil moisture sensor  
- Water pump  
- Relay module or transistor for controlling the pump  
- Tubing and container for water  
- Power supply  

## Software / Logic
- Continuously reads the soil moisture sensor  
- Compares sensor value to a predefined moisture threshold  
- Turns on the water pump if soil is dry  
- Turns off the pump once the soil is adequately moist  

## Technologies Used
- C / C++ (Arduino)  
- Arduino IDE  

## What I Learned
- Reading and interpreting sensor data  
- Controlling actuators (water pump) with Arduino  
- Structuring embedded programs for real-world applications  
- Designing

