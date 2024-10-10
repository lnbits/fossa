#include <HardwareSerial.h>
#include <Wire.h>
#define TX2 4 // Coinmech serial out
#define INHIBITMECH 2
HardwareSerial SerialPort2(2);
void setup() {
  Serial.begin(115200);
  SerialPort2.begin(4800, SERIAL_8N1, TX2);
   pinMode(INHIBITMECH, OUTPUT);
   digitalWrite(INHIBITMECH, LOW);
   delay(10000);
   digitalWrite(INHIBITMECH, HIGH);
}

void loop() {
  int x = 0;
  x = SerialPort2.read();
  if(x > 0){
    Serial.print("Worked, got: ");
    Serial.print(x);
    Serial.println(" from coin acceptor");
  }
  delay(500);
}
