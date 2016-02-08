#ifndef DIGITALIO_H

#define ARDUINO_H

#define LOW 0
#define HIGH 1
#define OUTPUT 0
#define INPUT 1

#define BOUND 100


class ardDigitalIO {
   
   public:

	void set_pin(int *pin, int pin_num)
	{
        int state;

		pin[pin_num] = pin_num;
		pin[state] = LOW;
	}

	int pinMode(int *pin, int mode)
	{
		int status;
        pin[status] = status;
	}

	int digitalWrite(int *pin, int state)
	{
        int cur_state;
        int mode;

		__ESBMC_assert(pin[mode] == OUTPUT, "Error");
		pin[cur_state] = state;
	}

	int digitalRead(int *pin)
	{
        int mode;
		__ESBMC_assert(pin[mode] == INPUT, "Error"  );
		int value;
		__ESBMC_assume (value ==  LOW || value == HIGH);
		return value;	
	}
};

#endif
