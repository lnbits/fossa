void to_upper(char *arr) {
  for (size_t i = 0; i < strlen(arr); i++) {
    if (arr[i] >= 'a' && arr[i] <= 'z') {
      arr[i] = arr[i] - 'a' + 'A';
    }
  }
}

String getJsonValue(JsonDocument &doc, const char *name) {
  for (JsonObject elem : doc.as<JsonArray>()) {
    if (strcmp(elem["name"], name) == 0) {
      String value = elem["value"].as<String>();
      return value;
    }
  }
  return "";
}

String getValue(String data, char separator, int index) {
  int found = 0;
  int strIndex[] = { 0, -1 };
  const int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }

  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void splitSettings(String str) {
  int firstComma = str.indexOf(',');
  int secondComma = str.indexOf(',', firstComma + 1);
  baseURLATM = str.substring(0, firstComma);
  Serial.println("baseURLATM: " + baseURLATM);
  // remove /api/v1.... and add /atm?lightning=
  int apiPos = baseURLATM.indexOf("api");
  baseUrlAtmPage = baseURLATM.substring(0, apiPos);
  baseUrlAtmPage += "atm?lightning=";
  Serial.println("baseUrlAtmPage: " + baseUrlAtmPage);
  secretATM = str.substring(firstComma + 1, secondComma);
  Serial.println("secretATM: " + secretATM);
  currencyATM = str.substring(secondComma + 1);
  Serial.println("currencyATM: " + currencyATM);
}

void convertStringToFloatArray(const char* str, float* floatArray) {
  char buffer[30];  // Temporary buffer to hold each substring
  int index = 0;  // Index for the float array
  int bufferIndex = 0;  // Index for the buffer

  for (int i = 0; str[i] != '\0'; i++) {
    if (str[i] == ',') {  // When a comma is found
      buffer[bufferIndex] = '\0';  // Null-terminate the buffer string
      floatArray[index] = atof(buffer);  // Convert buffer to float and store in array
      index++;  // Move to the next position in float array
      bufferIndex = 0;  // Reset buffer index
    } else {
      buffer[bufferIndex++] = str[i];  // Copy characters to buffer
    }
  }

  // Don't forget to convert the last number in the string
  buffer[bufferIndex] = '\0';  // Null-terminate the buffer
  floatArray[index] = atof(buffer);  // Convert buffer to float
}

void convertStringToIntArray(const char* str, int* intArray) {
  char buffer[20];  // Temporary buffer to hold each substring
  int index = 0;    // Index for the integer array
  int bufferIndex = 0;  // Index for the buffer

  for (int i = 0; str[i] != '\0'; i++) {
    if (str[i] == ',') {  // When a comma is found
      buffer[bufferIndex] = '\0';  // Null-terminate the buffer string
      intArray[index] = atoi(buffer);  // Convert buffer to int and store in array
      index++;  // Move to the next position in integer array
      bufferIndex = 0;  // Reset buffer index
    } else {
      buffer[bufferIndex++] = str[i];  // Copy characters to buffer
    }
  }

  // Don't forget to convert the last number in the string
  buffer[bufferIndex] = '\0';  // Null-terminate the buffer
  intArray[index] = atoi(buffer);  // Convert buffer to int
}
