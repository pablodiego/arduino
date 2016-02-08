#ifndef ARDUINO_H

#define ARDUINO_H

#define LOW 0
#define HIGH 1

#define INPUT 0
#define OUTPUT 1

#define BOUNDS 2

class ArduinoPin{
public:

int numPin;
int current_state;
int mode;

	
	ArduinoPin(int numPin){
		numPin = numPin;
	}


	void setMode (int mode){
		mode = mode;
	}

	void setState (int state){
		state = state;
	}
};


int pinMode (int pin, int mode){
		ArduinoPin pin(pin);
		pin.setMode(mode);
	}


int digitalWrite (int pin, int state)
{
	__ESBMC_assert(pin[mode] == OUTPUT, "Error");
	pin[cur_state] = LOW;
}

int digitalRead (int pin)
{
	__ESBMC_assert(pin[mode] == INPUT, "Error"  );
	int value;
	__ESBMC_assume (value ==  LOW || value == HIGH);
	return value;
}

int analogRead (int pin)
{
	__ESBMC_assume(digPin_num >=0 && digPin_num <=1023);
	return pin;
}

int analogWrite (int* digPin, int  value)
{
	__ESBMC_assert (value >= 0 && value <= 255, "Error" );
}

#endif
