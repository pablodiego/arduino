#include <iostream>
#include <math>

#include "libraries/analogRead/analogRead.h"i
#include "libraries/digitalIO/arduino_DigIO.h"

#define gPin 0    
#define xAccePin 1
#define yAccePin 2
#define zAccePin 3
#define ledPin 7  
#define rledPin 7  
#define Vin 322
#define xOffset 5081
#define yOffset 5080
#define zOffset 5517

int gOffset = 0;//, xOffset = 0, yOffset = 0, zOffset = 0;
long gRaw = 0, xRaw = 0, yRaw = 0, zRaw = 0;
unsigned long timeold_fast = 0, timeold_med = 0;
float rate = 0, rateold = 0, angle = 0, Azi = 0, Ele = 0, Roll = 0, AziOld = 0, EleOld = 0, R    ollOld = 0;
char tempc[10], printStr[50];

analogRead arduino;
arduinoPin pin;   

void A2Ddata (unsigned int n){
    long tempG = 0, tempY = 0, tempZ = 0;

    for ( unsigned k=1; k <= n; k++){
        tempG = arduino.analogRead (gPin);
        tempX = arduino.analogRead (xAccept);
        tempY = arduino.analogRead (yAccept);
        tempZ = arduino.analogRead (zAccept);
    }

    gRaw = tempG*10;
    xRaw = tempX*10/n-xOffset;
    yRaw = tempY*10/n-yOffset;
    zRaw = tempZ*10/n-zOffset;

}

void setup(){
    pin.pinMode(ledPin, OUTPUT);
    pin.pinMode(rledPin, OUTPUT);

    serial.begin(38400);

    arduino.analogReference(EXTERNAL);
    pin.digitalWrite(rledPin, HIGH);
    delay(1000);

    A2Ddata(1000);
    gOffset = gRaw*Vin/100;
    printStr[0] = '\0';
    pin.digitalWrite(rledPin, LOW);
}

void loop(){
    if (mi
