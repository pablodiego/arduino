#include <EEPROM.h>

void setup()
{
	for(i=0 i < 255; i++)
		EEPROM.write(i,i);
}

void loop()
 {
}

