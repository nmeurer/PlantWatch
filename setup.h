/*

  ____  _             _ __        __    _       _     
 |  _ \| | __ _ _ __ | |\ \      / /_ _| |_ ___| |__  
 | |_) | |/ _` | '_ \| __\ \ /\ / / _` | __/ __| '_ \ 
 |  __/| | (_| | | | | |_ \ V  V / (_| | || (__| | | |
 |_|   |_|\__,_|_| |_|\__| \_/\_/ \__,_|\__\___|_| |_|
                                                 SETUP                                                     

*/

/*##############################################################PLANT-RELATED-STUFF###################################################*/
#define plantName "Karsten" //name of your plant to be displayed
#define plantType "Grünlilie" //species of your plant
/*######################################################################################################################*/
/*######################################################################################################################*/
#define DHTtype DHT11 //set the type of your DHT here
#define DHTpin 14 //the data pin from your DHT-sensor
#define moistPin A0 //moisture sensor pin
#define maxMoist 650 //raw value after watering
#define minMoist 1023 //raw value when soil is dry
/*######################################################################################################################*/
/*######################################################################################################################*/
const char* ssid     = "MeuTekk"; // Replace with your networks SSID
const char* password = "0105166146172279"; // Replace with your networks password

WiFiServer server(80); // Set web server port. (Port 80 recommended)

#define useCustomServerName false //true: enable custom name; false: disable custom name | Default name: PlantWatch: [PlantName]
#define customServerName "My PlantWatchServer" //use for Custom server name
/*######################################################################################################################*/
