#inclue <iostream>

class EEPROM_write {

	int address , value;

	eeprom_arduino.write(address, value);
}

class EEPROM_read {
	int arg;

	eeprom_arduino.read(arg);
}

class EEPROM_update {
	int address, value;

	eeprom_update.update(address, value);
}




