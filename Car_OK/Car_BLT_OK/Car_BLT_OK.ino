/*
   Author : Tran Viet An
   Class  : 19CE - VKU
   Github : TranVietAn1606/Robocar2023_VKU
   Content: Wireless control car with robot arm
   Contact: tvan.19ce@vku.udn.vn
*/
#include <SoftwareSerial.h>
#include <ServoTimer2.h>
#define ENA   10
#define ENB   9
#define IN_1  8
#define IN_2  7
#define IN_3  6
#define IN_4  5
#define SV_1 13
#define SV_2 12
#define SV_3 11

ServoTimer2 sv1, sv2, sv3;

SoftwareSerial mySerial(4, 0); // RX, TX
byte speed_Coeff = 3;
char data;
byte armVal, sp = 0;
int sv1Val = 2240, sv2Val = 750, sv3Val = 1795;

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  pinMode(IN_3, OUTPUT);
  pinMode(IN_4, OUTPUT);
  sv1.attach(SV_1); sv1.write(sv1Val);
  sv2.attach(SV_2); sv2.write(sv2Val);
  sv3.attach(SV_3); sv3.write(sv3Val);
  Serial.println("BLT OK");
  mySerial.begin(9600);
}
void loop() {
  if (mySerial.available()) {
    data = mySerial.read();
    if (data == 'X') armVal = 1;
    if (data == 'x') armVal = 0;
    if (armVal == 1) {
      if (data == 'F') {
        sv1Val = sv1Val + 24;
        if (sv1Val >= 2240) sv1Val = 2240;
      }
      if (data == 'B') {
        sv1Val = sv1Val - 24;
        if (sv1Val <= 1255 ) sv1Val = 1255;
      }
      if (data == 'R') {
        sv2Val = sv2Val + 24;
        if (sv2Val >= 2180) sv2Val = 2180;
      }
      if (data == 'L') {
        sv2Val = sv2Val - 24;
        if (sv2Val <= 750 ) sv2Val = 750;
      }

      if (data == 'G') {
        sv3Val = sv3Val + 24;
        if (sv3Val >= 2222) sv3Val = 2222;
      }
      if (data == 'I') {
        sv3Val = sv3Val - 24;
        if (sv3Val <= 1795 ) sv3Val = 1795;
      }
      sv1.write(sv1Val);
      sv2.write(sv2Val);
      sv3.write(sv3Val);
      delay(7);
    }

    else if (armVal == 0) {
      if (data == '0')  sp = 0;
      if (data == '1')  sp = 24;
      if (data == '2')  sp = 48;
      if (data == '3')  sp = 72;
      if (data == '4')  sp = 96;
      if (data == '5')  sp = 120;
      if (data == '6')  sp  = 144;
      if (data == '7')  sp = 168;
      if (data == '8')  sp = 192;
      if (data == '9')  sp = 226;
      if (data == 'p')  sp = 254;
      if (data == 'F')  goAhead(sp);
      if (data == 'B')  goBack(sp);
      if (data == 'L')  goLeft(sp);
      if (data == 'R')  goRight(sp);
      if (data == 'G')  goAheadLeft(sp);
      if (data == 'I')  goAheadRight(sp);
      if (data == 'H')  goBackLeft(sp);
      if (data == 'J')  goBackRight(sp);
      if (data == 'S')  stopCar();
    }
  }
}
void goAhead(byte speedCar) {
  digitalWrite(IN_1, 1);
  digitalWrite(IN_2, 0);
  analogWrite(ENA, speedCar);
  digitalWrite(IN_3, 1);
  digitalWrite(IN_4, 0);
  analogWrite(ENB, speedCar);
}
void goBack(byte speedCar) {
  digitalWrite(IN_1, 0);
  digitalWrite(IN_2, 1);
  analogWrite(ENA, speedCar);
  digitalWrite(IN_3, 0);
  digitalWrite(IN_4, 1);
  analogWrite(ENB, speedCar);
}
void goRight(byte speedCar) {
  digitalWrite(IN_1, 1);
  digitalWrite(IN_2, 0);
  analogWrite(ENA, speedCar);
  digitalWrite(IN_3, 0);
  digitalWrite(IN_4, 1);
  analogWrite(ENB, speedCar);
}
void goLeft(byte speedCar) {
  digitalWrite(IN_1, 0);
  digitalWrite(IN_2, 1);
  analogWrite(ENA, speedCar);
  digitalWrite(IN_3, 1);
  digitalWrite(IN_4, 0);
  analogWrite(ENB, speedCar);
}
void goAheadRight(byte speedCar) {
  digitalWrite(IN_1, 1);
  digitalWrite(IN_2, 0);
  analogWrite(ENA, speedCar );
  digitalWrite(IN_3, 1);
  digitalWrite(IN_4, 0);
  analogWrite(ENB, speedCar / speed_Coeff);
}
void goAheadLeft(byte speedCar) {
  digitalWrite(IN_1, 1);
  digitalWrite(IN_2, 0);
  analogWrite(ENA, speedCar / speed_Coeff);
  digitalWrite(IN_3, 1);
  digitalWrite(IN_4, 0);
  analogWrite(ENB, speedCar);
}
void goBackRight(byte speedCar) {
  digitalWrite(IN_1, 0);
  digitalWrite(IN_2, 1);
  analogWrite(ENA, speedCar);
  digitalWrite(IN_3, 0);
  digitalWrite(IN_4, 1);
  analogWrite(ENB, speedCar / speed_Coeff);
}
void goBackLeft(byte speedCar) {
  digitalWrite(IN_1, 0);
  digitalWrite(IN_2, 1);
  analogWrite(ENA, speedCar / speed_Coeff);
  digitalWrite(IN_3, 0);
  digitalWrite(IN_4, 1);
  analogWrite(ENB, speedCar);
}
void stopCar() {
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, LOW);
  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, LOW);
}
