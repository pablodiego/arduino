#ifndef EEPROM_H

#define EEPROM_H

class EEPROM {

		public:
        
        int EEPROM_write(int *byte, int address, int size, int value)
		{
			__ESBMC_assert ((address < size), " teste") ;
			__ESBMC_assert ((value <= 255), " teste2");
			return byte[address] = value;
		}	

		int EEPROM_read (int *byte, int address, int size, int value)
		{
			__ESBMC_assert ((address,value), " teste3");
			return byte[address];
		}

		int EEPROM_update(int *byte, int address, int size, int value)
		{
			__ESBMC_assert ((address != value), " teste4") ;
			return byte[address];
		}
};

#endif
