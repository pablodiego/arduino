#ifndef EEPROM_H

#define EEPROM_H

class EEPROM {

	public:

		static int write(int address, int value)
		{
			__ESBMC_assert ((address < 255), " teste") ;
			__ESBMC_assert ((value <= 255), " teste2");
			return memory[address] = value;
		}	

		static int read (int address)
		{
			__ESBMC_assert ((address<255), " teste3");
			return memory[address];
		}

		static int update(int address, int value)
		{
			__ESBMC_assert ((address != value), " teste4") ;
			return memory[address];
		}

	private:
		static const int kMemorySize = 255;
		static int memory[kMemorySize];


};

int EEPROM::memory[EEPROM::kMemorySize] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};



#endif
