# 10-DOF Omnidirectional Mecanum Drive System

![Project Status](https://img.shields.io/badge/Status-Complete-brightgreen)
![Hardware](https://img.shields.io/badge/Hardware-Raspberry_Pi_Zero_2W_%7C_Arduino_Uno-blue)
![Software](https://img.shields.io/badge/Software-Python_Flask_%7C_C++-yellow)
![License](https://img.shields.io/badge/License-MIT-lightgrey)

## 📌 Overview
This project details the design, firmware development, and web-integration of a 4-wheel omnidirectional mobile robot. Utilizing Mecanum wheels and a custom asynchronous web interface, the platform achieves 10 Degrees of Freedom (10-DOF), allowing for highly precise spatial navigation, including true lateral (crabbing) movement, diagonal vectoring, and zero-radius pivots.

Originally designed as a hardware prototype, the architecture was upgraded to feature a headless Raspberry Pi Zero 2 W acting as a local web server, bridging wireless HTTP commands to a physical serial-driven kinematics engine.

---

## 🎥 Demonstrations

![Lateral Translation](media/crab_walk_demo.gif)
> **Lateral Translation:** The system successfully mitigates forward/backward momentum by opposing the lateral force vectors of the 45-degree rollers.

![Zero-Radius Pivot](media/zero_radius_spin.gif)
> **Zero-Radius Pivot:** Mimicking a skid-steer maneuver to achieve 0cm drift during purely rotational execution.

---

## 🏗️ Hardware Architecture

The physical chassis is stripped down to ensure maximum power delivery and signal integrity:
* **The Brain:** Raspberry Pi Zero 2 W (Running headless Raspberry Pi OS Lite, 32-bit).
* **The Microcontroller:** Arduino Uno R3.
* **The Bridge:** Micro-USB to USB Type-A OTG adapter, bypassing logic-level shifting for a direct, high-speed serial connection.
* **Motor Control:** L293D Motor Shield driving 4x independent DC TT Motors.
* **Kinematics:** 4x 60mm Mecanum Wheels configured in an 'X' roller pattern.
* **Power Delivery:** 11.1V Li-ion battery pack bypassing the logic boards to directly feed the L293D high-current terminals.

---

## 💻 Software Stack & Communication Bridge

The system operates across three distinct software layers, prioritizing low-latency execution from the user's touchscreen down to the physical wheel rotations.

### 1. The Frontend (UI/UX)
A lightweight, mobile-responsive HTML/CSS interface served locally. It utilizes JavaScript `fetch()` APIs bound to `touchstart` and `touchend` event listeners. This ensures asynchronous command transmission without page reloading, and guarantees an immediate `STOP` command is fired the millisecond the user lifts their finger.

### 2. The Backend (Python Flask Server)
Hosted on the Raspberry Pi Zero 2 W, a lightweight Flask server routes the HTTP requests. It uses the `pyserial` library to convert web commands into raw integer packets, pushing them over the physical OTG connection to the microcontroller at a 115200 baud rate.

### 3. The Firmware (C++ Kinematics Engine)
The Arduino Uno acts purely as the hardware execution layer. It continuously polls the hardware serial port, parses the incoming integers, and translates them into corresponding Pulse Width Modulation (PWM) and directional logic using the `AFMotor.h` library. 

---

## 🚀 How to Run Locally

### Prerequisites
* Raspberry Pi Zero 2 W accessible via SSH.
* Python 3, `flask`, and `pyserial` installed.
* Arduino IDE for flashing the `.ino` firmware.

### Execution
1. Flash the `mecanum_firmware.ino` to the Arduino Uno and connect it to the Pi via USB-OTG.
2. Clone this repository onto the Raspberry Pi:
   ```bash
   git clone [https://github.com/hihuzaifa/10-dof-mecanum-drive.git](https://github.com/hihuzaifa/10-dof-mecanum-drive.git)
   cd 10-dof-mecanum-drive