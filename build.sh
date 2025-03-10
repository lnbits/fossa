#!/bin/sh
command -v arduino-cli >/dev/null 2>&1 || { echo >&2 "arduino-cli not found. Aborting."; exit 1; }
arduino-cli config --additional-urls https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json init --overwrite
arduino-cli core update-index
arduino-cli upgrade
# uBitcoin is broken on esp32 3.x.x
arduino-cli core install esp32:esp32@2.0.17
arduino-cli lib install TFT_eSPI ArduinoJson uBitcoin JC_Button EspSoftwareSerial "Adafruit Thermal Printer Library"

tft_config=$(sh ./tft_config_build_flags.sh)
arduino-cli compile \
    --build-property "build.partitions=min_spiffs" \
    --build-property "upload.maximum_size=1966080" \
    --build-property "build.extra_flags.esp32=${tft_config}" \
    --library ./libraries/QRCode \
    --build-path build --fqbn esp32:esp32:ttgo-lora32 fossa
