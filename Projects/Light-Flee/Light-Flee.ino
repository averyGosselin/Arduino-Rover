/*
 * Author: Avery Gosselin
 * Last Updated: 9/27/2021
*/
#include <Servo.h>

//Set up Servo
Servo servo;
int curPos = 90;

//save photoresistor pin
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
  
  //Uncomment for debugging with serial monitor
  //Serial.begin(9600);
} 

/*
* Turns the front wheels to a target angle at a slow (1), medium (2), or high (3) speed
* target: the angle the servo should be set to to turn the wheels 
* speed: the speed at which the servo will be set to target, allowed speeds:
*   slow = 1
*   medium = 2
*   fast = 3
*/
void turn(int target, int speed = 2)
{
  int toAdd = 0;
  
  //Find out if the servo angle needs to increase or decrease
  if(target > curPos){
    toAdd = 1;
  }
  else{
    toAdd = -1;
  }

  //Turns the servo at the designated speed, defaults to medium if not specified or a valid number
  if(speed == 1){
    while(curPos != target){
      curPos += toAdd;
      delay(20);
      servo.write(curPos);
    }
  }
  else if(speed == 3){
    while(curPos != target){
      curPos += toAdd;
      delay(5);
      servo.write(curPos);
    }
  }
  else {
    while(curPos != target){
      curPos += toAdd;
      delay(5);
      servo.write(curPos);
    }
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
  //Gets the current reading of the photoresistor
  int lightVal = analogRead(photores);
  
  //Will drive the rover forward/backward and turn randomly until it is out of the bright light
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
    lightVal = analogRead(photores);
    delay(250);
  }
  halt();
} 
