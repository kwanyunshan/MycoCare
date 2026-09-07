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
// Computer IPv4: 192.168.0.226
// ========================================

const char* serverName =
"http://10.18.65.36/mycocare/save_data.php";


// ========================================
// DHT22 Settings
// ========================================

#define DHTPIN 4
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);


// ===============,,,,,,,,,,,,,,,,,vggffgfffg=========================
// MQ135 Settings
// ========================================
<<<<<<< HEAD
=======

>>>>>>> c227db6728d18ff65c986029df88dfbf9a3f1a4c
#define MQ135_PIN 32


// ========================================
// Sensor Variables
// ========================================

float temperature = 0;
float humidity = 0;
int airValue = 0;


// ========================================
// Sending Interval
// ========================================

unsigned long previousMillis = 0;
const long interval = 5000;


// ========================================
// Setup
// ========================================

void setup() {

  Serial.begin(115200);

  delay(1000);


  // Start DHT22

  dht.begin();

  Serial.println("DHT22 Started");


  // Connect WiFi

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
}


// ========================================
// Main Loop
// ========================================

void loop() {


  // ----------------------------------------
  // Read DHT22
  // ----------------------------------------

  humidity = dht.readHumidity();

  temperature = dht.readTemperature();


  // ----------------------------------------
  // Read MQ135
  // ----------------------------------------

  airValue = analogRead(MQ135_PIN);


  // ----------------------------------------
  // Check DHT22 Error
  // ----------------------------------------

  if (isnan(humidity) || isnan(temperature)) {

    Serial.println("DHT22 Reading Failed!");

    delay(2000);

    return;
  }


  // ----------------------------------------
  // Display Sensor Data
  // ----------------------------------------

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


  // ----------------------------------------
  // Send Data to PHP
  // ----------------------------------------

  if (WiFi.status() == WL_CONNECTED) {

    unsigned long currentMillis = millis();


    // Send data every 5 seconds

    if (currentMillis - previousMillis >= interval) {

      previousMillis = currentMillis;


      HTTPClient http;


      // Create URL with sensor data

      String serverPath = String(serverName) +
                          "?temperature=" + String(temperature, 2) +
                          "&humidity=" + String(humidity, 2) +
                          "&air_quality=" + String(airValue);


      Serial.println("Sending data to PHP...");

      Serial.println(serverPath);


      // Start HTTP Request

      http.begin(serverPath.c_str());


      // Send GET Request

      int httpResponseCode = http.GET();


      // Display Response

      Serial.print("HTTP Response Code: ");

      Serial.println(httpResponseCode);


      if (httpResponseCode > 0) {

        String response = http.getString();

        Serial.print("Server Response: ");

        Serial.println(response);

      }

      else {

        Serial.println("Error sending data!");

      }


      // Close HTTP Connection

      http.end();
    }
  }


  else {

    Serial.println("WiFi Disconnected!");
  }


  delay(2000);
}