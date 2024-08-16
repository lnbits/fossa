

void printMessage(String text1, String text2, String text3, int ftcolor, int bgcolor) {
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
void feedmefiat() {
  tft.setTextColor(TFT_WHITE);
  tft.setCursor(80, 40);
  tft.setTextSize(3);
  tft.println("FOSSA! Bitcoin ATM");
  tft.setCursor(10, 280);
  tft.println("(feed me fiat. " + String(charge) + "% charge)");
}
void feedmefiatloop() {
  tft.setTextColor(homeScreenColors[homeScreenNumColorCount]);
  tft.setTextSize(10);
  tft.setCursor(155, 80);
  tft.println("SATS");
  tft.setCursor(175, 140);
  tft.println("FOR");
  tft.setCursor(145, 190);
  tft.println("FIAT!");
  delay(100);
}
void qrShowCodeLNURL(String message) {
  if (printerBool) {
    printMessage("Printing", "please wait", "", TFT_WHITE, TFT_BLACK);
    delay(3000);
  }
  printReceipt();
  tft.fillScreen(TFT_WHITE);
  const char *qrDataChar = qrData.c_str();
  QRCode qrcoded;
  uint8_t qrcodeData[qrcode_getBufferSize(20)];
  qrcode_initText(&qrcoded, qrcodeData, 11, 0, qrDataChar);

  for (uint8_t y = 0; y < qrcoded.size; y++) {
    for (uint8_t x = 0; x < qrcoded.size; x++) {
      if (qrcode_getModule(&qrcoded, x, y)) {
        tft.fillRect(120 + 4 * x, 20 + 4 * y, 4, 4, TFT_BLACK);
      } else {
        tft.fillRect(120 + 4 * x, 20 + 4 * y, 4, 4, TFT_WHITE);
      }
    }
  }

  tft.setCursor(40, 290);
  tft.setTextSize(2);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.println(message);

  waitForTap = true;
  while (waitForTap) {
    BTNA.read();
    if (BTNA.wasReleased()) {
      waitForTap = false;
    }
  }
}