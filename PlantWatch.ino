/*

  ____  _             _ __        __    _       _     
 |  _ \| | __ _ _ __ | |\ \      / /_ _| |_ ___| |__  
 | |_) | |/ _` | '_ \| __\ \ /\ / / _` | __/ __| '_ \ 
 |  __/| | (_| | | | | |_ \ V  V / (_| | || (__| | | |
 |_|   |_|\__,_|_| |_|\__| \_/\_/ \__,_|\__\___|_| |_|
 http://github.com/nmeurer/PlantWatch/       MAIN-CODE                                                   

*/
#include <WiFi.h>

String header; // Variable to store the HTTP request
unsigned long currentTime = millis(); // Current time
unsigned long previousTime = 0; // Previous time
const long timeoutTime = 2000; // Define timeout time in milliseconds (example: 2000ms = 2s)
float moisture, humidity, temperature, brightness;
int moisturePercentage, brightnessPercentage;
String humidityLevel, temperatureLevel, moisturePercentageLevel, brightnessPercentageLevel, brightnessLevel;

#include "setup.h"
#include "index.h"

#if (useDHT)
  #include <DHT.h>
  DHT dht(DHTpin, DHTtype);
#endif

#if (useMDNS)
  #include <ESPmDNS.h>
#endif

void setup()
{
  Serial.begin(115200);

  #if (useDHT)
    dht.begin(); //initialize DHT-sensor
  #endif
  
  //WiFi-Setup
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  #if (useMDNS) // Add custom MDNS
  MDNS.begin(mdnsname);
  #endif
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop()
{
  Serial.println();
  
  #if (useDHT)
    delay(2000); //dont remove the delay, since the DHT is rather slow
    humidity = dht.readHumidity();
    temperature = dht.readTemperature();
    Serial.print(humidity, 1);
    Serial.print("\t");
    Serial.print(temperature, 1);
    Serial.print("\t");
  #endif

  #if (useMoisture)
  moisture = analogRead(moistPin);
  moisturePercentage = map(moisture, minMoist, maxMoist, 0.0, 100.0); //turn the ugly raw value into a nice percentage
  Serial.print(moisture, 1);
  Serial.print("\t");
  Serial.print(moisturePercentage, 1);
  Serial.print("\t");
  #endif

  #if (useBrightness)
  brightness = analogRead(brightPin);
  brightnessPercentage = map(brightness, minBright, maxBright, 0.0, 100.0); //turn the ugly raw value into a nice percentage
  Serial.print(brightnessPercentage, 1);
  Serial.print("\t");
  #endif

  #if (useDHT)
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
  #endif

  #if (useMoisture)
    if (moisturePercentage < 30 && moisturePercentage > 15){ //handling the background for soil moisture
      moisturePercentageLevel = "warning";
    } else if (moisturePercentage < 15) {
      moisturePercentageLevel = "danger";
    } else {
      moisturePercentageLevel = "success";
    }
  #endif

  #if (useBrightness)
    if (brightnessPercentage < 45 && brightnessPercentage > 30){ //handling the background for soil moisture
      brightnessPercentageLevel = "warning";
    } else if (brightnessPercentage < 30) {
      brightnessPercentageLevel = "danger";
    } else {
      brightnessPercentageLevel = "success";
    }
  #endif
  
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
          if (currentLine.length() == 0) {
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
