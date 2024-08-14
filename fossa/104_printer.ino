#include <cstdlib>  // Add this line to include the appropriate header file

// define a list of quote Strings that can be used to print on the receipt
const char* quotes[13] = {
  "It's very attractive to the libertarian viewpoint if we can explain it properly. I'm better with code than with words though.\r\nSatoshi Nakamoto, Dec 14, 2008",
  "In a few decades when the reward gets too small, the transaction fee will become the main compensation for nodes.\r\nSatoshi Nakamoto, Feb 14, 2010",
  "I'm sure that in 20 years there will either be very large transaction volume or no volume.\r\nSatoshi Nakamoto, Feb 14, 2010",
  "Imagine if gold turned to lead when stolen. If the thief gives it back, it turns to gold again.\r\nSatoshi Nakamoto, Aug 11, 2010",
  "If you don't believe me or don't get it, I don't have time to try to convince you, sorry.\r\nSatoshi Nakamoto, Jul 29, 2010",
  "The Times 03/Jan/2009 Chancellor on brink of second bailout for banks.",
  "It would have been nice to get this attention in any other context. WikiLeaks has kicked the hornet's nest, and the swarm is headed towards us.\r\nSatoshi Nakamoto, Dec 11, 2010",
  "Lost coins only make everyone else's coins worth slightly more. Think of it as a donation to everyone.\r\nSatoshi Nakamoto, Jul 21, 2010",
  "Sigh... why delete a wallet instead of moving it aside and keeping the old copy just in case?  You should never delete a wallet.\r\nSatoshi Nakamoto, October 3rd, 2010",
  "It's very attractive to the libertarian viewpoint if we can explain it properly. I'm better with code than with words though.\r\nSatoshi Nakamoto, Nov 14 2008",
  "It's time we had the same thing for money. With e-currency based on cryptographic proof, without the need to trust a third party middleman, money can be secure and transactions effortless.\r\nSatoshi Nakamoto, Jan 11 2009",
  "Sorry to be a wet blanket.  Writing a description for this thing for general audiences is bloody hard.  There's nothing to relate it to.\r\nSatoshi Nakamoto, 05 Jul 2010",
  "Yes, but we can win a major battle in the arms race and gain a new territory of freedom for several years.\r\nSatoshi Nakamoto, 6 Nov 2008"
};

//  function that returns a random quote from the list of quotes
const char* getRandomQuote() {
  return quotes[random(0, 13)];
}

void printQRcode(String qrData, byte size = 2, bool isMainQR = true) {
  // Using a smaller size or adjusting based on isMainQR
  byte adjustedSize = isMainQR ? size : max(1, size - 10);  // Ensure minimum size of 1

  // Adjust error correction: L (0x31), M (0x32), Q (0x33), H (0x34)
  byte eccLevel = 0x31;  // Start with low and increase if errors persist

  // Commands setup
  const byte modelCommand[] = { 0x1D, 0x28, 0x6B, 0x03, 0x00, 0x31, 0x43, adjustedSize };
  const byte eccCommand[] = { 0x1D, 0x28, 0x6B, 0x03, 0x00, 0x31, 0x45, eccLevel };
  const byte printCommand[] = { 0x1D, 0x28, 0x6B, 0x03, 0x00, 0x31, 0x51, 0x30 };

  printerSerial.write(modelCommand, sizeof(modelCommand));
  printerSerial.write(eccCommand, sizeof(eccCommand));

  int len = qrData.length() + 3;
  if (len > 255) {
    // Simple error handling for data that is too large
    Serial.println("Data too long for a single QR code!");
    return;
  }
  byte dataCommand[] = { 0x1D, 0x28, 0x6B, (byte)len, 0x00, 0x31, 0x50, 0x30 };
  printerSerial.write(dataCommand, sizeof(dataCommand));
  printerSerial.print(qrData);
  printerSerial.write(printCommand, sizeof(printCommand));
}

void printReceipt() {
  printer.wake();
  printer.setDefault();
  printer.justify('C');  // Center align text
  printer.feed(3);
  printer.boldOn();
  printer.setSize('L');
  printer.println("Thank you");
  printer.feed(1);
  printer.setSize('S');
  printer.println("This voucher can be redeemed for " + String(float(total / 100)) + " " + currencyATM + " of Bitcoin");
  printer.feed(1);
  printer.underlineOn();
  printer.println("Scan me with a Lightning wallet to get your Bitcoin");
  printer.underlineOff();
  printer.feed(1);
  printQRcode(qrData);
  printer.boldOff();
  printer.feed(1);
  printer.justify('L');
  printer.println(getRandomQuote());
  printer.feed(3);
  printer.sleep();
}