/*
 * Author: Avery Gosselin
 * Last Updated: 9/27/2021
 * NOTE: This project is not fully configured for use with the Arduino Rover yet.
*/
#include <IRremote.h>
#include <Servo.h>

//Save important pins
const int RECV_PIN = 7;
const int SERVO_PIN = 11;

//Save the integer value sent by your designated fire button on your remote
const int FIRE_CODE = -23971;

//Get the IR receiver working
IRrecv irrecv(RECV_PIN);
decode_results results;

// Setup servo
Servo servo;

void setup(){
  //Initialize IR receiver
  irrecv.enableIRIn();
  irrecv.blink13(true);

  //Initialize servo
  servo.attach(SERVO_PIN);
  servo.write(90);

  //Uncomment for degubbing
  //Serial.begin(9600);
}

//Fires the catapault with the trigger servo
void fire(){
  servo.write(150);
  delay(500);
  servo.write(90);
}

void loop(){
  //Constantly monitors button presses to determine if the fire button has been pressed
  //TODO: reconfigure second if statement to use fire code constant rather than hard coded value
  if (irrecv.decode(&results)){
        if (results.value == 0xFFA25D){
          fire();
          delay(500);
        }
        irrecv.resume();
  }
}

/* 
 *  MY REMOTE CODES:
 *  POWER:    FFA25D
 *  MODE:     FF629D
 *  MUTE:     FFE21D
 *  PAUS/PLA: FF22DD
 *  SKIP B:   FF02FD
 *  SKIP F:   FFC23D
 *  EQ:       FFE01F
 *  MINUS:    FFA857
 *  PLUS:     FF906F
 *  0:        FF6897
 *  ZIGZAG:   FF9867
 *  USBSCAN:  FFBO4F
 *  1:        FF30CF
 *  2:        FF18E7
 *  3:        FF7A85
 *  4:        FF10EF
 *  5:        FF38C7
 *  6:        FF5AA5
 *  7:        FF42BD
 *  8:        FF4AB5
 *  9:        FF5CAD
 */
