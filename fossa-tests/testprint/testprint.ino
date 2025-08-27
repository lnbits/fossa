#include <SoftwareSerial.h>
#include <Adafruit_Thermal.h>
#include <Wire.h>
#define PRINTER_RX 22         // TX of the thermal printer
#define PRINTER_TX 23         // RX of the thermal printer
SoftwareSerial printerSerial(PRINTER_RX, PRINTER_TX);
Adafruit_Thermal printer(&printerSerial);

void setup() {
  printerSerial.begin(9600);
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