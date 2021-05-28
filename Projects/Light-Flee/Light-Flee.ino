/*
 * Author: Avery Gosselin
 * Last Updated: 5/28/2021
*/
#include <Servo.h>

//Servo
Servo servo;
int curPos = 90;

//Photoresistor
const int photores = A0;

void setup() 
{ 
  //Initialize motor 
  pinMode(13, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(9, OUTPUT);
  digitalWrite(13, HIGH);

  //Initialize photoresistor
  pinMode(photores, INPUT);
  
  //Initialize servo
  servo.attach(3);
  servo.write(90);
  Serial.begin(9600);
} 

//Turns the rover to a specified servo angle at a reasonable speed.
void turn(int target)
{
  int toAdd = 0;
  if(target > curPos){
    toAdd = 1;
  }
  else{
    toAdd = -1;
  }
  while(curPos != target){
    curPos += toAdd;
    delay(10);
    servo.write(curPos);
  }
}

//Drive the rover backwards (may vary depending on how you wired the motor)
void backward()
{
  digitalWrite(13, HIGH);
  digitalWrite(11, LOW);
  digitalWrite(9, HIGH);
}

//Drive the rover forwards (may vary depending on how you wired the motor)
void forward()
{
  digitalWrite(13, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(9, LOW);
}

//Stops the rover
void halt()
{
  digitalWrite(13, LOW);
}

//AHHH bright lights!!!!
//Rover will run away from the brightness, it's nocturnal after all.
void loop() 
{ 
  int lightVal = analogRead(photores);
  
  while(lightVal >= 850){
    long randTurn = random(50, 130);
    long randDir = random(1,3);
    
    if(randDir < 2.0){
      forward();
    }
    else{
      backward();
    }
    turn((int)randTurn);
    Serial.println(randTurn);
    lightVal = analogRead(photores);
    Serial.println(lightVal);
    delay(250);
  }
  halt();
} 
