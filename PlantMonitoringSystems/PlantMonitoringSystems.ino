  /*
  *  FILE          : PlantMonitoringSystems.in
  *  PROJECT       : PlantMonitoringSystems
  *  PROGRAMMERS   : Group7,Bhavyasree,Darwin,Selbin
  *  Date          : 2018-07-25
  *  FIRST VERSION : 2018-06-20
  *  DESCRIPTION   :
  *                 This program interfaces temperature sensors , soil humidity sensor and a LDR and
  *                 sends the data to thingspeak.com channel 518310 & Ardutooth via Bluetooth.
  */
  //Include libraries
  #include <OneWire.h>        //Library for the temperature sensor
  #include <DallasTemperature.h>  //Library for the temperature sensor
  #include <SoftwareSerial.h> 
  #include <Lux.h>          //Library for the LDR sensor
  #include <soilHumidity.h>     //Library for the Soil Humidity sensor
  #include <temperature.h>      //Library for the temperature sensor 
  #include <ESP8266.h>        //Library for the Wifi Module ESP8266
  #include <HC_06.h>        //Library for the Bluetooth Module HC_06 
  
 
 
  void DisplayTemperature(void);
  void DisplaySoilHumidity(void);
  void lightIntesityInLux (void);
  void bluetooth(void);
  void sendCommand(String command, int maxTime, char readReplay[]);

 
  void setup() 
  {
    Serial.begin(9600); //This baudrate is corresponding to the UART serial communication
    //This baudrate is corresponding to the software implementation of serial communication
    esp8266.begin(115200);
    TemperatureSensors.begin();//Initialises the temperature sensor
    //esp8266 default firmware has AT commands for controlling the module.
    Serial.println("AT+CWJAP=\""+AP+"\",\""+PASS+"\"");//AT+CWJAP is used to provide our network SSID and password
    //AT is send to receive acknowledgment form the ESP266
    sendCommand("AT",5,"OK");//5 is the waiting time, and "OK" is acknowlegement
    sendCommand("AT+CWMODE=1",5,"OK");//AT+CWMODE=1 makes ESP8266 in staion mode
    sendCommand("AT+CWJAP=\""+AP+"\",\""+PASS+"\"",15,"OK");//AT+CWJAP is used to provide our network SSID and password
    CommandCount = 0; 
    DisplayTemperature();
    DisplaySoilHumidity();
    lightIntesityInLux();
    esp8266.end();
  }
  
  void loop() 
  {
    bluetooth();
    esp8266.begin(115200);
    //the string contains temperature,humidity and Lux along with the API key to update the data on the cloud
    String dataToCloud = "GET /update?api_key="+ API +"&"+ Tempfield +"="+String(Temperature) +"&"+ Humidityfield + "="+String(PercentageHumidity) +"&"+ LUXfield + "="+String(MeasuredLux);
    switch(CommandCount) 
    {
      case 0: sendCommand("AT",5,"OK");//Check esp8266 for acknowledgment
              break;
      case 1: sendCommand("AT+RST",10,"OK");//resets the esp8266
              break;
      case 2: sendCommand("AT+CIPMUX=1",5,"OK");//sets esp8266 in station mode
              break;
      case 3: sendCommand("AT+CIPSTART=0,\"TCP\",\""+ HOST +"\","+ PORT,15,"OK");//
              break;
      case 4: sendCommand("AT+CIPSEND=0," +String(dataToCloud.length()+4),4,">");//sends the string length
              break;
      case 5: esp8266.println(dataToCloud);
              delay(1500);
              CommandCount++; 
              break;
      case 6: sendCommand("AT+CIPCLOSE=0",5,"OK"); 
              break;
      case 7: Serial.print(dataToCloud);
              Serial.print(",");
              Serial.println(dataToCloud.length());
              DisplayTemperature();
              DisplaySoilHumidity();
              lightIntesityInLux();
              CommandCount = 0;//takes control back to the first command
              delay(10000);//takes next reading after 10 seconds
              break;
    }
    esp8266.end();
  }
    

  

