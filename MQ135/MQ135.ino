/*************************************************** 
  This is a library example for the MQ135 Sensor.

  VCC  -->  arduino 5V
  GND  -->  arduino GND
  AO   -->  A2
  
****************************************************/
#include <MQ135.h>
#define ANALOGPIN A2

int PPMStatus = 0;
int PPMStatusOld = 0;

float airTemperature, airHumidity, ppm, ppmbalanced, rzero;

MQ135 gasSensor = MQ135(ANALOGPIN);

void setup() {
  Serial.begin(9600);
}

void loop() {

  // current temperature and humidity for further calculation
  airTemperature = 28;
  airHumidity = 50;

  // zero value
  rzero = gasSensor.getRZero(); 
//  Serial.print("RZero=");
//  Serial.println(rzero);    

  // ppm value without adjustment
  ppm = gasSensor.getPPM(); 
//  Serial.print("PPM=");
//  Serial.println(ppm); 

  // ppm value after adjustment by zero value
  ppmbalanced = gasSensor.getCorrectedPPM(airTemperature, airHumidity);
//  Serial.print("PPM Corrected=");
  Serial.println(ppmbalanced); 
//  Serial.println();

  delay(100);
}
