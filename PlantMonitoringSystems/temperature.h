/*
temperature.h
*/
/*
 *  FILE          : HC-06.h
 *  PROJECT       : PlantMonitoringSystems
 *  PROGRAMMERS   : Group7,Bhavyasree,Darwin,Selbin
 *  Date          : 2018-07-25
 *  DESCRIPTION   : This program interface Temperarure sensor to Arudino.  
 *                 
 */

#include <DallasTemperature.h>  //Library for the temperature sensor

#define TEMPERATURE_SENSOR_WIRE_BUS 2


// Setup a oneWire instance to communicate with Dallas temperature
OneWire TemperatureSensor(TEMPERATURE_SENSOR_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature TemperatureSensors(&TemperatureSensor);


float   Temperature =0;  // just for testing the working of the code
//
//Function Name : DisplayTemperature
//Description   : Function to measure and display Temperature
//Parameters    : None
//Arguments     : None
void DisplayTemperature(void)
  {
    Serial.println("Temperature measurements");
    TemperatureSensors.requestTemperatures();//makes measurements on connected temperature sensors
    Serial.print("No of connected temperature sensor ");
    Serial.println(TemperatureSensors.getDeviceCount());
    Serial.print("Measured temperature on the first  temperature sensor ");
    Temperature=TemperatureSensors.getTempCByIndex(0);
    Serial.println(Temperature); ;//library function used to get the temperature in degree celsius
    //Serial.print("Measured temperature on the second temperature sensor");
    //Serial.println(TemperatureSensors.getTempCByIndex(1));
  }