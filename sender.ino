#define pin1 3
#define pin3 4
#define pin4 A1
#define pin5 6

#define acl 9
#define sum 7
#define we 8
#define l1 1
#define l2 2
#define m 3
#define ba 6
#define r2 4
#define r1 5
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>   //NRF24L01 2.4G无线模块的库文件,已发群里
RF24 radio(7, 8);   //创建一个RF24的对象CE=7, CSN=8
const byte address[6] = "00001";  //创建一个数组，建立发送机地址，或者说两个模块将用于通信的“管道”
int cases = 0;

void setup() {
Serial.begin(9600);
pinMode(pin1, INPUT);
pinMode(pin3, INPUT);
pinMode(pin4, INPUT);
radio.begin();    //初始化radio对象
  radio.openWritingPipe(address);  //使用radio.openWritingPipe（）函数设置的发送机地址
  radio.setPALevel(RF24_PA_MIN);  //设置功率放大器级别，将其设置为最小值
  radio.stopListening();  // 使用radio.stopListening()函数将模块设置为发送机
}

void loop() {
if (digitalRead(pin1) == 0) {
  cases = sum;
  send(cases);
  delay(500);
  for (int i = 2; i>1; i++) {
      if(digitalRead(pin1) == 0) {
      i = 0;
      cases = acl;
      send (cases);
      delay(500);
    }
    
    Serial.print(0);
    if(digitalRead(pin3) == 0){
      cases = we;
      send(we);
      delay(500);
      for (int a = 2; a > 1; a++){
      if(digitalRead(pin1) == 0){
      i = 0;
      a = 0;
      cases = acl;
      send (cases);
      delay(500);
     } else if (digitalRead(pin5) == 0){
      cases = ba;
      send(cases);
      delay(30);
      }else if (digitalRead(pin3) == 0){
       a = 0;
      cases = sum;
      send (cases);
      delay(500);
     }
     else if (analogRead(pin4) > 0 && analogRead(pin4) <= 209){
        cases = l1;
        send(cases);
      }else if (analogRead(pin4) > 209 && analogRead(pin4) <= 409){
        cases = l2;
        send(cases);
      }else if (analogRead(pin4) > 409 && analogRead(pin4) <= 714){
        cases = m;
        send(cases);
      }else if (analogRead(pin4) > 714 && analogRead(pin4) <= 914){
        cases = r2;
        send(cases);
      }else if (analogRead(pin4) > 914 && analogRead(pin4) <= 1023){
        cases = r1;
        send(cases);}
      }
     }
    }
  }
}



void send (int c) {
 radio.write(&c, sizeof(c)); 
 Serial.println(c);
}
