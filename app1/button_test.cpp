#include <iostream>
#include "../libraries/arduino.h"
#include "../libraries/eeprom.h"

// For 2x4 button pad. Prints message and toggles door lock on each press.
// Set your serial console to 19200
// Written by Will O'Brien, based on various others works.

using namespace std;
#define ROWS 2
#define COLS 4
#define OUTPUT 0
#define INPUT 1
#define LOW 0
#define HIGH 1

ArduinoPin digital;
SerialPin Serial;

typedef unsigned int byte;


extern void lock();
extern void set_lock();
extern void unlock();

int buttonWrite[2] = {2, 3}; //Pins for the Vin of the buttons
int buttonRead[4] = {6, 7, 8, 9}; //Pins for reading the state of the buttons
bool pressed[ROWS][COLS] = {  0};
int* lock_pin ;
bool lockState = 0;

int* pl = buttonWrite;
int* pl2 = buttonRead;

void setup(){
  Serial.begin(19200);
  digital.set_pin(lock_pin,6);
  digital.pinMode(lock_pin, OUTPUT);
  digital.digitalWrite(lock_pin, LOW);

for (int* pl = buttonWrite; *pl!=0; pl++){
    digital.pinMode(pl, OUTPUT);
    digital.digitalWrite(pl, LOW);
}


//setup the button inputs and outputs
 /* for(int i = 0; i < ROWS; ++i){ // ???? Is ROWS the right quanitity here?
    pinMode(buttonWrite[i], OUTPUT);
    digitalWrite(buttonWrite[i],LOW);
  }
  for(int j = 0; j<COLS; ++j) {
    pinMode(buttonRead[j], INPUT);
  }*/
}



void loop(){
/*  //Serial.print(".");
  for(unsigned char r = 0; r < ROWS; ++r){
    digitalWrite(buttonWrite[r], HIGH);
    for(unsigned char  c = 0; c < COLS; ++c){
      if(pressed[r][c] != digitalRead(buttonRead[c])){
        pressed[r][c] = digitalRead(buttonRead[c]);
>>>>>>>  some changes
        if(pressed[r][c]){
          on_press(r, c);
        } 
      } 
    }
    aTime.delay(5);
    digitalWrite(&buttonWrite[r], LOW);
  }
 aTime. delay(10);*/
}

void on_press(unsigned char r,  unsigned char c){
 //Serial.print(r, DEC);
 // Serial.print(", ");
 // Serial.println(c, DEC);
  set_lock();
}

void set_lock(){
 if(lockState){
   unlock(); 
 }
  else
   lock(); 
}

void unlock(){
 // Serial.print("Unlock door");
  digitalWrite(lock_pin, HIGH);
  lockState = !lockState;
}

void lock(){
 // Serial.print("Lock door");
  digitalWrite(lock_pin, LOW);
  lockState = !lockState;
}

int main()
{
    int i;
    setup();
    while (i <255);
    loop();
}
