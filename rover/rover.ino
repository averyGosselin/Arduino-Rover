#include <Servo.h>
/*
 * Author: Avery Gosselin
 * Last Updated: 5/15/2021
*/

//Servo
Servo servo;
int curPos = 90;

//Photoresistor
const int photores = A0;

//Joystick
int VRx = A1;
int VRy = A2;
int SW = 2;
int xPosition = 0;
int yPosition = 0;
int SW_state = 0;
int mapX = 0;
int mapY = 0;

//Buttons
int forwardBtn = A3;
int backwardBtn = A4;

void setup() 
{ 
  //Initialize motor 
  pinMode(13, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(9, OUTPUT);
  digitalWrite(13, HIGH);

  //Initialize photoresistor
  pinMode(photores, INPUT);

  //Initialize the buttons
  pinMode(forwardBtn, INPUT);
  pinMode(backwardBtn, INPUT);
  
  //Initialize servo
  servo.attach(3);
  servo.write(90);
  Serial.begin(9600);
  
  //Initialize joystick
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(SW, INPUT_PULLUP); 
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

//Makes the rover run away erratically from bright lights, they're scary!
void flee(){

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

//Put your code here, the functions above are just a starting point, connect them, change them, do whatever you want and
//  have fun playing with your rover!
//Current use: drive the tover around with the joystick and buttons.
void loop() 
{ 

  xPosition = analogRead(VRx);
  yPosition = analogRead(VRy);
  SW_state = digitalRead(SW);
  mapX = map(xPosition, 0, 1023, -512, 512);
  mapY = map(yPosition, 0, 1023, -512, 512);

  if(forwardBtn == HIGH and backwardBtn == HIGH){
    halt();
  }
  else if(forwardBtn == HIGH){
    forward();
  }
  else if(analogRead(backwardBtn == HIGH)){
    backward();
  }
  else{
    halt();
  }
  
  if(mapY > 25){
    turn(60);
  }
  else if(mapY < -25){
    turn(120);
  }
  else{
    turn(90);
  }
  delay(100);
} 
