#define ENA   10
#define ENB   9
#define IN_1  8
#define IN_2  7
#define IN_3  6
#define IN_4  5
#define l1 15
#define l2 16
#define l3 17
#define l4 18
#define l5 19
#define vr A5
byte speedDiv = 3;
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
void turnRight(int sp) {
  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, sp);
  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);
  analogWrite(ENB, sp);
  //  delay(5);
}
void turnLeft(int sp) {
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);
  analogWrite(ENA, sp);
  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);
  analogWrite(ENB, sp);
  //  delay(5);
}
//void goAheadLeft(int sp) {
//  digitalWrite(IN_1, LOW);
//  digitalWrite(IN_2, HIGH);
//  analogWrite(ENA, sp / speedDiv);
//  digitalWrite(IN_3, LOW);
//  digitalWrite(IN_4, HIGH);
//  analogWrite(ENB, sp);
//}
//void goAheadRight(int sp) {
//  digitalWrite(IN_1, LOW);
//  digitalWrite(IN_2, HIGH);
//  analogWrite(ENA, sp);
//  digitalWrite(IN_3, LOW);
//  digitalWrite(IN_4, HIGH);
//  analogWrite(ENB, sp / speedDiv);
//}
void stopCar() {
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, 0);
  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, LOW);
  analogWrite(ENB, 0);
}
boolean IFsensor(byte pinSS) {
  return !digitalRead(pinSS);
}
byte IFsensor_return() { //0-255 unit8_t ~ byte
  boolean ifs1 = IFsensor(l1);
  boolean ifs2 = IFsensor(l2);
  boolean ifs3 = IFsensor(l3);
  boolean ifs4 = IFsensor(l4);
  boolean ifs5 = IFsensor(l5);
  //  Serial.print(ifs1); Serial.print("\t");
  //  Serial.print(ifs2); Serial.print("\t");
  //  Serial.print(ifs3); Serial.print("\t");
  //  Serial.print(ifs4); Serial.print("\t");
  //  Serial.println(ifs5);  //  Serial.print("\t");
  if (ifs1 == 0 && ifs2 == 0 && ifs3 == 0 && ifs4 == 0 && ifs5 == 0)  return 0;
  else if (ifs1 == 1 && ifs2 == 0 && ifs3 == 0 && ifs4 == 0 && ifs5 == 0)  return 1;
  else if (ifs1 == 1 && ifs2 == 1 && ifs3 == 0 && ifs4 == 0 && ifs5 == 0)  return 2;
  else if (ifs1 == 0 && ifs2 == 1 && ifs3 == 0 && ifs4 == 0 && ifs5 == 0)  return 3;
  else if (ifs1 == 0 && ifs2 == 1 && ifs3 == 1 && ifs4 == 0 && ifs5 == 0)  return 4;
  else if (ifs1 == 0 && ifs2 == 0 && ifs3 == 1 && ifs4 == 0 && ifs5 == 0)  return 5;
  else if (ifs1 == 0 && ifs2 == 0 && ifs3 == 1 && ifs4 == 1 && ifs5 == 0)  return 6;
  else if (ifs1 == 0 && ifs2 == 0 && ifs3 == 0 && ifs4 == 1 && ifs5 == 0)  return 7;
  else if (ifs1 == 0 && ifs2 == 0 && ifs3 == 0 && ifs4 == 1 && ifs5 == 1)  return 8;
  else if (ifs1 == 0 && ifs2 == 0 && ifs3 == 0 && ifs4 == 0 && ifs5 == 1)  return 9;
  else if (ifs1 == 1 && ifs2 == 1 && ifs3 == 1 && ifs4 == 1 && ifs5 == 1) return 10;
  else if (ifs1 == 1 && ifs2 == 1 && ifs3 == 1 && ifs4 == 0 && ifs5 == 0) return 11;
  else if (ifs1 == 0 && ifs2 == 0 && ifs3 == 1 && ifs4 == 1 && ifs5 == 1) return 12;
  else if (ifs1 == 0 && ifs2 == 1 && ifs3 == 1 && ifs4 == 1 && ifs5 == 0) return 13;
}
