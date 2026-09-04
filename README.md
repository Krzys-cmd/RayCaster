

<h3 align="center">Terminal Raycaster 2.5D FPS</h3>

<p align="center">
A lightweight, retro 3D FPS engine based on Raycasting techniques, built from scratch in <b>C++23</b>. It renders pseudo-3D graphics directly in the Windows console using ASCII/ANSI characters and Unicode blocks.
</p>


## Key Features

| Feature | Description |
|---|---|
| **Raycasting Engine** | 2.5D perspective rendering, wall collision detection, "fisheye" effect correction, and terminal shading. |
| **Map Progression** | Multi-level support with varying room layouts, interactive doors, and spawn points. |
| **Artificial Intelligence (Zombies)** | Enemies featuring Line-of-Sight player tracking, dynamic positioning (`ZombiePositions.h`), and animations. |
| **Combat System** | Real-time shooting, hit registration, ammo management, and weapon animations. |
| **Custom User Interface (UI)** | Interactive Start/Death/Victory screens and a real-time HUD displaying health, ammo, and score. ||


## Controls

| Key | Action |
| :---: | :--- |
| **W / S** | Move forward / backward |
| **A / D** | Turn left / right |
| **Space** | Shoot |
| **E** | Open door (cost: 50 points) |
| **Enter** | Select menu option |

## Engine Architecture and Mathematics

The engine constructs a 2.5D environment based on a 2D map grid.

### Logika Raycastera
For every column on the screen, a ray is cast. The engine uses the Ray Marching method with a constant, small step size. The ray's distance is iteratively increased by a small value (0.002), and at each step, the coordinates are recalculated to check if the ray has hit a wall or a door on the map grid.
* **Ray Angle:** Calculated based on player view angle, Field of View (FOV), and current screen column: `rayAngle = startAngle + ((float)i / rayCount) * fov`.
* **"Fisheye" Correction:** To prevent spherical image distortion (fisheye effect), the engine avoids plain Euclidean distance, calculating **perpendicular distance** to the camera plane instead:
  `trueDistance = wallDistance * cosf(rayAngle - playerAngle);`
* **Shading:** Rendered wall height is inversely proportional to distance. Greater distances map to darker ANSI character shades.

### Enemy Logic and Positioning (Zombies)

Zombie screen positioning and rendering combine trigonometry, collision detection, and perspective scaling:

* **Movement and Player Tracking:** 
  The zombie's path is determined by the angle to the player (`angleToPlayer` computed via `std::atan2`). If a zombie has line-of-sight and is within range $2.0 \le \text{distance} < 10.0$, it moves toward the player using steps derived from `sinf` and `cosf`.

* **Wall Collision Detection:** 
  Prior to moving, the engine checks collisions using a physical radius around the zombie (`radius = 0.3f`) at 4 bounding points. This prevents enemies from passing through walls during pursuit.

* **Screen Projection (`z.centerX`):** 
  The horizontal screen position of the sprite is calculated from the difference between the player's view angle and the angle to the zombie (`angleDiff`), mapped to a specific screen column within the Field of View (`fov`):
  `z.centerX = (angleDiff + fov / 2.0f) / fov * screenWidth;`
