#include <iostream>
#include "libraries/EEPROM/arduino_EEPROM.h"

#define SIZE 255

int setup()
{
	int eeprom[SIZE+1];
	int addr = 0;

    EEPROM tes;
	
	while(addr < SIZE)
	{
		tes.EEPROM_write(eeprom, addr, SIZE, SIZE);
       
	}
}

int loop(){}

int main()
{
	int addr =0;
	setup();
	while (addr < SIZE);
	loop();
}
