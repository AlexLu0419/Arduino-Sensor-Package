/*************************************************** 
  This is a library example for the MQ135 Sensor.

  VCC  -->  arduino 5V
  GND  -->  arduino GND
  pin  -->  A2
  
****************************************************/

int gasSensor = A2; // 指定要量測的analog腳位為2
int gasval = 0;
void setup() {
  Serial.begin(9600);
}

void loop() {
  gasval = analogRead(gasSensor);
  Serial.println( gasval );
  delay(500);
}
