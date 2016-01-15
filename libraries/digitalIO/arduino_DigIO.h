#ifndef DIGITALIO_H

#define ARDUINO_H

#define LOW 0
#define HIGH 1

#define BOUND 100


class ardDigitalIO {

	void set_pin(int *pin, int pin_num)
	{	
		pin->pin_num = pin_num;
		pin->state = LOW;
	}

	void pinMode(int *pin, int mode)
	{
		pin->mode = mode;
	}

	void digitalIO_write(int *pin, int state)
	{
		__ESBMC_assert(pin->mode == OUTPUT);
		pin->cur_state = state;
	}

	int digitalIO_read(int *pin)
	{
		__ESBMC_assert(pin.mode == INPUT );
		int value;
		__ESBMC_assume (value ==  LOW || value == HIGH);
		return value;	
	}
};

#endif
