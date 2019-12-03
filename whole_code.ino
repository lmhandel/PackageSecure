#include <Keypad.h>
#include <Servo.h>

const byte ROWS = 4; 
const byte COLS = 4; 
const byte UNLOCK_ARR = 4;
const int buzzer = A0;

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
char key;
char keytrig;
//end keypad setup
int box_locked = 0; //changes to 1 when the box is locked
//begin US1 values
//NOTE:CHANGE THESE VALUES WHEN WE HAVE THE REAL BOX DIMENSIONS
const byte BOXDIST_BIG=2000;//upper range for how far away the front of the box should be
const byte BOXDIST_SMALL=50;//lower range for how far away the front of the box should be
const byte MIN_DIST = 200000;//how far away something has to be before the box starts screaming, this number should be changed later
const int trigPin1 = 11;
const int echoPin1 = 10;
//US2
const int trigPin2 = 13;
const int echoPin2 = 12;
// defines variables
long duration1;
int distance1;
long duration2;
long distance2;
int keypad_triggered=0;
int buzzlen;//sets how long you want the buzzer to go off for
//end US1 values

//begin Servo values
Servo myservo; 
int pos = 0;
int time_close;
//end servo values
void setup() {
// ultrasonic sensor
pinMode(trigPin1, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin1, INPUT); // Sets the echoPin as an Input
pinMode(trigPin2, OUTPUT);
pinMode(echoPin2, INPUT);
pinMode(buzzer, OUTPUT); //SETS UP pin for buzzer
myservo.attach(53); //setup for servo
Serial.begin(9600); // Starts the serial communication

}

void loop() {
  while (box_locked==0) { //while there is no package
    UltrasonicOne(); //looking for a package
    if (distance1 <=BOXDIST_SMALL) {
      box_locked=1;//sets the box as locked
      servoClose(); //closes the lock
      Serial.println("Flag1");
      buzzlen = 1000;
      BuzzerTurnOn(); //little tone to day the box is there
      Serial.println("Flag2");
      //STEP3: EMAIL TO SAY PACKAGE IS HERE IS SENT
    }
  }//this while loop is exited once the package is in and the box is locked

  while (box_locked==1) { //this is what the box will do when theres a package in it
     UltrasonicTwo(); //the sensor looking for someone to tamper with it
        while (distance2 >MIN_DIST) { //if no one is sensed the ultrasonic sensor keeps looping
          UltrasonicTwo();
        }
        if (distance2 < MIN_DIST) { //if someone is close to the box
          keytrig = customKeypad.getKey();
          if (keytrig) { //this breaks this cycle if someone tries to put in a code, so someone can get their package
            KeypadInput();
          }
          time_close+=1; //counts how many seconds the person has been close to the box
          delay(1000);
          Serial.println(time_close);
          UltrasonicTwo();
          if((distance2 > MIN_DIST)) { //if the person leaves the box we dont have to count anymore
            time_close =0;
          }
        }
          if (time_close >= 90) {
            keytrig = customKeypad.getKey();
            if (keytrig) {
            KeypadInput();
          }
            buzzlen = 10000000; //big long obnoxious buzzer
            BuzzerTurnOn();
            time_close = 0;
        }
}
}

void UltrasonicOne() {
  //this is US1 looking for a package
 digitalWrite(trigPin1, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin1, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin1, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration1 = pulseIn(echoPin1, HIGH);
// Calculating the distance
distance1= duration1*0.034/2;
  Serial.print("Distance1: ");
  Serial.println(distance1);
}

void UltrasonicTwo() {
  //this is US2 looking out for tamperers
digitalWrite(trigPin2, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin2, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin2, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration2 = pulseIn(echoPin2, HIGH);
// Calculating the distance
distance2= duration2*0.034/2;
}

void KeypadInput() {
    while (keypad_counter < 4) {

  key = customKeypad.getKey();
  
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
  if (keypad_counter ==4) {

    //THIS IS WHERE CODE FOR UNLOCKING THE DOOR GOES
  }
  // put your main code here, to run repeatedly:

}
}

void BuzzerTurnOn() {
  tone(buzzer, 1000); //change this value for pitch of the noise
  delay(buzzlen); //sets how long the buzzer goes off for
  noTone(buzzer);//shuts off the tone 
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
