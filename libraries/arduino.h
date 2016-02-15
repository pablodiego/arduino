#ifndef ARDUINO_H
#define ARDUINO_H

#define LOW 0
#define HIGH 1

#define INPUT 0
#define OUTPUT 1

#define BOUNDS 2

#include <vector>

class ArduinoPin {
public:

  ArduinoPin() { };

  ~ArduinoPin() { };

  void set_pin(int pin)
  {
    this->pin = pin;
  }

  void set_mode(int mode)
  {
    this->mode = mode;
  }

  void set_state(int current_state)
  {
    this->current_state = current_state;
  }

  int& get_pin()
  {
    return pin;
  }

  int& get_mode()
  {
    return mode;
  }

  int& get_state()
  {
    return current_state;
  }

private:

  int pin;

  int mode;

  int current_state;

};

const int number_of_pins = 1;

ArduinoPin * pin_array = new ArduinoPin[number_of_pins];

int current_size = 0;

int pinMode (int pin, int mode)
{
  pin_array[current_size].set_pin(pin);
  pin_array[current_size].set_mode(mode);
  pin_array[current_size].set_state(LOW);
  current_size++;
}

int digitalWrite(int pin, int state)
{
  int j = -1;
  for (int i = 0; i < current_size; i++) {
    if (pin_array[i].get_pin() == pin) {
      j = i;
    }
  }

  __ESBMC_assert(j != -1, "Pin has not been initialized previously");
  int pin_mode = pin_array[j].get_mode();
  __ESBMC_assert(pin_mode == OUTPUT, "Pin has not been set to OUTPUT mode");
  pin_array[j].set_state(state);
}

int digitalRead(int pin)
{
  int j = -1;
  for (int i = 0; i < current_size; i++) {
    if (pin_array[i].get_pin() == pin) {
      j = i;
    }
  }

  int current_state = pin_array[j].get_state();
  __ESBMC_assume(current_state ==  LOW || current_state == HIGH);
  pin_array[j].set_state(current_state);
  return current_state;
}

int analogRead(int pin)
{
  __ESBMC_assume(pin >= 0 && pin <= 1023);
  return pin;
}

int analogWrite(int pin, int value)
{
  int rvalue;
  rvalue = value;
  __ESBMC_assert(rvalue >= 0 && rvalue <= 255, "Value must be from 0 to 255" );
}

void delay(long time)
{
  __ESBMC_assert(time > 0, "Time must be greater than zero");
}

long millis()
{
  long time;
  __ESBMC_assume(time > 0);
  return time;
}

int searchPin (int pin)
{
  //for (int i =0; i <= kMemorySize , i++) vPin.push_back(i);
}

#endif
