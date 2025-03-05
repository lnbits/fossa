#ifdef LAYOUT_1
    int horizontalOffset = 480;
    int verticalOffset = 40;
    int qrPixelSize = 4;
    int qrHorizontalOffset = 120;
    int qrVerticalOffset = 20;
    int qrTextHorizontalOffset = 40;
    int qrTextVerticalOffset = 290;
#endif
#ifdef LAYOUT_2
    int horizontalOffset = 240;
    int verticalOffset = 20;
    int qrPixelSize = 3;
    int qrHorizontalOffset = 28;
    int qrVerticalOffset = 28;
    int qrTextHorizontalOffset = 10;
    int qrTextVerticalOffset = 220;
#endif

void printMessage(String text1, String text2, String text3, int ftcolor, int bgcolor) {
  tft.fillScreen(bgcolor);
  tft.setTextColor(ftcolor, bgcolor);
  tft.setTextSize(3);
  tft.setCursor((horizontalOffset - tft.textWidth(text1)) / 2, verticalOffset);
  tft.println(text1);
  tft.setCursor((horizontalOffset - tft.textWidth(text2)) / 2, verticalOffset + 60);
  tft.println(text2);
  tft.setTextSize(3);
  tft.setCursor((horizontalOffset - tft.textWidth(text3)) / 2, verticalOffset + 140);
  tft.println(text3);
}

void feedmefiat() {
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(2);
  tft.setCursor((horizontalOffset - tft.textWidth(fossaT)) / 2, verticalOffset);
  tft.println(fossaT);
#ifdef LAYOUT_1
  String printFeedT = feedT + " " + String(charge) + chargeT;
  tft.setCursor((horizontalOffset - tft.textWidth(printFeedT)) / 2, verticalOffset + 260);
  tft.println(printFeedT);
#endif
#ifdef LAYOUT_2
  tft.setCursor((horizontalOffset - tft.textWidth(feedT)) / 2, verticalOffset + 240);
  tft.println(feedT);
  tft.setCursor((horizontalOffset - tft.textWidth(String(charge) + chargeT)) / 2, verticalOffset + 260);
  tft.println(String(charge) + chargeT);
#endif
}

void feedmefiatloop() {
  tft.setTextColor(homeScreenColors[homeScreenNumColorCount]);
  tft.setTextSize(8);
  tft.setCursor((horizontalOffset - tft.textWidth(satsT)) / 2, verticalOffset + 40);
  tft.println(satsT);
  tft.setCursor((horizontalOffset - tft.textWidth(forT)) / 2, verticalOffset + 100);
  tft.println(forT);
  tft.setCursor((horizontalOffset - tft.textWidth(fiatT)) / 2, verticalOffset + 160);
  tft.println(fiatT);
  delay(100);
}

void qrShowCodeLNURL() {
  #ifdef PRINTER
    printMessage(printingT, waitT, "", TFT_WHITE, TFT_BLACK);
    delay(3000);
    printReceipt();
  #endif
  tft.fillScreen(TFT_WHITE);
  const char *qrDataChar = qrData.c_str();
  QRCode qrcoded;
  uint8_t qrcodeData[qrcode_getBufferSize(30)];
  qrcode_initText(&qrcoded, qrcodeData, 11, 0, qrDataChar);

  for (uint8_t y = 0; y < qrcoded.size; y++) {
    for (uint8_t x = 0; x < qrcoded.size; x++) {
      if (qrcode_getModule(&qrcoded, x, y)) {
        tft.fillRect(qrHorizontalOffset + qrPixelSize * x, qrVerticalOffset + qrPixelSize * y, qrPixelSize, qrPixelSize, TFT_BLACK);
      } else {
        tft.fillRect(qrHorizontalOffset + qrPixelSize * x, qrVerticalOffset + qrPixelSize * y, qrPixelSize, qrPixelSize, TFT_WHITE);
      }
    }
  }
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
#ifdef LAYOUT_1
  tft.setCursor(qrTextHorizontalOffset, qrTextVerticalOffset);
  tft.println(scanMeT + " " + tapScreenT);
#endif
#ifdef LAYOUT_2
  tft.setCursor(qrTextHorizontalOffset, qrTextVerticalOffset);
  tft.println(scanMeT);
  tft.setCursor(qrTextHorizontalOffset, qrTextVerticalOffset + 20);
  tft.println(tapScreenT);
#endif

  delay(2000);

  waitForTap = true;
  while (waitForTap) {
    BTNA.read();
    if (BTNA.wasReleased()) {
      waitForTap = false;
    }
  }
}
