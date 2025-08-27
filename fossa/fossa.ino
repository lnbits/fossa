#include <Wire.h>
#include <FS.h>
#include <SPIFFS.h>
#include <SoftwareSerial.h>
#include <HardwareSerial.h>
#include <JC_Button.h>
#include <Hash.h>
#include <ArduinoJson.h>
#include "qrcoded.h"
#include "Bitcoin.h"
#include <Adafruit_Thermal.h>
#include <cstdlib>
#include <TFT_eSPI.h>
#define FORMAT_ON_FAIL true
#define PARAM_FILE "/elements.json"

///////////////////////////////////////////////////
//////CHANGE MANUALLY OR USE FOSSA.lnbits.com//////
///////////////////////////////////////////////////

#define BTN1 39        // Screen tap button
#define BILL_RX 32     // RX Bill acceptor
#define BILL_TX 33     // TX Bill acceptor
#define COIN_TX 4      // TX Coinmech
#define COIN_INHIBIT 2 // Coinmech
#define PRINTER_RX 22  // RX of the thermal printer
#define PRINTER_TX 23  // TX of the thermal printer

// default settings
#define LANGUAGE "en" // Supports en, es, fr, de, it, pt, pl, hu, tr, ro, fi, sv
#define CHARGE 10 // % you will charge people for service, set in LNbits extension
#define MAX_AMOUNT 30 // max amount per withdraw
#define MAX_BEFORE_RESET 300 // max amount you want to sell in the atm before having to reset power
#define DEVICE_STRING "https://XXXX.lnbits.com/fossa/api/v1/lnurl/XXXXX,XXXXXXXXXXXXXXXXXXXXXX,USD"
#define COIN_AMOUNTS "0.05,1.0,0.25,0.5,0.1,2.0"
#define BILL_AMOUNTS "0.01,0.05,0.1,0.25,0.5,1"

bool hardcoded = false; // set to true if you want to use the above hardcoded settings

int billAmountInt[16];
float coinAmountFloat[6];
int charge = 10;          // % you will charge people for service, set in LNbits extension
int maxamount = 30;       // max amount per withdraw
int maxBeforeReset = 300;  // max amount you want to sell in the atm before having to reset power
bool printerBool = false;
String language = "en";  // Supports en, es, fr, de, it, pt, pl, hu, tr, ro, fi, sv

///////////////////////////////////////////////////
///////////////////////////////////////////////////
///////////////////////////////////////////////////

String baseURLATM;
String secretATM;
String currencyATM;
String deviceString;

#define BTN1 39        // Screen tap button
#define RX1 32         // Bill acceptor
#define TX1 33         // Bill acceptor
#define TX2 4          // Coinmech
#define INHIBITMECH 2  // Coinmech
#define RXP 22         // TX of the thermal printer
#define TXP 23         // RX of the thermal printer

fs::SPIFFSFS &FlashFS = SPIFFS;

String qrData;

int maxBeforeResetTally;
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

String usbT, tapScreenT, scanMeT, totalT, fossaT, satsT, forT, fiatT, feedT, chargeT, printingT, waitT, workingT, thisVoucherT, ofBitcoinT, thankYouT, scanMeClaimT, tooMuchFiatT, contactOwnerT;

HardwareSerial SerialPort1(1);
HardwareSerial SerialPort2(2);
SoftwareSerial printerSerial(RXP, TXP);
Adafruit_Thermal printer(&printerSerial);
TFT_eSPI tft = TFT_eSPI(320, 480);
Button BTNA(BTN1);

void setup() {
  translateAll(language);
  Serial.begin(115200);
  Serial.println(workingT);
  BTNA.begin();
  FlashFS.begin(FORMAT_ON_FAIL);
  tft.init();
  tft.setRotation(1);
  tft.invertDisplay(false);
  printMessage("", "Loading..", "", TFT_WHITE, TFT_BLACK);

  // wait few secods for tap to start config mode
  while (waitForTap && total < 100 && hardcoded == false) {
    BTNA.read();
    if (BTNA.wasReleased()) {
      printMessage(usbT, "", tapScreenT, TFT_WHITE, TFT_BLACK);
      executeConfig();
      waitForTap = false;
    }
    delay(20);
    total++;
  }
  
  if(hardcoded == false){
    readFiles();
    translateAll(language);
  }
  splitSettings(deviceString);

  // initialize bill and coin acceptor
  SerialPort1.begin(300, SERIAL_8N2, TX1, RX1);
  SerialPort2.begin(4800, SERIAL_8N1, TX2);
  pinMode(INHIBITMECH, OUTPUT);

  // initialize printer
  if(printerBool == true){
    printerSerial.begin(9600);
    printer.begin();
  }
}

void loop() {
  if (maxBeforeResetTally >= maxBeforeReset) {
    printMessage("", tooMuchFiatT, contactOwnerT, TFT_WHITE, TFT_BLACK);
    delay(100000000);
  } else {
    SerialPort1.write(184);
    digitalWrite(INHIBITMECH, HIGH);
    tft.fillScreen(TFT_BLACK);
    BTNA.read(); // needed to clear accidental taps
    moneyTimerFun();
    Serial.println(total);
    Serial.println(maxBeforeResetTally);
    maxBeforeResetTally = maxBeforeResetTally + (total / 100);
    Serial.println(maxBeforeResetTally);
    makeLNURL();
    qrShowCodeLNURL(scanMeT);
  }
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
        printMessage("", "WARNING: print bool", String(x), TFT_WHITE, TFT_BLACK);
        delay(3000);
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
