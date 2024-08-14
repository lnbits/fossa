#include <Wire.h>
#include <FS.h>
#include <SPIFFS.h>
#include <TFT_eSPI.h>
#include <HardwareSerial.h>
#include <JC_Button.h>
#include <Hash.h>
#include <ArduinoJson.h>
#include "qrcoded.h"
#include "Bitcoin.h"

#define PARAM_FILE "/elements.json"

//=========================================================//
//===EDIT of using hardcoded, or want to change hardware===//
//=========================================================//

// LNURLDevices ATM details, set hardcoded=true, if adding here and not in the webinstaller config.

// #define ILI9341_DRIVER
#define ST7796_DRIVER

bool hardcoded = false;
String baseURLATM = "https://legend.lnbits.com/lnurldevice/api/v1/lnurl/M8wiiij8oLEgK6RNXLvoFs";
String secretATM = "3czaYALeuAp4H36tH3nasH";
String currencyATM = "USD";

// GPIOs used for Hardware

#define BTN1 39 // Screen tap button

#define RX1 32 // Bill acceptor
#define TX1 33 // Bill acceptor

#define TX2 4         // Coinmech
#define INHIBITMECH 2 // Coinmech

// Coin and Bill Acceptor amounts
int billAmountInt[3] = {5, 10, 20};
float coinAmountFloat[6] = {0.02, 0.05, 0.1, 0.2, 0.5, 1};
int charge = 10;    // % you will charge people for service, set in LNbits extension
int maxamount = 30; // max amount per withdraw

// Screen selection

//============================//
//============================//
//============================//

fs::SPIFFSFS &FlashFS = SPIFFS;

String qrData;

int bills;
float coins;
float total;

int billAmountSize = sizeof(billAmountInt) / sizeof(int);
float coinAmountSize = sizeof(coinAmountFloat) / sizeof(float);

int moneyTimer = 0;

bool waitForTap = true;

struct KeyValue
{
  String key;
  String value;
};

HardwareSerial SerialPort1(1);
HardwareSerial SerialPort2(2);

TFT_eSPI tft = TFT_eSPI();
Button BTNA(BTN1);

void setup()
{
  Serial.begin(115200);
  Serial.println("Working...");
  BTNA.begin();

  while (waitForTap && total < 100 && hardcoded == false)
  {
    BTNA.read();
    if (BTNA.wasReleased())
    {
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

void loop()
{
  // Turn on machines
  SerialPort1.write(184);
  digitalWrite(INHIBITMECH, HIGH);

  tft.fillScreen(TFT_BLACK);
  printMessage("Feed me FIAT", String(charge) + "% charge", "", TFT_WHITE, TFT_BLACK);
  moneyTimerFun();
  makeLNURL();
  qrShowCodeLNURL("SCAN ME. TAP SCREEN WHEN FINISHED");
}

void moneyTimerFun()
{
  waitForTap = true;
  coins = 0;
  bills = 0;
  total = 0;
  printMessage("Feed me fiat", String(charge) + "% charge", "", TFT_WHITE, TFT_BLACK);
  while (waitForTap || total == 0)
  {
    if (SerialPort1.available())
    {
      int x = SerialPort1.read();
      for (int i = 0; i < billAmountSize; i++)
      {
        if ((i + 1) == x)
        {
          bills = bills + billAmountInt[i];
          total = (coins + bills);
          printMessage(billAmountInt[i] + currencyATM, "Total: " + String(total) + currencyATM, "TAP SCREEN WHEN FINISHED", TFT_WHITE, TFT_BLACK);
        }
      }
    }
    if (SerialPort2.available())
    {
      int x = SerialPort2.read();
      for (int i = 0; i < coinAmountSize; i++)
      {
        if ((i + 1) == x)
        {
          coins = coins + coinAmountFloat[i];
          total = (coins + bills);
          printMessage(coinAmountFloat[i] + currencyATM, "Total: " + String(total) + currencyATM, "TAP SCREEN WHEN FINISHED", TFT_WHITE, TFT_BLACK);
        }
      }
    }
    BTNA.read();
    if (BTNA.wasReleased() || total > maxamount)
    {
      waitForTap = false;
    }
  }
  total = (coins + bills) * 100;

  // Turn off machines
  SerialPort1.write(185);
  digitalWrite(INHIBITMECH, LOW);
}

/////////////////////////////////
////////////UTILS////////////////
/////////////////////////////////

void to_upper(char *arr)
{
  for (size_t i = 0; i < strlen(arr); i++)
  {
    if (arr[i] >= 'a' && arr[i] <= 'z')
    {
      arr[i] = arr[i] - 'a' + 'A';
    }
  }
}

String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  const int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++)
  {
    if (data.charAt(i) == separator || i == maxIndex)
    {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }

  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

String getJsonValue(JsonDocument &doc, const char *name)
{
  for (JsonObject elem : doc.as<JsonArray>())
  {
    if (strcmp(elem["name"], name) == 0)
    {
      String value = elem["value"].as<String>();
      return value;
    }
  }
  return "";
}

////////////////////////////////////////////
///////////////LNURL STUFF//////////////////
////USING STEPAN SNIGREVS GREAT CRYTPO//////
////////////THANK YOU STEPAN////////////////
////////////////////////////////////////////

void makeLNURL()
{
  int randomPin = random(1000, 9999);
  byte nonce[8];
  for (int i = 0; i < 8; i++)
  {
    nonce[i] = random(256);
  }

  byte payload[51]; // 51 bytes is max one can get with xor-encryption

  size_t payload_len = xor_encrypt(payload, sizeof(payload), (uint8_t *)secretATM.c_str(), secretATM.length(), nonce, sizeof(nonce), randomPin, float(total));
  String preparedURL = baseURLATM + "?atm=1&p=";
  preparedURL += toBase64(payload, payload_len, BASE64_URLSAFE | BASE64_NOPADDING);

  Serial.println(preparedURL);
  char Buf[200];
  preparedURL.toCharArray(Buf, 200);
  char *url = Buf;
  byte *data = (byte *)calloc(strlen(url) * 2, sizeof(byte));
  size_t len = 0;
  int res = convert_bits(data, &len, 5, (byte *)url, strlen(url), 8, 1);
  char *charLnurl = (char *)calloc(strlen(url) * 2, sizeof(byte));
  bech32_encode(charLnurl, "lnurl", data, len);
  to_upper(charLnurl);
  qrData = charLnurl;
}

int xor_encrypt(uint8_t *output, size_t outlen, uint8_t *key, size_t keylen, uint8_t *nonce, size_t nonce_len, uint64_t pin, uint64_t amount_in_cents)
{
  // check we have space for all the data:
  // <variant_byte><len|nonce><len|payload:{pin}{amount}><hmac>
  if (outlen < 2 + nonce_len + 1 + lenVarInt(pin) + 1 + lenVarInt(amount_in_cents) + 8)
  {
    return 0;
  }

  int cur = 0;
  output[cur] = 1; // variant: XOR encryption
  cur++;

  // nonce_len | nonce
  output[cur] = nonce_len;
  cur++;
  memcpy(output + cur, nonce, nonce_len);
  cur += nonce_len;

  // payload, unxored first - <pin><currency byte><amount>
  int payload_len = lenVarInt(pin) + 1 + lenVarInt(amount_in_cents);
  output[cur] = (uint8_t)payload_len;
  cur++;
  uint8_t *payload = output + cur;                                 // pointer to the start of the payload
  cur += writeVarInt(pin, output + cur, outlen - cur);             // pin code
  cur += writeVarInt(amount_in_cents, output + cur, outlen - cur); // amount
  cur++;

  // xor it with round key
  uint8_t hmacresult[32];
  SHA256 h;
  h.beginHMAC(key, keylen);
  h.write((uint8_t *)"Round secret:", 13);
  h.write(nonce, nonce_len);
  h.endHMAC(hmacresult);
  for (int i = 0; i < payload_len; i++)
  {
    payload[i] = payload[i] ^ hmacresult[i];
  }

  // add hmac to authenticate
  h.beginHMAC(key, keylen);
  h.write((uint8_t *)"Data:", 5);
  h.write(output, cur);
  h.endHMAC(hmacresult);
  memcpy(output + cur, hmacresult, 8);
  cur += 8;

  // return number of bytes written to the output
  return cur;
}