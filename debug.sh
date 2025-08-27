if [ -z "$1" ]; then
    echo "Usage: ./debug.sh /dev/ttyUSB0"
    exit 1
fi
echo "User TFT Config: "
cat tft_config.txt
tft_config=$(sh ./tft_config_build_flags.sh)
arduino-cli compile \
    --build-property "build.partitions=min_spiffs" \
    --build-property "upload.maximum_size=1966080" \
    --build-property "build.extra_flags.esp32=${tft_config}" \
    --build-path build --fqbn esp32:esp32:ttgo-lora32 fossa && \
arduino-cli upload --input-dir build --fqbn esp32:esp32:ttgo-lora32 -p $1 && \
arduino-cli monitor -p $1 -c baudrate=115200
