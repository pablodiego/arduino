#ifndef TIME_H

#define TIME_H

class ardTime{

	long ardMillis(){
		long time;
		__ESBMC_assume(time >= 0 );
		return time;
	}

	long ardMicros(){
		long time;
		__ESBMC_assum (time >= 0 );
		return time;
	}

	long ardDelay(){
		long time;
		__ESBMC_assume (time >= 0 );
		return;
	}

	long ardDelayMicroSec(){
		long time;
		__ESBMC_assume (time >= 0 );
		return;
	}
};

#endif
