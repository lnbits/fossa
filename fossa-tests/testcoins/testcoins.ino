#include <HardwareSerial.h>
#include <Wire.h>
#define COIN_TX 4 // Coinmech serial out
#define COIN_INHIBIT 2
HardwareSerial SerialPort2(2);
void setup() {
  Serial.begin(115200);
  SerialPort2.begin(4800, SERIAL_8N1, COIN_TX);
   pinMode(COIN_INHIBIT, OUTPUT);
   digitalWrite(COIN_INHIBIT, LOW);
   delay(10000);
   digitalWrite(COIN_INHIBIT, HIGH);
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
