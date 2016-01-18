#include <iostream>
#include "../libraries/digitalIO/arduino_DigIO.h"
#include "../libraries/time/ardTime.h"

// For 2x4 button pad. Prints message and toggles door lock on each press.
// Set your serial console to 19200
// Written by Will O'Brien, based on various others works.

using namespace std;
ardDigitalIO digitalIO;
ardTime aTime;

#define ROWS 2
#define COLS 4

int buttonWrite[2] = {2, 3}; //Pins for the Vin of the buttons
int  buttonRead[4] = {6, 7, 8, 9}; //Pins for reading the state of the buttons
bool pressed[ROWS][COLS] = {  0};
int* lock_pin;
bool lockState = 0;


void setup(){
  //Serial.begin(19200);
  digitalIO.pinMode(lock_pin, OUTPUT);
  digitalIO.digitalWrite(lock_pin, LOW);

//setup the button inputs and outputs
  for(int i = 0; i < ROWS; ++i){ // ???? Is ROWS the right quanitity here?
    digitalIO.pinMode(buttonWrite[i], OUTPUT);
    digitalIO.digitalWrite(buttonWrite[i],LOW);
  }
  for(int j = 0; j<COLS; ++j) {
    digitalIO.pinMode(buttonRead[j], INPUT);
  }
}



void loop(){
//  Serial.print(".");
  for(int r = 0; r < ROWS; ++r){

    digitalIO.digitalWrite(buttonWrite[r], HIGH);
    for(int  c = 0; c < COLS; ++c){
      if(pressed[r][c] != digitalIO.digitalRead(*buttonRead[c])){
        pressed[r][c] = digitalIO.digitalRead(*buttonRead[c]);
        if(pressed[r][c]){
          on_press(r, c);
        } 
      } 
    }
    aTime.delay(5);
    digitalIO.digitalWrite(&buttonWrite[r], LOW); 
  }
 aTime. delay(10);
}

void on_press(int r, int c){
 // Serial.print(r, DEC);
 // Serial.print(", ");
  //Serial.println(c, DEC);
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
  digitalIO.digitalWrite(&lock_pin, HIGH);
  lockState = !lockState;
}
void lock(){
 // Serial.print("Lock door");
  digitalIO.digitalWrite(&lock_pin, LOW);
  lockState = !lockState;
}

int main()
{
    int i;
    setup();
    while (i <255);
    loop();
}
