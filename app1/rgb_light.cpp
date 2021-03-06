// Each button randomly cycles through colors. 
// When a button is pressed, all of the buttons change to that color and pause
// The pressed button(s) is/are lit up white while pressed
// distributed from biboug.org.

#include <iostream>
#include <eeprom.h>
#include <arduino.h>

#define DATAOUT 11//MOSI (pin 7 of AD5206)
#define DATAIN 12//MISO - not used, but part of builtin SPI
#define SPICLOCK  13//sck (pin 8 of AD5206)
#define ROWS 4
#define COLS 4
#define H 254
#define L 64

#define slavesel(x) ((x<6) ? 0 : 1)
//const byte rowpin[ROWS] = {14,15,16,17};
//const byte slaveselect[2] = {10, 18};

int rowpin[ROWS] = {14,15,16,17};
int slaveselect[2] = {10, 18};
// The pot register numbers for each of the red, green, and blue channels
const byte red[4] = {5, 2, 7, 8};
const byte green[4] = {3, 0, 6, 11};
const byte blue[4] = {1, 4, 9, 10};
byte rGrid[ROWS][COLS] = {  0};
byte gGrid[ROWS][COLS] = {  0};
byte bGrid[ROWS][COLS] = {  0};

const byte buttonWrite[4] = {2, 5, 3, 4}; //Pins for the Vin of the buttons
const byte buttonRead[4] = {6, 7, 9, 8}; //Pins for reading the state of the buttons
boolean pressed[ROWS][COLS] = {  0};

byte trajectory[ROWS][COLS] = {  0};
unsigned long time;
#define PAUSE 1000

// END DEFINITIONS, BEGIN PROGRAM

char spi_transfer(volatile char data)
{
  SPDR = data;                    // Start the transmission
  while (!(SPSR & (1<<SPIF)))     // Wait the end of the transmission
  {
  };
  return SPDR;                    // return the received byte
}

byte write_pot(byte address, byte value)
{
  digitalWrite(slaveselect[slavesel(address)], LOW);
  //2 byte opcode
  spi_transfer(address % 6);
  spi_transfer(constrain(255-value,0,255));
  digitalWrite(slaveselect[slavesel(address)], HIGH); //release chip, signal end transfer
}

void setup(){
  randomSeed(1);

  byte i;
  byte clr;
  pinMode(DATAOUT, OUTPUT);
  pinMode(DATAIN, INPUT);
  pinMode(SPICLOCK,OUTPUT);
  pinMode(slaveselect[0],OUTPUT);
  pinMode(slaveselect[1],OUTPUT);

  for(byte r = 0; r < ROWS; ++r){
    pinMode(rowpin[r], OUTPUT); // Initialize rows
    digitalWrite(rowpin[r], LOW); // Turn all rows off
  }

  digitalWrite(slaveselect[0],HIGH); //disable device
  digitalWrite(slaveselect[1],HIGH);
  // SPCR = 01010000
  //interrupt disabled,spi enabled,msb 1st,master,clk low when idle,
  //sample on leading edge of clk,system clock/4 (fastest)
  SPCR = (1<<SPE)|(1<<MSTR);
  clr=SPSR;
  clr=SPDR;
  delay(10);
  // clear all of the pot registers
  for (i=0;i<12;i++)
  {
    write_pot(i,0);
  }

  //setup the button inputs and outputs
  for(int i = 0; i < ROWS; ++i){ // ???? Is ROWS the right quanitity here?
    pinMode(buttonWrite[i], OUTPUT);
    digitalWrite(buttonWrite[i],LOW);
    pinMode(buttonRead[i], INPUT);
  }

  grid_init();

  delay(10);

  time = millis();
}

void loop(){
  always();

  for(byte r = 0; r < 4; ++r){
    digitalWrite(buttonWrite[r], HIGH);
    for(byte c = 0; c < COLS; ++c){

      if(pressed[r][c] != digitalRead(buttonRead[c])){
        pressed[r][c] = digitalRead(buttonRead[c]);
        if(pressed[r][c]){
          on_press(r, c);
        } 
        else {
          on_release(r, c);
        }
      } 
      else {
        if(pressed[r][c]){
          while_pressed(r, c);
        } 
        else {
          while_released(r,c);
        }

      } 
        write_pot(red[c],rGrid[c][r]);
        write_pot(green[c],gGrid[c][r]);
        write_pot(blue[c],bGrid[c][r]);
    }
    digitalWrite(buttonWrite[r], LOW);

    digitalWrite(rowpin[r], HIGH); //turn one row on
    delayMicroseconds(750); // display
    digitalWrite(rowpin[r], LOW); //turn the row back off 
  }
}

void grid_init(){
  grid_rand();
}

void grid_rand(){
   //initialize the button grids with random data
  for(byte x = 0; x < ROWS; ++x){
    for(byte y = 0; y < COLS; ++y){
      rGrid[x][y] = random(0,256);
      gGrid[x][y] = random(0,256);
      bGrid[x][y] = random(0,256);
      trajectory[x][y] = random(1,8);
    } 
  }  
}

void grid_blank(){
  //initialize the button grids with random data
  for(byte x = 0; x < ROWS; ++x){
    for(byte y = 0; y < COLS; ++y){
      rGrid[x][y] = 0;
      gGrid[x][y] = 0;
      bGrid[x][y] = 0;
      trajectory[x][y] = random(1,8);
    } 
  } 
}

void always(){
    if((long)millis() - (long)time > 10){
      time = millis();
      for(byte x = 0; x < ROWS; ++x){
        for(byte y = 0; y < COLS; ++y){
          rGrid[x][y] = constrain(rGrid[x][y] + ((trajectory[x][y] & B001 ) ? 1 : -1),L, H);
          gGrid[x][y] = constrain(gGrid[x][y] + ((trajectory[x][y] & B010 ) ? 1 : -1),L, H);
          bGrid[x][y] = constrain(bGrid[x][y] + ((trajectory[x][y] & B100 ) ? 1 : -1),L, H);
          if (rGrid[x][y] == ( (trajectory[x][y] & B001) ? H : L ) && gGrid[x][y] == ( (trajectory[x][y] & B010) ? H : L ) && bGrid[x][y] == ( (trajectory[x][y] & B100) ? H : L ) ) {
            trajectory[x][y] = random(1,8);
          }
        } 
      } 
    }
  }


void on_press(byte r, byte c){
  for(byte x = 0; x < ROWS; ++x){
    for(byte y = 0; y < COLS; ++y){
      rGrid[x][y] = rGrid[r][c];
      bGrid[x][y] = bGrid[r][c];
      gGrid[x][y] = gGrid[r][c];
    }
  }
}

void on_release(byte r, byte c){
  rGrid[r][c] = rGrid[(r+1) % ROWS][(c+1) % COLS];
  gGrid[r][c] = gGrid[(r+1) % ROWS][(c+1) % COLS];
  bGrid[r][c] = bGrid[(r+1) % ROWS][(c+1) % COLS];  
}

void while_pressed(byte r, byte c){
  time = millis() + PAUSE;
  rGrid[r][c] = 255;
  gGrid[r][c] = 255;
  bGrid[r][c] = 255;
}

void while_released(byte r, byte c){

}
