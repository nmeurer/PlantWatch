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
   /*if (useCustomServerName == false){ //handling custom server name
    WiFi.setHostname("PlantWatch: "+plantName);
  } else if (useCustomServerName == true){
    WiFi.setHostname(String(customServerName));
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

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  float moisture = analogRead(moistPin);

  int moisturePercentage = map(moisture, minMoist, maxMoist, 0.0, 100.0); //turn the ugly raw value into a nice percentage
  
  Serial.println();
  Serial.print(humidity, 1);
  Serial.print("\t");
  Serial.print(temperature, 1);
  Serial.print("\t");
  Serial.print(moisture, 1);
  Serial.print("\t");
  Serial.print(moisturePercentage, 1);

  String humidityLevel, temperatureLevel, moisturePercentageLevel;

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
            
            
            //Display the HTML web page
            //Variables are coded in
            
            client.println("<!DOCTYPE html>");
            client.println("<html lang='en'>");
            client.println("  <head>");
            client.println("    <meta http-equiv='X-UA-Compatible' content='IE=edge'>");
            client.println("    <meta name='viewport' content='width=device-width, initial-scale=1'>");
            client.println("    <meta charset='utf-8'/>");
            client.println("    <link rel='stylesheet' href='https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css' integrity='sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T' crossorigin='anonymous'>");
            client.println("    <title>PlantWatch: "+String(plantName)+"</title>");
            client.println("  </head>");
            client.println("  <body>");
            client.println("    <div class='container-fluid text-center'>");
            client.println("      <div class='row'>");
            client.println("        <div class='col-md-12'>");
            client.println("          <div class='page-header'>");
            client.println("            <h1>");
            client.println("              <large><b>PlantWatch</b></large><br>");
            client.println("              <small>Plant: "+String(plantName)+ ", <i>"+String(plantType)+"</i></small>");
            client.println("            </h1>");
            client.println("          </div>");
            client.println("          <div class='progress'>");
            client.println("            <div class='progress-bar progress-bar-striped progress-bar-animated' style='width: "+String(moisturePercentage)+"%;'>");
            client.println("            </div>");
            client.println("          </div>");
            client.println("          <table class='table'>");
            client.println("            <thead>");
            client.println("              <tr>");
            client.println("                <th>");
            client.println("                  Sensor");
            client.println("                </th>");
            client.println("                <th>");
            client.println("                Value");
            client.println("                </th>");
            client.println("              </tr>");
            client.println("            </thead>");
            client.println("            <tbody>");
            client.println("              <tr class='table-"+moisturePercentageLevel+"'>");
            client.println("                <td>");
            client.println("                  Soil-moisture");
            client.println("                </td>");
            client.println("                <td>");
            client.println("                  "+String(moisturePercentage)+"%");
            client.println("                </td>");
            client.println("              </tr>");
            client.println("            </tbody>");
            client.println("            <tbody>");
            client.println("              <tr class='table-"+humidityLevel+"'>");
            client.println("                <td>");
            client.println("                  Humidity");
            client.println("                </td>");
            client.println("                <td>");
            client.println("                  "+String(humidity)+"%");
            client.println("                </td>");
            client.println("              </tr>");
            client.println("            </tbody>");
            client.println("            <tbody>");
            client.println("              <tr class='table-"+temperatureLevel+"'>");
            client.println("                <td>");
            client.println("                  Temperature");
            client.println("                </td>");
            client.println("                <td>");
            client.println("                  "+String(temperature)+"°C");
            client.println("                </td>");
            client.println("              </tr>");
            client.println("            </tbody>");
            client.println("          </table>");
            client.println("         <h6>My IP-adress: "+ WiFi.localIP().toString() +"</h6>");
            client.println("        </div>");
            client.println("      </div>");
            client.println("    </div>");
            client.println("    <script src='https://code.jquery.com/jquery-3.3.1.slim.min.js' integrity='sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo' crossorigin='anonymous'></script>");
            client.println("    <script src='https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.7/umd/popper.min.js' integrity='sha384-UO2eT0CpHqdSJQ6hJty5KVphtPhzWj9WO1clHTMGa3JDZwrnQq4sF86dIHNDz0W1' crossorigin='anonymous'></script>");
            client.println("    <script src='https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/js/bootstrap.min.js' integrity='sha384-JjSmVgyd0p3pXB1rRibZUAYoIIy6OrQ6VrjIEaFf/nJGzIxFDsf4x0xIM+B07jRM' crossorigin='anonymous'></script>");
            client.println("  </body>");
            client.println("</html>");
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
