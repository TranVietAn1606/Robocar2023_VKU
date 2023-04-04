#include "func.h"
//[390 50 30 10], [390 50 30 10]
int sp = 390;
byte s1 = 50, s2 = 30, s3 = 10;
void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  pinMode(IN_3, OUTPUT);
  pinMode(IN_4, OUTPUT);
  pinMode(l1, INPUT);
  pinMode(l2, INPUT);
  pinMode(l3, INPUT);
  pinMode(l4, INPUT);
  pinMode(l5, INPUT);
  pinMode(vr, INPUT);
  Serial.begin(9600);
  Serial.println("Begin:....");
}
void loop() {

  //  turnRight(sp);
  switch (IFsensor_return()) {
    case 0:
      Serial.println("000");
      //      goBack(sp);
      break;
    case 1:
      Serial.println("Right 1");
      turnLeft(sp + s1);
      break;
    case 2:
      Serial.println("Right 1+2");
      turnLeft(sp + s2);
      break;
    case 3:
      Serial.println("Right 2");
      turnLeft(sp + s3);
      break;
    case 4:
      Serial.println("Right 2+3");
      turnLeft(sp);
      break;
    case 5:
      Serial.println("Ahead");
      goAhead(sp);
      break;
    case 6:
      Serial.println("left 2+3");
      turnRight(sp);
      break;
    case 7:
      Serial.println("Left 2");
      turnRight(sp + s3);
      break;
    case 8:
      Serial.println("Left 1+2");
      turnRight(sp + s2);
      break;
    case 9:
      Serial.println("Left 1");
      turnRight(sp + s1);
      break;
    case 10:
      Serial.println("Stop");
      stopCar();
      delay(500);
      break;
    case 11:
      Serial.println("Right 1+2+3");
      turnLeft(sp + s1);
      delay(50);
      break;
//    case 12:
//      Serial.println("Left 1+2+3");
//      turnRight(sp + s1);
//      delay(50);
//      break;
      //      case 13:
      //        Serial.println("Left 1+2+3");
      //        goAheadLeft(spL - s2);
      //        break;
  }
}
