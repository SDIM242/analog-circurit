
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

Servo zkyservo;
Servo cyservo;
int relayServo=2;
int relayPump=11;
RF24 radio(7, 8);   //创建一个RF24的对象CE=7, CSN=8
const byte address[6] = "00001";  //创建一个数组，建立接收机地址，或者说两个模块将用于通信的“管道”


void setup() {
  Serial.begin(9600);
  radio.begin();   //初始化radio对象
  radio.openReadingPipe(0, address);   //使用radio.openReadingPipe（）函数设置的接收机地址
  radio.setPALevel(RF24_PA_MIN);   //设置功率放大器级别，将其设置为最小值
  radio.startListening();    // 使用radio..startListening()将模块设置为接收机
  cyservo.attach(3);
  zkyservo.attach(15);
  pinMode(relayServo,OUTPUT);
  pinMode(relayPump,OUTPUT);
  cyservo.write(40);
  zkyservo.write(40);
}

void loop() {
  if (digitalRead(relayServo)==0){
    digitalWrite(relayPump,LOW);
  }
  if (radio.available()) {
     int text;
     radio.read(&text, sizeof(text));
     Serial.println(text);
     switch(text)
     {
      case 1:
          OpenRelayServo();
          Forward();
          zkyservo.write(10);
          break;
      case 2:
          OpenRelayServo();
          Forward();
          zkyservo.write(25);
          break;
      case 3:
          OpenRelayServo();
          Forward();
          zkyservo.write(40);
          break;
      case 4:
          OpenRelayServo();
          Forward();
          zkyservo.write(55);
          break;
      case 5:
          OpenRelayServo();
          Forward();
          zkyservo.write(70);
          break;
      case 6:
          OpenRelayServo();
          zkyservo.write(40);
          Backoff();
          break;
      case 7:
          OpenRelayServo();
          CloseRelayPump();
          break;
      case 8:
          OpenRelayServo();
          OpenRelayPump();
          break;
      case 9:
          CloseRelayServo();
          break;
     }
  }

}
void OpenRelayServo()
{
  digitalWrite(relayServo,HIGH);
}

void CloseRelayServo()
{
  digitalWrite(relayServo,LOW);
  if(digitalRead(relayPump)==1){
    digitalWrite(relayPump,LOW);
  }
}

void OpenRelayPump()
{
  if(digitalRead(relayServo)==1){
    digitalWrite(relayPump,HIGH);
  }
}

void CloseRelayPump()
{
  digitalWrite(relayPump,LOW);
}

void Forward()
{
  cyservo.write(40);
}

void Backoff()
{
  cyservo.write(0);
}
