#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include "LittleFS.h"
#include "credentials.hpp"

#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPmDNS.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESP8266mDNS.h>
#endif

AsyncWebServer server(9080);

const char *ssid = WIFI_SSID;
const char *password = WIFI_PASSWORD;

void notFound(AsyncWebServerRequest *request)
{
    request->send(404, "text/plain", "Not found");
}

void setup()
{
    Serial.begin(115200);

    // LittleFS initialization
    if (!LittleFS.begin())
    {
        Serial.println("An error has occurred while mounting LittleFS filesystem.");
        return;
    }

    // WiFi initialization
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    if (WiFi.waitForConnectResult() != WL_CONNECTED)
    {
        Serial.println("WiFi connection failed!");
        return;
    }

    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    if (!MDNS.begin("esp8266"))
    {
        Serial.println("Error setting up mDNS responder.");
    }

    server.onNotFound(notFound);
    server.serveStatic("/", LittleFS, "/www/");
    server.on("*", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(LittleFS, "/www/index.html"); });

    server.begin();
}

void loop()
{
    MDNS.update();
}