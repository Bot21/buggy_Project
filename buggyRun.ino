//main file that runs when program is called.

#include <Servo.h>
#include "motors.h"
#include "servo.h"
#include "ultrasonic.h"
#include <NewPing.h>

int go = 1; //bool to track status of buggy motion
int i = 0;
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

  Serial.print(cm1);
  Serial.println(" cm1");


//  if (cm1 >= 5){
//    i = 0;
//    go = 1;
//    forward();

    if (cm2 > 10 ){
      clockwise();
      forward();
    }
//  } 
//  else if (cm1 < 5){
//    go = 0;
//    ++i;
//    freeze();
//    backward();
//    //calculate distance after turning.
//      if (i == 1){
//        
//        anticlockwise();
//        delay(100);
//      }
//      else if (i == 2){
//        
//        clockwise();
//        clockwise();
//        delay(100);
//      }
//      else if (i == 3){
//        anticlockwise();
//        i = 0;
//        delay(100);
//      }
//  }

//  if (go == 0){
//    compare(trigPinSF, echoPinSF, trigPinSB, echoPinSB);
//  }
}
