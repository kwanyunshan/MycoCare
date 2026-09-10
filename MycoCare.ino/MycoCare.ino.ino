#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>


// ========================================
// WiFi Settings
// ========================================

const char* ssid = "kwan";
const char* password = "ys030305";


// ========================================
// PHP Server
// ========================================

// Send sensor data
const char* serverName =
"http://172.22.176.36/mycocare/save_data.php";

// Get pump control status
const char* controlServer =
"http://172.22.176.36/mycocare/get_control.php";


// ========================================
// DHT22 Settings
// ========================================

#define DHTPIN 4
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);


// ========================================
// MQ135 Settings
// ========================================

#define MQ135_PIN 32


// ========================================
// Relay Settings
// ========================================

// Relay IN1 → ESP32 GPIO 26
#define RELAY_PIN 26


// ========================================
// Sensor Variables
// ========================================

float temperature = 0;
float humidity = 0;
int airValue = 0;


// ========================================
// Timing
// ========================================

// Sensor data upload interval
unsigned long previousSensorMillis = 0;
const long sensorInterval = 5000;


// Pump control checking interval
unsigned long previousControlMillis = 0;
const long controlInterval = 2000;


// ========================================
// Setup
// ========================================

void setup() {

  Serial.begin(115200);

  delay(1000);


  // ----------------------------------------
  // Start DHT22
  // ----------------------------------------

  dht.begin();

  Serial.println();
  Serial.println("================================");
  Serial.println("MycoCare IoT System Starting...");
  Serial.println("================================");

  Serial.println("DHT22 Started");


  // ----------------------------------------
  // Start Relay
  // ----------------------------------------

  pinMode(RELAY_PIN, OUTPUT);

  // Active LOW relay:
  // HIGH = OFF
  // LOW  = ON

  digitalWrite(RELAY_PIN, HIGH);

  Serial.println("Relay Started");
  Serial.println("Pump Default Status: OFF");


  // ----------------------------------------
  // Connect WiFi
  // ----------------------------------------

  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);

    Serial.print(".");
  }

  Serial.println();

  Serial.println("WiFi Connected!");

  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP());

  Serial.println();

}


// ========================================
// Check Pump Control
// ========================================

void checkPumpControl() {

  if (WiFi.status() != WL_CONNECTED) {

    Serial.println("WiFi disconnected - cannot check pump");

    return;
  }


  HTTPClient http;

  Serial.println("Checking Pump Control...");


  // Connect to get_control.php

  http.begin(controlServer);


  // Send GET request

  int httpResponseCode = http.GET();


  Serial.print("Control HTTP Code: ");
  Serial.println(httpResponseCode);


  // ----------------------------------------
  // Server Response
  // ----------------------------------------

  if (httpResponseCode > 0) {

    String response = http.getString();

    Serial.print("Control Response: ");
    Serial.println(response);


    // ----------------------------------------
    // Pump ON
    // ----------------------------------------

    if (response.indexOf("\"pump_status\":\"ON\"") >= 0) {

      digitalWrite(RELAY_PIN, LOW);

      Serial.println("💧 Pump Status: ON");
      Serial.println("Relay GPIO 26: LOW");

    }


    // ----------------------------------------
    // Pump OFF
    // ----------------------------------------

    else if (response.indexOf("\"pump_status\":\"OFF\"") >= 0) {

      digitalWrite(RELAY_PIN, HIGH);

      Serial.println("Pump Status: OFF");
      Serial.println("Relay GPIO 26: HIGH");

    }


    else {

      Serial.println("Pump status not found in response");

    }

  }


  else {

    Serial.println("Error connecting to control server");

  }


  http.end();

}


// ========================================
// Send Sensor Data
// ========================================

void sendSensorData() {

  if (WiFi.status() != WL_CONNECTED) {

    Serial.println("WiFi disconnected - cannot send data");

    return;
  }


  HTTPClient http;


  // ----------------------------------------
  // Create URL
  // ----------------------------------------

  String serverPath = String(serverName) +
                      "?temperature=" + String(temperature, 2) +
                      "&humidity=" + String(humidity, 2) +
                      "&air_quality=" + String(airValue);


  Serial.println();
  Serial.println("Sending sensor data...");

  Serial.println(serverPath);


  // ----------------------------------------
  // Start HTTP Request
  // ----------------------------------------

  http.begin(serverPath.c_str());


  // ----------------------------------------
  // Send GET Request
  // ----------------------------------------

  int httpResponseCode = http.GET();


  Serial.print("Sensor HTTP Response Code: ");
  Serial.println(httpResponseCode);


  // ----------------------------------------
  // Server Response
  // ----------------------------------------

  if (httpResponseCode > 0) {

    String response = http.getString();

    Serial.print("Server Response: ");
    Serial.println(response);

  }

  else {

    Serial.println("Error sending sensor data!");

  }


  // ----------------------------------------
  // Close Connection
  // ----------------------------------------

  http.end();

}


// ========================================
// Main Loop
// ========================================

void loop() {


  // ======================================
  // Read DHT22
  // ======================================

  humidity = dht.readHumidity();

  temperature = dht.readTemperature();


  // ======================================
  // Read MQ135
  // ======================================

  airValue = analogRead(MQ135_PIN);


  // ======================================
  // Check DHT22 Error
  // ======================================

  if (isnan(humidity) || isnan(temperature)) {

    Serial.println("DHT22 Reading Failed!");

    delay(2000);

    return;
  }


  // ======================================
  // Display Sensor Data
  // ======================================

  Serial.println();
  Serial.println("------------------------");

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  Serial.print("Air Quality: ");
  Serial.println(airValue);

  Serial.println("------------------------");


  // ======================================
  // Current Time
  // ======================================

  unsigned long currentMillis = millis();


  // ======================================
  // Send Sensor Data Every 5 Seconds
  // ======================================

  if (currentMillis - previousSensorMillis >= sensorInterval) {

    previousSensorMillis = currentMillis;

    sendSensorData();

  }


  // ======================================
  // Check Pump Control Every 2 Seconds
  // ======================================

  if (currentMillis - previousControlMillis >= controlInterval) {

    previousControlMillis = currentMillis;

    checkPumpControl();

  }


  // Small delay

  delay(1000);

}