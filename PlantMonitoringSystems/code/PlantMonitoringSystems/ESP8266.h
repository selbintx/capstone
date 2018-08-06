/*
ESP8266.h
*/
/*
 *  FILE          : ESP8266.h
 *  PROJECT       : PlantMonitoringSystems
 *  PROGRAMMERS   : Group7,Bhavyasree,Darwin,Selbin
 *  Date          : 2018-07-25
 *  DESCRIPTION   : This program interface ESP8266 Wifi Module to Arudino  
 *                  and send the data to thingspeak.com channel 518310.
*/

#include <SoftwareSerial.h>

#define RX 10
#define TX 11

//software implementation of serial communication
 SoftwareSerial esp8266(RX,TX);

/* The strings that needed to be send to the thingspeak.com for
 * data logging and graphical representation.
 */

String HOST = "api.thingspeak.com";
String PORT = "80";
String AP = "Rogers221";//SSID of the wifi network
String PASS = "Rogers66704";//Password of wifi network
String API = "I0AXSWHCV5NOGRLR";//API key from thingspeak
String Tempfield = "field1";
String Humidityfield = "field2";
String LUXfield = "field3";
  
int CommandCount=0;
int CommandWaitTime=0;
boolean foundOk = false;
  
//
//Function Name : sendCommand
//Description   : This function is used to send inbuild commands to esp8266
//Parameters    : None
//Arguments     : None
void sendCommand(String command, int maxTime, char readReplay[]) 
  {
    Serial.print(CommandCount);
    Serial.print(". at command => ");
    Serial.print(command);
    Serial.print(" ");
    // while command wait time is not maximum we are checking for ok acknowledgment
    //meaning that the current command executed successfully.
    while(CommandWaitTime < (maxTime*1))
    {
      esp8266.println(command);//sends the at commands to the esp8266
      if(esp8266.find(readReplay))//ok
      {
      foundOk = true;
      break;//exit the loop if the ok acknoledgment is recevied.
      }
      CommandWaitTime++;//increment the waiting time counter
    }
    if(foundOk == true)//if ok acknowledgment received
    {
    Serial.println("Success");
    CommandCount++;//move to next command if the current one is successs 
    CommandWaitTime = 0;//resets the wait time for command
    }
    if(foundOk == false)//if fail to receive ok ack
    {
    Serial.println("Fail");
    CommandCount = 0;//starts from the first command
    CommandWaitTime = 0;//resets the wait time for command
    }
    foundOk = false;//making default as false before going to next check
 }