#ifndef SERIAL_H
#define SERIAL_H

#include <iostream>
#include <arduino.h>


class SerialPin {

public:
   // Serial () { }
    //~Serial () { }

    void begin(long begin)
    {
         std::cout << " Begin";
        long _begin =  begin;
        __ESBMC_assume ( _begin > 0);
    }

    void setTimeout(long timeout)
    {
         std::cout << " Timeout";
        long _timeout =  timeout;
        __ESBMC_assume (_timeout > 0);
    }

    int readBytes(char* buffer, int lenght)
    {
         std::cout << " readBytes";

        char* _buffer = buffer ;
        int _lenght = lenght;

        __ESBMC_assert ( _buffer > 0, " ERROR ");
        __ESBMC_assert ( _lenght > 0, " ERROR ");

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
