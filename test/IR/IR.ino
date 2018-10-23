
// test No.3 IR distance sensor
// test fail on 9-18, always get 0.
// it turns out that , instead of distance to obstacles, IR gives only 1 or 0 indicats that there is  or there is not an obstacl.
// GND：接电源负极
// OUT：信号输出引脚，输出1表示前方没有障碍，输出0表示有障碍
// VCC：接电源正极


const int pinIR = 13;

void setup() {
  // put your setup code here, to run once:
  pinMode(pinIR,INPUT);
  Serial.begin(9600);
  Serial.println("IR test begin.");
}

void loop() {
  // put your main code here, to run repeatedly:
  test2();
}

void test1()
{
  int x = digitalRead(pinIR);
  Serial.println(x);
  delay(500);    
}

void test2()
{
  int x = digitalRead(pinIR);
  bool blocked = x==0?true:false;
  if(blocked) {
    Serial.println("obstacle detected.");
  } else {
    Serial.println("path clear.");
  }
  delay(500);
}

// end of file
