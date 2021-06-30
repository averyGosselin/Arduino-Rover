
#include <Servo.h>

//Servo
Servo servo;
int curPos = 90;

// Conductive foil inputs
int f = 7;
int b = 6;
int r = 5;
int l = 4;

void setup()
{
  //Initialize motor 
  pinMode(13, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(9, OUTPUT);
  digitalWrite(13, HIGH);

  //Initialize servo
  servo.attach(3);
  servo.write(90);

  //Initialize conductive fingers
  pinMode(f, INPUT);
  pinMode(b, INPUT);
  pinMode(r, INPUT);
  pinMode(l, INPUT);
  
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


void loop()
{
  // Move forward if the "f" finger is active, stops if back is also active.
  if(digitalRead(f) == LOW){
    if(digitalRead(b) == LOW){
      halt();
    }
    else{
      forward();
    }
  }
  // Move backward if the "b" finger is active, stops if forward is also active.
  else if(digitalRead(b) == LOW){
    if(digitalRead(f) == LOW){
      halt();
    }
    else{
      backward();
    }
  }
  else{
    halt();
  }

  // Turn right if the "r" finger is active, stops if the left finger is also active.
  if(digitalRead(r) == LOW){
    if(digitalRead(l) == LOW){
      turn(90);
    }
    else{
      turn(120);
    }
  }
  // Turn left if the "l" finger is active, stops if the right finger is also active.
  else if(digitalRead(l) == LOW){
    if(digitalRead(r) == LOW){
      turn(90);
    }
    else{
      turn(60);
    }
  }
  else{
    turn(90);
  }

}
