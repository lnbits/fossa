// FOSSA NO ACCESS POINT, SIMPLE

//====================================//
//==EDIT IF USING DIFFERENT HARDWARE==//
//====================================//

#define BTN1 39 // Screen tap button
#define BILL_ACCEPTOR_RX 32 // Bill acceptor
#define BILL_ACCEPTOR_TX 33 // Bill acceptor
#define COIN_MACHINE_TX 4 // Coin machine
#define INHIBITMECH 2 // Coin machine

#define BillAcceptor Serial1
#define CoinAcceptor Serial2

// Setup the WT32-SC01 screen correctly.
#define USER_SETUP_LOADED // Prevents loading the default User_Setup.h
#define ST7796_DRIVER // This is the driver for the WT32-SC01
#define TFT_WIDTH  320
#define TFT_HEIGHT 480
#define TFT_BACKLIGHT_ON HIGH
#define USE_HSPI_PORT
#define TFT_MISO 12
#define TFT_MOSI 13
#define TFT_SCLK 14
#define TFT_CS   15
#define TFT_DC   21
#define TFT_RST  22
#define TFT_BL   23
#define LOAD_GLCD
#define LOAD_FONT2
#define LOAD_FONT4
#define LOAD_FONT6
#define LOAD_FONT7
#define LOAD_FONT8
#define LOAD_GFXFF
#define SMOOTH_FONT
#define SPI_FREQUENCY  27000000
#define SPI_READ_FREQUENCY  20000000
#define SPI_TOUCH_FREQUENCY  2500000

//========================================================//
//========================================================//
//========================================================//

#include <Hash.h>
#include "qrcoded.h"
#include "Bitcoin.h"
#include <Wire.h>
#include <TFT_eSPI.h>
#include <HardwareSerial.h>
#include <JC_Button.h>

//============================//
//============================//
//============================//

// LNURLDevices ATM details
String baseURLATM = "https://demo.lnbits.com/lnurldevice/api/v1/lnurl/irqKs,fhHkEYrzPgvDRdSjLgYvNk,GBP";
String secretATM = "	fhHkEYrzPgvDRdSjLgYvNk";
String currencyATM = "GBP";

String qrData;

int bills;
float coins;
float total;
int charge = 5; // % you will charge people for service, set in LNbits extension
int maxamount = 30; // max amount per withdraw

// Coin and Bill Acceptor amounts
int billAmountInt[3] = {5,10,20};
float coinAmountFloat[6] = {0.02, 0.05, 0.1, 0.2, 0.5, 1};
int billAmountSize = sizeof(billAmountInt) / sizeof(int);
float coinAmountSize = sizeof(coinAmountFloat) / sizeof(float);

int moneyTimer = 0;

TFT_eSPI tft = TFT_eSPI();
Button BTNA(BTN1);

void setup()  
{  
  Serial.begin(115200);

  // See if the device is in SIO fast mode or not (300 vs 9600), see "8.3 Program check procedure" in "NV10Manual_2.PDF.pdf")
  BillAcceptor.begin(9600, SERIAL_8N2, BILL_ACCEPTOR_TX, BILL_ACCEPTOR_RX); // Initialize the bill acceptor, listen at a baud rate of 300.
  delay(5000); // Wait for the device to initialize

  pinMode(BILL_ACCEPTOR_RX, INPUT_PULLUP); // Pullup serial RX pin.

  // If the device is in SIO (start-up disabled mode, see "8.3 Program check procedure" in "NV10Manual_2.PDF.pdf")
  uint8_t enableCommand = 0x02; // Enable command for NV10 USB+
  BillAcceptor.write(enableCommand);

  BillAcceptor.write(170); // Enable serial escrow mode (see ""Recognised Receive Codes to BV100" in "NV10Manual_2.PDF.pdf"")
  BillAcceptor.write(184); // Enable all (see "Recognised Receive Codes to BV100" in "NV10Manual_2.PDF.pdf")
  Serial.println("Bill acceptor serial port initialized.");

  CoinAcceptor.begin(4800, SERIAL_8N1, COIN_MACHINE_TX);
  //digitalWrite(INHIBITMECH, HIGH); // Enable coin acceptor
  pinMode(INHIBITMECH, OUTPUT);
  digitalWrite(INHIBITMECH, HIGH);

  BTNA.begin();
  
  tft.init();
  tft.setRotation(1);
  tft.invertDisplay(false);
  tft.fillScreen(TFT_BLACK);
  logo();
}

void loop()
{
  Serial.println("Starting ATM ...");
  // Turn on machines
  Serial.println("Turning on machines ...");
  BillAcceptor.write(184);
  digitalWrite(INHIBITMECH, HIGH);
  
  tft.fillScreen(TFT_BLACK);
  //printMessage("Feed me FIAT", String(charge) + "% charge", "", TFT_WHITE, TFT_BLACK);
  moneyTimerFun();
  Serial.println("Money timer done");
  makeLNURL();
  Serial.println("LNURL done");
  qrShowCodeLNURL();
  Serial.println("LNURL done");
}

void printMessage(String text1, String text2, String text3, int ftcolor, int bgcolor)
{
  tft.fillScreen(bgcolor);
  tft.setTextColor(ftcolor, bgcolor);
  tft.setTextSize(5);
  tft.setCursor(30, 40);
  tft.println(text1);
  tft.setCursor(30, 120);
  tft.println(text2);
  tft.setCursor(30, 200);
  tft.setTextSize(3);
  tft.println(text3);
}

void logo()
{
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(130, 100);
  tft.setTextSize(10);
  tft.setTextColor(TFT_PURPLE);
  tft.println("FOSSA");
  tft.setTextColor(TFT_WHITE);
  tft.setCursor(40, 170);
  tft.setTextSize(3);
  tft.println("Bitcoin Lightning ATM");
  tft.setCursor(300, 290);
  tft.setTextSize(2);
  tft.println("(GRIFF Edition)");
}

void feedmefiat()
{
  tft.setTextColor(TFT_WHITE);
  tft.setCursor(60, 40);
  tft.setTextSize(3);
  tft.println("Bitcoin Lightning ATM");
  tft.setCursor(10, 280);
  tft.println("(feed me fiat. " + String(charge) + "% charge)");
  tft.setTextSize(10);
  tft.setCursor(160, 80);
  tft.println("SATS");
  tft.setCursor(180, 140);
  tft.println("FOR");
  tft.setCursor(160, 200);
  tft.println("FIAT!");
  delay(100);
  tft.setTextColor(TFT_GREEN);
  tft.setCursor(160, 80);
  tft.println("SATS");
  tft.setCursor(180, 140);
  tft.println("FOR");
  tft.setCursor(160, 200);
  tft.println("FIAT!");
  delay(100);
  tft.setTextColor(TFT_BLUE);
  tft.setCursor(160, 80);
  tft.println("SATS");
  tft.setCursor(180, 140);
  tft.println("FOR");
  tft.setCursor(160, 200);
  tft.println("FIAT!");
  delay(100);
  tft.setTextColor(TFT_ORANGE);
  tft.setCursor(160, 80);
  tft.println("SATS");
  tft.setCursor(180, 140);
  tft.println("FOR");
  tft.setCursor(160, 200);
  tft.println("FIAT!");
  delay(100);
}

void qrShowCodeLNURL()
{
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(3);
  tft.setTextDatum(MC_DATUM);
  tft.drawString("Please wait while your", tft.width() / 2, tft.height() / 2 - 20);
  tft.drawString("voucher is printed", tft.width() / 2, tft.height() / 2 + 20);
  
  //printReceipt();

  tft.fillScreen(TFT_WHITE);
  qrData.toUpperCase();
  const char *qrDataChar = qrData.c_str();
  QRCode qrcoded;
  uint8_t qrcodeData[qrcode_getBufferSize(20)];
  qrcode_initText(&qrcoded, qrcodeData, 11, 0, qrDataChar);

  // calculate start position on screen to get center, use tft.width() and qrcoded.size
  int startX = (tft.width() - qrcoded.size * 3) / 2;
  for (uint8_t y = 0; y < qrcoded.size; y++)
  {
    for (uint8_t x = 0; x < qrcoded.size; x++)
    {
      if (qrcode_getModule(&qrcoded, x, y))
      {
        tft.fillRect(startX + 3 * x, 30 + 3 * y, 4, 4, TFT_BLACK);
      }
      else
      {
        tft.fillRect(startX + 3 * x, 30 + 3 * y, 4, 4, TFT_WHITE);
      }
    }
  }

  tft.setTextSize(2);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.drawString("Scan me or your printed voucher", tft.width() / 2, 235);
  tft.drawString("with a Bitcoin Lightning wallet", tft.width() / 2, 260);
  tft.drawString("Tap the screen when finished", tft.width() / 2, 295);
  
  bool waitForTap = true;
  while(waitForTap){
    BTNA.read();
    if (BTNA.wasReleased()) {
      waitForTap = false;
    }
  }
}

// This function processes money input from two serial ports, updates the total amount of money collected, and displays messages to the user 
// until the user indicates they are finished or a maximum amount is reached.
void moneyTimerFun()
{
  Serial.println("Starting moneyTimerFun ...");

  bool waitForTap = true;
  coins = 0;
  bills = 0;
  total = 0;
  
  while (waitForTap || total == 0){
    if (total == 0) {
      Serial.println("Feed me fiat");
      feedmefiat();
    }
    if (BillAcceptor.available()) {
      Serial.println("Bill Acceptor available");
      int x = BillAcceptor.read();
      Serial.println("Bill Acceptor Data: ");
      Serial.println(x); // Debugging line to print bill acceptor data
      for (int i = 0; i < billAmountSize; i++){
        if((i+1) == x){
          bills = bills + billAmountInt[i];
          total = (coins + bills);
          printMessage(billAmountInt[i] + currencyATM, "Total: " + String(total) + currencyATM, "TAP SCREEN WHEN FINISHED", TFT_WHITE, TFT_BLACK);
        }
      }
    } else {
      //Serial.println("Bill acceptor unavailable");
    }
    if (CoinAcceptor.available()) {
      int x = CoinAcceptor.read();
      Serial.print("Coin Acceptor Data: ");
      Serial.println(x); // Debugging line to print coin acceptor data
      for (int i = 0; i < coinAmountSize; i++){
         if((i+1) == x){
           coins = coins + coinAmountFloat[i];
           total = (coins + bills);
           printMessage(coinAmountFloat[i] + currencyATM, "Total: " + String(total) + currencyATM, "TAP SCREEN WHEN FINISHED", TFT_WHITE, TFT_BLACK);
         }
       }
    } else {
      //Serial.println("Coin acceptor unavailable");
    }
    Serial.println("Waiting for tap");
    BTNA.read();
    if (BTNA.wasReleased() || total > maxamount) {
      waitForTap = false;
    }
  }
  total = (coins + bills) * 100;
  Serial.println("Total: " + String(total));

  // Turn off machines
  Serial.println("Turning machines turned off ...");
  BillAcceptor.write(185);
  digitalWrite(INHIBITMECH, LOW);
}

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
  int res = convert_bits(data, &len, 5, (byte *) url, strlen(url), 8, 1);
  char *charLnurl = (char *) calloc(strlen(url) * 2, sizeof(byte));
  bech32_encode(charLnurl, "lnurl", data, len);
  to_upper(charLnurl);
  qrData = charLnurl;
}

// This function is performing a custom encryption operation, combining XOR-based encryption with HMAC for authentication
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
  h.write((uint8_t *) "Round secret:", 13);
  h.write(nonce, nonce_len);
  h.endHMAC(hmacresult);
  for (int i = 0; i < payload_len; i++)
  {
    payload[i] = payload[i] ^ hmacresult[i];
  }

  // add hmac to authenticate
  h.beginHMAC(key, keylen);
  h.write((uint8_t *) "Data:", 5);
  h.write(output, cur);
  h.endHMAC(hmacresult);
  memcpy(output + cur, hmacresult, 8);
  cur += 8;

  // return number of bytes written to the output
  return cur;
}
