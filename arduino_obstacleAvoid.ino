// SPAC2 초음파센서 서보패닝 장애물회피 구동실험

int Left_motor_back=8;     //좌측모터후진(IN1)
int Left_motor_go=9;     //좌측모터전진(IN2)

int Right_motor_go=10;    // 우측모터전진(IN3)
int Right_motor_back=11;    // 우측모터후진(IN4)

int Echo = A1;  // 초음파센서 Echo
int Trig = A0;  // 초음파센서 Trig

int Front_Distance = 0;
int Left_Distance = 0;
int Right_Distance = 0;

int servopin=2;//서보모터핀을 2번으로 설정
int myangle;//서보모터각도
int pulsewidth;//펄스폭 설정
int val;

void setup()
{
  //모터구동을을 위한 초기화
  pinMode(Left_motor_go,OUTPUT); // PIN 8 (PWM)
  pinMode(Left_motor_back,OUTPUT); // PIN 9 (PWM)
  pinMode(Right_motor_go,OUTPUT);// PIN 10 (PWM)
  pinMode(Right_motor_back,OUTPUT);// PIN 11 (PWM)

  //초음파센서 핀설정
  pinMode(Echo, INPUT);    // 입력설정
  pinMode(Trig, OUTPUT);   // 출력설정
  //서보모터 핀설정
  pinMode(servopin,OUTPUT);// 출력설정
}
void run()     // 전진
{
  digitalWrite(Right_motor_go,HIGH);  // 우측모터전진
  digitalWrite(Right_motor_back,LOW);
  analogWrite(Right_motor_go,100);//PWM값 0~255 조정,모터의 회전속도 조절.
  analogWrite(Right_motor_back,0);
  digitalWrite(Left_motor_go,HIGH);  // 좌측모터전진
  digitalWrite(Left_motor_back,LOW);
  analogWrite(Left_motor_go,100);//PWM값 0~255 조정,모터의 회전속도 조절.
  analogWrite(Left_motor_back,0);
  //delay(time * 100);   //딜레이
}

void brake(int time)         //제동, 정지
{
  digitalWrite(Right_motor_go,LOW);
  digitalWrite(Right_motor_back,LOW);
  digitalWrite(Left_motor_go,LOW);
  digitalWrite(Left_motor_back,LOW);
  delay(time * 100);//딜레이
}

void left(int time)         //좌회전(좌측정지，우측직진)
{
  digitalWrite(Right_motor_go,HIGH);  // 우측모터전진
  digitalWrite(Right_motor_back,LOW);
  analogWrite(Right_motor_go,100);
  analogWrite(Right_motor_back,0);//PWM값 0~255 조정,모터의 회전속도 조절.
  digitalWrite(Left_motor_go,LOW);   //좌측모터정지
  digitalWrite(Left_motor_back,LOW);
  analogWrite(Left_motor_go,0);
  analogWrite(Left_motor_back,0);//PWM값 0~255 조정,모터의 회전속도 조절.
  delay(time * 100);  //딜레이
}

void spin_left(int time)         //좌측스핀(좌측후진，우측직진)
{
  digitalWrite(Right_motor_go,HIGH);  // 우측모터전진
  digitalWrite(Right_motor_back,LOW);
  analogWrite(Right_motor_go,100);
  analogWrite(Right_motor_back,0);//PWM값 0~255 조정,모터의 회전속도 조절.
  digitalWrite(Left_motor_go,LOW);   //좌측모터후진
  digitalWrite(Left_motor_back,HIGH);
  analogWrite(Left_motor_go,0);
  analogWrite(Left_motor_back,100);//PWM값 0~255 조정,모터의 회전속도 조절.
  delay(time * 100);  //딜레이
}

void right(int time)        //우회전(우측정지, 좌측직진)
{
  digitalWrite(Right_motor_go,LOW);   //우측모터정지
  digitalWrite(Right_motor_back,LOW);
  analogWrite(Right_motor_go,0);
  analogWrite(Right_motor_back,0);//PWM값 0~255 조정,모터의 회전속도 조절.
  digitalWrite(Left_motor_go,HIGH);//좌측모터전진
  digitalWrite(Left_motor_back,LOW);
  analogWrite(Left_motor_go,100);
  analogWrite(Left_motor_back,0);//PWM값 0~255 조정,모터의 회전속도 조절.
  delay(time * 100);  //딜레이
}

void spin_right(int time)        //우측스핀(우측후진, 좌측전진)
{
  digitalWrite(Right_motor_go,LOW);   //우측모터후진
  digitalWrite(Right_motor_back,HIGH);
  analogWrite(Right_motor_go,0);
  analogWrite(Right_motor_back,100);//PWM값 0~255 조정,모터의 회전속도 조절.
  digitalWrite(Left_motor_go,HIGH);//좌측모터전진
  digitalWrite(Left_motor_back,LOW);
  analogWrite(Left_motor_go,100);
  analogWrite(Left_motor_back,0);//PWM값 0~255 조정,모터의 회전속도 조절.
  delay(time * 100);  //딜레이
}

void back(int time)          //후진
{
  digitalWrite(Right_motor_go,LOW);  //우측모터후진
  digitalWrite(Right_motor_back,HIGH);
  analogWrite(Right_motor_go,0);
  analogWrite(Right_motor_back,200);//PWM값 0~255 조정,모터의 회전속도 조절.
  digitalWrite(Left_motor_go,LOW);  //좌측모터후진
  digitalWrite(Left_motor_back,HIGH);
  analogWrite(Left_motor_go,0);
  analogWrite(Left_motor_back,200);//PWM값 0~255 조정,모터의 회전속도 조절.
  delay(time * 100);     //딜레이
}

float Distance_test()   // 전방거리측정
{
  digitalWrite(Trig, LOW);   // 트리거핀LOW 2μs
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);  // 트리거핀HIGH 10μs
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);    // 트리거핀 LOW
  float Fdistance = pulseIn(Echo, HIGH);  // HIGH 시간 읽기 (단위:MICRO SECOND)
  Fdistance= Fdistance/58;       //58로나누면 CM로 변환，  Y미터=（X초*344）/2
  // X초=（ 2*Y미터）/344 ==》X초=0.0058*Y미터 ==》CM = MICRO SECOND/58
  return Fdistance;
}

void servopulse(int servopin,int myangle) //서보모터를 각도만큼 회전
{
  pulsewidth=(myangle*11)+500;//각도를 500-2480 사이의 펄스값으로 변환
  digitalWrite(servopin,HIGH);//서보핀 HIGH
  delayMicroseconds(pulsewidth);//펄스폭만큼 딜레이
  digitalWrite(servopin,LOW);//서보핀 LOW
  delay(20-pulsewidth/1000);//남은 딜레이
}

void front_detection() //전방 장애물 감지
{

  for(int i=0;i<=5;i++)
  {
    servopulse(servopin,90);//서보모터 PWM펄스 발생
  }
  Front_Distance = Distance_test();
}

void left_detection()
{
  for(int i=0;i<=15;i++)
  {
    servopulse(servopin,175);//서보모터 PWM펄스 발생
  }
  Left_Distance = Distance_test();
}

void right_detection()
{
  for(int i=0;i<=15;i++)
  {
    servopulse(servopin,5);//서보모터 PWM펄스 발생(우측서보패닝)
  }
  Right_Distance = Distance_test();
}

void loop()
{
  while(1)
  {
    front_detection();//전방거리측정
    if(Front_Distance < 32)//전방 장애물 감지시
    {
      back(2);//후진
      brake(2);//정지
      left_detection();//좌측거리측정
      right_detection();//우축거리측정
      if((Left_Distance < 35 ) &&( Right_Distance < 35 ))//좌우 양측에 장애물이 감지시
        spin_left(0.7);//방향전환시도
      else if(Left_Distance > Right_Distance)//좌측이 우측보다 공간여유가 있는 경우
      {
        left(3);//좌회전
        brake(1);//정지
      }
      else//우측이 좌측보다 공간여유가 있는 경우
      {
        right(3);//우회전
        brake(1);//정지
      }
    }
    else
    {
      run(); //전방 장애물이 없는 경우 전진
    }
  }
}
