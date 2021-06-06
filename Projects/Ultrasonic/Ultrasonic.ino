/*
 * Author: Avery Gosselin
 * Last Updated: 6/6/2021
*/
#include <Servo.h>

//Servo
Servo servo;
int curPos = 90;

//Ultrasonic sensor
#define echoPin 4
#define trigPin 5

void setup() 
{ 
  //Initialize motor 
  pinMode(13, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(9, OUTPUT);
  digitalWrite(13, HIGH);
  forward();
  
  //Initialize servo
  servo.attach(3);
  servo.write(90);
  Serial.begin(9600);

  //Initialize ultrasonic sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
} 

int checkDist(){
  long duration; // variable for the duration of sound wave travel
  int distance; // variable for the distance measurement

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  
  // Returns calculated distance
  return distance;
}

void changeDir(){
  long randTime = random(1500, 2500);
  long randTurn = random(1,3);
  if(randTurn < 2.0){
    turn(50);
  }
  else{
    turn(130);
  }
  backward();
  delay(randTime);

  turn(90);
  forward();
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


void loop() {
  int distance = 0;
  for(int i = 0; i < 3; i++){
    distance += checkDist();
  }
  if(distance / 3 <= 15){
    changeDir();
  }
}
