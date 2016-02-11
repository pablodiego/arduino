#ifndef EEPROM_H

#define EEPROM_H
#define BOUNDS 2


class EEPROM {

	public:

		static int* byte;

		static int write(int address, int value)
		{
			__ESBMC_assert ((address < 255), " teste") ;
			__ESBMC_assert ((value <= 255), " teste2");
			return byte[address] = value;
		}	

		static int read (int address)
		{
			__ESBMC_assert ((address<255), " teste3");
			return byte[address];
		}

		static int update(int address, int value)
		{
			__ESBMC_assert ((address != value), " teste4") ;
			return byte[address];
		}
};

#endif