#ifndef SERIAL_H
#define SERIAL_H

#include <iostream>


class SerialPin {

public:
   // Serial () { }
    //~Serial () { }

    void begin(long begin)
    {

        __ESBMC_assume ( begin > 0);
    }

    void setTimeout(long timeout)
    {

        __ESBMC_assume (timeout > 0);
    }

    int readBytes(char* buffer, int lenght)
    {

        char* buffer = buffer ;
        int lenght = lenght;

        __ESBMC_assert ( buffer > 0, " ERROR ");
        __ESBMC_assert ( lenght > 0, " ERROR ");

        return lenght;
    }

    int available ()
    {
        int value;
        __ESBMC_assume ( value > 0);
        return value;
    }
};

#endif // SERIAL_H
