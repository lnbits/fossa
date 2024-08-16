// Supports languages:
// en (English), es (Spanish), zh (Chinese), hi (Hindi), ar (Arabic), pt (Portuguese), bn (Bengali), ru (Russian), ja (Japanese), pa (Punjabi),
// de (German), ko (Korean), fr (French), tr (Turkish), it (Italian)
String translate(String key, String language) {
  const char* translations = R"(
[en]
usb = USB config mode
tapScreen = TAP SCREEN WHEN FINISHED
scanMe = SCAN ME TAP SCREEN WHEN FINISHED
total = Total: 
fossa = FOSSA! Bitcoin ATM
sats = SATS
forT = FOR
fiat = FIAT!
feed = feed me fiat.
charge = % charge
printing = Printing
wait = please wait
working = Working...

[es]
usb = Modo de configuración USB
tapScreen = TOQUE LA PANTALLA CUANDO TERMINE
scanMe = ESCÁNEME TOQUE LA PANTALLA CUANDO TERMINE
total = Total: 
fossa = ¡FOSSA! Cajero Bitcoin
sats = SATS
forT = PARA
fiat = ¡FIAT!
feed = dame fiat.
charge = % de carga
printing = Imprimiendo
wait = por favor espera
working = Trabajando...

[fr]
usb = Mode de configuration USB
tapScreen = TOUCHEZ L'ÉCRAN QUAND TERMINÉ
scanMe = SCANEZ MOI TOUCHEZ L'ÉCRAN QUAND TERMINÉ
total = Total: 
fossa = FOSSA! Distributeur Bitcoin
sats = SATS
forT = POUR
fiat = FIAT!
feed = nourrissez-moi de fiat
charge = % charge
printing = Impression
wait = veuillez patienter
working = En cours...
)";

  String line;
  bool inCorrectLanguage = false;
  int startPos = 0;
  int endPos;

  while (startPos < strlen(translations)) {
    endPos = startPos;
    while (translations[endPos] != '\n' && translations[endPos] != '\0') {
      endPos++;
    }
    line = String(translations).substring(startPos, endPos);
    line.trim();  // Trim line
    startPos = endPos + 1;

    if (line.length() == 0) {
      continue;
    }

    // Check for language section
    if (line.startsWith("[")) {
      inCorrectLanguage = (line == "[" + language + "]");
      continue;
    }

    if (inCorrectLanguage) {
      int separatorPos = line.indexOf('=');
      if (separatorPos != -1) {
        String currentKey = line.substring(0, separatorPos);
        currentKey.trim();  // Trim key separately

        String value = line.substring(separatorPos + 1);
        value.trim();  // Trim value separately

        if (currentKey == key) {
          return value;
        }
      }
    }
  }

  return key;  // Return the key if no translation is found
}

void translateAll(String language) {
  usbT = translate("usb", language);
  tapScreenT = translate("tapScreen", language);
  scanMeT = translate("scanMe", language);
  totalT = translate("total", language);
  fossaT = translate("fossa", language);
  satsT = translate("sats", language);
  forT = translate("forT", language);
  fiatT = translate("fiat", language);
  feedT = translate("feed", language);
  chargeT = translate("charge", language);
  printingT = translate("printing", language);
  waitT = translate("wait", language);
  workingT = translate("working", language);
}
