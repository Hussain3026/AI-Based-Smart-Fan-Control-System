# AI-Based-Smart-Fan-Control-System
An intelligent embedded system that controls fan speed based on temperature using Machine Learning prediction, PID control, and real-time fault detection.

🚀 AI-Based Smart Fan Control System
An intelligent embedded system that dynamically controls fan speed based on temperature using Machine Learning (ML), PID control, and real-time fault detection.

📌 Overview
This project implements a smart fan control system using Arduino that not only reacts to temperature changes but predicts future trends and adjusts fan speed accordingly. It combines ML-based prediction with PID control to achieve smooth, stable, and efficient operation.

🧠 Key Features
🌡️ Real-time temperature monitoring using DHT11 sensor

🤖 Machine Learning-based temperature prediction (Linear Regression)

⚙️ PID control for smooth and stable fan speed adjustment

🔄 PWM-based fan control using Arduino

⚠️ Fault detection (sensor failure & abnormal conditions)

📟 LCD display for real-time system monitoring

🔔 Buzzer alert for system faults

🛠️ Technologies Used
Arduino UNO

Embedded C (Arduino IDE)

DHT11 Temperature Sensor

PID Control Algorithm

Machine Learning (Linear Regression Model)

PWM Signal Processing

📊 System Architecture
DHT11 Sensor → Arduino UNO → ML Prediction → PID Control
                      ↓
               Decision Logic
                      ↓
               PWM Signal Output
                      ↓
                TIP122 Transistor
                      ↓
                    Fan
                      
+ Fault Detection → Buzzer Alert
+ LCD Display → Monitoring

🔄 Working Principle
1.The DHT11 sensor reads real-time temperature
2.Arduino processes the data
3.ML model predicts future temperature
4.PID controller calculates correction
5.ML and PID outputs are combined
6.PWM signal controls fan speed
7.Fault detection monitors system health
8.LCD displays temperature and fan speed

🧠 Machine Learning Model
The system uses a lightweight regression model:

Future Temperature = (1.01 × Temp) + 0.9
Fan Speed = (10.5 × Temp) − 200
👉 The model is trained offline using dataset and embedded into Arduino as an equation.

🔧 Hardware Setup
1.Connect DHT11 sensor to Arduino
2.Connect fan using TIP122 transistor
3.Add LCD display and buzzer
4.Ensure common ground

💻 Software Setup
1.Open Arduino IDE
2.Load main.ino
3.Select board: Arduino UNO
4.Connect Arduino via USB
5.Click Upload

📈 Sample Output
Temp: 33°C  
Future: 34.5°C  
Fan Speed: 85–138 

⚠️ Fault Detection
❌ Sensor failure → LCD shows “Sensor Error”
❌ Fan failure → Buzzer alert + LCD warning

🎯 Applications
1.Smart home automation
2.Temperature control systems
3.Energy-efficient cooling
4.Embedded AI-based control systems

🏆 Key Highlights
1.Hybrid ML + PID control system
2.Real-time predictive control
3.Smooth and stable performance
4.Fault-tolerant design
5.Embedded AI implementation

🔮 Future Scope
1.IoT-based remote monitoring
2.Mobile app integration
3.Cloud data logging
4.Advanced ML models

