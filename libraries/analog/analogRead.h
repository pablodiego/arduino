#ifndef ANALOGREAD_H

#define ANALOGREAD_H

#define LOW 0
#define HIGH 1

#define INPUT 0
#define OUTPUT 1

class ardAnalog {
    public:

	void set_digitalPin (float *digPin, int digPin_num) {
		digPin[digPin_num] = digPin_num;
	}

	float analogReference ( float value)
	{
        __ESBMC_assert (value >=0 && value <= 5);
	}

	float analogRead (float  digPin) {
		float digPin_num;
		__ESBMC_assume(digPin_num >=0 && digPin_num <=1023);
		return digPin_num;
	}

	float analogWrite ( float* digPin ,float value)
	{
		__ESBMC_assert (value >= 0 && value <= 255, "Error" );
	}
};
#endif

