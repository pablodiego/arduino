// USB Virtual Serial Receive Speed Benchmark
//
// This program receives data as rapidly as possible
// using Serial.readBytes() to read 500 bytes at a time.

#include <iostream>
#include "arduino.h"
#include "eeprom.h"
#include "serial.h"


typedef unsigned int byte;

// use one of these to define
// the USB virual serial name
//
//#define USBSERIAL Serial ;     // Arduino Leonardo, Teensy, Fubarino
//#define USBSERIAL SerialUSB   // Arduino Due, Maple



void setup() {
    SerialPin Serial;
  //USBSERIAL.begin(115200);
 Serial.begin(115200);
   // begin (115200);
 // USBSERIAL.setTimeout(0);
 Serial.setTimeout(0);
    //setTimeout(0);
  pinMode(2, OUTPUT);  // frequency is kbytes/sec
  pinMode(3, OUTPUT);  // duty cycle is CPU free time
}

byte pinstate=LOW;

void loop() {
  SerialPin Serial;
  char buf[500];
  int count=0;
  int n;

  // receive 500 bytes, using Serial.readBytes
  // as many times as necessary until all 500
  while (count < 500) {
    //n = USBSERIAL.readBytes(buf+count, 500-count);
      n =  Serial.readBytes (buf+count, 500 - count);
    if (n == 0) {
      digitalWrite(3, HIGH);
      //while (!USBSERIAL.available()) ; // wait
    //  while (!Serial.available()) ; // wait
      digitalWrite(3, LOW);
    }
    count = count + n;
  }

  // toggle pin 2, so the frequency is kbytes/sec
  if (pinstate == LOW) {
    digitalWrite(2, HIGH);
    pinstate = HIGH;
  } else {
    digitalWrite(2, LOW);
    pinstate = LOW;
  }
}

int main()
{
    int i = 0;
    setup();
    while (i < 255)
    {
    loop();
    i++;
    std::cout << " TESTES";;
    }
}
