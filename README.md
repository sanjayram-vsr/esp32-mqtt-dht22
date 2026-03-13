**ESP32 MQTT Environment Monitor**



An IoT project using ESP32, MQTT protocol, and DHT22 sensor to monitor environmental conditions and remotely control an LED.



The ESP32 connects to WiFi, communicates with an MQTT broker, and publishes temperature and humidity data when requested. It also listens for commands to control an LED remotely.



**Features**



* Remote LED control via MQTT
* Temperature and humidity monitoring
* MQTT-based IoT communication
* Real-time sensor data publishing
* Works with public MQTT broker



**Hardware Components**



* ESP32
* DHT22 Sensor
* LED
* Resistor (220Ω)
* Jumper Wires
* Breadboard



**Pin Configuration**



* LED - GPIO 4
* DHT22 Data - GPIO 5



**MQTT Broker**

Broker used in this project:



* mqtt-dashboard.com
* Port: 1883



**MQTT Topics**



* home/led: Control LED (ON / OFF)
* home/command: Request sensor data
* home/environment: Publish sensor readings



**Libraries Used**



Install these Arduino libraries before uploading code:



* WiFi.h
* PubSubClient
* DHT sensor library



**How to Run the Project**



1\. Install Arduino IDE

2\. Install ESP32 board support

3\. Install required libraries

4\. Connect ESP32 to your computer

5\. Upload the code

6\. Open Serial Monitor

7\. Use MQTT dashboard to send commands



**Project Workflow**



1\. ESP32 connects to WiFi

2\. ESP32 connects to MQTT broker

3\. ESP32 subscribes to topics

4\. User sends commands through MQTT

5\. ESP32 controls LED or publishes sensor data



**Wokwi Link**: https://wokwi.com/projects/458374621021915137

