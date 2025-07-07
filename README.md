# 🚨 Fall Detection and Prevention System using ESP8266 and ADXL345

This project is a **low-cost, portable, and real-time fall detection system** developed using the **ESP8266 NodeMCU** microcontroller and **ADXL345 3-axis accelerometer**. It is designed to detect sudden falls and postural instability events and send **instant alerts** to caregivers via a **mobile application** using the **Blynk IoT platform**.

## 🎯 Objective

To create an effective, wearable fall detection system that:
- Detects free falls and unstable postures
- Alerts caregivers via push notifications
- Supports remote health monitoring for elderly or industrial workers
- Operates on low power with long battery life

---

## 🔧 Hardware Components

| Component        | Purpose                                             |
|------------------|-----------------------------------------------------|
| ESP8266 NodeMCU  | Core controller for processing & Wi-Fi connectivity |
| ADXL345          | 3-axis accelerometer for fall & tilt detection      |
| TP4056           | Battery charging and protection module              |
| Li-Ion Battery   | 3.7V, 3000mAh rechargeable power source             |
| 5V Boost Converter | Boosts voltage from 3.7V to 5V                     |
| AMS1117          | 5V to 3.3V voltage regulator                        |
| Buzzer           | Audible alert in case of fall                       |
| OLED Display (optional) | Displays real-time data and system status     |
| LEDs (optional)  | Visual indicators for status                        |

---

## 💻 Software Features

- **Sensor Communication**: I²C interface between ESP8266 and ADXL345
- **Direct Register Access**: Configuration of motion thresholds in ADXL345
- **Detection Algorithm**:
  - Free-fall detection using interrupts
  - Tilt angle calculation (threshold > 45° triggers event)
  - Threshold-based movement classification
- **Mobile App Integration**: Blynk platform used for real-time alerts
- **Power Optimization**: Interrupt-driven wake-up and deep sleep options

---

## 📱 Mobile App Integration (Blynk)

- Real-time alerts sent to caregiver's smartphone
- **Virtual Pins**:
  - `V0`, `V1`, `V2`: X, Y, Z acceleration data
  - `V3`: Device status (active/idle)
- **Push Notifications**:
  - `"Free Fall Detected!"` (on fall)
  - `"Loss of Balance Detected!"` (on tilt > 45°)

### 📲 Example Notification:
> 🔔 *Free Fall Detected! Please check on the user immediately.*

---

## 📈 Performance Summary

| Metric                    | Result                   |
|---------------------------|--------------------------|
| Fall Detection Accuracy   | ~93%                     |
| Response Time             | 1–1.5 seconds            |
| Battery Life              | ~23 hours per charge     |
| Charging Time             | ~3–4 hours               |

---

## 🧠 Skills Demonstrated

- 🛠️ Embedded Systems (ESP8266, ADXL345)
- 🧮 Real-time Sensor Data Processing
- 📲 IoT Integration using Blynk
- 🔋 Power Optimization Techniques
- 🔌 I²C Communication & Interrupt Handling
- 🖥️ Arduino IDE Programming in C++
- 📐 Hardware Prototyping and Design
- 💡 Wearable Device Development

---

## 🔬 Future Improvements

- Integrate **gyroscope** for improved orientation analysis
- Apply **machine learning** for adaptive fall detection
- Enable **user-specific profiles** with dynamic thresholds
- Add **voice alerts** or **SMS functionality**

---


## 🤝 Contributions

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

---

## 📧 Contact

**Sai Sundar P**  
Department of Electrical and Electronics Engineering  
Chennai Institute of Technology  


---

> ⚠️ *This project is for educational and prototyping purposes. It is not certified for medical use.*

