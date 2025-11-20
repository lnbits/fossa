
void printQRcode(const String& qrData, uint8_t moduleSize = 6, bool isMainQR = true) {
  if (!printerBool) {
    Serial.println("No printer connected");
    return;
  }
  uint8_t ms = isMainQR ? moduleSize : (moduleSize > 1 ? moduleSize - 1 : 1);
  if (ms < 1) ms = 1;
  if (ms > 16) ms = 16;

  Stream& out = printerSerial;           // or your HardwareSerial if you swapped
  const uint8_t ecc = '1';               // M is a good default for receipts

  // Some units like an init/reset
  const uint8_t init[]   = { 0x1B, 0x40 };                                      // ESC @
  const uint8_t model2[] = { 0x1D,0x28,0x6B, 0x04,0x00, 0x31,0x41, 0x32,0x00 }; // GS ( k ... 1 A '2' 0
  const uint8_t sizeCmd[] = { 0x1D,0x28,0x6B, 0x03,0x00, 0x31,0x43, ms };       // module size
  const uint8_t eccCmd[]  = { 0x1D,0x28,0x6B, 0x03,0x00, 0x31,0x45, ecc };      // ECC

  out.write(init, sizeof(init));
  out.write(model2, sizeof(model2));
  out.write(sizeCmd, sizeof(sizeCmd));
  out.write(eccCmd, sizeof(eccCmd));

  // Store data: pL/pH = (len + 3), little-endian
  const uint16_t k   = (uint16_t)qrData.length();   // your ~170 fits easily
  const uint16_t len = k + 3;
  const uint8_t storeHdr[] = { 0x1D,0x28,0x6B, (uint8_t)(len & 0xFF), (uint8_t)(len >> 8), 0x31,0x50,0x30 };
  out.write(storeHdr, sizeof(storeHdr));
  out.print(qrData);

  // Print symbol
  const uint8_t printCmd[] = { 0x1D,0x28,0x6B, 0x03,0x00, 0x31,0x51,0x30 };
  out.write(printCmd, sizeof(printCmd));

  out.flush();
  delay(50);
  printer.feed(1);   // ensure it renders out of the head
}


void printReceipt() {
  if (!printerBool) {
    Serial.println("No printer connected");
    return;
  }
  printer.wake();
  printer.setDefault();
  printer.justify('C');  // Center align text
  printer.feed(3);
  printer.boldOn();
  printer.setSize('L');
  printer.println(thankYouT);
  printer.feed(1);
  printer.setSize('S');
  printer.println(thisVoucherT + " " + String(float(total / 100)) + " " + currencyATM + " " + ofBitcoinT);
  printer.feed(1);
  printer.underlineOn();
  printer.println(scanMeClaimT);
  printer.underlineOff();
  printer.feed(1);
  printQRcode(qrData);
  printer.boldOff();
  printer.feed(3);
  printer.sleep();
}