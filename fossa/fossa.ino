#include <Wire.h>
#include <FS.h>
#include <SPIFFS.h>
#include <SoftwareSerial.h>
#include <HardwareSerial.h>
#include <JC_Button.h>
#include <ArduinoJson.h>
#include "qrcoded.h"
#include "Bitcoin.h"
#include <TFT_eSPI.h>
#include "mbedtls/aes.h"

#define FORMAT_ON_FAIL true
#define PARAM_FILE "/elements.json"

#define VERSION "0.3.0"

//#define BILL_ACCEPTOR
#define BILL_RX 32      // RX Bill acceptor
#define BILL_TX 33      // TX Bill acceptor

#define COIN_ACCEPTOR
#define COIN_TX 34      // TX Coinmech
#define COIN_INHIBIT 35 // Coinmech interrupt

//#define PRINTER
#define PRINTER_RX 22   // RX of the thermal printer
#define PRINTER_TX 23   // TX of the thermal printer

#define BTN1 21         // Screen tap button
#define BILL_RX 32     // RX Bill acceptor
#define BILL_TX 33     // TX Bill acceptor
#define COIN_TX 4      // TX Coinmech
#define COIN_INHIBIT 2 // Coinmech inhibit pin
#define PRINTER_RX 22  // RX of the thermal printer
#define PRINTER_TX 23  // TX of the thermal printer

// uncomment to use always hardcoded default settings
#define HARDCODED

// default settings
#define LANGUAGE "en" // Supports en, es, fr, de, it, pt, pl, hu, tr, ro, fi, sv
#define CHARGE 10      // % you will charge people for service, set in LNbits extension
#define MAX_AMOUNT 30  // max amount per withdraw
#define MAX_BEFORE_RESET 300 // max amount you want to sell in the atm before having to reset power
//#define DEVICE_STRING "https://XXXX.lnbits.com/fossa/api/v1/lnurl/XXXXX,XXXXXXXXXXXXXXXX,EUR"
#define DEVICE_STRING "https://test.b1tco1n.org/fossa/api/v1/lnurl/atm/T7HxgedvRJCZVHTm,9rtVvLAsx22hk9W6,USD"
#define COIN_AMOUNTS "0.05,1.0,0.25,0.5,0.1,2.0"
//#define BILL_AMOUNTS "0.01,0.05,0.1,0.25,0.5,1"

int billAmountInt[16];
float coinAmountFloat[6];
int charge;
int maxamount;
int maxBeforeReset;
String language;
String deviceString;

String baseURLATM;
String baseUrlAtmPage;
String secretATM;
String currencyATM;

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

#ifdef BILL_ACCEPTOR
HardwareSerial SerialBillAcceptor(1);
#endif
#ifdef COIN_ACCEPTOR
HardwareSerial SerialCoinAcceptor(2);
#endif
#ifdef PRINTER
SoftwareSerial SerialPrinter(PRINTER_RX, PRINTER_TX);
Adafruit_Thermal printer(&SerialPrinter);
#endif

TFT_eSPI tft = TFT_eSPI(TFT_WIDTH, TFT_HEIGHT);
Button BTNA(BTN1);


void setup() {
  Serial.begin(115200);
  Serial.println("Welcome to FOSSA, running on version: " + String(VERSION));
  Serial.println("TFT: " + String(TFT_WIDTH) + "x" + String(TFT_HEIGHT));
  Serial.println("TFT pin MISO: " + String(TFT_MISO));
  Serial.println("TFT pin CS: " + String(TFT_CS));
  Serial.println("TFT pin MOSI: " + String(TFT_MOSI));
  Serial.println("TFT pin SCLK: " + String(TFT_SCLK));
  Serial.println("TFT pin DC: " + String(TFT_DC));
  Serial.println("TFT pin RST: " + String(TFT_RST));

#ifdef HARDCODED
  setDefaultValues();
  translateAll(language);
#else
  Serial.println("Waiting for tap to start config mode..");
  while (waitForTap && total < 100) {
    BTNA.read();
    if (BTNA.wasReleased()) {
      Serial.println("Tap detected, starting config mode..");
      printMessage(usbT, "", tapScreenT, TFT_WHITE, TFT_BLACK);
      executeConfig();
      waitForTap = false;
    }
    delay(20);
    total++;
  }
  Serial.println("Config mode ended.");
  Serial.println("Reading files..");
  readFiles();
  translateAll(language);
#endif

  splitSettings(deviceString);

  BTNA.begin();
  FlashFS.begin(FORMAT_ON_FAIL);

  tft.init();
  tft.setRotation(1);
  tft.invertDisplay(false);

  char buf[100];
  sprintf(buf, "TFT (%dx%d) initialized.", TFT_WIDTH, TFT_HEIGHT);
  Serial.println(buf);

  printMessage("", "Loading..", "", TFT_WHITE, TFT_BLACK);

#ifdef BILL_ACCEPTOR
  SerialBillAcceptor.begin(300, SERIAL_8N2, BILL_RX, BILL_TX);
  Serial.println("Bill Acceptor serial started.");
#endif
#ifdef COIN_ACCEPTOR
  pinMode(COIN_TX, INPUT);
  pinMode(COIN_INHIBIT, INPUT);
  SerialCoinAcceptor.begin(4800, SERIAL_8N1, COIN_TX);
  Serial.println("Coin Acceptor serial started.");
#endif
#ifdef PRINTER
  SerialPrinter.begin(9600);
  printer.begin();
#endif
}

void loop() {
  if (maxBeforeResetTally >= maxBeforeReset) {
    Serial.println("Max amount reached, please reset power.");
    printMessage("", tooMuchFiatT, contactOwnerT, TFT_WHITE, TFT_BLACK);
    delay(100000000);
  } else {
#ifdef BILL_ACCEPTOR
    SerialBillAcceptor.write(184);
#endif
#ifdef COIN_ACCEPTOR
    digitalWrite(COIN_INHIBIT, LOW);
#endif
    tft.fillScreen(TFT_BLACK);
    BTNA.read(); // clear accidental taps
    moneyTimerFun();
    Serial.println("Total: " + String(total));
    Serial.println("maxBeforeResetTally: " + String(maxBeforeResetTally));
    maxBeforeResetTally += total / 100;
    Serial.println("maxBeforeResetTally: " + String(maxBeforeResetTally));
    makeLNURL();
    qrShowCodeLNURL();
  }
}

// FIXED: only honor tap *after* first money input
void moneyTimerFun() {
  Serial.println("Waiting for money...");
  waitForTap = true;
  coins = 0;
  bills = 0;
  total = 0;

  // 1) Flush any leftover presses/releases
  BTNA.read();
  while (BTNA.wasPressed() || BTNA.wasReleased()) {
    BTNA.read();
    delay(10);
  }

  bool firstInputDone = false;

  // 2) Main loop: never break on tap until we see money
  while (true) {
    // show “insert money” prompt until first input
    if (!firstInputDone) {
      feedmefiat();
      feedmefiatloop();
    }

    // a) Bill acceptor
#ifdef BILL_ACCEPTOR
    if (SerialBillAcceptor.available()) {
      int x = SerialBillAcceptor.read();
      for (int i = 0; i < billAmountSize; i++) {
        if ((i + 1) == x) {
          bills += billAmountInt[i];
          total = coins + bills;
          printMessage(
            billAmountInt[i] + currencyATM,
            totalT + String(total) + currencyATM,
            tapScreenT,
            TFT_WHITE, TFT_BLACK
          );
          firstInputDone = true;
        }
      }
    }
    SerialBillAcceptor.write(185);  // turn off
#endif

    // b) Coin acceptor
#ifdef COIN_ACCEPTOR
    if (SerialCoinAcceptor.available()) {
      int x = SerialCoinAcceptor.read();
      for (int i = 0; i < coinAmountSize; i++) {
        if ((i + 1) == x) {
          coins += coinAmountFloat[i];
          total = coins + bills;
          String printCoin = coinAmountFloat[i] + currencyATM;
          Serial.println("Coin inserted: " + String(i) + " -> " + printCoin);
          String printTotal = totalT + String(total) + currencyATM;
          Serial.println(printTotal);
          printMessage(printCoin, printTotal, tapScreenT, TFT_WHITE, TFT_BLACK);
          firstInputDone = true;
        }
      }
    }
    digitalWrite(COIN_INHIBIT, LOW);  // turn off
#endif

    // c) Only now check for a tap to finish
    BTNA.read();
    if (firstInputDone && BTNA.wasReleased()) {
      break;
    }

    // d) Optional: cap on maxamount
    if (firstInputDone && total > maxamount) {
      break;
    }
  }

  // finalize total (in cents)
  total = (coins + bills) * 100;
#ifdef BILL_ACCEPTOR
    // Turn off
    SerialBillAcceptor.write(185);
#endif
#ifdef COIN_ACCEPTOR
    // Turn off
    digitalWrite(COIN_INHIBIT, LOW);
#endif
}
