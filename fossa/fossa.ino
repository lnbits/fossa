#include <Wire.h>
#include <FS.h>
#include <SPIFFS.h>
#include <SoftwareSerial.h>
#include <TFT_eSPI.h>
#include <HardwareSerial.h>
#include <JC_Button.h>
#include <Hash.h>
#include <ArduinoJson.h>
#include "qrcoded.h"
#include "Bitcoin.h"
#include <Adafruit_Thermal.h>

#define PARAM_FILE "/elements.json"

///////////////////////////////////////////////////
//////CHANGE MANUALLY OR USE FOSSA.lnbits.com//////
///////////////////////////////////////////////////

bool hardcoded = true;
String LNURLsettings = "https://demo.lnbits.com/lnurldevice/api/v1/lnurl/KVJyh,5UhHkwGhGxasXm2G3LS7RT,USD";
int billAmountInt[3] = { 5, 10, 20 };
float coinAmountFloat[6] = { 0.02, 0.05, 0.1, 0.2, 0.5, 1 };
int charge = 10;     // % you will charge people for service, set in LNbits extension
int maxamount = 30;  // max amount per withdraw
bool printerBool = true;

///////////////////////////////////////////////////
///////////////////////////////////////////////////
///////////////////////////////////////////////////

String baseURLATM;
String secretATM;
String currencyATM;

#define BTN1 39        // Screen tap button
#define RX1 32         // Bill acceptor
#define TX1 33         // Bill acceptor
#define TX2 4          // Coinmech
#define INHIBITMECH 2  // Coinmech
#define RXP 22         // TX of the thermal printer
#define TXP 23         // RX of the thermal printer

fs::SPIFFSFS &FlashFS = SPIFFS;

String qrData;

int bills;
float coins;
float total;
int billAmountSize = sizeof(billAmountInt) / sizeof(int);
float coinAmountSize = sizeof(coinAmountFloat) / sizeof(float);
int moneyTimer = 0;
bool waitForTap = true;
struct KeyValue {
  String key;
  String value;
};

HardwareSerial SerialPort1(1);
HardwareSerial SerialPort2(2);
SoftwareSerial printerSerial(RXP, TXP);
Adafruit_Thermal printer(&printerSerial);
TFT_eSPI tft = TFT_eSPI(320, 480);
Button BTNA(BTN1);

void setup() {
  splitSettings(LNURLsettings);
  Serial.begin(115200);
  Serial.println("Working...");
  BTNA.begin();

  while (waitForTap && total < 100 && hardcoded == false) {
    BTNA.read();
    if (BTNA.wasReleased()) {
      printMessage("USB config mode", "", "TAP SCREEN WHEN FINISHED", TFT_WHITE, TFT_BLACK);
      executeConfig();
      waitForTap = false;
    }
    total++;
  }

  tft.init();
  tft.setRotation(1);
  tft.invertDisplay(false);

  SerialPort1.begin(300, SERIAL_8N2, TX1, RX1);
  SerialPort2.begin(4800, SERIAL_8N1, TX2);

  pinMode(INHIBITMECH, OUTPUT);
}

void loop() {
  SerialPort1.write(184);
  digitalWrite(INHIBITMECH, HIGH);
  tft.fillScreen(TFT_BLACK);
  moneyTimerFun();
  makeLNURL();
  qrShowCodeLNURL("SCAN ME. TAP SCREEN WHEN FINISHED");
}

void moneyTimerFun() {
  waitForTap = true;
  coins = 0;
  bills = 0;
  total = 0;
  printMessage("Feed me fiat", String(charge) + "% charge", "", TFT_WHITE, TFT_BLACK);
  while (waitForTap || total == 0) {
    if (SerialPort1.available()) {
      int x = SerialPort1.read();
      for (int i = 0; i < billAmountSize; i++) {
        if ((i + 1) == x) {
          bills = bills + billAmountInt[i];
          total = (coins + bills);
          printMessage(billAmountInt[i] + currencyATM, "Total: " + String(total) + currencyATM, "TAP SCREEN WHEN FINISHED", TFT_WHITE, TFT_BLACK);
        }
      }
    }
    if (SerialPort2.available()) {
      int x = SerialPort2.read();
      for (int i = 0; i < coinAmountSize; i++) {
        if ((i + 1) == x) {
          coins = coins + coinAmountFloat[i];
          total = (coins + bills);
          printMessage(coinAmountFloat[i] + currencyATM, "Total: " + String(total) + currencyATM, "TAP SCREEN WHEN FINISHED", TFT_WHITE, TFT_BLACK);
        }
      }
    }
    BTNA.read();
    if (BTNA.wasReleased() || total > maxamount) {
      waitForTap = false;
    }
  }
  total = (coins + bills) * 100;

  // Turn off machines
  SerialPort1.write(185);
  digitalWrite(INHIBITMECH, LOW);
}
