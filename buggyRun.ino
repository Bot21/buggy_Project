//main file that runs when program is called.

#include <Servo.h>
#include "motors.h"
#include "servo.h"
#include "ultrasonic.h"
#include <NewPing.h>

int go = 1; //bool to track status of buggy motion
int i = 0; //bool to track number of turns made
int j = 0; //bool that decides whether buggy should turn in response to side sensor measurements.
int cm1 = 0; //cm1 for distance of Front sensor, cm2 for distance of Side sensor
int cm2 = 0;
int dist = 0; //variable to keep the previous measurement of cm2 for distance calculation

NewPing sonar(trigPinF, echoPinF, max_dist);

void setup(){
  pinMode(trigPinF, OUTPUT);
  pinMode(echoPinF, INPUT);
  pinMode(trigPinS, OUTPUT);
  pinMode(echoPinS, INPUT);
//  pinMode(trigPinSF, OUTPUT);
//  pinMode(echoPinSF, INPUT);
//  pinMode(trigPinSB, OUTPUT);
//  pinMode(echoPinSB, INPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  servo1.attach(11);

  Serial.begin(9600);
}

long readPing(){
  int distance = sonar.ping_cm();
  return distance;
}

void loop() {

//  if (state == 1){
//    clockwise();
//  }
//  else if (state == 0){
//    anticlockwise();
//  }
//
//  delay(1000);
//
//  if (i % 2 == 0){
//    state = 1;
//  }
//  else {
//    state = 0;
//  }
//  i++;

  cm1 = ultrasound(trigPinF, echoPinF);
  dist = cm2;
  cm2 = ultrasound(trigPinS, echoPinS);

// cm1 = sonar.ping_cm();

  Serial.print(cm2);
  Serial.println(" cm2");


  if (cm1 >= 10){
    i = 0;
    go = 1;
    forward();

    if (cm2 > 20 && j == 0){ //if there is a path to the left, and buggy is allowed to turn i.e. j == 0
      j = 1; //This is to ensure buggy does not turn repeatedly.
      delay(300);//delay to ensure buggy clears the wall to its side before turning.
      clockwise();
    }
    else if (cm2 < 15){
      j = 0;//Enables buggy to turn only if it sensed a wall previously. 
    }
    else if (cm2 - dist > 0 && j == 0){
      adjust_clock(); //if buggy is moving away from wall and is allowed to turn, make a clocwise adjustment
    }
    else if (cm2 - dist < 0 && j == 0){
      adjust_anticlock(); //if buggy is toward from wall and is allowed to turn, make a anticlocwise adjustment
    }
  } 
  else if (cm1 < 10){
    go = 0;
    ++i;
    freeze(); //Stop and move backwards for some space.
    backward();
      if (i == 1){
        anticlockwise(); //Turn anticlockwise. 
        delay(100);
      }
      else if (i == 2){
        anticlockwise(); //Go back the way it came.
        i = 0;
        delay(100);
      }
  }

//  if (go == 0){
//    compare(trigPinSF, echoPinSF, trigPinSB, echoPinSB);
//  }
}
