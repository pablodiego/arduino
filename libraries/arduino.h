#ifndef ARDUINO_H

#define ARDUINO_H

#define LOW 0
#define HIGH 1

#define INPUT 0
#define OUTPUT 1

#define BOUNDS 2

class ArduinoPin{
public:

int numPin[] ={ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0 };

int current_state;
int mode;

	
	ArduinoPin(int numPin){
		numPin = numPin;
	}


	void setMode (int mode){
		mode = mode;
	}

	void setState (int state){
		current_state = state;
	}
};


int pinMode (int pin, int mode){
		ArduinoPin numPin(pin);
		numPin.setMode(mode);
	}


int digitalWrite (int pin, int state)
{
	int cur_state;
	int mode;
	int* numPin;
	
	__ESBMC_assert(numPin[mode] == OUTPUT, "Error");
	numPin[cur_state] = LOW;
}

int digitalRead (int pin)
{
	int mode;
	int* numPin;
	
	__ESBMC_assert(numPin[mode] == INPUT, "Error"  );
	int value;
	__ESBMC_assume (value ==  LOW || value == HIGH);
	return value;
}

int analogRead (int pin)
{
	int numPin;
	__ESBMC_assume(numPin >=0 && numPin <=1023);
	return numPin;
}

int analogWrite (int numPin, int  value)
{
	__ESBMC_assert (value >= 0 && value <= 255, "Error" );
}

long delay(long time)
{
	long time;
	__ESBMC_assume (time > 0);
}

long millis()
{
	long time;
	__ESBMC_assume (time > 0);
	return time;
}

#endif
