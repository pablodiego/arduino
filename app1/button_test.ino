// For 2x4 button pad. Prints message and toggles door lock on each press.
// Set your serial console to 19200
// Written by Will O'Brien, based on various others works.

#define ROWS 2
#define COLS 4

const byte buttonWrite[2] = {
  2, 3}; //Pins for the Vin of the buttons
const byte buttonRead[4] = {
  6, 7, 8, 9}; //Pins for reading the state of the buttons
boolean pressed[ROWS][COLS] = {
  0};
  const byte lock_pin = 4;
boolean lockState = 0;

void setup(){
  Serial.begin(19200);
  pinMode(lock_pin, OUTPUT);
  digitalWrite(lock_pin, LOW);

//setup the button inputs and outputs
  for(int i = 0; i < ROWS; ++i){ // ???? Is ROWS the right quanitity here?
    pinMode(buttonWrite[i], OUTPUT);
    digitalWrite(buttonWrite[i],LOW);
  }
  for(int j = 0; j<COLS; ++j) {
    pinMode(buttonRead[j], INPUT);
  }
}



void loop(){
  Serial.print(".");
  for(byte r = 0; r < ROWS; ++r){

    digitalWrite(buttonWrite[r], HIGH);
    for(byte c = 0; c < COLS; ++c){
      if(pressed[r][c] != digitalRead(buttonRead[c])){
        pressed[r][c] = digitalRead(buttonRead[c]);
        if(pressed[r][c]){
          on_press(r, c);
        } 
      } 
    }
    delay(5);
    digitalWrite(buttonWrite[r], LOW); 
  }
  delay(10);
}

void on_press(byte r, byte c){
  Serial.print(r, DEC);
  Serial.print(", ");
  Serial.println(c, DEC);
  set_lock();
}

void set_lock(){
 if(lockState){
   unlock(); 
 }
  else
   lock(); 
}
void unlock(){
  Serial.print("Unlock door");
  digitalWrite(lock_pin, HIGH);
  lockState = !lockState;
}
void lock(){
  Serial.print("Lock door");
  digitalWrite(lock_pin, LOW);
  lockState = !lockState;
}
