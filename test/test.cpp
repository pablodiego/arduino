#include <arduino.h>
#include <arduino_bounded_model_checking.h>

#define PIN 15

void setup()
{
    pinMode(PIN, OUTPUT);
}

void loop()
{
    digitalWrite(PIN, HIGH);
    delay(1000);
    digitalWrite(PIN, LOW);
    delay(1000);
}

int main(void)
{
    unsigned int i = 0;
    setup();
    while (i++ <= bmc::bounds)
        loop();
    return 0;
}
