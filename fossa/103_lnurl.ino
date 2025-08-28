// --- AES-CBC encrypt ---
void encrypt(unsigned char* key, unsigned char* iv, int length, const char* plainText, unsigned char* outputBuffer){
  mbedtls_aes_context aes;
  mbedtls_aes_init(&aes);

  // AES-256 key is 32 bytes (256 bits)
  mbedtls_aes_setkey_enc(&aes, key, 256);

  // Note: mbedtls_aes_crypt_cbc mutates the IV internally
  unsigned char working_iv[16];
  memcpy(working_iv, iv, sizeof(working_iv));

  mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_ENCRYPT, (size_t)length,
                        working_iv, (const unsigned char*)plainText, outputBuffer);

  mbedtls_aes_free(&aes);
}

// --- Derive 32-byte key + 16-byte IV from secret + 8-byte salt (EVP_BytesToKey-like, MD5 rounds) ---
void deriveKeyAndIV(const char* secret, unsigned char* salt, unsigned char* outKeyIV) {
  // outKeyIV must be 48 bytes: first 32 = key, next 16 = IV
  // We generate MD5 blocks until we have 48 bytes.
  unsigned char md5_buf[16];
  size_t have = 0;

  const unsigned char* sec = (const unsigned char*)secret;
  size_t sec_len = strlen(secret);

  mbedtls_md5_context ctx;

  while (have < 48) {
    mbedtls_md5_init(&ctx);
    // D_i = MD5( D_{i-1} (if any) + secret + salt )
    if (have > 0) {
      mbedtls_md5_update(&ctx, md5_buf, 16);
    }
    if (sec_len > 0) {
      mbedtls_md5_update(&ctx, sec, sec_len);
    }
    mbedtls_md5_update(&ctx, salt, 8);
    mbedtls_md5_finish(&ctx, md5_buf);
    mbedtls_md5_free(&ctx);

    size_t to_copy = (48 - have) < 16 ? (48 - have) : 16;
    memcpy(outKeyIV + have, md5_buf, to_copy);
    have += to_copy;
  }
}

// --- Build LNURL (prints URL and LNURL, sets global qrData) ---
bool makeLNURL() {
  // 8-byte salt
  unsigned char salt[8];
  for (int i = 0; i < 8; i++) {
    salt[i] = (unsigned char)random(0, 255);
  }

  // Derive key+iv (48 bytes)
  unsigned char keyIV[32 + 16] = {0};
  deriveKeyAndIV(secretATM.c_str(), salt, keyIV);

  unsigned char key[32];
  unsigned char iv[16];
  memcpy(key, keyIV, 32);
  memcpy(iv,  keyIV + 32, 16);

  // Random 4-digit PIN
  int randomPin = (int)random(1000, 9999);

  // Payload "PIN:total" + PKCS7 padding to 16 bytes
  String payload = String(randomPin) + ":" + String(total);
  size_t payload_len = payload.length();
  int padding = 16 - (payload_len % 16);
  if (padding == 16) padding = 16;
  payload_len += padding;

  // Create padded copy
  String padded = payload;
  for (int i = 0; i < padding; i++) {
    padded += (char)padding;
  }

  // Encrypt
  unsigned char* encrypted = (unsigned char*)malloc(payload_len);
  if (!encrypted) {
    Serial.println("ERR: malloc encrypted");
    return false;
  }
  encrypt(key, iv, (int)payload_len, padded.c_str(), encrypted);

  // "Salted__" header + 8-byte salt + ciphertext
  const unsigned char SALTED_HDR[8] = {'S','a','l','t','e','d','_','_'};
  size_t salted_len = 8 + 8 + payload_len;
  unsigned char* salted = (unsigned char*)malloc(salted_len);
  if (!salted) {
    Serial.println("ERR: malloc salted");
    free(encrypted);
    return false;
  }
  memcpy(salted,        SALTED_HDR, 8);
  memcpy(salted + 8,    salt,       8);
  memcpy(salted + 16,   encrypted,  payload_len);

  // Build full HTTP URL with urlsafe base64
  String preparedURL = baseURLATM + "?p=" + toBase64(salted, salted_len, BASE64_URLSAFE);

  Serial.println(preparedURL);
  lnurl_encode(preparedURL);  // prints LNURL and sets qrData

  free(salted);
  free(encrypted);
  return true;
}

// --- Safe LNURL bech32 encode (no fixed 200-byte buffer) ---
void lnurl_encode(const String& preparedURL) {
  size_t url_len = preparedURL.length();
  if (url_len == 0) {
    Serial.println("ERR: empty URL");
    return;
  }

  // Copy URL to C buffer
  char* url = (char*)malloc(url_len + 1);
  if (!url) {
    Serial.println("ERR: malloc url");
    return;
  }
  preparedURL.toCharArray(url, url_len + 1);

  // Convert 8-bit bytes to 5-bit groups (bech32 data part).
  // Worst-case output is about ceil(8/5 * url_len) -> ~1.6x, allocate extra headroom.
  size_t data_cap = url_len * 2 + 16;
  byte* data = (byte*)malloc(data_cap);
  if (!data) {
    Serial.println("ERR: malloc data");
    free(url);
    return;
  }
  size_t data_len = 0;
  int ok = convert_bits(data, &data_len, 5, (byte*)url, url_len, 8, 1);
  if (ok != 1 || data_len == 0) {
    Serial.println("ERR: convert_bits failed");
    free(data);
    free(url);
    return;
  }

  // Bech32 output length ~= hrp(5) + '1'(1) + data_len + checksum(6)
  // Add margin +1 for null.
  size_t lnurl_cap = 5 + 1 + data_len + 6 + 32;
  char* charLnurl = (char*)malloc(lnurl_cap);
  if (!charLnurl) {
    Serial.println("ERR: malloc lnurl");
    free(data);
    free(url);
    return;
  }

  int enc_len = bech32_encode(charLnurl, "lnurl", data, data_len);
  if (enc_len <= 0) {
    Serial.println("ERR: bech32_encode failed");
    free(charLnurl);
    free(data);
    free(url);
    return;
  }

  // Uppercase for QR readability (if your bech32 impl returns lowercase)
  to_upper(charLnurl);

  // Publish LNURL and final QR target
  qrData = baseUrlAtmPage + String(charLnurl);
  Serial.println(qrData);

  free(charLnurl);
  free(data);
  free(url);
}
