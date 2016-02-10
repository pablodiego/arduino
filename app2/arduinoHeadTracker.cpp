#include <math.h>
#include <string.h>
#include <eeprom.h>
#include <arduino.h>
#include <cmath>

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
float rate = 0, rateold = 0, angle = 0, Azi = 0, Ele = 0, Roll = 0, AziOld = 0, EleOld = 0, RollOld = 0;
char tempc[10], printStr[50];



void A2Ddata(unsigned int n) {
 long tempG = 0, tempX = 0, tempY = 0, tempZ = 0;

 for(unsigned int k = 1; k <= n; k++){
   tempG += analogRead(gPin);  
   tempX += analogRead(xAccePin);
   tempY += analogRead(yAccePin);
   tempZ += analogRead(zAccePin);
   //delayMicroseconds(10);
 }
 gRaw = tempG*10/n;
 xRaw = tempX*10/n-xOffset;
 yRaw = tempY*10/n-yOffset;
 zRaw = tempZ*10/n-zOffset;
}


void setup() {
 pinMode(ledPin, OUTPUT);  
 pinMode(rledPin, OUTPUT);
// Serial.begin(38400);        

 //analogReference(EXTERNAL);
 digitalWrite(rledPin,HIGH);
 delay(1000);
 //Find Gyro rate offset
 A2Ddata(10000);
 gOffset = gRaw*Vin/100;
 printStr[0]= '\0';
 digitalWrite(rledPin,LOW);
}



void loop() {

 if (millis()-timeold_fast > 10) {
   timeold_fast = millis();
   A2Ddata(8);

   //Calculate gyro turn rate
   rate = (gRaw*Vin/100-gOffset)*0.0150;

 //  if (abs(rate) > 2.5) {
   //  angle += (rateold+rate)*0.010;  //trapz intergration
   //}
   rateold = rate;

   //Calculate elevation and roll angles
 //  Ele = (atan2(zRaw,xRaw)*57.296-90+EleOld)/2;
   //gRoll = (atan2(zRaw,yRaw)*57.296-90+RollOld)/2;

 }

 if (millis()-timeold_med > 50) {
   timeold_med = millis();
   // hysterisis dead band
   if (abs(Ele - EleOld) > 0.5) {
     EleOld = Ele;
   }
   else {
     Ele = EleOld;
   }

   if (abs(Roll - RollOld) > 0.5) {
     RollOld = Roll;
   }
   else {
     Roll = RollOld;
   }
   
// reset yaw angle to 0 when head is lowered > 60 degrees
   if (Ele < -60) {
     angle = 0;
   }
 
/*
// code to reduce gyro drift under steady conditions
   if (rate < 5) {
     if (rate > 0) {
       gOffset++;
     }
     else{
       gOffset--;
     }
   }
*/
   digitalWrite(ledPin, HIGH);

  /* strcat(printStr,floatToString(tempc,rate,2,6,false));
   strcat(printStr,",");
   strcat(printStr,floatToString(tempc,Ele,3,6,false));
   strcat(printStr,",");
   strcat(printStr,floatToString(tempc,Roll,3,6,false));
   strcat(printStr,",");
   strcat(printStr,floatToString(tempc,angle,3,6,false));
   Serial.println(printStr); */

   printStr[0] = '\0';
   /*
   Serial.print(floatToString(tempc,rate,2,6,false));
    Serial.print(',');
    //Serial.println(floatToString(tempc,angle,2,6,false));  
    Serial.print(floatToString(tempc,Ele,2,6,false));
    Serial.print(',');
    Serial.print(floatToString(tempc,Roll,2,6,false));
    Serial.print(',');
    Serial.println(floatToString(tempc,angle,2,6,false));
    */
   digitalWrite(ledPin, LOW);  
 }

}

int main (){
	
	int lim =0;
	setup();
	while(lim < BOUNDS);
	loop();
}