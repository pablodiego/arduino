#ifndef ARDUINO_H

#define ARDUINO_H

#define LOW 0
#define HIGH 1

#define INPUT 0
#define OUTPUT 1

#define BOUNDS 2
#define kMemorySize 255

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class ArduinoPin{

public:
	
	int rpin;
	int mode;
	int current_state;

	ArduinoPin(){}

	void setPin(int pin){
		this->pin = pin;
	}

	void setMode (int mode){
		mode = mode;
	}

	void setState (int state){
		current_state = state;
	}

	int& getPin(){
		return pin;
	}

	int& getMode(){
		return mode;
	}

	int& getState(){
		return current_state;
	}

private:
	int pin;
};


ArduinoPin *vPin = new ArduinoPin[1];
int size =0;


int pinMode (int pin, int mode){

	vPin[size].setPin(pin);
	vPin[size].setMode(mode);
	vPin[size].setState(LOW);
	size++;

	}

int digitalWrite (int pin, int state)
{

	int j= -1;

	for (int i=0; i < size; i++){
		if (vPin[i].getPin() == pin){
			j = i;
		}
	} 
	
	__ESBMC_assert(j != -1, "Error Cabuloso");
	int uPin = vPin[j].getMode();
	__ESBMC_assert(uPin == OUTPUT, "Error");
	vPin[j].setState(state);
}

int digitalRead (int pin)
{
	
	int j= -1;

	for (int i=0; i < size; i++){
		if (vPin[i].getPin() == pin){
			j = i;
		}
	}

	int uPin = vPin[j].getState();

	__ESBMC_assume( uPin ==  LOW || uPin == HIGH);
	return uPin;
}

int analogRead (int pin)
{
	__ESBMC_assume(pin >=0 && pin <=1023);
	return pin;
}

int analogWrite (int pin, int value)
{
	int rvalue;
	rvalue = value;
	__ESBMC_assert (rvalue >= 0 && rvalue <= 255, "Error" );
}

void delay(long time)
{
	
	__ESBMC_assert (time > 0, " Error");
}

long millis()
{
	long time;
	__ESBMC_assume (time > 0);
	return time;
}

int searchPin (int pin){

	//for (int i =0; i <= kMemorySize , i++) vPin.push_back(i);
}

#endif
