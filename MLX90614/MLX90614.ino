/*************************************************** 
  This is a library example for the MLX90614 Temp Sensor based on open source code from Adafruit Industries.

  VIN --> arduino 3.3V
  GND  -->  arduino GND
  SCL  -->  A5
  SDA  -->  A4
  
****************************************************/
#include <Wire.h>
#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {
  Serial.begin(9600);
//  Serial.println("Adafruit MLX90614 test");  

  mlx.begin();  
}
void loop() {
//  Serial.print("Ambient = "); 
  Serial.println(mlx.readAmbientTempC()); 
//  Serial.print("*C\tObject = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");
//  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempF()); Serial.print("*F\tObject = "); Serial.print(mlx.readObjectTempF()); Serial.println("*F");
//  Serial.println();

  delay(500);
}
