# Wearable ESP32 Air Quality & Climate Tracker 🌍📡

An IoT-based, wearable environmental monitoring system designed to track real-time Air Quality Index (AQI), temperature, and humidity. Developed as a Tinkering Lab project, this device helps users visualize immediate pollution levels and make data-driven decisions to avoid high-exposure zones (like construction sites or traffic hotspots) during daily commutes.

## ✨ Key Features
* **Real-Time Environmental Sensing:** Utilizes an MQ135 (Gas/Pollution) and a DHT11/22 (Temperature & Humidity) sensor to capture data every 10 seconds.
* **On-Board Display:** Live data visualization on a 0.96" OLED screen.
* **Autonomous Alert System:** * **Good (AQI < 50):** Green LED
  * **Moderate (AQI 51-150):** Yellow LED
  * **Hazardous (AQI > 150):** Red LED + Piezo Buzzer Alarm
* **Cloud Integration:** Live synchronization with the **Blynk IoT Cloud** via WiFi for remote dashboard monitoring and historical exposure tracking.
* **Wearable Design:** Designed to be powered by a 3.7V 18650 Li-ion battery and housed in a lightweight (<100g) custom 3D-printed enclosure.

## 🛠️ Hardware Components
* **Microcontroller:** ESP32 Development Board (NodeMCU)
* **Gas Sensor:** MQ135 (Detects CO2, smoke, ammonia, and other pollutants)
* **Climate Sensor:** DHT11 or DHT22
* **Display:** 0.96" OLED Display (SSD1306, I2C)
* **Alerts:** Common Cathode RGB LED & Active Piezo Buzzer
* **Power:** 3.7V 18650 Li-ion Battery (2000mAh) + TP4056 Charging Module
* **Misc:** Breadboard, Jumper Wires, 220Ω Resistors

## 🔌 Circuit & Pin Mapping

| Component | ESP32 Pin | Notes |
| :--- | :--- | :--- |
| **DHT22 Data** | GPIO 15 | Requires 3.3V power |
| **MQ135 Analog** | GPIO 34 | Analog input for pollution levels |
| **OLED SDA** | GPIO 21 | I2C Data |
| **OLED SCL** | GPIO 22 | I2C Clock |
| **Buzzer (+)** | GPIO 5 | Ground the other leg |
| **RGB - Red** | GPIO 4 | Use 220Ω resistor |
| **RGB - Green** | GPIO 16 | Use 220Ω resistor |
| **RGB - Blue** | GPIO 17 | Use 220Ω resistor |

*(Note: In the Wokwi simulation, a Slide Potentiometer is used on GPIO 34 to simulate the analog readings of the MQ135 sensor).*

## 💻 Software & Libraries
To run this project in the Arduino IDE or Wokwi, install the following libraries via the Library Manager:
1. `Adafruit SSD1306`
2. `Adafruit GFX Library`
3. `DHT sensor library` (by Adafruit)
4. `Blynk`

## 🚀 Setup Instructions

### 1. Blynk Cloud Setup
1. Create a free account at [Blynk.cloud](https://blynk.cloud/).
2. Create a New Template (Hardware: ESP32, Connection: WiFi).
3. Set up three **Virtual Datastreams**:
   * `V0` (Integer, 0-500) -> For AQI
   * `V1` (Double, -10 to 50) -> For Temperature
   * `V2` (Double, 0 to 100) -> For Humidity
4. Create a new Device from your template and copy the **Template ID, Device Name, and Auth Token**.

### 2. Code Configuration
1. Clone this repository or open the `sketch.ino` file.
2. Paste your Blynk credentials at the very top of the code:
   ```cpp
   #define BLYNK_TEMPLATE_ID "Your_Template_ID"
   #define BLYNK_TEMPLATE_NAME "Your_Template_Name"
   #define BLYNK_AUTH_TOKEN "Your_Auth_Token"
