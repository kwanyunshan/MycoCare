# 🍄 MycoCare

## Smart Mushroom Cultivation Monitoring and Environmental Control System

## 📌 Project Overview

MycoCare is an IoT-based mushroom cultivation monitoring system developed to monitor environmental conditions in a mushroom cultivation area.

The system uses an ESP32 to collect temperature, humidity, and air quality data. The collected data is sent through WiFi to a PHP server and stored in a MySQL database.

The sensor readings can be viewed through a web-based dashboard.

---

## 🎯 Project Objectives

* Monitor temperature in the mushroom cultivation area.
* Monitor humidity in the mushroom cultivation area.
* Monitor air quality in the cultivation environment.
* Send sensor data from ESP32 to the server using WiFi.
* Store sensor data in a MySQL database.
* Display sensor readings through a web dashboard.
* Reduce the need for manual environmental monitoring.

---

## ⚙️ Main Functions

### 🌡️ Temperature Monitoring

The DHT22 sensor is used to monitor the temperature of the mushroom cultivation area.

* The ESP32 reads the temperature from the DHT22 sensor.
* The temperature reading is displayed on the Serial Monitor.
* The temperature data is sent to the PHP server.
* The data can be stored in the MySQL database.
* The temperature reading is displayed on the web dashboard.

**ESP32 Pin:** GPIO 4

---

### 💧 Humidity Monitoring

The DHT22 sensor is also used to monitor humidity.

* The ESP32 reads the humidity level from the DHT22 sensor.
* The humidity reading is displayed on the Serial Monitor.
* The humidity data is sent to the PHP server.
* The data can be stored in the MySQL database.
* The humidity reading is displayed on the web dashboard.

**ESP32 Pin:** GPIO 4

---

### 🌫️ Air Quality Monitoring

The MQ135 sensor is used to monitor air quality.

* The ESP32 reads the analog value from the MQ135 sensor.
* The air quality reading is displayed on the Serial Monitor.
* The air quality data is sent to the PHP server.
* The data can be stored in the MySQL database.
* The air quality reading is displayed on the web dashboard.

**ESP32 Pin:** GPIO 32

---

### 📡 WiFi Connection

The ESP32 connects to a WiFi network to communicate with the PHP server.

* Connects the ESP32 to the configured WiFi network.
* Checks the WiFi connection status.
* Sends sensor data to the server through HTTP.
* Displays the ESP32 IP address through the Serial Monitor.

---

### 🌐 Data Transmission

The ESP32 sends the collected sensor readings to the PHP server using an HTTP GET request.

The data sent includes:

* Temperature
* Humidity
* Air Quality

The ESP32 sends the sensor data every 5 seconds when the WiFi connection is available.

---

### 🖥️ Web Dashboard

The web dashboard provides an interface for users to monitor the collected sensor data.

The dashboard displays:

* Temperature
* Humidity
* Air Quality

The dashboard is developed using HTML, CSS, and JavaScript.

---

### 🗄️ Database

MycoCare uses MySQL to store sensor readings received from the ESP32.

The PHP server receives the sensor data and stores it in the database.

The stored data includes:

* Temperature
* Humidity
* Air Quality

---

## 📂 File Functions

### `MycoCare.ino`

Contains the main ESP32 program.

Functions include:

* Connects the ESP32 to WiFi.
* Reads temperature from DHT22.
* Reads humidity from DHT22.
* Reads air quality from MQ135.
* Sends sensor data to the PHP server.
* Displays sensor readings through the Serial Monitor.

---

### `index.html`

Contains the main structure of the MycoCare web dashboard.

Functions include:

* Displays the dashboard interface.
* Displays sensor information.
* Organises the monitoring sections.

---

### `style.css`

Controls the appearance of the web dashboard.

Functions include:

* Dashboard layout.
* Sensor card design.
* Text formatting.
* Button and interface styling.

---

### `script.js`

Contains the JavaScript functions used by the web dashboard.

Functions include:

* Requests sensor data from the PHP server.
* Processes the received data.
* Updates sensor information on the dashboard.
* Handles dashboard interactions.

---

### `db_connect.php`

Connects the PHP system to the MySQL database.

---

### `get_data.php`

Retrieves sensor data from the MySQL database and provides the data to the web dashboard.

---

### `save_data.php`

Receives sensor data from the ESP32 and saves the data into the MySQL database.

---

## 🛠️ Technologies Used

### Hardware

* ESP32
* DHT22 Sensor
* MQ135 Sensor

### Software

* Arduino IDE
* Visual Studio Code
* HTML
* CSS
* PHP
* MySQL
* GitHub

### Communication

* WiFi
* HTTP

