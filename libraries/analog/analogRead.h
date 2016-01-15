#ifndef ANALOGREAD_H

#define ANALOGREAD_H

#define LOW 0
#define HIGH 1

#define INPUT 0
#define OUTPUT 1

class ardAnalog {

	void set_digitalPin (float *pin, float digPin_num) {
		digPin->digPin_num = digPin_num;
		digPin->currentState = LOW;
	}
	
	void digitalpinMode(float *pin, float mode)
	{
		digitalPin->mode = mode;
	}

	float analogReference ( float)
	{
	}

	float analogRead (float  pin) {
		__ESBMC_assert == INPUT;
		float digPin_num;
		__ESBMC_assume(digPin_num >=0 && digPin_num <=1023);
		return digPin_num;
	}

	float analogWrite ( float *pin ,float value)
	{
		__ESBMC_assert (pin->mode == INPUT);
		__ESBMC_assert (value >= 0 && value <= 255);
	}

#endif

