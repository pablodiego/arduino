#include <iostream>
#include <eeprom.h> 

#define SIZE 255

/*int setup()
{
	int eeprom[SIZE+1];
	int addr = 0;

    EEPROM tes;
	
	while(addr < SIZE)
	{
		tes.EEPROM_write(eeprom, addr, SIZE, SIZE);
       
	}
}*/

void setup()
{
	for (int i=0; i < 255; i++)
		EEPROM.write (i,i);
}

void loop(){}

int main()
{
	int addr =0;
	setup();
	while (addr++ < BOUNDS)
	loop();
}
