void encrypt(unsigned char* key, unsigned char* iv, int length, const char* plainText, unsigned char* outputBuffer){
  mbedtls_aes_context aes;
  mbedtls_aes_init(&aes);
  mbedtls_aes_setkey_enc(&aes, key, 256); // AES-256 requires a 32-byte key
  mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_ENCRYPT, length, iv, (const unsigned char*)plainText, outputBuffer);
  mbedtls_aes_free(&aes);
}

void deriveKeyAndIV(const char* secret, unsigned char* salt, unsigned char* outputBuffer) {
  mbedtls_md5_context md5_ctx;
  unsigned char data[24]; // 16 bytes key + 8 bytes salt
  unsigned char md5Output[16]; // 16 bytes for MD5 output

  memcpy(data, secret, 16);
  memcpy(data + 16, salt, 8);

  // first iteration
  mbedtls_md5_init(&md5_ctx);
  mbedtls_md5_update(&md5_ctx, data, sizeof(data));
  mbedtls_md5_finish(&md5_ctx, md5Output);

  // Copy the first 16 bytes to the output buffer for the key
  memcpy(outputBuffer, md5Output, 16);

  unsigned char data_md5[16 + 16 + 8]; // 16 bytes md5 output + 16 bytes key + 8 bytes salt

  for (int i = 16; i <= 48; i+=16) {
    memcpy(data_md5, md5Output, 16);
    memcpy(data_md5 + 16, data, 24);
    mbedtls_md5_init(&md5_ctx);
    mbedtls_md5_update(&md5_ctx, data_md5, sizeof(data_md5));
    mbedtls_md5_finish(&md5_ctx, md5Output);
    // Copy the next 16 bytes to the output buffer
    memcpy(outputBuffer + i, md5Output, 16);
  }

  mbedtls_md5_free(&md5_ctx);
}


bool makeLNURL() {
  int salt_length = 8;
  unsigned char salt[salt_length];
  for (int i = 0; i < salt_length; i++) {
      salt[i] = random(0, 255);
  }
  unsigned char keyIV[32 + 16] = {0};
  deriveKeyAndIV(secretATM.c_str(), salt, keyIV);

  unsigned char key[32] = {0};
  unsigned char iv[16] = {0};

  int randomPin = random(1000, 9999);

  String payload = String(randomPin) + String(":") + String(total);
  size_t payload_len = payload.length();
  int padding = 16 - (payload_len % 16);
  payload_len += padding;
  for (int i = 0; i < padding; i++) {
    payload += String((char)padding);
  }


  unsigned char encrypted[payload_len] = {0};
  encrypt(key, iv, payload_len, payload.c_str(), encrypted);

  const unsigned char *saltedChars = (const unsigned char *)"Salted__";
  unsigned char salted[payload_len + 16];
  memcpy(salted, saltedChars, 8);
  memcpy(salted + 8, salt, salt_length);
  memcpy(salted + 16, encrypted, payload_len);

  String preparedURL = baseURLATM + "?p=";
  preparedURL += toBase64(salted, payload_len+16, BASE64_URLSAFE);

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
