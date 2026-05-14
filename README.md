# 🚨 Intelligent Fire & Heat Detection System

An automated environmental safety system built with an Arduino Uno and a high-precision DHT22 thermal sensor. This project continuously evaluates ambient temperatures, outputs live data to an I2C LCD, and deploys high-priority sound and visual alerts when an active fire threat is detected.

🔗 **Live Simulation:** [View Project on Wokwi](https://wokwi.com/projects/417728180462924801)]

---

## 📌 Core Features

* 🌡️ **High-Precision Thermal Monitoring:** Collects ambient temperature metrics using a DHT22 sensor.
* 📺 **Expanded Status Interface:** Renders real-time temperatures and fire warning updates on an I2C 20x4 LCD screen.
* 🔇 **Smart Alarm Muting:** Integrates a physical push-button to toggle and silence the emergency siren manually.
* 🚨 **Dual Visual/Audio Indicators:** Drives an emergency speaker and a status-synchronized flashing LED indicator.

---

## 🔌 Hardware Configuration & Pin Map

Wire your physical or simulated components to the Arduino Uno exactly as defined in the source firmware:

### Pinout Reference Table


| Component | Arduino Pin | Configuration Type | Core Function |
| :--- | :--- | :--- | :--- |
| **DHT22 Sensor** | `D2` | Digital Input | Transmits temperature and humidity packets |
| **Speaker / Buzzer** | `D12` | Digital Output | Emits a high-frequency (1000Hz) alert tone |
| **Alarm LED** | `D6` | Digital Output | Flashes synchronously during hazard events |
| **Push Button** | `D13` | Input (Internal Pull-up) | Mutes/Unmutes active alarms on press |
| **I2C LCD (SDA)** | `A4` | Dedicated I2C Data | Interfaces serial display information |
| **I2C LCD (SCL)** | `A5` | Dedicated I2C Clock | Syncs clock pulses for data streams |

---

## ⚙️ Operational Logic & Thresholds

* **Normal Monitoring Mode:** The system updates serial and LCD telemetry loops every 1000ms.
* **Fire Alarm Trigger:** If the temperature rises into the **70°C to 80°C** safety window, the display flashes `W:FIRE DETECTED!`.
* **Alarm Response:** The 1000Hz speaker tone sounds and the LED strobes unless overridden by the mute button.

---
## Diagram

  <img width="707" height="556" alt="image" src="https://github.com/user-attachments/assets/89364f21-43b0-45e1-be1a-36d0c339bec1" />

```
