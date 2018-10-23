
// temperature & humidity test with DHT11

// it turns out that dht11 is pretty hard to manipulate.
#include "dht11.h"

dht11 d;

int pinDHT = 8;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("mid test start");
  Serial.println(DHT11LIB_VERSION);

  // pinMode(pinMID,INPUT);
}

void loop()
{
    Serial.println("doing test...");
    test1();
}
void test1() {
  // put your main code here, to run repeatedly:

  int chk = d.read(pinDHT);
  Serial.print("reading sensor: ");

  switch(chk) {
    case DHTLIB_OK:
      Serial.println("OK");
      break;
    case DHTLIB_ERROR_CHECKSUM: 
      Serial.println("Checksum error"); 
      break;
    case DHTLIB_ERROR_TIMEOUT: 
      Serial.println("Time out error"); 
      break;
    default: 
      Serial.println("Unknown error"); 
      break;
  }

  Serial.print("Humidity (%):");
  Serial.println((float)d.humidity,2);
  Serial.print("Temperature(C):");
  Serial.println((float)d.temperature,2);

  delay(2000);

}
