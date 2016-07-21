#ifndef ARDUINO_H
#define ARDUINO_H

#include "arduino_board.h"

static arduino_board board;

int pinMode(int pin, int mode)
{
    board.pin_mode(pin, mode);
}

int digitalWrite(int pin, int value)
{
    board.digital_write(pin, value);
}

int digitalRead(int pin)
{
    return board.digital_read(pin);
}

int analogRead(int pin)
{
    return board.analog_read(pin);
}

int analogWrite(int pin, int value)
{
    board.analog_write(pin, value);
}

void delay(unsigned long ms)
{
    __ESBMC_assert(ms > 0, "Time must be greater than zero");
}

unsigned long millis()
{
    return board.millis();
}

#endif
