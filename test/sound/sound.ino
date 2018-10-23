

int RE =3 ;              //定义录音引脚
int PL =4 ;              //定义播放引脚
void setup()
{
  Serial.begin(9600);
  Serial.println("start sound play and recording test.");
  
  pinMode(RE, OUTPUT);     //设置RE为输出
  pinMode(PL, OUTPUT);     //设置PL为输出
} 

void loop()
{
  digitalWrite(RE, LOW);  
  digitalWrite(PL, LOW);  
  delay(1000);
  
  Serial.println("start recording for 6 secs.");
  digitalWrite(RE, HIGH);  
  delay(6000);
  digitalWrite(RE, LOW);  
  delay(1000);

  Serial.println("start playing for 6secs.");
  digitalWrite(PL, HIGH);  
  delay(6000);

}

/* 
int play = 4 ;
int rec = 3 ;

void setup() {
  Serial.begin(9600);
  Serial.println("start sound play and recording test.");

  Serial.println("start playing for 10secs.");
  pinMode(play,OUTPUT);//针脚模式设置为数字输出
  pinMode(rec,OUTPUT);//针脚模式设置为数字输出
  digitalWrite(play,HIGH);//开始播放已有的录音
  delay(10000);//保持播放状态10秒

  digitalWrite(play,LOW);//关闭播放
  delay(1000);//保持关闭1秒---这行省略会出现bug
  
  Serial.println("start recording for 5 secs.");
  digitalWrite(rec,HIGH);//开始录音
  delay(5000);//保持录音状态10秒
  digitalWrite(rec,LOW);//关闭录音
  delay(1000);//保持关闭1秒---这行省略会导致重启不能录音

  Serial.println("start  playing the sound just recorded.");
  digitalWrite(play,HIGH); //播放刚刚录制的声音
}

void loop() {

}
*/


/*
作者：爱猫猫的老狗
链接：https://www.jianshu.com/p/d4a1a9a86507
來源：简书
简书著作权归作者所有，任何形式的转载都请联系作者获得授权并注明出处。
*/
