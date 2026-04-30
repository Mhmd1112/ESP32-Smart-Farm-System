# Integrated Autonomous Irrigation & Fire Mitigation System

[![Platform: ESP32](https://img.shields.io/badge/Platform-ESP32-red.svg)](https://www.espressif.com/en/products/socs/esp32)
[![Framework: Arduino](https://img.shields.io/badge/Framework-Arduino-00979D.svg)](https://www.arduino.cc/)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

## 1. Executive Summary
This project implements a dual-core-capable firmware solution for an ESP32-based Smart Farming system. It utilizes asynchronous, non-blocking execution logic to manage two distinct safety and utility subsystems: **Precision Hydraulic Irrigation** and **IR-based Fire Hazard Mitigation**.

By eliminating `delay()` calls, the system ensures real-time responsiveness ($f \approx 2\text{Hz}$ alarm polling) even during high-latency mechanical operations like servo-driven water distribution.

---

## 2. System Architecture

### 2.1 Irrigation Subsystem
The irrigation logic is triggered by a digital soil moisture threshold. 
* **Spatial Distribution:** A PWM-controlled servo performs a continuous sweep from $0^{\circ}$ to $180^{\circ}$.
* **Hydraulic Control:** A relay module toggles a water pump/turbine to ensure active delivery during the sweep cycle.

### 2.2 Fire Mitigation Subsystem
A high-priority monitoring task that polls an IR flame sensor. 
* **State Logic:** If a fire event is detected, the system enters an alert state, toggling the `buzzerLED` pin at a $500\text{ms}$ interval.
* **Safety Protocol:** The alarm functions independently of the irrigation cycle to ensure zero-latency hazard notification.

---

## 3. Hardware Specifications

### Pin Mapping (GPIO Configuration)
| Component | GPIO | Mode | Signal Type |
| :--- | :---: | :--- | :--- |
| **SG90 Servo** | 14 | Output | PWM (Angular Control) |
| **Soil Moisture Sensor** | 13 | Input | Digital (Logic High = Dry) |
| **Relay (Pump/Turbine)** | 26 | Output | Digital (Active Low) |
| **Flame Sensor** | 25 | Input | Digital (IR Threshold) |
| **Alarm (Buzzer/LED)** | 27 | Output | Digital (Pulsed) |

### Electrical Characteristics
* **MCU Voltage:** $3.3\text{V}$ DC.
* **External Power:** Recommended $5\text{V}$ rail for Servo and Relay to prevent MCU brownouts during high current draw.

---

## 4. Technical Implementation
The firmware leverages the `millis()` function to track elapsed time, allowing for pseudo-multitasking.

**Servo Sweep Update Frequency:**
$$t_{update} = 15\text{ms}$$

**Alarm Toggle Frequency:**
$$f = \frac{1}{2 \times 0.5\text{s}} = 1\text{Hz}$$

---

## 5. Installation & Setup
1. **Clone the Repository:**
   ```bash
   git clone [https://github.com/Mhmd1112/ESP32-Smart-Farm-System.git](https://github.com/Mhmd1112/ESP32-Smart-Farm-System.git)
