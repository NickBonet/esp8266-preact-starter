#include <Arduino.h>
#include <ESPAsyncWebServer.h>

#ifdef ESP8266
#include "LittleFS.h"
#include <Updater.h>
#include <ESP8266mDNS.h>
#define U_PART U_FS
#endif

class FirmwareUpdater
{

public:
    void handleFirmwareUpdate(AsyncWebServerRequest *request, String filename, size_t index,
                              uint8_t *data, size_t len, bool final);

private:
    size_t update_file_len;
    bool isUpdating;
    void sendUpdateHttpResponse(AsyncWebServerRequest *request);
    void startUpdate(AsyncWebServerRequest *request, String filename);
    void endUpdate();
};