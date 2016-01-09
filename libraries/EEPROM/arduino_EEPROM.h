#ifndef EEPROM_H

#define EEPROM_H

class EEPROM {
	

		int EEPROM_write(int *byte, int address, int size, int value)
		{
			__ESBMC_assert (address < size);
			__ESBMC_assert (value <= 255);
			return byte[address] = value;
		}	

		int EEPROM_read (int *byte, int address, int size, int value)
		{
			__ESBMC_assert (address,value);
			return byte[address];
		}

		int EEPROM_update(int *byte, int address, int size, int value)
		{
			__ESBMC_assert(address != value) ;
			return byte[address];
		}

}

#endif
