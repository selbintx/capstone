
/*
*  FILE          : PlantMonitoringSystems.ino
*  PROJECT       : PlantMonitoringSystems
*  PROGRAMMERS   : Group7,Bhavyasree,Darwin,Selbin
*  FIRST VERSION : 2018-05-30
*  DESCRIPTION   :
*                 This program interfaces temperature sensors , soil humidity sensor and a LDR and
*                 prints the data on the serial monitor.
*/
  
  //Include libraries
  #include <OneWire.h>            //Library for the temperature sensor
  #include <DallasTemperature.h>  //Library for the temperature sensor
  
  #define TEMPERATURE_SENSOR_WIRE_BUS 2
  #define HUMIDITY_SENSOR_BUS A0    //A0 pin on arduino uno
  #define LDR_ANALOG_PIN A1        //A1 pin on arduino uno
  #define ReferenceVoltage 5
  #define SeriesResistance 10       //10kilo ohm
  
  void DisplayTemperature(void);
  void DisplaySoilHumidity(void);
  void lightIntesityInLux (void);
  
  // Setup a oneWire instance to communicate with Dallas temperature
  OneWire TemperatureSensor(TEMPERATURE_SENSOR_WIRE_BUS);
  // Pass our oneWire reference to Dallas Temperature. 
  DallasTemperature TemperatureSensors(&TemperatureSensor);

  void setup(void)
  {
    Serial.begin(9600); //Begin serial communication
    TemperatureSensors.begin();//Initialises the temperature sensor
  } 
  void loop(void)
  { 
    DisplayTemperature();
    DisplaySoilHumidity();
    lightIntesityInLux();
    delay(3000);
  }
  
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
    Serial.println(TemperatureSensors.getTempCByIndex(0));//library function used to get the temperature in degree celsius
    Serial.print("Measured temperature on the second temperature sensor");
    Serial.println(TemperatureSensors.getTempCByIndex(1));
  }
  
  //
  //Function Name : DisplaySoilHumidity
  //Description   : Function to measure and display soil humidity
  //Parameters    : None
  //Arguments     : None
  void DisplaySoilHumidity(void)
  {
    int   rawTemperatureValues=0;
    float PercentageRelativeHumidity=0;
    rawTemperatureValues=analogRead(HUMIDITY_SENSOR_BUS);
    //Due to the lack of data sheet the humidity sensor is caliberated using the experimental results
    rawTemperatureValues = 1023-rawTemperatureValues;//the raw values are inverted from the 1023 to get a direct proportionality with humidity
    //the sensor outputs 852 when it is immersed in water which is taken as 100% humidity
    //the percentage humidity is expressed as the percentage of(852)
    if(rawTemperatureValues<852)
    PercentageRelativeHumidity=(rawTemperatureValues*0.11);//0.11627 = 100/(852)
    else
    Serial.print("\nThe percentage humidity :");
    Serial.println(PercentageRelativeHumidity); 
  }
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
    double  MeasuredLux=0;
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
