#include <Keypad.h>

const byte ROWS = 4; 
const byte COLS = 4; 
const byte UNLOCK_ARR = 4;
int box_locked =0;

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
// begin ultrasonic setup
const int trigPin = 11;
const int echoPin = 10;
// defines variables
long duration;
int distance;

void setup() {
  // US set
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
Serial.begin(9600); // Starts the serial communication

}

void loop() {
  // put your main code here, to run repeatedly:
Ultrasonic();
if (distance <8) {
KeypadInput();
}
}
void Ultrasonic() {
  digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= duration*0.034/2;
// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);
}
void KeypadInput() {
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
        box_locked = 1;
  }
  if (keypad_counter ==4) {

    //THIS IS WHERE CODE FOR UNLOCKING THE DOOR GOES
  }
  // put your main code here, to run repeatedly:

}
}
