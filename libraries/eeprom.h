#ifndef EEPROM_H

#define EEPROM_H

class EEPROM {

	public:

    static int write(int address, int value)
    {
      __ESBMC_assert(address < 255, "Address must be greater than 0 and less than 255") ;
      __ESBMC_assert(value <= 255, "Value must be greater than 0 and less than 255");
      return memory[address] = value;
    }

    static int read (int address)
    {
      __ESBMC_assert(address < 255, "Address must be greater than 0 and less than 255");
      return memory[address];
    }

    static int update(int address, int value)
    {
      __ESBMC_assert(address != value, "Address must be already initialized");
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
