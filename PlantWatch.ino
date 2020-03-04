/*

  ____  _             _ __        __    _       _     
 |  _ \| | __ _ _ __ | |\ \      / /_ _| |_ ___| |__  
 | |_) | |/ _` | '_ \| __\ \ /\ / / _` | __/ __| '_ \ 
 |  __/| | (_| | | | | |_ \ V  V / (_| | || (__| | | |
 |_|   |_|\__,_|_| |_|\__| \_/\_/ \__,_|\__\___|_| |_|
 http://github.com/nmeurer/PlantWatch/       MAIN-CODE                                                   

*/

#include <ESPmDNS.h>
#include <WiFi.h>
#include <DHT.h>
#include "setup.h"

String header; // Variable to store the HTTP request
unsigned long currentTime = millis(); // Current time
unsigned long previousTime = 0; // Previous time
const long timeoutTime = 2000; // Define timeout time in milliseconds (example: 2000ms = 2s)
float moisture, humidity, temperature;
int moisturePercentage;
String humidityLevel, temperatureLevel, moisturePercentageLevel;

#include "index.h"

DHT dht(DHTpin, DHTtype);

void setup()
{
  Serial.begin(115200);

  dht.begin(); //initialize DHT-sensor

  //WiFi-Setup

  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Add custom server name and MDNS
 /*  if (useCustomServerName == false){ //handling custom server name
    WiFi.setHostname("PlantWatch: "+plantName.toString());
  } else if (useCustomServerName == true){
    WiFi.setHostname(customServerName.toString());
  }*/
  MDNS.begin("plantwatch");
  
  // Print local IP address and start web server
  
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop()
{

  //reading the sensors. Dont remove the delay, since the DHT is rather slow
  
  delay(2000);

  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  moisture = analogRead(moistPin);

  moisturePercentage = map(moisture, minMoist, maxMoist, 0.0, 100.0); //turn the ugly raw value into a nice percentage
  
  Serial.println();
  Serial.print(humidity, 1);
  Serial.print("\t");
  Serial.print(temperature, 1);
  Serial.print("\t");
  Serial.print(moisture, 1);
  Serial.print("\t");
  Serial.print(moisturePercentage, 1);

  if (humidity < 45 && humidity > 40){ //handling the background for humidity
    humidityLevel = "warning";
  } else if (humidity < 40) {
    humidityLevel = "danger";
  } else {
    humidityLevel = "success";
  }

  if (temperature > 25 && temperature < 30){ //handling the background for temperature
    temperatureLevel = "warning";
  } else if (temperature > 30) {
    temperatureLevel = "danger";
  } else {
    temperatureLevel = "success";
  }

  if (moisturePercentage < 30 && moisturePercentage > 15){ //handling the background for soil moisture
    moisturePercentageLevel = "warning";
  } else if (moisturePercentage < 15) {
    moisturePercentageLevel = "danger";
  } else {
    moisturePercentageLevel = "success";
  }

  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) { // loop while the client's connected
      currentTime = millis();         
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            client.println(getIndex()); //Display the HTML web page
            client.println(); // The HTTP response ends with another blank line
            break; // Break out of the while loop
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    header = ""; // Clear the header variable
    client.stop(); // Close the connection
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
