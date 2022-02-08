#include <FirmwareUpdater.hpp>
#include <Utils.hpp>

void FirmwareUpdater::sendUpdateHttpResponse(AsyncWebServerRequest *request)
{
    AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", "Device will update and reboot, please wait.");
    response->addHeader("Refresh", "20");
    response->addHeader("Location", "/");
    request->send(response);
    Serial.println("Sent reboot notification to webpage.");
}

void FirmwareUpdater::startUpdate(AsyncWebServerRequest *request, String filename)
{
    Serial.println("Update request beginning...");
    activateESPLED();

    update_file_len = request->contentLength();

    // Check if firmware update or filesystem update
    // TODO: Improve this, include update type in request from frontend
    int cmd = (filename == "firmware.bin") ? U_FLASH : U_PART;

    Update.runAsync(true);

    size_t fsSize = ((size_t)&_FS_end - (size_t)&_FS_start);
    uint32_t maxSketchSpace = (ESP.getFreeSketchSpace() - 0x1000) & 0xFFFFF000;

    if (!Update.begin((cmd == U_PART) ? fsSize : maxSketchSpace, cmd))
    {
        Update.printError(Serial);
    }
    else
    {
        sendUpdateHttpResponse(request);
        isUpdating = true;

        if (cmd == U_PART)
        {
            LittleFS.end();
        }
    }
}

void FirmwareUpdater::endUpdate()
{
    if (!Update.end(true))
    {
        Update.printError(Serial);
    }
    else
    {
        Serial.println("Update complete, restarting!");
        Serial.flush();
        ESP.restart();
    }
}

void FirmwareUpdater::handleFirmwareUpdate(AsyncWebServerRequest *request, String filename, size_t index,
                                           uint8_t *data, size_t len, bool final)
{
    // TODO: Incorporate isUpdating
    if (!index)
    {
        startUpdate(request, filename);
    }

    // Handles writing update file to flash or filesystem.
    if (Update.write(data, len) != len)
    {
        Update.printError(Serial);
    }

    if (final)
    {
        endUpdate();
    }
}