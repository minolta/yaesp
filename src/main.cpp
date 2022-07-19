#include <Arduino.h>
#include "Configfile.h"
#include "sensorlist.h"
#include <WiFi.h>
#include <HTTPClient.h>
Configfile cfg("default.cfg");
Sensorlist SL;
/**
 * @brief
 * for read sensor data
 */
void readValue()
{
    // for test now
    for (int i = 0; i < 10; i++)
    {
        SL.add(10.0, 99.0, 100000, i, "noname");
    }
}
/**
 * @brief
 * for send value to server
 */
void senddataToServer()
{
 // for test now
    String json = SL.toJson();
    HTTPClient http;

    String serverPath = cfg.getConfig("serverurl", "http://192.168.88.225:8080") + "/adddata";

    http.begin(serverPath.c_str());
    http.addHeader("Content-Type", "application/json");
    int code = http.POST(json);

    http.end();
}
void connectWifi()
{
}
void setup()
{
}

void loop()
{
}