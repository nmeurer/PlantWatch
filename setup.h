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
#define useDHT true
#if (useDHT)
  #define DHTtype DHT11 //set the type of your DHT here
  #define DHTpin 26 //the data pin from your DHT-sensor
#endif

#define useBrightness true
#if (useBrightness)
  #define brightPin 21 //brightness sensor pin
  #define minBright 0 //raw value when no light's shining
  #define maxBright 1023 //raw value when light's shining bright
#endif

#define useMoisture true
#if (useMoisture)
  #define moistPin A0 //moisture sensor pin
  #define maxMoist 650 //raw value after watering
  #define minMoist 1023 //raw value when soil is dry
#endif
/*#########################################################################################################################*/

/*### WiFi setup ##########################################################################################################*/
const char* ssid     = "MeuTekk"; // Replace with your networks SSID
const char* password = "0105166146172279"; // Replace with your networks password

WiFiServer server(80); // Set web server port. (Port 80 recommended)

#define useMDNS true //true: enable custom DNS; false: disable custom DNS
#if (useMDNS)
  #define mdnsname "plant" //use for custom dns (server name)
#endif
/*######################################################################################################################*/
