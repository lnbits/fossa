void encrypt(const char* key, unsigned char* iv, int length, const char* plainText, unsigned char* outputBuffer){
  if (strlen(key) != 16) {
    Serial.println("Key must be 16 bytes long. not " + String(strlen(key)) + " bytes.");
    return;
  }
  mbedtls_aes_context aes;
  mbedtls_aes_init(&aes);
  mbedtls_aes_setkey_enc(&aes, (const unsigned char*)key, strlen(key)*8);
  mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_ENCRYPT, length, iv, (const unsigned char*)plainText, outputBuffer);
  mbedtls_aes_free(&aes);
}


bool makeLNURL() {
  unsigned char iv_init[16];
  unsigned char iv[16];
  for (int i = 0; i < 16; i++) {
      iv[i] = random(0, 255);
      iv_init[i] = iv[i];
  }
  int randomPin = random(1000, 9999);
  String payload = String(randomPin) + String(":") + String(total);
  size_t payload_len = payload.length();
  int padding = 16 - (payload_len % 16);
  unsigned char encrypted[payload_len + padding] = {0};
  encrypt(secretATM.c_str(), iv, payload_len + padding, payload.c_str(), encrypted);
  String preparedURL = baseURLATM + "?p=";
  preparedURL += toBase64(encrypted, payload_len, BASE64_URLSAFE | BASE64_NOPADDING);
  preparedURL += "&iv=";
  preparedURL += toBase64(iv_init, iv_length, BASE64_URLSAFE | BASE64_NOPADDING);
  Serial.println(preparedURL);
  lnurl_encode(preparedURL);
  return true;
}

void lnurl_encode(String preparedURL) {
  char Buf[200];
  preparedURL.toCharArray(Buf, 200);
  char *url = Buf;
  byte *data = (byte *)calloc(strlen(url) * 2, sizeof(byte));
  size_t len = 0;
  int res = convert_bits(data, &len, 5, (byte *)url, strlen(url), 8, 1);
  char *charLnurl = (char *)calloc(strlen(url) * 2, sizeof(byte));
  bech32_encode(charLnurl, "lnurl", data, len);
  to_upper(charLnurl);
  qrData = baseUrlAtmPage + charLnurl;
  Serial.println(qrData);
}
