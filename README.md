# 🤖 Avoid Obstacle Robot Cacing Naga Team from SMKN65

> Autonomous robot developed for an **Avoid Obstacle Competition**, capable of navigating through obstacles using three ultrasonic sensors.

🥈 **2nd Place - Provincial Robotics Competition (DKI Jakarta)**

---

## 📸 Robot

![Robot](assets/robot.png)

---

## 🎥 Contest

![Demo](assets/competition.gif)

---

# 📖 Overview

This project is an autonomous obstacle avoidance robot built using an ESP32, three HC-SR04 ultrasonic sensors, and an L298N motor driver.

The robot continuously scans its surroundings, detects obstacles, compares available paths, and selects the safest direction automatically.

The source code in this repository is the original competition version used during the event.

---

## 👥 Authors

- [Alvian Cahyo P](https://github.com/pian17-ai)
- [Muhammad Ramadhan Putra Wietanto](https://github.com/Ramadhan1914)
- [Madison Dipatulus](https://github.com/madisondipatulus)

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
| DC Motor | 4 |
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

# ⚙ Pin Configuration

# 🔌 Wiring Diagram

## ESP32 ↔ HC-SR04 Ultrasonic Sensors

| HC-SR04 | ESP32 |
|----------|--------|
| Left VCC | 5V |
| Left GND | GND |
| Left TRIG | GPIO 5 |
| Left ECHO | GPIO 18 |
| Center VCC | 5V |
| Center GND | GND |
| Center TRIG | GPIO 19 |
| Center ECHO | GPIO 21 |
| Right VCC | 5V |
| Right GND | GND |
| Right TRIG | GPIO 22 |
| Right ECHO | GPIO 23 |

---

## ESP32 ↔ L298N

| L298N | ESP32 |
|--------|--------|
| IN1 | GPIO 26 |
| IN2 | GPIO 27 |
| IN3 | GPIO 14 |
| IN4 | GPIO 12 |
| ENA | GPIO 25 |
| ENB | GPIO 33 |
| GND | GND (Common Ground) |

> **Important:** ESP32 GND **must be connected** to the L298N GND.

---

## Power Connections

| Device | Connection |
|----------|-----------|
| ESP32 VIN / 5V | 5V Supply *(or USB while programming)* |
| ESP32 GND | Battery GND |
| L298N +12V / VIN | Battery Positive |
| L298N GND | Battery Negative |
| HC-SR04 VCC | ESP32 5V |
| HC-SR04 GND | ESP32 GND |

> All grounds must be connected together (Common Ground).

---

## L298N ↔ Motors

The robot uses **4 DC motors**.

```
Motor A (Left Side)

OUT1 ───── Left Front Motor (+)
OUT2 ───── Left Front Motor (-)

           │
           └── Parallel

OUT1 ───── Left Rear Motor (+)
OUT2 ───── Left Rear Motor (-)
```

```
Motor B (Right Side)

OUT3 ───── Right Front Motor (+)
OUT4 ───── Right Front Motor (-)

            │
            └── Parallel

OUT3 ───── Right Rear Motor (+)
OUT4 ───── Right Rear Motor (-)
```

---

## GPIO Summary

| GPIO | Function |
|-------|----------|
| GPIO 5 | Left Ultrasonic Trigger |
| GPIO 18 | Left Ultrasonic Echo |
| GPIO 19 | Center Ultrasonic Trigger |
| GPIO 21 | Center Ultrasonic Echo |
| GPIO 22 | Right Ultrasonic Trigger |
| GPIO 23 | Right Ultrasonic Echo |
| GPIO 26 | Motor Driver IN1 |
| GPIO 27 | Motor Driver IN2 |
| GPIO 14 | Motor Driver IN3 |
| GPIO 12 | Motor Driver IN4 |
| GPIO 25 | Motor Driver ENA (PWM) |
| GPIO 33 | Motor Driver ENB (PWM) |

---

## Hardware Architecture

```
                 +------------------+
                 |      ESP32       |
                 +------------------+

        GPIO5  ------------ TRIG Left
        GPIO18 ----------- ECHO Left

        GPIO19 ----------- TRIG Center
        GPIO21 ----------- ECHO Center

        GPIO22 ----------- TRIG Right
        GPIO23 ----------- ECHO Right

        GPIO26 ----------- IN1
        GPIO27 ----------- IN2
        GPIO14 ----------- IN3
        GPIO12 ----------- IN4
        GPIO25 ----------- ENA
        GPIO33 ----------- ENB
                     │
                     ▼
               +------------+
               |   L298N    |
               +------------+
                 │        │
            Left Motors  Right Motors
             (2 Motors)   (2 Motors)

```

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