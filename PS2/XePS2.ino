//Trần Viết An 19CE001
#include <AFMotor.h>
#include <PS2X_lib.h>
AF_DCMotor motor1(1,MOTOR12_64KHZ);
AF_DCMotor motor2(2,MOTOR12_64KHZ);
AF_DCMotor motor3(3,MOTOR12_64KHZ);
AF_DCMotor motor4(4,MOTOR12_64KHZ);

PS2X ps2x;
int error = 0;
int type = 0;
int vibrate = 0;
int  ps2;

void setup(){
//  pinMode(9,OUTPUT);
  motor1.setSpeed(255);
  motor2.setSpeed(255);
  motor3.setSpeed(255);
  motor4.setSpeed(255);

// chân data: 12. cmd: 11, cs: 10; clk: 13
// chân data: A5. cmd: A4, cs: A3, clk: A2
error = ps2x.config_gamepad(A2,A4,A3,A5,true,true);
Serial.begin(9600);

 if(error == 0){
   Serial.println("Đã tìm thấy Bộ điều khiển, đã định cấu hình thành công ");
 }
  else if(error == 1)
   Serial.println("Không tìm thấy bộ điều khiển, hãy kiểm tra hệ thống dây điện");
   
  else if(error == 2)
   Serial.println("Đã tìm thấy bộ điều khiển nhưng không chấp nhận lệnh");
   
  else if(error == 3)
   Serial.println("Bộ điều khiển từ chối vào chế độ Pressures, có thể không hỗ trợ nó.  ");

   type = ps2x.readType(); 
   switch(type)
   {
    case 0:
      Serial.println("Loại bộ điều khiển không xác định ");
      break;
    case 1:
      Serial.println("Đã tìm thấy bộ điều khiển DualShock ");
      break;
    case 2:
      Serial.println("Đã tìm thấy bộ điều khiển Guitar Hero ");
      break;
   }
}
  
void sp(int s){     //dieu chinh toc do
  motor1.setSpeed(s);
  motor2.setSpeed(s);
  motor3.setSpeed(s);
  motor4.setSpeed(s);
}
//toi F
void tien(){    
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}
//lui B 
void lui(){   
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}
// trai L
void trai(){    
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(FORWARD);
}
//phai R
void phai(){   
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(BACKWARD);
}
// toi trai  G
void tientrai(){  
  motor1.run(FORWARD);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(FORWARD);
}
//toi phai I
void tienphai(){  
  motor1.run(RELEASE);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(RELEASE);
}
//lui trai  H
void luitrai(){   
  motor1.run(BACKWARD);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(BACKWARD);
}
//lui phai  J
void luiphai(){  
  motor1.run(RELEASE);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(RELEASE);
}

//dung S
void st(){    
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void carRun(){
  ps2x.read_gamepad(false, vibrate);
  
  if(ps2x.Button(PSB_PAD_UP)){
    ps2 = 1;
    Serial.println("tien");
  }else if(ps2x.Button(PSB_PAD_DOWN)){
    ps2 = 2;
    Serial.println("lui");  
  }
  else if(ps2x.Button(PSB_PAD_LEFT)){
    ps2 = 3;
    Serial.println("trai");
    
  }  else if(ps2x.Button(PSB_PAD_RIGHT)){
    ps2 = 4;
    Serial.println("phai");
    
  }
    else if(ps2x.Button(PSB_PINK)){
      ps2 = 5;
      Serial.println("tien trai");
    
  }
    else if(ps2x.Button(PSB_RED)){
      ps2 = 6;
    Serial.println("tien phai");
  }
    else if(ps2x.Button(PSB_BLUE)){
      ps2 = 7;
      Serial.println("lui trai");
    
  }
    else if(ps2x.Button(PSB_GREEN)){
      ps2 = 8;
      Serial.println("lui phai");
    
  }
    else if(ps2x.Button(PSB_L1)){
    ps2 = 9;
    Serial.println("L1");
  }
    else if(ps2x.Button(PSB_L2)){
      ps2 = 10;
      Serial.println("L2");
    
  }
    else if(ps2x.Button(PSB_R1)){
      ps2 = 11;
      Serial.println("R1");
    
  }
  else if(ps2x.Button(PSB_R2)){
    ps2 = 12;
    Serial.println("R2");
    
  }
  else ps2 = 0;
delay(50);
}                                                                                                                                                                                                                                                                                                                                                                                                                

void loop(){
carRun();
if(ps2 ==1) tien();
else if(ps2 == 2) lui();
else if(ps2 == 3) trai();
else if(ps2 == 4) phai();
else if(ps2 == 5) tientrai();
else if(ps2 == 6) tienphai();
else if(ps2 == 7) luiphai();
else if(ps2 == 8) luitrai();
else if(ps2 == 9) sp(255);
else if(ps2 == 10) sp(180);
else if(ps2 == 11) sp(100);
else if(ps2 == 12) sp(0);

else st();
}
