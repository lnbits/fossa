void executeConfig()
{
    while (true)
    {
        BTNA.read();
        if (BTNA.wasReleased())
        {
            readFiles();
            return;
        }
        if (Serial.available() == 0)
            continue;
        String data = Serial.readStringUntil('\n');
        Serial.println("received: " + data);
        KeyValue kv = extractKeyValue(data);
        String commandName = kv.key;
        if (commandName == "/config-done")
        {
            Serial.println("/config-done");
            return;
        }
        executeCommand(commandName, kv.value);
    }
}

void executeCommand(String commandName, String commandData)
{
    Serial.println("executeCommand: " + commandName + " > " + commandData);
    KeyValue kv = extractKeyValue(commandData);
    String path = kv.key;
    String data = kv.value;

    if (commandName == "/file-remove")
    {
        return removeFile(path);
    }
    if (commandName == "/file-append")
    {
        return appendToFile(path, data);
    }

    if (commandName == "/file-read")
    {
        Serial.println("prepare to read");
        readFile(path);
        Serial.println("readFile done");
        return;
    }

    Serial.println("command unknown");
}

void removeFile(String path)
{
    Serial.println("removeFile: " + path);
    SPIFFS.remove("/" + path);
}

void appendToFile(String path, String data)
{
    Serial.println("appendToFile: " + path);
    File file = SPIFFS.open("/" + path, FILE_APPEND);
    if (!file)
    {
        file = SPIFFS.open("/" + path, FILE_WRITE);
    }
    if (file)
    {
        file.println(data);
        file.close();
    }
}

void readFile(String path)
{
    Serial.println("readFile: " + path);
    File file = SPIFFS.open("/" + path);
    if (file)
    {
        while (file.available())
        {
            String line = file.readStringUntil('\n');
            Serial.println("/file-read " + line);
        }
        file.close();
    }
    Serial.println("");
    Serial.println("/file-done");
}

KeyValue extractKeyValue(String s)
{
    int spacePos = s.indexOf(" ");
    String key = s.substring(0, spacePos);
    if (spacePos == -1)
    {
        return {key, ""};
    }
    String value = s.substring(spacePos + 1, s.length());
    return {key, value};
}

void readFiles()
{
    File paramFile = FlashFS.open(PARAM_FILE, "r");
    if (paramFile)
    {
        StaticJsonDocument<1000> doc;
        DeserializationError error = deserializeJson(doc, paramFile.readString());

        String lnurlATM = getJsonValue(doc, "config_lnurlatm");
        baseURLATM = getValue(lnurlATM, ',', 0);
        secretATM = getValue(lnurlATM, ',', 1);
        currencyATM = getValue(lnurlATM, ',', 2);
        if (secretATM != "")
        {
            printMessage("Failed to load details", "Use web-config or hardcode", "", TFT_WHITE, TFT_BLACK);
            while (true)
            {
            }
        }

        String maxAmountConfig = getJsonValue(doc, "config_maxamount");
        if (maxAmountConfig != "")
        {
            maxamount = maxAmountConfig.toInt();
        }
        else
        {
            printMessage("Failed to load max amount", "Will use default", "", TFT_WHITE, TFT_BLACK);
            delay(3000);
        }

        String chargeConfig = getJsonValue(doc, "config_charge");
        if (chargeConfig != "")
        {
            charge = chargeConfig.toInt();
        }
        else
        {
            printMessage("Failed to load charge", "Will use default", "", TFT_WHITE, TFT_BLACK);
            delay(3000);
        }
    }
    paramFile.close();
}