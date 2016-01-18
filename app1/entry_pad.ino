//based on buttton_test
//This is the v1 release of the RGB door lock code. The hard coded code is:
// [r][g][b][r]
// [r][g][b][r]
// The buttons will flash blue in order while idle.
// On a press, the color is toggled, starting from blank. The password is entered
// by pressing the buttons to set the color code.
// When the code is entered, the pad will turn green and unlock for 10 seconds.
// If the counter is exceeded, the pad will turn red for 30 seconds.
// Written by Will O'Brien, based on various others works.

#define DATAOUT 11//MOSI (pin 7 of AD5206)
#define DATAIN 12//MISO - not used, but part of builtin SPI
#define SPICLOCK  13//sck (pin 8 of AD5206)
#define SLAVESELECT 10 //removed the slave switching code entirely.
#define COLS 4 //x axis
#define ROWS 2 //y axis
#define effect_select 1 //choose idle effect

const byte colpin[COLS] = { //pins for led column grounding transistors
  14,15,16,17}; // Using the analog inputs as digital pins (14=A0,15=A1,16=A2,17=A3)

const byte buttonWrite[ROWS] = {
  2, 3}; //Pins for the Vin of the buttons, y-axis
const byte buttonRead[COLS] = {
  9, 8, 7, 6}; //Pins for reading the state of the buttons, x-axis
boolean pressed[COLS][ROWS] = {
  0};
  const byte lock_pin = 4;
boolean lockState = 0;
boolean effect[COLS][ROWS] = {
  0};
byte effect_color = 3;
byte effect_state = 0;
byte effect_count = 0;


// The pot register numbers for each of the red, green, and blue channels
// Address map for AD5206:
// Pin bin dec
// 2   101 5
// 11  100 4
// 14  010 2
// 17  000 0
// 20  001 1
// 23  011 3

const byte red[2] = {
  5, 0};
const byte green[2] = {
  4, 1};
const byte blue[2] = {
  2, 3};

// Main data for the drawing routine
byte rGrid[COLS][ROWS] = {
  0};
byte gGrid[COLS][ROWS] = {
  0};
byte bGrid[COLS][ROWS] = {
  0};


//  Entry code definition
byte rCode[COLS][ROWS] = {
  0};
byte gCode[COLS][ROWS] = {
  0};
byte bCode[COLS][ROWS] = {
  0};
  
  

byte COLORS = 4;//0  1    2    3
byte rColors[] = {0, 255, 0,   0  }; //red
byte gColors[] = {0, 0,   255, 0  }; //green
byte bColors[] = {0, 0,   0,   255}; //blue

byte colorcode[COLS][ROWS] = { 0 };
byte count;

void setup(){
  count = 0; //init count
  //set entry code
  colorcode[0][0] = 1; //row 1
  colorcode[1][0] = 2;
  colorcode[2][0] = 3;
  colorcode[3][0] = 1;
    colorcode[0][1] = 1; //row 2
    colorcode[1][1] = 2;
    colorcode[2][1] = 3;
    colorcode[3][1] = 1;
 
 
  Serial.begin(19200);
  pinMode(lock_pin, OUTPUT);
  digitalWrite(lock_pin, LOW);

//setup the button inputs and outputs
  for(int i = 0; i < ROWS; ++i){ //set row lines to output and zero them
    pinMode(buttonWrite[i], OUTPUT);
    digitalWrite(buttonWrite[i],LOW);
  }
  for(int j = 0; j<COLS; ++j) { //set column lines to input
    pinMode(buttonRead[j], INPUT);
  }
  byte i;
  byte clr;
  pinMode(DATAOUT, OUTPUT);
  pinMode(DATAIN, INPUT);
  pinMode(SPICLOCK,OUTPUT);
  pinMode(SLAVESELECT,OUTPUT);

  for(byte c = 0; c < COLS; ++c){
    pinMode(colpin[c], OUTPUT); // Initialize LED columns
    digitalWrite(colpin[c], LOW); // Turn all LED cols off
  }

  digitalWrite(SLAVESELECT,HIGH); //disable device  // SPCR = 01010000
  //interrupt disabled,spi enabled,msb 1st,master,clk low when idle,
  //sample on leading edge of clk,system clock/4 (fastest)
  SPCR = (1<<SPE)|(1<<MSTR);
  clr=SPSR;
  clr=SPDR;
  delay(10);
  // clear all of the pot registers
  for (i=0;i<6;i++)
  {
    write_pot(i,0);
  }
grid_init(); //clear rgb grid.
code_init(); //set code in memory.
effect_init();
}

void grid_init(){
  //initialize the button grids with blank data
  for(byte c = 0; c < COLS; ++c){
    for(byte r = 0; r < ROWS; ++r){
      rGrid[c][r] = 0;
      gGrid[c][r] = 0;
      bGrid[c][r] = 0;
    }
  }
}

void effect_init(){
  //initialize the button grids with blank data
  for(byte c = 0; c < COLS; ++c){
    for(byte r = 0; r < ROWS; ++r){
      effect[c][r] = 0;
    }
  }
  effect[0][0] = 1;
}


void loop(){

  Serial.print(".");
  effect_count++;
  if(count > 15){
   color_effect(255, 0, 0, 30);
   grid_init();
   count = 0;
  }
  for(byte r = 0; r < ROWS; ++r){
    digitalWrite(buttonWrite[r], HIGH); //bring button row high for reading presses
    clear_pot(); //clear pot regs between rows, otherwise the row not being read will be lit during other row reads.
    if(code_check()){
     count = 0;
     Serial.print("code matched!"); //silly debug statment.
     open_door(); //unlock the door.
     grid_init(); //clear entered code and return to scanning mode.
    }
    
    
    for(byte c = 0; c < COLS; ++c){
      if(pressed[c][r] != digitalRead(buttonRead[c])){
        pressed[c][r] = digitalRead(buttonRead[c]);
        if(pressed[c][r]){

          if(count == 0){
           grid_init(); //clear the button states once a code entry is begun. 
          }
           on_press(c, r); //on button press, call on_press
          count++;
        } else {
          on_release(r, c); //on release, call on_release
        }
      } else {
        if(pressed[r][c]){
          while_pressed(c, r); //on button hold
        } else {
          while_released(c,r); //on release
        }
      }
      if(count == 0){
        if(effect_count == 20) {
           idle_effect();
           effect_count = 0;
        }
      }
    write_pot(red[r],rGrid[c][r]); //writes state of colors to the digital pot register
    write_pot(green[r],gGrid[c][r]);
    write_pot(blue[r],bGrid[c][r]);
      
    digitalWrite(colpin[c], HIGH); //turn one col on while pot is written.
    delayMicroseconds(750); // display. Persistance of Vision makes things appear lit constantly.
    digitalWrite(colpin[c], LOW); //turn the col back off
    
  
    }
    digitalWrite(buttonWrite[r], LOW); //bring current row low.
    delay(4);
    
  }
  
  
  //delay(10);
}

void on_press(byte c, byte r){
  Serial.print(c, DEC);
  Serial.print(", ");
  Serial.println(r, DEC);
  //set_lock();
  color_cycle(c, r);
}

void on_release(byte c, byte r){
  //rgb(c, r, 0, 0, 0);
}

void while_pressed(byte c, byte r){

}

void while_released(byte c, byte r){

}

void open_door(){
  digitalWrite(lock_pin, HIGH);
  color_effect(0, 255, 0, 5); //effect the keypad green for 5 seconds or soish.
  digitalWrite(lock_pin, LOW);
}

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
  digitalWrite(SLAVESELECT, LOW);
  //2 byte opcode
  spi_transfer(address % 6);
  spi_transfer(constrain(255-value,0,255));
  digitalWrite(SLAVESELECT, HIGH); //release chip, signal end transfer
}

void rgb(byte c, byte r, byte R, byte G, byte B){
  rGrid[c][r] = R;
  gGrid[c][r] = G;
  bGrid[c][r] = B;
}

void clear_pot(){
    // clear all of the pot registers
   byte i;
  for (i=0;i<6;i++)
  {
    write_pot(i,0);
  }
}

void code_init(){
//This is where the entry code is defined.
//    c r where c is column, r is row. Each is 0-255. Values are mixed to create colors.
// The code consists for four colors to be displayed on one row.
for(byte c=0; c < COLS; c++){
  for(byte r=0; r < ROWS; r++){
    rCode[c][r] = rColors[colorcode[c][r]]; //column 0, row 0
    gCode[c][r] = gColors[colorcode[c][r]];
    bCode[c][r] = bColors[colorcode[c][r]];
  }
}
}

boolean code_check(){ //check color state of grid to see if it matches entry code.


for(byte c=0;c<COLS;c++){
  for(byte r=0; r < ROWS; r++){

    if(rGrid[c][r] != rCode[c][r]){
      return(0);
    }
    if(gGrid[c][r] != gCode[c][r]){
      return(0);
    }
    if(bGrid[c][r] != bCode[c][r]){
      return(0);
    }
  }
}
  return(1);
}

void color_effect(byte dRed, byte dGreen, byte dBlue, byte time){
  //effect all of the keypad buttons to the provided color for n seconds and turn it off again.
  byte c;
      for(byte r=0; r<ROWS; r++){ //leave the grid alone, just write the pot.
        write_pot(red[r],dRed);
        write_pot(green[r],dGreen);
        write_pot(blue[r],dBlue);
      }
      for(c=0;c<COLS;c++){
    digitalWrite(colpin[c], HIGH); //turn one col on while pot is written.
      }    
    delay(time*1000); //turn time into secondsish
      for(c=0;c<COLS;c++){
    digitalWrite(colpin[c], LOW); //turn the col back off
      }
    clear_pot(); //turn off everything in the pot.
  
}

void color_cycle(byte c, byte r){
  byte color = get_color(c, r);
  Serial.print("got color");
  Serial.print( color, DEC );
  if(color < COLORS){
    color++;
  } else {
    color = 1; //skip blank color 0
  }
  rgb(c, r, rColors[color], gColors[color], bColors[color]); 
}

byte get_color(byte c, byte r){
   for(byte i=0; i < COLORS; i++){
  if(rGrid[c][r] == rColors[i]){
    if(bGrid[c][r] == bColors[i]){
      if(gGrid[c][r] == gColors[i]){
        return(i);
      }
    }
  } 
  }  
}

void idle_effect(){ //this is he eye candy while the keypad isn't in use.
  grid_init();
if(effect_select==1)
{
   for(byte r=0; r < ROWS; r++){
     for(byte c=0;c<COLS;c++){
    if(effect_state == 1){
     effect[c][r] = 1; 
     effect_state = 0;
     return;
    }
    if(effect[c][r]) {
      rGrid[c][r] = rColors[effect_color];
      gGrid[c][r] = gColors[effect_color];
      bGrid[c][r] = bColors[effect_color];      
      effect[c][r] = 0;
      effect_state = 1;
     }

    
   }
  }
}
if(effect_select==2){
  
byte red = rColors[effect_color];
byte blue = bColors[effect_color];
byte green = gColors[effect_color];
if(red != 0)
  red = red - effect_state;



  for(byte r=0; r < ROWS; r++){
      for(byte c=0;c<COLS;c++){

      rGrid[c][r] = rColors[effect_color];
      gGrid[c][r] = gColors[effect_color];
      bGrid[c][r] = bColors[effect_color];      
      effect[c][r] = 0;
      effect_state = 1;
      }
     }
  
}
}
