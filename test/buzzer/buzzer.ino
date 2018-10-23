
// test No.2
// buzzer

const int pinBuzzer = 3;
const int maxCount = 3;
unsigned int count = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("buzzer test begins");
  pinMode(pinBuzzer,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  
  count++;
  if(1 && count <= maxCount) {
    Serial.println(count);Serial.println(maxCount);
    test1();
  } else {
    delay(100);
    
  }
}

void test1()
{
  digitalWrite(pinBuzzer,HIGH);
  delay(500);
  
  digitalWrite(pinBuzzer,LOW);
  delay(1000);
  
}

void test2()
{
  long freq = 300;
  tone(pinBuzzer,freq);
  delay(500);
  noTone(pinBuzzer);
  delay(1000);  
}

// song of "the little star"   https://www.arduino.cn/thread-1513-1-1.html
int speakerPin = pinBuzzer;
 
int length = 15; // the number of notes
char notes[] = "ccggaagffeeddc "; // a space represents a rest
int beats[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 };
int tempo = 300;
 
void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }
}
 
void playNote(char note, int duration) {
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };
 
  // play the tone corresponding to the note name
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}
 
void test_star() {
  for (int i = 0; i < length; i++) {
    if (notes[i] == ' ') {
      delay(beats[i] * tempo); // rest
    } else {
      playNote(notes[i], beats[i] * tempo);
    }
 
    // pause between notes
    delay(tempo / 2); 
  }
}
