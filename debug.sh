if [ -z "$1" ]; then
    echo "Usage: ./debug.sh /dev/ttyUSB0"
    exit 1
fi
echo "User TFT Config: "
cat tft_config.txt
tft_config=$(sh ./tft_config_build_flags.sh)

if [ ! -f fossa/hardcoded_user_config.h ]; then
    echo "No hardcoded_user_config.h found, creating from example..."
    cp fossa/hardcoded_user_config.h.example fossa/hardcoded_user_config.h
fi

echo "COMPILING..."
arduino-cli compile \
    --library ./libraries/QRCode \
    --build-property "build.partitions=min_spiffs" \
    --build-property "upload.maximum_size=1966080" \
    --build-property "build.extra_flags.esp32=${tft_config}" \
    --build-path build --fqbn esp32:esp32:ttgo-lora32 fossa && \
echo "UPLOADING..."
arduino-cli upload --input-dir build --fqbn esp32:esp32:ttgo-lora32 -p $1 && \
echo "MONITORING SERIAL..."
arduino-cli monitor -p $1 -c baudrate=115200
