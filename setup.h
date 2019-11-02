/*

  ____  _             _ __        __    _       _     
 |  _ \| | __ _ _ __ | |\ \      / /_ _| |_ ___| |__  
 | |_) | |/ _` | '_ \| __\ \ /\ / / _` | __/ __| '_ \ 
 |  __/| | (_| | | | | |_ \ V  V / (_| | || (__| | | |
 |_|   |_|\__,_|_| |_|\__| \_/\_/ \__,_|\__\___|_| |_|
 http://github.com/nmeurer/PlantWatch/           SETUP                                                     

*/

/*### Plant-related stuff #################################################################################################*/
#define plantName "living room plant" //name of your plant to be displayed
#define plantType "Chlorophytum comosum" //species of your plant
/*#########################################################################################################################*/

/*### Electronics setup ###################################################################################################*/
#define DHTtype DHT11 //set the type of your DHT here
#define DHTpin 14 //the data pin from your DHT-sensor
#define moistPin A0 //moisture sensor pin
#define maxMoist 650 //raw value after watering
#define minMoist 1023 //raw value when soil is dry
/*#########################################################################################################################*/

/*### WiFi setup ##########################################################################################################*/
const char* ssid     = "YOUR_SSID"; // Replace with your networks SSID
const char* password = "YOUR_PASSWORD"; // Replace with your networks password

WiFiServer server(80); // Set web server port. (Port 80 recommended)

#define useCustomServerName false //true: enable custom name; false: disable custom name | Default name: PlantWatch: [PlantName]
#define customServerName "My PlantWatchServer" //use for Custom server name
/*######################################################################################################################*/
