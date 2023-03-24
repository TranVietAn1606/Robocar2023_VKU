#include <Servo.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define ENA   3
#define IN_1  4
#define IN_2  8  //5->8
#define IN_3  6
#define IN_4  7
#define ENB   5 //8->5

#define Sv1 19 // A5
#define Sv2 16 // A2
#define Sv3 17 // A3
#define Sv4 14 // A0

Servo servo1, servo2, servo3, servo4;

const uint64_t pipe = 0xA1E8F0F0E1LL;
RF24 radio(9, 10); //CE,CSN
struct Mydata {
  int val_vr1;
  int val_vr2;
  int val_vr3;
  int val_vr4;
  int val_vrX1;
  int val_vrY1;
  int val_vrX2;
  int val_vrY2;
  int val_bt1;
  int val_bt2;
  int val_bt3;
  int val_bt4;
};
Mydata data;

int speedCar = 1000;
int speedDiv = 3;
void goAhead(int sp);
void goBack(int sp);
void turnLeft(int sp);
void turnRight(int sp);
void goAheadLeft(int sp);
void goAheadRight(int sp);
void goBackLeft(int sp);
void goBackRight(int sp);
void stopCar();
void dataControl();

void setup() {
  servo1.attach(Sv1);
  servo2.attach(Sv2);
  servo3.attach(Sv3);
  Serial.begin(9600);
  Serial.println("Begin");
  radio.begin();
  radio.setDataRate(RF24_250KBPS);
  radio.openReadingPipe(0, pipe);
  radio.setPALevel(RF24_PA_MAX);
  radio.setChannel(80);
  radio.startListening();
}

void loop() {
    dataControl();
//  goAhead(1000);
}

void goAhead(int sp) {
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);
  analogWrite(ENA, sp);
  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);
  analogWrite(ENB, sp);
}
void goBack(int sp) {
  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, sp);
  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);
  analogWrite(ENB, sp);
}
void turnLeft(int sp) {
  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, sp);
  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);
  analogWrite(ENB, sp);
}
void turnRight(int sp) {
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);
  analogWrite(ENA, sp);
  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);
  analogWrite(ENB, sp);
}
void goAheadLeft(int sp) {
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);
  analogWrite(ENA, sp / speedDiv);
  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);
  analogWrite(ENB, sp);
}
void goAheadRight(int sp) {
  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);
  analogWrite(ENB, sp / speedDiv);

  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);
  analogWrite(ENA, speedCar);
}
void goBackLeft(int sp) {
  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, sp / speedDiv);
  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);
  analogWrite(ENB, sp);
}
void goBackRight(int sp) {
  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);
  analogWrite(ENB, sp / speedDiv);

  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, sp);
}
void stopCar() {
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, 0);
  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, LOW);
  analogWrite(ENB, 0);
}

void dataControl() {
  if (radio.available()) {
    radio.read(&data, sizeof(Mydata));
  }
  //  Serial.print(data.val_vr1);
  //  Serial.print("\t");
  //  Serial.print(data.val_vr2);
  //  Serial.print("\t");
  //  Serial.print(data.val_vr3);
  //  Serial.print("\t");
  //  Serial.print(data.val_vr4);
  //  Serial.print("\t");
  //  Serial.print(data.val_vrX1);
  //  Serial.print("\t");
  //  Serial.print(data.val_vrY1);
  //  Serial.print("\t");
  //  Serial.print(data.val_vrX2);
  //  Serial.print("\t");
  //  Serial.print(data.val_vrY2);
  //  Serial.print("\t");
  //  Serial.print(data.val_bt1);
  //  Serial.print("\t");
  //  Serial.print(data.val_bt2);
  //  Serial.print("\t");
  //  Serial.print(data.val_bt3);
  //  Serial.print("\t");
  //  Serial.print(data.val_bt4);
  //  Serial.print("\n");
  speedCar = data.val_vr4;
  servo1.write(data.val_vr1);
  servo2.write(data.val_vr2);
  servo3.write(data.val_vr3);
  if (data.val_bt1 == 1 && data.val_bt2 == 0 && data.val_bt3 == 0 && data.val_bt4 == 0) goAhead(speedCar);
  else if (data.val_bt1 == 0 && data.val_bt2 == 1 && data.val_bt3 == 0 && data.val_bt4 == 0) goBack(speedCar);
  else if (data.val_bt1 == 0 && data.val_bt2 == 0 && data.val_bt3 == 1 && data.val_bt4 == 0) turnLeft(speedCar) ;
  else if (data.val_bt1 == 0 && data.val_bt2 == 0 && data.val_bt3 == 0 && data.val_bt4 == 1) turnRight(speedCar);
  else if (data.val_bt1 == 1 && data.val_bt2 == 0 && data.val_bt3 == 1 && data.val_bt4 == 0) goAheadLeft(speedCar);
  else if (data.val_bt1 == 1 && data.val_bt2 == 0 && data.val_bt3 == 0 && data.val_bt4 == 1) goAheadRight(speedCar);
  else if (data.val_bt1 == 0 && data.val_bt2 == 1 && data.val_bt3 == 1 && data.val_bt4 == 0) goBackLeft(speedCar);
  else if (data.val_bt1 == 0 && data.val_bt2 == 1 && data.val_bt3 == 0 && data.val_bt4 == 1) goBackRight(speedCar);
  else stopCar();
}
