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
const int speed_av = 400;

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
  analogWrite(pinMotorFG, speed_av);
  analogWrite(pinMotorFD, speed_av);  
  
}

void move_left() {  

  analogWrite(pinMotorBG, speed_av);
  analogWrite(pinMotorBD, lowTh);
  analogWrite(pinMotorFG, lowTh);
  analogWrite(pinMotorFD, speed_av);  
  delay(1000);                   // pour se retrouver à 90° après ce temps
  
}

void move_right() {

  analogWrite(pinMotorBG, lowTh);
  analogWrite(pinMotorBD, speed_av);
  analogWrite(pinMotorFG, speed_av);
  analogWrite(pinMotorFD, lowTh); 
  delay(1000);                     // pour se retrouver à 90° après ce temps
  
}

void stop_running() {

  analogWrite(pinMotorBG, lowTh);
  analogWrite(pinMotorBD, lowTh);
  analogWrite(pinMotorFG, lowTh);
  analogWrite(pinMotorFD, lowTh); 
  
}

void stay_steady() {

  int sensor_diff;
  sensor_diff = sensor_left - sensor_right;
  
  if (sensor_diff > 30 || sensor_diff < -30)
  {
    if (sensor_diff > 30 && sensor_diff < 60)
    {
      move_left();
      move_forward();
      delay(10*sensor_diff);
      move_right();
      stop_running();
    }
    if (sensor_diff < -30 && sensor_diff > -60)
    {
      move_right();
      move_forward();
      delay(10*sensor_diff*(-1));
      move_left();
      stop_running();
    }
  }

}

void chose_direction(int &left_increment , int &right_increment , int &forward_increment , int &back_increment) {

  if(sensor_front > 40)
  {
    move_forward();

    if (sensor_left > 100 && sensor_right > 100)
    {
      forward_increment++;
        if (forward_increment > 2)
        {
          decrement_pile = false;
          if (memory.empty())
          {
            move_left();
            stop_running();
            memory.push('L');

          }
          else
          {
            if (memory.top() == 'L')
            {
              move_left();
              stop_running();
              while(!memory.empty())
                memory.pop();         //nettoyage de la pile
              memory.push('L');
            }
            
            if (memory.top() == 'R')
            {
              move_right();
              stop_running();
              while(!memory.empty())
                memory.pop();         //nettoyage de la pile
              memory.push('R');
            }
          }
         }
         forward_increment = 0;
         move_forward();
         delay(1000);
       }

    else if (sensor_left > 100 || sensor_right > 100)
    {
      if (sensor_left > 100 && sensor_right <= 100)
      {
        left_increment++;
        if (left_increment > 2)
        {
          move_left();
          stop_running();
          if (decrement_pile == false)
          {
            memory.push('L');
          }
          else if (decrement_pile == true)
          {
            memory.pop();
          }
          left_increment = 0;
          move_forward();
          delay(1000);
        }
      }
      else if (sensor_right > 100 && sensor_left <= 100)
      {
        right_increment++;
        if (right_increment > 2)
        {
          if (memory.top() == 'F')
          {
            move_forward();
          }
          else
          {
            move_right();
            stop_running();
            if (decrement_pile == false)
            {
              memory.push('R');
            }
            else if (decrement_pile == true)
            {
              memory.pop();
            }
            right_increment = 0;
            move_forward();
            delay(1000);
          }
        }
      }
    }

    else
    {
      left_increment = 0;
      right_increment = 0;
      forward_increment = 0;
    }
  }

  else if (sensor_front <= 40)
  {
    stop_running();
    
    if (sensor_left > 100 && sensor_right > 100)
    {
      forward_increment++;
        if (forward_increment > 2)
        {
          decrement_pile = false;
          
          move_left();
          stop_running();
          memory.push('F');   // F for forward
          
          forward_increment = 0;
          move_forward();
          delay(1000);
        }
      }
    
    else if (sensor_left > 100 || sensor_right > 100)
    {
      if (sensor_left > 100 && sensor_right <= 100)
      {
        left_increment++;
        if (left_increment > 2)
        {
          move_left();
          stop_running();
          if (decrement_pile == false)
          {
            memory.push('L');
          }
          if (decrement_pile == true)
          {
            memory.pop();
          }
          left_increment = 0;
          move_forward();
          delay(1000);
        }
      }
      else if (sensor_right > 100 && sensor_left <= 100)
      {
        right_increment++;
        if (right_increment > 2)
        {
          move_right();
          stop_running();
          if (decrement_pile == false)
          {
            memory.push('R');
          }
          else if (decrement_pile == true)
          {
            memory.pop();
          }
          right_increment = 0;
          move_forward();
          delay(1000);
         }
       }
    }
    
    else if (sensor_left < 100 && sensor_right < 100)
    {
      back_increment++;
      if (back_increment > 2)
      {
        Serial.println("UTURN");
        move_left();
        delay(2000);
        stop_running();
        decrement_pile = true;
        back_increment = 0;
       }
     }
   }
}

void sensing(int &sensor_f , int &sensor_l , int &sensor_r)
{
    //CAPTOR 1 : adress 112 for FRONT SENSOR
  
  // step 1: instruct sensor to read echoes
  Wire.beginTransmission(112); // transmit to device #112 (0x70)
  // the address specified in the datasheet is 224 (0xE0)
  // but i2c adressing uses the high 7 bits so it's 112
  Wire.write(byte(0x00));      // sets register pointer to the command register (0x00)
  Wire.write(byte(0x51));      // command sensor to measure in "centimeters" (0x51)
  // use 0x51 for centimeters
  // use 0x52 for ping microseconds
  Wire.endTransmission();      // stop transmitting
  
  //CAPTOR 2 : adress 113 for LEFT SENSOR
  
  Wire.beginTransmission(113); // transmit to device #113
  Wire.write(byte(0x00));      // sets register pointer to the command register (0x00)
  Wire.write(byte(0x51));      // command sensor to measure in "centimeters" (0x51)
  // use 0x51 for centimeters
  // use 0x52 for ping microseconds
  Wire.endTransmission();      // stop transmitting
  
  //CAPTOR 3 : adress 114 for RIGHT SENSOR
  
  Wire.beginTransmission(114); // transmit to device #114
  Wire.write(byte(0x00));      // sets register pointer to the command register (0x00)
  Wire.write(byte(0x51));      // command sensor to measure in "centimeters" (0x51)
  // use 0x51 for centimeters
  // use 0x52 for ping microseconds
  Wire.endTransmission();      // stop transmitting
  
  // step 2: wait for readings to happen
  delay(65);                   // datasheet suggests at least 65 milliseconds
  
  // step 3: instruct sensor to return a particular echo reading
  Wire.beginTransmission(112); // transmit to device #112
  Wire.write(byte(0x02));      // sets register pointer to echo #1 register (0x02)
  Wire.endTransmission();      // stop transmitting
  
  // step 4: request reading from sensor
  Wire.requestFrom(112, 2);    // request 2 bytes from slave device #112
  
  // step 5: receive reading from sensor
  if (2 <= Wire.available())   // if two bytes were received
  {
    sensor_f = Wire.read();  // receive high byte (overwrites previous reading)
    sensor_f = sensor_f << 8;    // shift high byte to be high 8 bits
    sensor_f |= Wire.read(); // receive low byte as lower 8 bits
    Serial.println("captor front : ");
    Serial.print(sensor_f);   // print the reading
    Serial.println("cm");
  }
  
  Wire.beginTransmission(113); // transmit to device #113
  Wire.write(byte(0x02));      // sets register pointer to echo #1 register (0x02)
  Wire.endTransmission();      // stop transmitting
  
  Wire.requestFrom(113, 2);    // request 2 bytes from slave device #113
  
  if (2 <= Wire.available())   // if two bytes were received
  {
    sensor_l = Wire.read();  // receive high byte (overwrites previous reading)
    sensor_l = sensor_l << 8;    // shift high byte to be high 8 bits
    sensor_l |= Wire.read(); // receive low byte as lower 8 bits
    Serial.println("captor left : ");
    Serial.print(sensor_l);   // print the reading
    Serial.println("cm");
  }
  
  Wire.beginTransmission(114); // transmit to device #114
  Wire.write(byte(0x02));      // sets register pointer to echo #1 register (0x02)
  Wire.endTransmission();      // stop transmitting

  Wire.requestFrom(114, 2);    // request 2 bytes from slave device #114
  
  if (2 <= Wire.available())   // if two bytes were received
  {
    sensor_r = Wire.read();  // receive high byte (overwrites previous reading)
    sensor_r = sensor_r << 8;    // shift high byte to be high 8 bits
    sensor_r |= Wire.read(); // receive low byt e as lower 8 bits
    Serial.println("captor right : ");
    Serial.print(sensor_r);   // print the reading
    Serial.println("cm");
  }
}

void loop() {
  
  sensing(sensor_front, sensor_left, sensor_right);
  
  stay_steady();
  
  sensing(sensor_front, sensor_left, sensor_right);
  
  chose_direction(l, r, forward_param, back);
}
