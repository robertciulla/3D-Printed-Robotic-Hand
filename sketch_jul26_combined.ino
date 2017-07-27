#include <Servo.h>

Servo finger1, finger2, finger3, finger4;

int encoderPin1 = 2;
int encoderPin2 = 3;

int servoPin1 = 5;
int servoPin2 = 6;
int servoPin3 = 8;
int servoPin4 = 9;
//int servoPin5 = 3;  //not in use

int flexPin1 = A0;
int flexPin2 = A1;
int flexPin3 = A2;
int flexPin4 = A3;
int flexPin5 = A4;  //not in use

int potpin = 3;  // analog pin used to connect the potentiometer

volatile int lastEncoded = 0;
volatile long encoderValue = 0;

long lastencoderValue = 0;

int lastMSB = 0;
int lastLSB = 0;

Servo myservo;  // create servo object to control a servo

int val;   

//finger move

void setup() {
  // put your setup code here, to run once:

  Serial.begin (9600);
  myservo.attach(10);
  pinMode(encoderPin1, INPUT); 
  pinMode(encoderPin2, INPUT);

  digitalWrite(encoderPin1, HIGH); //turn pullup resistor on
  digitalWrite(encoderPin2, HIGH); //turn pullup resistor on

  //call updateEncoder() when any high/low changed seen
  //on interrupt 0 (pin 2), or interrupt 1 (pin 3) 
  attachInterrupt(0, updateEncoder, CHANGE); 
  attachInterrupt(1, updateEncoder, CHANGE);

// finger move

  finger1.attach(servoPin1);
  finger2.attach(servoPin2);
  finger3.attach(servoPin3);
  finger4.attach(servoPin4);
 // finger5.attach(servoPin5);
  
  /* set each servo pin to output; I'm not acutally sure if this is
  even necessary, but I did just in case it is */
  pinMode(servoPin1, OUTPUT);
  pinMode(servoPin2, OUTPUT);
  pinMode(servoPin3, OUTPUT);
  pinMode(servoPin4, OUTPUT);
 // pinMode(servoPin5, OUTPUT);
  
  //Set each flex sensor pin to input: this is necessary
  pinMode(flexPin1, INPUT);
  pinMode(flexPin2, INPUT);
  pinMode(flexPin3, INPUT);
  pinMode(flexPin4, INPUT);
  pinMode(flexPin5, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:


//Do stuff here
  myservo.write(encoderValue);  
  Serial.println(encoderValue);
  //delay(500); //just here to slow down the output, and show it will work  even during a delay 
  
  int flex1 = analogRead(flexPin1);
  int flex2 = analogRead(flexPin2);
  int flex3 = analogRead(flexPin3);
  int flex4 = analogRead(flexPin4);
  //int flex5 = analogRead(flexPin5);

  
  int pos1 = map(flex1, 400, 700, 0, 180);
  pos1 = constrain(pos1, 0, 180);
  int pos2 = map(flex2, 400, 700, 0, 180);
  pos2 = constrain(pos2, 0, 180);
  int pos3 = map(flex3, 400, 700, 0, 180);
  pos3 = constrain(pos3, 0, 180);
  int pos4 = map(flex4, 480, 640, 0, 180);
  pos4 = constrain(pos4, 0, 180);
  //int pos5 = map(flex5, 400, 700, 0, 180);
  //pos5 = constrain(pos5, 0, 180);

  finger1.write(pos1);
  finger2.write(pos2);
  finger3.write(pos3);
  finger4.write(pos4);
  
}

void updateEncoder(){
  int MSB = digitalRead(encoderPin1); //MSB = most significant bit
  int LSB = digitalRead(encoderPin2); //LSB = least significant bit
  
  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue ++;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue --;

  lastEncoded = encoded; //store this value for next time
}

