void printMessage(String text1, String text2, String text3, int ftcolor, int bgcolor) {
  tft.fillScreen(bgcolor);
  tft.setTextColor(ftcolor, bgcolor);
  tft.setTextSize(4);
  tft.setCursor((480 - textWidth(text1, 4)) / 2, 40);
  tft.println(text1);
  tft.setCursor((480 - textWidth(text2, 4)) / 2, 120);
  tft.println(text2);
  tft.setTextSize(3);
  tft.setCursor((480 - textWidth(text3, 3)) / 2, 200);
  tft.println(text3);
}

void feedmefiat() {
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
  tft.setCursor((480 - textWidth(fossaT, 2)) / 2, 40);
  tft.setTextSize(2);
  tft.println(fossaT);
  tft.setCursor((480 - textWidth(feedT + " " + String(charge) + chargeT, 2)) / 2, 280);
  tft.setTextSize(2);
  tft.println(feedT + " " + String(charge) + chargeT);
}

void feedmefiatloop() {
  tft.setTextColor(homeScreenColors[homeScreenNumColorCount]);
  tft.setTextSize(8);
  tft.setCursor((480 - textWidth(satsT, 8)) / 2, 80);
  tft.println(satsT);
  tft.setCursor((480 - textWidth(forT, 8)) / 2, 140);
  tft.println(forT);
  tft.setCursor((480 - textWidth(fiatT, 8)) / 2, 200);
  tft.println(fiatT);
  delay(100);
}

void qrShowCodeLNURL() {
  #ifdef RECEIPT_PRINTER
    printMessage(printingT, waitT, "", TFT_WHITE, TFT_BLACK);
    delay(3000);
    printReceipt();
  #endif
  Serial.println(qrData);
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
  tft.println(scanMeT);
  delay(2000);
  waitForTap = true;
  while (waitForTap) {
    BTNA.read();
    if (BTNA.wasReleased()) {
      waitForTap = false;
    }
  }
}

int textWidth(String text, int textSize) {
  tft.setTextSize(textSize);
  return tft.textWidth(text);
}
