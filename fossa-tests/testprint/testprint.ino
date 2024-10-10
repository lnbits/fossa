#include <SoftwareSerial.h>
#include <Adafruit_Thermal.h>
#include <Wire.h>
#define RXP 22         // TX of the thermal printer
#define TXP 23         // RX of the thermal printer
SoftwareSerial printerSerial(RXP, TXP);
Adafruit_Thermal printer(&printerSerial);
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
