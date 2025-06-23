# 🩺 BreatheSafe: Predictive Healthcare with Edge AI

> ⚠️ This project uses **sample test data only**, not real patient data. It is intended for educational and prototyping purposes only.

---

## 📌 Overview

**BreatheSafe** is an Edge AI-powered, real-time health monitoring system built with **ESP32** and **MAX30102**. It measures heart rate (BPM) and oxygen saturation (SpO₂), then classifies health risk level using a lightweight **SVM** (Support Vector Machine) model running fully on-device — no cloud needed.

---

## 🎯 Features

- 💡 Real-time heart rate (BPM) & SpO₂ readings  
- 🧠 On-device ML prediction with SVM  
- 📶 Bluetooth output via ESP32 ("ESP32-BPM")  
- 🔋 Portable and fully offline  
- ⚠️ Risk classification: `No Risk`, `Low Risk`, `High Risk`  
- 🔎 Easy to retrain with your own data  

---

## ⚠️ Note on Dataset

This project uses a **synthetic dataset** for demonstration and educational purposes.  
**No real patient data is used.**

Example:

| BPM | SpO₂ (%) | Label       |
|-----|----------|-------------|
| 75  | 98       | no_risk     |
| 55  | 93       | low_risk    |
| 130 | 88       | high_risk   |

---

## 🧠 Machine Learning Model

- **Algorithm**: SVM (Support Vector Machine)  
- **Features**: BPM, SpO₂  
- **Labels**: `no_risk`, `low_risk`, `high_risk`  
- **Training Tool**: Python (`scikit-learn`)  
- **Deployed using**: `micromlgen` (SVM → `model.h`)  

---

## 🔧 Hardware Requirements

| Component      | Role                         |
|----------------|------------------------------|
| ESP32-WROOM    | Microcontroller + Bluetooth  |
| MAX30102       | Heart Rate & SpO₂ Sensor     |
| USB Cable      | For flashing and power       |
| (Optional)     | OLED/Serial Monitor Display  |

---

## 🚀 Getting Started

### 1. Install Arduino IDE and ESP32 Board

- Install the **ESP32 board** via Board Manager  
- Required libraries:
  - `MAX30105 by SparkFun`  
  - `BluetoothSerial` (default in ESP32)

### 2. Connect MAX30102 to ESP32

```
MAX30102     ESP32
----------   -----
VIN          3.3V  
GND          GND  
SCL          GPIO 22  
SDA          GPIO 21  
```

### 3. Upload Code

- Open `BreatheSafe.ino` in Arduino IDE  
- Upload to your ESP32 board  
- Pair Bluetooth with **ESP32-BPM**  
- Open serial monitor or Bluetooth terminal app  

---

## 📊 Sample Output

```
🧠 Measuring...
📤 BPM: 91.2 | SpO₂: 96.3 | Risk: Low Risk  
📤 BPM: 130.5 | SpO₂: 88.9 | Risk: High Risk  
📤 BPM: 75.6 | SpO₂: 98.7 | Risk: No Risk  
```

---

## 💡 Applications

- 🏥 Personal health tracking  
- 🧓 Elderly monitoring systems  
- 🚑 Remote health risk alert  
- 📶 Offline diagnostics  
- 🎓 Embedded ML learning projects  

---

## 🙌 Credits

- Developed by: **Anora Sharon Tessie S.**  
- Tools used: `scikit-learn`, `micromlgen`, `ESP32`, `MAX30102`, `Arduino`

---
