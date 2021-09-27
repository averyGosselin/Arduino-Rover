/*
 * Author: Avery Gosselin
 * Last Updated: 9/27/2021
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
  // variable for the duration of sound wave travel
  long duration;
  //variable for the distance measurement
  int distance;

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

// Changes the direction of the rover for a random amount of time to attempt to escape a barrier
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

// Main loop, will check if the rover is close to hitting something and activate changeDir to escape
// Averages the recorded distance over three checks to avoid false assumptions of walls
void loop() {
  int distance = 0;
  for(int i = 0; i < 3; i++){
    distance += checkDist();
  }
  if(distance / 3 <= 15){
    changeDir();
  }
}
