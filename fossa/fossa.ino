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
String LNURLsettings = "https://a57a71fcc81f03aa86f943acbc9eb476.serveo.net/lnurldevice/api/v1/lnurl/n3Zrf,Phko2N2qzeXcT9fbW96TwS,USD";
int billAmountInt[3] = { 5, 10, 20 };
float coinAmountFloat[6] = { 0.02, 0.05, 0.1, 0.2, 0.5, 1 };
int charge = 10;     // % you will charge people for service, set in LNbits extension
int maxamount = 30;  // max amount per withdraw
bool printerBool = true;
String language = "ro"; // Supports en, es, fr, de, it, pt, pl, hu, tr, ro, fi, sv

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
String translate(String key);
uint16_t homeScreenColors[] = { TFT_GREEN, TFT_BLUE, TFT_ORANGE };
int homeScreenNumColors = sizeof(homeScreenColors) / sizeof(homeScreenColors[0]);
int homeScreenNumColorCount = 0;

String usbT, tapScreenT, scanMeT, totalT, fossaT, satsT, forT, fiatT, feedT, chargeT, printingT, waitT, workingT;

HardwareSerial SerialPort1(1);
HardwareSerial SerialPort2(2);
SoftwareSerial printerSerial(RXP, TXP);
Adafruit_Thermal printer(&printerSerial);
TFT_eSPI tft = TFT_eSPI(320, 480);
Button BTNA(BTN1);

void setup() {
  translateAll(language);
  splitSettings(LNURLsettings);
  Serial.begin(115200);
  Serial.println(workingT);
  BTNA.begin();

  while (waitForTap && total < 100 && hardcoded == false) {
    BTNA.read();
    if (BTNA.wasReleased()) {
      printMessage(usbT, "", tapScreenT, TFT_WHITE, TFT_BLACK);
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
  qrShowCodeLNURL(scanMeT);
}

void moneyTimerFun() {
  waitForTap = true;
  coins = 0;
  bills = 0;
  total = 0;
  while (waitForTap || total == 0) {
    if (homeScreenNumColorCount == homeScreenNumColors) {
      homeScreenNumColorCount = 0;
    }
    if (total == 0) {
      feedmefiat();
      feedmefiatloop();
    }
    if (SerialPort1.available()) {
      int x = SerialPort1.read();
      for (int i = 0; i < billAmountSize; i++) {
        if ((i + 1) == x) {
          bills = bills + billAmountInt[i];
          total = (coins + bills);
          printMessage(billAmountInt[i] + currencyATM, totalT + String(total) + currencyATM, tapScreenT, TFT_WHITE, TFT_BLACK);
        }
      }
    }
    if (SerialPort2.available()) {
      int x = SerialPort2.read();
      for (int i = 0; i < coinAmountSize; i++) {
        if ((i + 1) == x) {
          coins = coins + coinAmountFloat[i];
          total = (coins + bills);
          printMessage(coinAmountFloat[i] + currencyATM, totalT + String(total) + currencyATM, tapScreenT, TFT_WHITE, TFT_BLACK);
        }
      }
    }
    BTNA.read();
    if (BTNA.wasReleased() || total > maxamount) {
      waitForTap = false;
    }
    homeScreenNumColorCount++;
  }
  total = (coins + bills) * 100;

  // Turn off machines
  SerialPort1.write(185);
  digitalWrite(INHIBITMECH, LOW);
}
