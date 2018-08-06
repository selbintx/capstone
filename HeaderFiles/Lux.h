/*
Lux.h
*/
/*
 *  FILE          : Lux.h
 *  PROJECT       : PlantMonitoringSystems
 *  PROGRAMMERS   : Group7,Bhavyasree,Darwin,Selbin
 *  Date          : 2018-07-25
 *  DESCRIPTION   : This program interface LDR to Arudino.
 */

double  MeasuredLux=0;

#define LDR_ANALOG_PIN A1        //A1 pin on arduino uno
#define ReferenceVoltage 5
#define SeriesResistance 10       //10kilo ohm

//
//Function Name : LightIntesityInLux
//Description   : Function to convert LDR analog value to lux
//Parameters    : None
//Arguments     : None
void lightIntesityInLux(void)
  { 
    int     rawAnalogValue=0;
    double  VoltageOnLDR =0;
    double  LDRresistance=0;
    //(reference voltage 5)/(maximum adc value 1023)=0.004882815
    rawAnalogValue=analogRead(LDR_ANALOG_PIN);
    VoltageOnLDR = rawAnalogValue*0.0048828125;
    LDRresistance= ((VoltageOnLDR * SeriesResistance)/(ReferenceVoltage - VoltageOnLDR));
    //From ldr data sheet lux=369.71*(ldrResistance^-1.415)
    MeasuredLux= ( 369.71 * (pow(LDRresistance, (-1.415))));
    Serial.print("\nLight Intensity in Lux : ");
    Serial.println(MeasuredLux);
    Serial.print("\n\n");
  }

