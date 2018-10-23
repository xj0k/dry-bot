
/*
  button is very easy to use. 
  While this programm shows how to use a button to simluate onoff switch.
*/

int pinButton = 7;

static bool onoff = false;
static int cur_btn_val = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(pinButton,INPUT);
  Serial.begin(9600);
  Serial.println("button test started.");
}

void loop() {
  // put your main code here, to run repeatedly:
  test2();
  delay(300);
}

void test_switch()
{
  int b = digitalRead(pinButton);
  
  if( 1== b && 0==cur_btn_val) {
  
    onoff = !onoff;
    Serial.print("we now are ");
    Serial.println(onoff?"on":"off");
  } else {
    Serial.print("button status:");
    Serial.println(b);
  }
  cur_btn_val = b;
}

bool btn_switched()
{
  int b = digitalRead(pinButton);
  bool r = false;
  
  if( 1== b && 0==cur_btn_val) {
  
    onoff = !onoff;
    r = true;
  } else {
    
    r = false;
  }
  cur_btn_val = b;
      return r;
}

void test2()
{
  if(btn_switched() ){
    Serial.print("status changed.We now are ");
    Serial.println(onoff?"on":"off");
  } else {
   // Serial.print("button status:");
    //Serial.println(b);
  }
  if(onoff) {
    Serial.println("start running ...");
  }
}
