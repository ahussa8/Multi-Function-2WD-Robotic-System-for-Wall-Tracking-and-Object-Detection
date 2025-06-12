# ME331 Final Project – Autonomous and Remote-Controlled Robot

## 🛠️ Overview
This project involved designing, building, and programming a multifunctional mobile robot capable of performing three challenge-based tasks using both autonomous and remote-controlled operation.

## 🧩 Hardware Components
| Part Name         | Source             | Notes                         |
|-------------------|--------------------|-------------------------------|
| TT DC Motors (x2) | Provided            | Drive mechanism               |
| Ultrasonic Sensor | Provided            | Obstacle sensing              |
| Servo Motor       | Provided            | Sensor panning + wall following |
| Arduino Uno       | Provided            | Microcontroller brain         |
| Motor Driver Board| Provided            | ULN2003                       |
| Chassis Base      | Custom Fabricated   | Acrylic w/ hot glue + screws  |
| Wheels (x2)       | Provided            | Attached to TT motors         |
| Optional IR Module| Optional            | Used for remote control input |

## ⚙️ Challenge Tasks

### 🌀 Challenge 1: U-Turn (Autonomous)
- Robot advanced 2 meters toward a wall
- Turned around autonomously at 30 cm from the wall
- Returned to start zone within 50 cm margin
- Used ultrasonic sensor for distance detection and timed braking logic

### 🚧 Challenge 2: Obstacle Course
**(Two Modes: Autonomous or Remote)**
- Used servo-mounted ultrasonic sensor to scan and steer
- Avoided static obstacles and navigated toward a goal zone
- Remote version used directional input for navigation

### 🧱 Challenge 3: Wall Following with PD (Autonomous)
- Used proportional–derivative control to maintain 30 cm distance from a wall
- Servo sweep provided angular distance feedback for directional correction

## 💻 Software Structure
- Separate `.ino` sketches for each challenge
- Modular functions for movement control, sensor reading, and condition logic
- Servo scanning loop and distance logic integrated into PD controller and object tracker

## 🧠 Key Features
- Hybrid autonomous/manual design
- Real-time distance classification via servo sweeping
- Collision-safe wall following with PD tuning

## 🧪 Testing & Evaluation
- Tested on multiple surfaces (tile, cardboard)
- Calibrated motor speeds and distances for consistent performance
- Debugged angle offsets and adjusted motor delay timing

## 📚 References
- [DroneBot Workshop – Stepper Motors](https://dronebotworkshop.com/stepper-motors-with-arduino/)
- Arduino PD control tutorials
- Elegoo and Adafruit documentation for sensors and motor control
