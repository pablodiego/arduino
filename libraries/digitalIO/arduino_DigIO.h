#ifndef DIGITALIO_H

#define ARDUINO_H

#define LOW 0
#define HIGH 1

#define BOUND 100


class ardDigitalIO {
   
   public:

    int mode;
    int cur_state;
    int state;

	int set_pin(int *pin, int pin_num)
	{	
		pin[pin_num] = pin_num;
		pin[state] = LOW;
	}

	int pinMode(int *pin, int mode)
	{
		pin[mode] = mode;
	}

	int digitalWrite(int *pin, int state)
	{
		__ESBMC_assert(pin[mode] == OUTPUT, "Error");
		pin[cur_state] = state;
	}

	int digitalRead(int *pin)
	{
		__ESBMC_assert(pin[mode] == INPUT, "Error"  );
		int value;
		__ESBMC_assume (value ==  LOW || value == HIGH);
		return value;	
	}
};

#endif
