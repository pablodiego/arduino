#include "libraries/EEPROM/arduino_EEPROM.h"
#include <stdio.h>

#define SIZE 255

int setup()
{
	int eeprom[SIZE+1];
	int addr = 0;
	
	while (addr< SIZE)
	{
		EEPROM_write(eeprom, addr, SIZE, SIZE);
	}
}

void loop(){}

int main()
{
	int addr =0;
	setup();
	while (addr < SIZE);
	loop();
}

