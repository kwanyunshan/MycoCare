#include <WiFi.h>
#include <DHT.h>


// ================= WiFi =================

const char* ssid = "kwan";
const char* password = "ys030305";

WiFiServer server(80);


// ================= DHT22 =================

#define DHTPIN 4
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);


// ================= MQ135 =================

#define MQ135_PIN 32



// Store sensor data

float temperature;
float humidity;

int airValue;



void setup() {

  Serial.begin(115200);


  // Start DHT22

  dht.begin();



  // Connect WiFi

  WiFi.begin(ssid, password);


  Serial.print("Connecting WiFi");


  while(WiFi.status() != WL_CONNECTED){

    delay(500);

    Serial.print(".");

  }


  Serial.println();

  Serial.println("WiFi Connected!");



  Serial.print("ESP32 IP Address: ");

  Serial.println(WiFi.localIP());



  // Start Web Server

  server.begin();


  Serial.println("Web Server Started");

}



void loop() {


  // Read DHT22

  humidity = dht.readHumidity();

  temperature = dht.readTemperature();



  // Read MQ135

  airValue = analogRead(MQ135_PIN);



  // Check DHT error

  if(isnan(humidity) || isnan(temperature)){


    Serial.println("DHT22 Reading Failed!");

    return;

  }



  // Serial Monitor

  Serial.println("-------------------");


  Serial.print("Temperature: ");

  Serial.print(temperature);

  Serial.println(" °C");



  Serial.print("Humidity: ");

  Serial.print(humidity);

  Serial.println(" %");



  Serial.print("Air Quality: ");

  Serial.println(airValue);



  Serial.println("-------------------");





  // Web Client

  WiFiClient client = server.available();



  if(client){


    Serial.println("New Client");



    String request = client.readStringUntil('\r');

    client.flush();



    // HTML Web Page


    client.println("HTTP/1.1 200 OK");

    client.println("Content-type:text/html");

    client.println();



    client.println("<!DOCTYPE html>");

    client.println("<html>");

    client.println("<head>");



    client.println("<title>MycoCare Dashboard</title>");



    client.println("<meta name='viewport' content='width=device-width, initial-scale=1'>");
    client.println("<meta http-equiv='refresh'content='2'>");



    client.println("<style>");

    client.println("body{font-family:Arial;text-align:center;background:#f2f2f2;}");

    client.println(".box{background:white;margin:20px;padding:20px;border-radius:10px;}");

    client.println("h1{color:green;}");

    client.println("</style>");



    client.println("</head>");



    client.println("<body>");



    client.println("<h1>MycoCare Smart Mushroom Monitoring</h1>");



    client.println("<div class='box'>");


    client.print("<h2>Temperature: ");

    client.print(temperature);

    client.println(" °C</h2>");



    client.print("<h2>Humidity: ");

    client.print(humidity);

    client.println(" %</h2>");



    client.print("<h2>Air Quality: ");

    client.print(airValue);

    client.println("</h2>");



    // Air Quality Status


    if(airValue > 2000){

      client.println("<h2 style='color:red'>Air Quality: Poor</h2>");

    }

    else{

      client.println("<h2 style='color:green'>Air Quality: Good</h2>");

    }



    client.println("</div>");



    client.println("</body>");

    client.println("</html>");



    client.stop();



    Serial.println("Client Disconnected");


  }



  delay(1000);

}