#include <HardwareSerial.h>
#include <Wire.h>
#define RX1 32 // Bill acceptor serial in
#define TX1 33 // Bill acceptor serial out
HardwareSerial SerialPort1(1);
void setup() {
  Serial.begin(115200);
  SerialPort1.begin(300, SERIAL_8N2, TX1, RX1);
  SerialPort1.write(184);
}

void loop() {
  int x = 0;
  x = SerialPort1.read();
  if(x > 0 && x < 10){
    Serial.print("Worked, got: ");
    Serial.print(x);
    Serial.println(" from bill acceptor (which is the number of the note in the notes list set using the validator software)");
  }
  delay(500);
}
