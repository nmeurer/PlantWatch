/*

  ____  _             _ __        __    _       _     
 |  _ \| | __ _ _ __ | |\ \      / /_ _| |_ ___| |__  
 | |_) | |/ _` | '_ \| __\ \ /\ / / _` | __/ __| '_ \ 
 |  __/| | (_| | | | | |_ \ V  V / (_| | || (__| | | |
 |_|   |_|\__,_|_| |_|\__| \_/\_/ \__,_|\__\___|_| |_|
 http://github.com/nmeurer/PlantWatch/       WEB-STUFF                                                   

*/

String getIndex(){
  String web = "<!DOCTYPE html>";
         web += "<html lang='en'>";
         web += "  <head>";
         web += "    <meta http-equiv='X-UA-Compatible' content='IE=edge'>";
         web += "    <meta name='viewport' content='width=device-width, initial-scale=1'>";
         web += "    <meta charset='utf-8'/>";
         web += "    <link rel='stylesheet' href='https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css' integrity='sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T' crossorigin='anonymous'>";
         web += "    <title>PlantWatch: "+String(plantName)+"</title>";
         web += "  </head>";
         web += "  <body>";
         web += "    <div class='container-fluid text-center'>";
         web += "      <div class='row'>";
         web += "        <div class='col-md-12'>";
         web += "          <div class='page-header'>";
         web += "            <h1>";
         web += "              <large><b>PlantWatch</b></large><br>";
         web += "              <small>Plant: "+String(plantName)+ ", <i>"+String(plantType)+"</i></small>";
         web += "            </h1>";
         web += "          </div>";
         web += "          <div class='progress'>";
         web += "            <div class='progress-bar progress-bar-striped progress-bar-animated' style='width: "+String(moisturePercentage)+"%;'>";
         web += "            </div>";
         web += "          </div>";
         web += "          <table class='table'>";
         web += "            <thead>";
         web += "              <tr>";
         web += "                <th>";
         web += "                  Sensor";
         web += "                </th>";
         web += "                <th>";
         web += "                Value";
         web += "                </th>";
         web += "              </tr>";
         web += "            </thead>";
         web += "            <tbody>";
         web += "              <tr class='table-"+moisturePercentageLevel+"'>";
         web += "                <td>";
         web += "                  Soil-moisture";
         web += "                </td>";
         web += "                <td>";
         web += "                  "+String(moisturePercentage)+"%";
         web += "                </td>";
         web += "              </tr>";
         web += "            </tbody>";
         web += "            <tbody>";
         web += "              <tr class='table-"+humidityLevel+"'>";
         web += "                <td>";
         web += "                  Humidity";
         web += "                </td>";
         web += "                <td>";
         web += "                  "+String(humidity)+"%";
         web += "                </td>";
         web += "              </tr>";
         web += "            </tbody>";
         web += "            <tbody>";
         web += "              <tr class='table-"+temperatureLevel+"'>";
         web += "                <td>"; 
         web += "                  Temperature";
         web += "                </td>";
         web += "                <td>";
         web += "                  "+String(temperature)+"°C";
         web += "                </td>";
         web += "              </tr>";
         web += "            </tbody>";
         web += "          </table>";
         web += "         <h6>My IP-adress: "+ WiFi.localIP().toString() +"</h6>";
         web += "        </div>";
         web += "      </div>";
         web += "    </div>";
         web += "    <script src='https://code.jquery.com/jquery-3.3.1.slim.min.js' integrity='sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo' crossorigin='anonymous'></script>";
         web += "    <script src='https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.7/umd/popper.min.js' integrity='sha384-UO2eT0CpHqdSJQ6hJty5KVphtPhzWj9WO1clHTMGa3JDZwrnQq4sF86dIHNDz0W1' crossorigin='anonymous'></script>";
         web += "    <script src='https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/js/bootstrap.min.js' integrity='sha384-JjSmVgyd0p3pXB1rRibZUAYoIIy6OrQ6VrjIEaFf/nJGzIxFDsf4x0xIM+B07jRM' crossorigin='anonymous'></script>";
         web += "  </body>";
         web += "</html>";
         return web;
}
