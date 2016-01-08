#inclue <iostream>

class EEPROM {
	public: 
		int address, value, size;
		std::vector<int> byte;

		int EEPROM_write( *byte,address, size, value)
		{
			__ESBMC_assert (address < size);
			__ESBMC_assert (value <= 255);
			return byte[address] = value;
		}	

		int EEPROM_read (*byte, address, value, size)
		{
			__ESBMC_assert (address,value);
			return byte[address];
		}

		int EEPROM_update(*byte, address, value, size)
		{
			__ESBMC_assert(address != value) ;
			return byte[address];
		}

}
