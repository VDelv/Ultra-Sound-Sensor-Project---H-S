#include <stack>
#include <Wire.h>

using namespace std;


#define pinMotorBD D2
#define pinMotorFD D3 
#define pinMotorBG D6
#define pinMotorFG D7

stack<char> memory;

bool decrement_pile = false;
int l = 0;
int r = 0;
int forward_param = 0;
int back = 0;

int sensor_front;
int sensor_left;
int sensor_right;

const int lowTh = 0;
const int speed_av = 275;

void setup() {

  Wire.begin(D4, D5);                // join i2c bus (address optional for master)

  pinMode(pinMotorFG, OUTPUT); 
  pinMode(pinMotorBG, OUTPUT);
  pinMode(pinMotorFD, OUTPUT);
  pinMode(pinMotorBD, OUTPUT);
  Serial.begin(9600);
  
}

void move_forward() {

  analogWrite(pinMotorBG, lowTh);
  analogWrite(pinMotorBD, lowTh);
  analogWrite(pinMotorFG, 1.05*speed_av);
  analogWrite(pinMotorFD, speed_av);  
  
}

void move_left() {  

  analogWrite(pinMotorBG, speed_av);
  analogWrite(pinMotorBD, lowTh);
  analogWrite(pinMotorFG, lowTh);
  analogWrite(pinMotorFD, speed_av);  
  delay(150);                   // pour se retrouver à 90° après ce temps
  
}

void move_right() {

  analogWrite(pinMotorBG, lowTh);
  analogWrite(pinMotorBD, speed_av);
  analogWrite(pinMotorFG, speed_av);
  analogWrite(pinMotorFD, lowTh); 
  delay(150);                     // pour se retrouver à 90° après ce temps
  
}

void stop_running() {

  analogWrite(pinMotorBG, lowTh);
  analogWrite(pinMotorBD, lowTh);
  analogWrite(pinMotorFG, lowTh);
  analogWrite(pinMotorFD, lowTh); 
  
}

void loop() {
  
  move_forward();
  delay(1500);
  move_left();
  move_forward();
  delay(1500);
  move_right();
  stop_running();
  delay(5000);
    
}
