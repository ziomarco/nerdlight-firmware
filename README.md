# nerdlight-firmware

nerdlight | ESP8266 Firmware

# Introduction

This is the repo for ESP8266 firmware.
Written bad, without knowing C/C++, using Arduino IDE.
It now can send heartbeats and receive messages formatted like

```json
{
  "r": 100,
  "g": 0,
  "b": 122,
  "timeoutMs": 1000 // optional
}
```

to change its light.

Basic actions done:
- [x] Created basic startup LED sequence and logics
- [x] Connecting to WiFi - if not, it will start in AP mode with "nerdlight" SSID in order to configure it
- [x] Connecting to AWS IOT Core with its certificates
- [x] Subscribing to its MQTT topic ("$MACADDRESS-SUB")
- [x] Publishing heartbeats to its MQTT topic ("$MACADDRESS-PUB")
- [x] Parsing JSON messages and change LED output basing on values

## Flashing the firmware
1) Install Arduino IDE

2) Download and install all required libraries/boards
- https://nerdyelectronics.com/upload-files-to-esp8266-spiffs/
- https://github.com/esp8266/Arduino/releases/tag/2.7.4
- https://github.com/knolleary/pubsubclient/releases/tag/v2.8
- https://github.com/arduino-libraries/NTPClient/releases/tag/3.2.0
- https://github.com/esp8266/Arduino/releases/tag/2.7.4
- https://github.com/tzapu/WiFiManager

2b) If you want to use Makefile please substitute in Makefile appropriate bin values

3) Upload SPIFF data on NodeMCU
[Follow this tutorial](https://nerdyelectronics.com/upload-files-to-esp8266-spiffs/)

4) Flash firmware with these settings
```
Board: NodeMCU 1.0 (ESP-12E)
Upload Speed: 115200
Flash Size: 4MB (FS 2MB)
```

5) Enjoy!