#ifndef ARDUINO_BOARD_H
#define ARDUINO_BOARD_H

#include "arduino_pin.h"

using namespace pin_mode;

class arduino_board
{
public:
    arduino_board() : m_number_of_pins(16), m_previous_ts(0)
    {
    }

    ~arduino_board()
    {
    }

    unsigned int analog_read(const unsigned int& pin)
    {
        __ESBMC_assert(pin > 0 && pin <= m_number_of_pins, "Pin number is not valid");
        __ESBMC_assert(m_pins[pin].mode() != undefined, "Pin has not been initialized previously");
        __ESBMC_assert(m_pins[pin].mode() == input, "Pin has not been set to INPUT mode");
        unsigned int value = m_pins[pin].value();
        __ESBMC_assume(value >= ANALOG_MIN_VALUE && value <= ANALOG_MAX_READ_VALUE);
        m_pins[pin].set_value(value);
        return value;
    }

    void analog_write(const unsigned int& pin, const unsigned int& value)
    {
        __ESBMC_assert(pin > 0 && pin <= m_number_of_pins, "Pin number is not valid");
        __ESBMC_assert(m_pins[pin].mode() != undefined, "Pin has not been initialized previously");
        __ESBMC_assert(m_pins[pin].mode() == output, "Pin has not been set to OUTPUT mode");
        __ESBMC_assert(value >= ANALOG_MIN_VALUE && value <= ANALOG_MAX_WRITE_VALUE, "Value is not analog");
        m_pins[pin].set_value(value);
    }

    unsigned int digital_read(const unsigned int& pin)
    {
        __ESBMC_assert(pin > 0 && pin <= m_number_of_pins, "Pin number is not valid");
        __ESBMC_assert(m_pins[pin].mode() != undefined, "Pin has not been initialized previously");
        __ESBMC_assert(m_pins[pin].mode() == input, "Pin has not been set to INPUT mode");
        unsigned int value = m_pins[pin].value();
        __ESBMC_assume(value == LOW || value == HIGH);
        m_pins[pin].set_value(value);
        return value;
    }

    void digital_write(const unsigned int& pin, const unsigned int& value)
    {
        __ESBMC_assert(pin > 0 && pin <= m_number_of_pins, "Pin number is not valid");
        __ESBMC_assert(m_pins[pin].mode() != undefined, "Pin has not been initialized previously");
        __ESBMC_assert(m_pins[pin].mode() == output, "Pin has not been set to OUTPUT mode");
        __ESBMC_assert(value == LOW || value == HIGH, "Value is not digital");
        m_pins[pin].set_value(value);
    }

    void pin_mode(const unsigned int& pin, const unsigned int& pin_mode)
    {
        __ESBMC_assert(pin > 0 && pin <= m_number_of_pins, "Pin number is not valid");
        m_pins[pin].set_mode(pin_mode);
        m_pins[pin].set_value(0);
    }

    unsigned long millis()
    {
        unsigned long current_ts;
        __ESBMC_assume(current_ts == m_previous_ts);
        m_previous_ts = current_ts;
        return current_ts;
    }

private:
    const int m_number_of_pins;
    arduino_pin m_pins[16];
    unsigned long m_previous_ts;
};

#endif
