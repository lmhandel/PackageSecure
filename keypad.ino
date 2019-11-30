#include <Keypad.h>

const byte ROWS = 4; 
const byte COLS = 4; 
const byte UNLOCK_ARR = 4;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
char unlock_array[UNLOCK_ARR] = {'1','2','3','4'}; 
char input_array[UNLOCK_ARR] = {'-','-','-','-'};
int keypad_counter = 0;
int keypad_match = 0;
//end keypad setup


void setup(){
  Serial.begin(9600);
}

void loop() {
 
  while (keypad_counter < 4) {
  char key = customKeypad.getKey();
  
  if(key) {
    Serial.println(key);
    if (key == unlock_array[keypad_counter]) {
      keypad_counter+=1;
    } else {
      keypad_counter =0;
    }
 
  }
  if (keypad_counter ==4) {
    Serial.println("Success");
  }
  if (keypad_counter ==4) {
    //THIS IS WHERE CODE FOR UNLOCKING THE DOOR GOES
  }
  // put your main code here, to run repeatedly:

}
}
