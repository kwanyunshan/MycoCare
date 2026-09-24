#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


// ========================================
// WiFi Settings
// ========================================

const char* ssid = "kwan";
const char* password = "05030302";


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
#define WATER_LEVEL_PIN 34


// ========================================
// Relay Settings
// ========================================

#define RELAY_PIN 26


// ========================================
// LCD Settings
// ========================================

// LCD I2C address: usually 0x27
// 16 columns, 2 rows

LiquidCrystal_I2C lcd(0x27, 16, 2);


// ========================================
// Sensor Variables
// ========================================

float temperature = 0;
float humidity = 0;
int airValue = 0;
int waterLevel = 0;

// ========================================
// Timing
// ========================================

// Update every 8 seconds
unsigned long previousMillis = 0;
const long updateInterval = 8000;


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

  // Active LOW relay
  // HIGH = OFF
  // LOW  = ON

  digitalWrite(RELAY_PIN, LOW);

  Serial.println("Relay Started");
  Serial.println("Pump Default Status: OFF");


  // ----------------------------------------
  // Start LCD
  // ----------------------------------------

  Wire.begin(21, 22);

  lcd.init();
  lcd.backlight();

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("MycoCare");

  lcd.setCursor(0, 1);
  lcd.print("Starting...");

  delay(2000);

  lcd.clear();


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
// Display LCD
// ========================================

void displayLCD() {

  lcd.clear();


  // First line
  lcd.setCursor(0, 0);

  lcd.print("T:");

  lcd.print(temperature, 1);

  lcd.print((char)223);

  lcd.print("C");


  // Second part of first line
  lcd.setCursor(9, 0);

  lcd.print("H:");

  lcd.print(humidity, 1);

  lcd.print("%");


  // Second line
  lcd.setCursor(0, 1);

  lcd.print("Air:");

  lcd.print(airValue);

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


  http.begin(controlServer);


  int httpResponseCode = http.GET();


  Serial.print("Control HTTP Code: ");
  Serial.println(httpResponseCode);


  if (httpResponseCode > 0) {

    String response = http.getString();

    Serial.print("Control Response: ");
    Serial.println(response);


    // ----------------------------------------
    // Pump ON
    // ----------------------------------------

    if (response.indexOf("\"pump_status\":\"ON\"") >= 0) {

      digitalWrite(RELAY_PIN, HIGH);

      Serial.println("Pump Status: ON");
      Serial.println("Relay GPIO 26: HIGH");

    }


    // ----------------------------------------
    // Pump OFF
    // ----------------------------------------

    else if (response.indexOf("\"pump_status\":\"OFF\"") >= 0) {

      digitalWrite(RELAY_PIN, LOW);

      Serial.println("Pump Status: OFF");
      Serial.println("Relay GPIO 26: LOW");

    }


    else {

      Serial.println("Pump status not found");

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


  String serverPath = String(serverName) +
                      "?temperature=" + String(temperature, 2) +
                      "&humidity=" + String(humidity, 2) +
                      "&air_quality=" + String(airValue)+
                      "&water_level=" + String(waterLevel);


  Serial.println();
  Serial.println("Sending sensor data...");

  Serial.println(serverPath);


  http.begin(serverPath.c_str());


  int httpResponseCode = http.GET();


  Serial.print("Sensor HTTP Response Code: ");
  Serial.println(httpResponseCode);


  if (httpResponseCode > 0) {

    String response = http.getString();

    Serial.print("Server Response: ");
    Serial.println(response);

  }

  else {

    Serial.println("Error sending sensor data!");

  }


  http.end();

}


// ========================================
// Main Loop
// ========================================

void loop() {

  unsigned long currentMillis = millis();


  // ======================================
  // Update every 8 seconds
  // ======================================

  if (currentMillis - previousMillis >= updateInterval) {

    previousMillis = currentMillis;


    // ====================================
    // Read DHT22
    // ====================================

    humidity = dht.readHumidity();

    temperature = dht.readTemperature();


    // ====================================
    // Read MQ135
    // ====================================

    airValue = analogRead(MQ135_PIN);

    // Read Water Level
    waterLevel = analogRead(WATER_LEVEL_PIN);


    // ====================================
    // Check DHT22
    // ====================================

    if (isnan(humidity) || isnan(temperature)) {

      Serial.println("DHT22 Reading Failed!");

      lcd.clear();

      lcd.setCursor(0, 0);
      lcd.print("DHT22 Error");

      return;
    }


    // ====================================
    // Serial Monitor
    // ====================================

    Serial.println();
    Serial.println("------------------------");

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" C");

    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");

    Serial.print("Air Quality: ");
    Serial.println(airValue);

    Serial.print("Water Level: ");
    Serial.println(waterLevel);

    Serial.println("------------------------");


    // ====================================
    // LCD
    // ====================================

    displayLCD();


    // ====================================
    // Send data to PHP
    // ====================================

    sendSensorData();


    // ====================================
    // Check Pump
    // ====================================

    checkPumpControl();

  }

}