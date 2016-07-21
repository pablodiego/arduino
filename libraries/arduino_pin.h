#ifndef ARDUINO_PIN_H
#define ARDUINO_PIN_H

namespace pin_mode
{
    const unsigned int input = 0;
    const unsigned int output = 1;
    const unsigned int undefined = 2;
}

const unsigned int INPUT = 0;
const unsigned int OUTPUT = 1;
const unsigned int LOW = 0;
const unsigned int HIGH = 1;
const unsigned int ANALOG_MIN_VALUE = 0;
const unsigned int ANALOG_MAX_VALUE = 255;

class arduino_pin {
public:
    arduino_pin()
    {
        m_mode = pin_mode::undefined;
        m_value = 0;
    };

    ~arduino_pin() { };

    void set_mode(const int& mode)
    {
        m_mode = mode;
    }

    void set_value(const int& value)
    {
        m_value = value;
    }

    inline const unsigned int mode() const
    {
        return m_mode;
    }

    inline const unsigned int value() const
    {
        return m_value;
    }

private:
    unsigned int m_mode;
    unsigned int m_value;
};

#endif
