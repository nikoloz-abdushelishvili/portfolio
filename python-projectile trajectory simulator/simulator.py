"""
Projectile Motion Simulator
Simulates trajectories for multiple launch angles and highlights maximum heights
"""

import numpy as np
import matplotlib.pyplot as plt

def simulate_trajectory(v0, angle_deg, h0=0, g=9.81, dt=0.01):
    """
    Simulates projectile motion and returns x, y, max height, range, flight time
    """
    angle_rad = np.radians(angle_deg)
    vx = v0 * np.cos(angle_rad)
    vy = v0 * np.sin(angle_rad)

    t, x, y = 0, 0, h0
    t_list, x_list, y_list = [0], [0], [h0]

    while y >= 0:
        vy -= g * dt
        x += vx * dt
        y += vy * dt
        t += dt
        t_list.append(t)
        x_list.append(x)
        y_list.append(y)

    # Correct final point to y=0 (linear interpolation)
    if y_list[-1] < 0:
        x_last = x_list[-2] + (x_list[-1] - x_list[-2]) * (0 - y_list[-2]) / (y_list[-1] - y_list[-2])
        x_list[-1] = x_last
        y_list[-1] = 0

    max_height = max(y_list)
    range_distance = x_list[-1]
    flight_time = t_list[-1]

    return np.array(x_list), np.array(y_list), max_height, range_distance, flight_time

# ----- Main Program -----
v0 = float(input("Enter initial velocity (m/s): "))
h0 = float(input("Enter initial height (m): "))
angles = input("Enter launch angles (degrees, comma-separated, e.g. 30,45,60): ")
angles = [float(a.strip()) for a in angles.split(",")]

plt.figure(figsize=(10, 6))

for angle in angles:
    x, y, max_height, range_distance, flight_time = simulate_trajectory(v0, angle, h0)
    max_idx = np.argmax(y)
    
    # Plot trajectory
    plt.plot(x, y, label=f'{angle}°')
    # Highlight maximum height
    plt.plot(x[max_idx], y[max_idx], 'o', markersize=8)
    plt.text(x[max_idx], y[max_idx]+0.5, f'{y[max_idx]:.1f} m', fontsize=9, ha='center')
    
    print(f"\nAngle: {angle}°")
    print(f"Max Height: {max_height:.2f} m")
    print(f"Range: {range_distance:.2f} m")
    print(f"Flight Time: {flight_time:.2f} s")

# Customize plot
plt.xlabel('Distance (m)')
plt.ylabel('Height (m)')
plt.title(f'Projectile Motion for Different Angles (v₀={v0} m/s)')
plt.grid(True, alpha=0.3)
plt.legend(title='Launch Angle')
plt.xlim(left=0)
plt.ylim(bottom=0)
plt.tight_layout()
plt.show()
