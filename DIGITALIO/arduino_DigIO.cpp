#include <iostream>

class digitalIO {
	
	int	pin_num;
	int state;
	int mode;
	std::vector<int> pin;

	void set_pin(*pin, int pin_num)
	{	
		pin->pin_num = pin_num;
		pin->state = LOW;
	}

	void pinMode(*pin, mode)
	{
		pin->mode = mode;
	}

	void digitalIO_write(*pin, state)
	{
		__ESBMC_assert(pin->mode == OUTPUT);
		pin->cur_state = state;
	}

	int digitalIO_read(*pin)
	{
		__ESBMC_assert(pin.mode == INPUT );
		int value;
		__ESBMC_assume (value ==  LOW || value == HIGH);
		return value;	
	}

