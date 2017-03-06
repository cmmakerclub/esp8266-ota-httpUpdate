#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>


#include <CMMC_Interval.hpp>
// OTA
CMMC_Interval timer;

static const char* fw_rev = "__FW_REV__";

#define USE_SERIAL Serial

void setup() {
  USE_SERIAL.begin(115200);
  // USE_SERIAL.setDebugOutput(true);

  USE_SERIAL.println();
  USE_SERIAL.println();
  USE_SERIAL.println();
}

#define FIRMWARE_URL "http://cmmc.io/firmware.php?version="

void loop() {
  timer.every_ms(5000, []() {
    String url = String(FIRMWARE_URL);
    url += fw_rev;
    t_httpUpdate_return ret = ESPhttpUpdate.update(url, fw_rev);
    switch (ret) {
      case HTTP_UPDATE_FAILED:
        Serial.printf("HTTP_UPDATE_FAILD Error (%d): %s", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
        break;

      case HTTP_UPDATE_NO_UPDATES:
        Serial.println("HTTP_UPDATE_NO_UPDATES");
        break;

      case HTTP_UPDATE_OK:
        Serial.println("HTTP_UPDATE_OK");
        break;
    }
  });

}
