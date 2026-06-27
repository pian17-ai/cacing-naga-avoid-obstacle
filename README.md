# 🤖 Avoid Obstacle Robot Cacing Naga Team from SMKN65

> Autonomous robot developed for an **Avoid Obstacle Competition**, capable of navigating through obstacles using three ultrasonic sensors.

🥈 **2nd Place - Provincial Robotics Competition (DKI Jakarta)**

---

## 📸 Robot

![Robot](assets/robot.png)

---

## 🎥 Demo

> Add your competition video or GIF here.

![Demo](assets/competition.mp4)

---

# 📖 Overview

This project is an autonomous obstacle avoidance robot built using an ESP32, three HC-SR04 ultrasonic sensors, and an L298N motor driver.

The robot continuously scans its surroundings, detects obstacles, compares available paths, and selects the safest direction automatically.

The source code in this repository is the original competition version used during the event.

---

# ✨ Features

- Autonomous navigation
- Triple ultrasonic sensors
- Automatic path selection
- Sprint mode on open path
- Reverse recovery when trapped
- Optimized for speed competition

---

# 🛠 Hardware

| Component | Quantity |
|-----------|----------|
| ESP32 | 1 |
| HC-SR04 Ultrasonic Sensor | 3 |
| L298N Motor Driver | 1 |
| DC Motor | 2 |
| Robot Chassis | 1 |
| Battery | 1 |

---

# 📦 Components

![Components](docs/images/components.jpg)

---

# 🧠 Navigation Algorithm

```
Start

↓

Read Left, Center, Right Sensors

↓

Front Clear?

├── Yes
│
│   Is Center Sensor = 999?
│
│   ├── Yes → Sprint Forward
│   └── No  → Normal Forward
│
└── No
      ↓
 Stop
      ↓
 Read Left & Right Again
      ↓
 Compare Distance
      ↓
 Turn to Wider Direction
      ↓
 If Both Blocked
      ↓
 Reverse
      ↓
 Turn Right
```

---

# 📂 Project Structure

```
avoid-obstacle/

│
├── AvoidObstacle.ino
│
├── docs/
│   ├── images/
│   │   ├── robot.jpg
│   │   ├── components.jpg
│   │   └── demo.gif
│   │
│   └── wiring.png
│
└── README.md
```

---

# ⚙ Pin Configuration

## Ultrasonic Sensors

| Sensor | Trigger | Echo |
|---------|---------|------|
| Left | GPIO 5 | GPIO 18 |
| Center | GPIO 19 | GPIO 21 |
| Right | GPIO 22 | GPIO 23 |

---

## Motor Driver

| Pin | GPIO |
|------|------|
| IN1 | 26 |
| IN2 | 27 |
| IN3 | 14 |
| IN4 | 12 |
| ENA | 25 |
| ENB | 33 |

---

# 🚀 Robot Strategy

The robot follows a simple but effective navigation strategy:

1. Continuously read all ultrasonic sensors.
2. Move forward if the front path is clear.
3. Enable Sprint Mode when no obstacle is detected (distance = 999).
4. Stop when an obstacle is detected.
5. Compare left and right distances.
6. Turn toward the wider path.
7. Reverse if both directions are blocked.

This strategy was optimized during the competition to maximize speed while maintaining reliable obstacle avoidance.

---

# 💡 Sprint Mode

When the center ultrasonic sensor returns **999**, it means no obstacle is detected within the sensor range.

Instead of moving at normal speed, the robot immediately switches to maximum speed.

```cpp
if (jarakTengah == 999) {
    majuSprint();
}
```

This optimization significantly improves performance on long straight paths.

---

<!-- # 📷 Gallery

| Robot | Components |
|--------|------------|
| ![](docs/images/robot.jpg) | ![](docs/images/components.jpg) |

--- -->

# 🏆 Competition

🥈 **2nd Place**

Provincial Robotics Competition (Avoid Obstacle Category)

---

# 🔮 Future Improvements

- PID motor control
- Better turning algorithm
- Dynamic obstacle prediction
- IMU integration
- Refactored source code

---

# 📄 License

MIT License