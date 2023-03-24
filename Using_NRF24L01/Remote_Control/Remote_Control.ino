#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define ledPin  2
#define vr1 A1
#define vr2 A0
#define vr3 A2
#define vr4 A3
#define vrY1 A4 //duoi 0, tren 1023
#define vrX1 A5 // phai 0. trai 1023
#define sw1 4
#define vrY2 A6 // duoi 1023, tren 0
#define vrX2 A7 //trai 0, phai 1023
#define sw2 3
#define bt1 8
#define bt2 7
#define bt3 6
#define bt4 5

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
void setup() {

  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(vr1, INPUT);
  pinMode(vr2, INPUT);
  pinMode(vr3, INPUT);
  pinMode(vr4, INPUT);
  pinMode(bt1, INPUT);
  pinMode(bt2, INPUT);
  pinMode(bt3, INPUT);
  pinMode(bt4, INPUT);
  pinMode(vrX1, INPUT);
  pinMode(vrY1, INPUT);
  pinMode(vrX2, INPUT);
  pinMode(vrY2, INPUT);

  //  radio.begin();
  //  radio.setAutoAck(1);
  //  radio.setRetries(1, 1);
  //  radio.setDataRate(RF24_250KBPS);
  //  radio.setPALevel(RF24_PA_MAX);
  //  radio.setChannel(10);
  //  radio.openWritingPipe(pipe);

  radio.begin();
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(pipe);
  radio.setPALevel(RF24_PA_MAX);
  radio.setChannel(80);  
  radio.stopListening();
}

void loop() {
  int val_sv1 = analogRead(vr1);
  int val_sv2 = analogRead(vr2);
  int val_sv3 = analogRead(vr3);

  data.val_vr1 = map(val_sv1, 0, 1023, 0, 180);
  data.val_vr2 = map(val_sv2, 0, 1023, 0, 180);
  data.val_vr3 = map(val_sv3, 0, 1023, 80, 180);
  data.val_vr4 = analogRead(vr4);
  data.val_vrX1 = analogRead(vrX1);
  data.val_vrY1 = analogRead(vrY1);
  data.val_vrX2 = analogRead(vrX2);
  data.val_vrY2 = analogRead(vrY2);
  data.val_bt1 = digitalRead(bt1);
  data.val_bt2 = digitalRead(bt2);
  data.val_bt3 = digitalRead(bt3);
  data.val_bt4 = digitalRead(bt4);

  radio.write(&data, sizeof(Mydata));
}
