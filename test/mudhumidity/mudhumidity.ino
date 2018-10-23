
// earth humidity test
// it looks like this is the right choice for dry-bot wet-floor detection.
// https://blog.csdn.net/xieyan0811/article/details/56011772
/*
用于土壤的湿度检测。
可通过电位器调节土壤湿度的阀值，顺时针调节，控制的湿度会越大，逆时针越小；
湿度低于设定值时，DO输出高电平，模块提示灯亮；湿度高于设定值时，DO输出低电平，模块提示灯灭。
工作电压3.3V-5V。3V时，在空气中AO读取的值最大为695 ， 浸泡在水里的 最小值245；
5V时，在空气中AO读取的值最大为1023 ，浸泡在水里的最小值 245。数值越小，湿度越高，反之越低。
湿度高于阈值时（实际读取数值小于阈值），D0=0，反之为1
*/

const int pinAO=2;
const int pinDO=12;

const int moisture_degress = 100;
int initial_readout = 0;
static int limit = 60;

void setup() {  
  pinMode(pinAO, INPUT);
  pinMode(pinDO, INPUT);  
  Serial.begin(9600); 
  Serial.println(" humidity test."); 
  
  Serial.println("min moisture:");Serial.println(moisture_convert(1023));  
  Serial.println("max moisture:");Serial.println(moisture_convert(245));
  Serial.println("conver of 821:");Serial.println(moisture_convert(821));

  initial_readout = analogRead(pinAO);
  Serial.println("current moisture:");
  Serial.print(initial_readout);
  Serial.print("->");
  Serial.println(moisture_convert(initial_readout));
  
  delay(2000);
}  

void loop()
{
   //return;
  test3();
  delay(1000);
}

void test1() {
  Serial.print("AO=");  
  Serial.print(analogRead(pinAO));
  Serial.print(", DO=");  
  Serial.println(digitalRead(pinDO));
  delay(1500);  
}

void test2()
{
  bool is_floor_wet = false;
  unsigned int moisture = 0;

  int readouts = analogRead(pinAO);
  moisture = moisture_convert(readouts);
  is_floor_wet = digitalRead(pinDO)==0?true:false;

  Serial.print("AO read:");Serial.println(readouts);
  Serial.print("Moisture:");Serial.println(moisture);
  
  if(is_floor_wet) {
    Serial.println("wet floor detected!");
  }
}


void test3()
{
  bool is_do = false;
  unsigned int moisture = 0;

  int readout = analogRead(pinAO);
  moisture = moisture_convert(readout);
  is_do = digitalRead(pinDO)==0?true:false;

  Serial.print("AO read:");Serial.println(readout);
  Serial.print("Moisture:");Serial.println(moisture);
  
  if(is_do) {
    Serial.println("wet floor detected by DO read!");
  }
  if( (initial_readout-readout)>=limit) {
    Serial.println("wet floor detect by AO read.");  
  }
}

// convert the analog readouts to a relative moisture:1~99. 
unsigned int moisture_convert(int readout)
{
  return readout;
  
  unsigned int mMAX=1024, mMIN=245;
  unsigned int interval = (mMAX-mMIN)/moisture_degress;
  return ((mMAX-readout)/interval);
}
