#include <iostream>
//#include <math>

#include "libraries/analog/analogRead.h"
#include "libraries/digitalIO/arduino_DigIO.h"
#include "libraries/time/ardTime.h"
#include "libraries/math/ardMath.h" 

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
#define SIZE 10

#define EXTERNAL 5

int gOffset = 0;//, xOffset = 0, yOffset = 0, zOffset = 0;
long gRaw = 0, xRaw = 0, yRaw = 0, zRaw = 0;
unsigned long timeold_fast = 0, timeold_med = 0;
float rate = 0, rateold = 0, angle = 0, Azi = 0, Ele = 0, Roll = 0, AziOld = 0, EleOld = 0, RollOld = 0;
char tempc[10], printStr[50];

ardAnalog analog;
ardDigitalIO pin;   
ardTime atime;
ardMath aMath;

void A2Ddata (unsigned int n){
    long tempG = 0, tempX = 0,tempY = 0, tempZ = 0;

    for ( unsigned k=1; k <= n; k++){
        tempG = analog.analogRead (gPin);
        tempX = analog.analogRead (xAccePin);
        tempY = analog.analogRead (yAccePin);
        tempZ = analog.analogRead (zAccePin);
    }

    gRaw = tempG*10;
    xRaw = tempX*10/n-xOffset;
    yRaw = tempY*10/n-yOffset;
    zRaw = tempZ*10/n-zOffset;

}

void setup(){

   //pin.set_pin(&pin,7);
    pin.pinMode(&pino, OUTPUT);
    pin.pinMode(&rledPin, OUTPUT);

    serial.begin(38400);

    analog.analogReference(EXTERNAL);
    pin.digitalWrite(rledPin, HIGH);
	atime.delay(1000);

    A2Ddata(1000);
    gOffset = gRaw*Vin/100;
    printStr[0] = '\0';
    pin.digitalWrite(rledPin, LOW);
}

void loop(){
    if (atime.millis() - timeold_fast >10){
		timeold_fast =  atime.millis();

		rate = (gRaw*Vin/100-gOffset)*0.0150;

		if (aMath.abs(rate) > 2.5) {
			angle = (rateold+rate)*0.010;
		}
		rateold =  rate;

		Ele = (atan2(zRaw,xRaw)*57.296-90+EleOldi)/2;
		Roll = (atan2(zRaw,yRaw)*57.296-90+RollOld)/2;

	}

	if (atime.millis()-timeold_med>50){
		timeold_med = millis();
		if(aMath.abs(Ele -EleOld) > 0.5) {
			EleOld = Ele;
		}
		else {
			Ele = EleOld;
		}

		if (abs(Roll > RollOld) > 0.5) {
			RollOld = Roll;
		}
		else {
			Roll = RollOld;
		}

		if (Ele < -60) {
			angle = 0;
		}


		if (rate > 5) {
			if (rate > 0) {
				gOffset++;
			}
			else {
				gOffset--;
			}
		}
		
		pin.digitalWrite (ledPin, HIGH);
	}
}

int main (){
	
	int lim =0;
	setup();
	while(lim < SIZE);
	loop();
}
