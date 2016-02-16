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

  void set_value(int value)
  {
    this->value = value;
  }

  int get_pin()
  {
    return pin;
  }

  int get_mode()
  {
    return mode;
  }

  int get_value()
  {
    return value;
  }

private:

  int pin;

  int mode;

  int value;

};

const int number_of_pins = 16;

ArduinoPin * pin_array = new ArduinoPin[number_of_pins];

int current_size = 0;

int pinMode (int pin, int mode)
{
  pin_array[pin].set_pin(pin);
  pin_array[pin].set_mode(mode);
  pin_array[pin].set_value(LOW);

}

int digitalWrite(int pin, int value)
{

  __ESBMC_assert(pin != -1, "Pin has not been initialized previously");
  int pin_mode = pin_array[pin].get_mode();
  __ESBMC_assert(pin_mode == OUTPUT, "Pin has not been set to OUTPUT mode");
  pin_array[pin].set_value(value);
}

int digitalRead(int pin)
{

  int current_state = pin_array[pin].get_value();
  __ESBMC_assume(current_state ==  LOW || current_state == HIGH);
  pin_array[pin].set_value(current_state);
  return current_state;
}

int analogRead(int pin)
{
    int value_pin;
  __ESBMC_assume(value_pin >= 0 && value_pin <= 1023);
  return pin;
}

int analogWrite(int pin, int value)
{
    int analog_value = pin_array[pin].get_value();
  __ESBMC_assert(analog_value >= 0 && analog_value <= 255, "Value must be from 0 to 255" );
  pin_array[pin].set_value(analog_value);
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

#endif
