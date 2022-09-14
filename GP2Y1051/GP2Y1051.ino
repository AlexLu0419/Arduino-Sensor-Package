/*************************************************** 
  This is a code example for the SHARP GP2Y1051 Dust Sensor.

  VCC(RED)    -->  arduino 5V
  GND(Black)  -->  arduino GND
  TX(White)  -->  10

  The sensor's baud rate is 2400bps.
  
****************************************************/
#include <SoftwareSerial.h>
#define RX 10
#define TX 11

SoftwareSerial mySerial(RX, TX);

int getSerial() {
    while (!mySerial.available()) {}
    return mySerial.read();
}

void setup() {
    Serial.begin(9600);
    mySerial.begin(2400);
    
    // Wait a second for startup.
    delay(1000);
}

void loop() {
    static int frame[7];
    static int dataStart, VoutH, VoutL, VrefH, VrefL, checksum, dataEnd;
    // Look for end of frame.
    if ( getSerial() != 0xff ) { return; }
    // Read in next frame.
    for(int i = 0; i < 7; i++) {
        frame[i] = getSerial();
    }
    
    // Assign values.
    dataStart = frame[0];
    VoutH = frame[1];
    VoutL = frame[2];
    VrefH = frame[3];
    VrefL = frame[4];
    checksum = frame[5];
    dataEnd = frame[6];

    // Check the start and end of frame.
    if ( dataStart != 0xaa || dataEnd != 0xff ) { return; }

    // Verify the checksum.
    int testSum = VoutH + VoutL + VrefH + VrefL;
    if ( testSum != checksum ) { return; }

    // Calculate Vout.
    float Vout = (VoutH * 256 + VoutL) / 1024.0 * 5.0;
    
    // Calculate "a" coefficient beforehand by using a reference dust monitor.
    // The coefficient will be different depending on the reference dust monitor used
    // and your specific application conditions. Linear adjustment might be needed for 
    // different usage environment.
    float a = 100 / 0.35;

    // Calculate dust density.
    float dustDensity = a * Vout;
//    Serial.print("dustDensity=");
    Serial.print(dustDensity);
//    Serial.print("ug/m3");
    Serial.println("");
    delay(100);
}
// END PROGRAM
