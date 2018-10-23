
// test No.5 water sensor. MH-unknown

// test pass.  dry->0,  1 square cm -> about 700

const int pinWater = A0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("water sensor test begin.");
}

void loop() {
  // put your main code here, to run repeatedly:
  // test1();
}

void test1()
{
  Serial.println("reading...:");
  Serial.println(analogRead(pinWater));
  delay(1000);
}
