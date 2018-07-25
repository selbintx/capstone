/*
HC_06.h
*/
/*
 *  FILE          : HC-06.h
 *  PROJECT       : PlantMonitoringSystems
 *  PROGRAMMERS   : Group7,Bhavyasree,Darwin,Selbin
 *  Date          : 2018-07-25
 *  DESCRIPTION   : This program interface  HC_06 to Arudino  and send the data to Ardutooth.
 */              

#include <SoftwareSerial.h>

#define RX 5
#define TX 6

void bluetooth(void);

//software implementation of serial communication
  SoftwareSerial BTserial(RX,TX);

void bluetooth(void){
    DisplayTemperature();
    DisplaySoilHumidity();
    lightIntesityInLux();
    BTserial.begin(9600); 
    BTserial.print(String(Temperature));
    BTserial.print(",");
    BTserial.print(String(PercentageHumidity));
    BTserial.print(",");
    BTserial.print(String(MeasuredLux));
    BTserial.print(";");
    BTserial.end(); 
  }
  