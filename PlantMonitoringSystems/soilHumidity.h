/*
soilHumidity.h
*/
/*
 *  FILE          : HC-06.h
 *  PROJECT       : PlantMonitoringSystems
 *  PROGRAMMERS   : Group7,Bhavyasree,Darwin,Selbin
 *  Date          : 2018-07-25
 *  DESCRIPTION   : This program interfaces soil humidity sensor to Arudino.
 *                 
 */

#define HUMIDITY_SENSOR_BUS A0    //A0 pin on arduino uno
float   PercentageHumidity=0;

//
  //Function Name : DisplaySoilHumidity
  //Description   : Function to measure and display soil humidity
  //Parameters    : None
  //Arguments     : None
  void DisplaySoilHumidity(void)
  {
    int   rawTemperatureValues=0;
    rawTemperatureValues=analogRead(HUMIDITY_SENSOR_BUS); 
	//Due to the lack of data sheet the humidity sensor is caliberated using the experimental results
    rawTemperatureValues = 1023-rawTemperatureValues;
	//the raw values are inverted from the 1023 to get a direct proportionality with humidity
    //the sensor outputs 852 when it is immersed in water which is taken as 100% humidity
    //the percentage humidity is expressed as the percentage of(852)
    if(rawTemperatureValues<=852)
    PercentageHumidity=(rawTemperatureValues*0.11);//0.11627 = 100/(852)
    else
    PercentageHumidity=100;
    Serial.print("\nThe percentage humidity :");
    Serial.println(PercentageHumidity); 
  }