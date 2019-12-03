#include <Keypad.h>
#include <Servo.h>
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
Servo myservo; 
int pos = 0;
void setup() {
  // put your setup code here, to run once:
    myservo.attach(53);  // attaches the servo on pin 53 to the servo object

Serial.begin(9600); // Starts the serial communication
}

void loop() {
  // put your main code here, to run repeatedly:
  box_locked=1;
  if (box_locked ==1) {
    servoClose();
}
delay(15);
  KeypadInput();
  if (box_locked==0) {
    servoOpen();
  }

}
void servoOpen() {
  for (pos=0; pos<=180; pos+=1) {
    myservo.write(pos);
    Serial.println(pos);
  }
}

void servoClose() {
  for (pos=180; pos >=0; pos-=1) {
    myservo.write(pos);
    Serial.println(pos);
  }
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
        box_locked = 0;
  }
    }
}
