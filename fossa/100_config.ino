String failedT, unableT, maxaT, willT, loadT, maxrT, printY, langT;

void executeConfig() {
  while (true) {
    BTNA.read();
    if (BTNA.wasReleased()) {
      readFiles();
      return;
    }
    if (Serial.available() == 0)
      continue;
    String data = Serial.readStringUntil('\n');
    Serial.println("received: " + data);
    KeyValue kv = extractKeyValue(data);
    String commandName = kv.key;
    if (commandName == "/config-done") {
      Serial.println("/config-done");
      return;
    }
    executeCommand(commandName, kv.value);
  }
}

void executeCommand(String commandName, String commandData) {
  Serial.println("executeCommand: " + commandName + " > " + commandData);
  KeyValue kv = extractKeyValue(commandData);
  String path = kv.key;
  String data = kv.value;

  if (commandName == "/file-remove") {
    return removeFile(path);
  }
  if (commandName == "/file-append") {
    return appendToFile(path, data);
  }

  if (commandName == "/file-read") {
    Serial.println("prepare to read");
    readFile(path);
    Serial.println("readFile done");
    return;
  }

  Serial.println("command unknown");
}

void removeFile(String path) {
  Serial.println("removeFile: " + path);
  SPIFFS.remove("/" + path);
}

void appendToFile(String path, String data) {
  Serial.println("appendToFile: " + path);
  File file = SPIFFS.open("/" + path, FILE_APPEND);
  if (!file) {
    file = SPIFFS.open("/" + path, FILE_WRITE);
  }
  if (file) {
    file.println(data);
    file.close();
  }
}

void readFile(String path) {
  Serial.println("readFile: " + path);
  File file = SPIFFS.open("/" + path);
  if (file) {
    while (file.available()) {
      String line = file.readStringUntil('\n');
      Serial.println("/file-read " + line);
    }
    file.close();
  }
  Serial.println("");
  Serial.println("/file-done");
}

KeyValue extractKeyValue(String s) {
  int spacePos = s.indexOf(" ");
  String key = s.substring(0, spacePos);
  if (spacePos == -1) {
    return { key, "" };
  }
  String value = s.substring(spacePos + 1, s.length());
  return { key, value };
}

void printDefaultValues() {
  Serial.println("Device string: " + deviceString);
  Serial.println("Language: " + language);
  Serial.println("Charge: " + String(charge) + "%");
  Serial.println("Max amount: " + String(maxAmount));
  Serial.println("Max before reset: " + String(maxBeforeReset));
  convertStringToFloatArray(coinAmounts.c_str(), coinAmountFloat);
  convertStringToIntArray(billAmounts.c_str(), billAmountInt);
  Serial.println("Coin amounts: " + String(coinAmounts));
  Serial.println("Bill amounts: " + String(billAmounts));
}

void readFiles() {
  File paramFile = FlashFS.open(PARAM_FILE, "r");
  if (!paramFile) {
      Serial.println("unable to open spiffs.");
      printDefaultValues();
      printMessage("", failedT, unableT, TFT_WHITE, TFT_BLACK);
      return;
  }
  StaticJsonDocument<1000> doc;
  DeserializationError error = deserializeJson(doc, paramFile.readString());

  String LNURLConfig = getJsonValue(doc, "config_lnurl");
  if (LNURLConfig != "") {
    deviceString = LNURLConfig;
    Serial.println("Device string: " + deviceString);
  }
  else{
    Serial.println("LNURLdevice config not found, endless loop");
    printMessage("", failedT, unableT, TFT_WHITE, TFT_BLACK);
      while (true) {
    }
  }

  String maxAmountConfig = getJsonValue(doc, "config_max_amount, using default");
  if (maxAmountConfig != "") {
    maxAmount = maxAmountConfig.toInt();
    Serial.println("maxAmount: " + maxAmountConfig);

  } else {
    maxAmount = MAX_AMOUNT;
    printMessage("", maxaT + " " + String(maxAmount), willT, TFT_WHITE, TFT_BLACK);
    delay(3000);
    tft.fillScreen(TFT_BLACK);
  }

  String chargeConfig = getJsonValue(doc, "config_charge");
  if (chargeConfig != "") {
    charge = chargeConfig.toInt();
    Serial.println("charge: " + chargeConfig);
  } else {
    charge = CHARGE;
    Serial.println("charge config not found, using default");
    printMessage("", loadT, willT + " " + String(charge), TFT_WHITE, TFT_BLACK);
    delay(3000);
    tft.fillScreen(TFT_BLACK);
  }

  String maxBeforeResetConfig = getJsonValue(doc, "config_max_amount_reset");
  if (maxBeforeResetConfig != "") {
    maxBeforeReset = maxBeforeResetConfig.toInt();
    Serial.println("maxBeforeReset: " + maxBeforeResetConfig);
  } else {
    maxBeforeReset = MAX_BEFORE_RESET;
    Serial.println("maxBeforeReset config not found, using default");
    printMessage("", maxrT, willT + " " + String(maxBeforeReset), TFT_WHITE, TFT_BLACK);
    delay(3000);
    tft.fillScreen(TFT_BLACK);
  }

  billAmounts = getJsonValue(doc, "config_bill_ints");
  convertStringToIntArray(billAmounts.c_str(), billAmountInt);

  coinAmounts = getJsonValue(doc, "config_coin_floats");
  convertStringToFloatArray(coinAmounts.c_str(), coinAmountFloat);

  String langConfig = getJsonValue(doc, "config_lang");
  if (langConfig != "") {
    language = langConfig;
    Serial.println("language: " + langConfig);
  }
  else{
    language = LANGUAGE;
    Serial.println("language config not found");
    printMessage("", langT, willT + " " + language, TFT_WHITE, TFT_BLACK);
    delay(3000);
    tft.fillScreen(TFT_BLACK);
  }
  paramFile.close();
}
