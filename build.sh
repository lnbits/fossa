#!/bin/sh
set -e

# ---- desired toolchain (matches your working local) ----
REQUIRED_CORE="esp32:esp32@2.0.17"
# Optional: warn if CLI differs from your local (1.2.2). Comment out if not needed.
REQUIRED_CLI_VER="1.2.2"

# ---- sanity: arduino-cli present ----
command -v arduino-cli >/dev/null 2>&1 || { echo >&2 "arduino-cli not found. Aborting."; exit 1; }

# ---- (optional) warn if CLI version differs, but don't fail ----
CLI_VER="$(arduino-cli version | awk '{print $3}')"
[ "$CLI_VER" = "$REQUIRED_CLI_VER" ] || echo "WARN: arduino-cli $CLI_VER != $REQUIRED_CLI_VER (ok if CI pins it)."

# ---- make sure Espressif index is configured (idempotent) ----
if ! arduino-cli config dump | grep -q 'package_esp32_index.json'; then
  arduino-cli config init --overwrite
  arduino-cli config set board_manager.additional_urls \
    https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
fi

arduino-cli core update-index

# ---- ensure the exact core version is installed (idempotent) ----
arduino-cli core install "$REQUIRED_CORE"

# NOTE: DO NOT run `arduino-cli upgrade` here; it can pull newer tool bundles and change behavior.

# ---- ensure the exact library versions you used locally (idempotent) ----
# If already present at that version, this is a no-op.
while IFS= read -r lib; do
  [ -n "$lib" ] || continue
  arduino-cli lib install "$lib"
done <<'EOF'
TFT_eSPI@2.5.43
ArduinoJson@7.2.0
uBitcoin@0.2.0
JC_Button@2.1.4
EspSoftwareSerial@8.1.0
Adafruit Thermal Printer Library@1.4.1
EOF

# ---- your existing flags & compile (unchanged) ----
tft_config=$(sh ./tft_config_build_flags.sh)
arduino-cli compile \
  --build-property "build.partitions=min_spiffs" \
  --build-property "upload.maximum_size=1966080" \
  --build-property "build.extra_flags.esp32=${tft_config}" \
  --library ./libraries/QRCode \
  --build-path build \
  --fqbn esp32:esp32:ttgo-lora32 \
  fossa
