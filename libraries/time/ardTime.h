#ifndef TIME_H

#define TIME_H

class ardTime{
    public:

	long int millis ){
		long time;
		__ESBMC_assume(time >= 0 );
		return time;
	}

	long int micros(){
		long time;
		__ESBMC_assume (time >= 0 );
		return time;
	}

	long int delay(int y ){
		long time;
		__ESBMC_assume (time >= 0 );
		return 0;
	}

	long int delayMicroSec(){
		long time;
		__ESBMC_assume (time >= 0 );
		return 0;
	}
};

#endif
