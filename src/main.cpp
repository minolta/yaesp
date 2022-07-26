#include <Arduino.h>
#include "Configfile.h"
#include "sensorlist.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <ESPAsyncWebServer.h>
#include "Ticker.h"

long uptime = 0;
long readtime = 0;
long sendtime = 0;
Ticker ticker;
AsyncWebServer server(80);
Configfile cfg("/default.cfg");
Sensorlist SL;

/**
 * @brief
 * for read sensor data
 */
void readValue()
{
    // for test now
    for (int i = 1; i < 10; i++)
    {
        SL.add(i,10.0, 99.0, 100000, i, "noname");
    }
}

void runTicker()
{
    uptime++;
    readtime++;
    sendtime++;
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

    String serverPath = cfg.getConfig("adddatas", "http://192.168.88.225:8080/addsensorvalues");
    Serial.printf("Call %s\n", serverPath.c_str());
    http.begin(serverPath.c_str());
    http.addHeader("Content-Type", "application/json");
    Serial.println(json);
    int code = http.POST(json);
    Serial.printf("\n Code :%d\n", code);
    http.end();
    SL.clear();
}
void connectWifi()
{

    WiFi.begin(cfg.getConfig("ssid", "forpi").c_str(), cfg.getConfig("password", "04qwerty").c_str());
    Serial.println("Connecting to WiFi..");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(100);
        Serial.print(".");
    }
    Serial.println("Connected");
    Serial.printf("\n %s", WiFi.localIP().toString().c_str());
}
void defaultwww(AsyncWebServerRequest *request)
{
    request->send(200, "text/plain", "OK");
}
void setconfigwww(AsyncWebServerRequest *request)
{
    cfg.setconfigwww(request);
}
void allconfigwww(AsyncWebServerRequest *request)
{
    cfg.allconfigwww(request);
}
void setHttp()
{

    server.on("/", HTTP_GET, defaultwww);
    server.on("/setconfig", HTTP_GET, setconfigwww);
    server.on("/allconfig", HTTP_GET, allconfigwww);
    server.begin();
}
void setup()
{
    cfg.openFile();
    Serial.begin(9600);
    connectWifi();
    ticker.attach(1, runTicker);
    setHttp();
}

void loop()
{

    if (readtime >= 10)
    {
        readtime = 0;
        readValue();
    }
    if (sendtime >= 30)
    {
        sendtime = 0;
        senddataToServer();
    }
}