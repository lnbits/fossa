#include <SoftwareSerial.h>
#include <Adafruit_Thermal.h>
#include <Wire.h>
#define RXP 22         // TX of the thermal printer
#define TXP 23         // RX of the thermal printer
SoftwareSerial SerialPrinter(RXP, TXP);
Adafruit_Thermal printer(&SerialPrinter);

void setup() {
  SerialPrinter.begin(9600);
  printer.begin();
  printer.wake();
  printer.setDefault();
  printer.justify('C');
  printer.feed(3);
  printer.boldOn();
  printer.setSize('L');
  printer.println("Working :)");
  printer.sleep();
}

void loop() {
}