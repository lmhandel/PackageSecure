const int buzzer = A0;
const int trigPin = 11;
const int echoPin = 10;
const int MIN_DIST = 50;
// defines variables
long duration;
int distance;
int time_close = 0;
int buzzlen;
void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(buzzer, OUTPUT);
  Ultrasonic();
 Serial.begin(9600);
}

void loop() {
  while ((distance >MIN_DIST) && (distance <2100)) {
  Ultrasonic();
  }
  if (distance < MIN_DIST) {
    time_close+=1;
    delay(1000);
    Serial.println(time_close);
    Ultrasonic();
    if((distance > MIN_DIST)) {
      time_close =0;
    }
  }
  if (time_close >= 20) {
    buzzlen = 10000000;
    BuzzerTurnOn();
    time_close = 0;
  }
  // put your main code here, to run repeatedly:

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

void BuzzerTurnOn() {
  tone(buzzer, 1000); //change this value for pitch of the noise
  delay(buzzlen); //sets how long the buzzer goes off for
  noTone(buzzer);//shuts off the tone 
}
