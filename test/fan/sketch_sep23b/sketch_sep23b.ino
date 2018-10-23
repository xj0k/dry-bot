
// test for fan (modified from a USB fan)
// failed on 9-23:
// works fine if connect the lines of fan direct into VCC-5v and GND of arduino.
// But fails when plug the red line into one of the digital port.

const int pinFAN = 7;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Fan test begin");

    pinMode(pinFAN,OUTPUT);
    digitalWrite(pinFAN,LOW);  

}

void loop() {
  // put your main code here, to run repeatedly:
  test2();
}

void test2()
{
  digitalWrite(pinFAN,HIGH);  
}
void test1()
{
  digitalWrite(pinFAN,LOW);  
  delay(50);

  Serial.println("start fan.");
  digitalWrite(pinFAN,HIGH);
  delay(10000);
}
