

const int pinTrig = 3, pinEcho = 2;
float distance;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pinTrig,OUTPUT);
  pinMode(pinEcho,INPUT);

  Serial.println("ultrasonic test inited.\n");
}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(pinTrig,LOW);
  delayMicroseconds(2);
  digitalWrite(pinTrig,HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrig,LOW);

  distance = pulseIn(pinEcho,HIGH)/58.00;
  Serial.print("distance:");
  Serial.print(distance);
  Serial.println("cm");
  delay(1000);
  
}
