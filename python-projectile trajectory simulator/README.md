# Projectile Motion Simulator

## Overview
This project is an **interactive projectile motion simulator** built using Python.  
It allows users to visualize and compare the trajectories of objects launched at different angles, highlighting the maximum height of each trajectory.

## Objective
The goal of this project was to create a simulator that can:  
- Model the motion of a projectile in two dimensions  
- Allow users to input initial velocity, launch height, and multiple angles  
- Visualize multiple trajectories on the same plot for easy comparison  
- Highlight and report key metrics such as maximum height, range, and flight time for each angle  

## How It Works
The simulator uses **time-step integration** to calculate the position of a projectile over time under uniform gravity.  
For each angle:  
1. The program calculates horizontal and vertical positions at small time intervals.  
2. It stores trajectory data in arrays and identifies the maximum height.  
3. Trajectories are plotted on a graph, with maximum height points highlighted and labeled.  
4. Key metrics are printed in the console for each launch angle.

## Software / Logic
- Accepts user input for velocity, initial height, and launch angles  
- Uses a loop to update projectile position over time  
- Detects the maximum height and final impact point for each trajectory  
- Plots all trajectories together for visual comparison  
- Prints Maximum Height, Range, and Flight Time for each angle  

## Technologies Used
- Python  
- NumPy (for numerical calculations)  
- Matplotlib (for plotting trajectories)  

## What I Learned
- Implementing physics equations in code for multiple scenarios  
- Comparing multiple trajectories visually and quantitatively  
- Using Python libraries to create interactive simulations  
- Translating real-world physics concepts into a graphical simulation  

## Future Improvements
- Add air resistance for more realistic projectile motion  
- Include interactive GUI sliders for live parameter adjustment  
- Allow multiple projectiles with different velocities for side-by-side comparison  
