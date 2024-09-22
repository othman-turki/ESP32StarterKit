#include <Arduino.h>
#include "project_macros.h"
#include "WiFiManager.h"
#include "utils.h"

WiFiManager wifiManager;

void setup()
{
    Serial.begin(PROJECT_BAUD_RATE);

    // Add your Wi-Fi networks
    wifiManager.addNetwork("o-turki", "01234567");
    // wifiManager.addNetwork("ooredoo_8E1780", "3E7TNX74K9N9P");

    // Connect to the strongest available network
    wifiManager.connect();

    const char *lines[] = {
        "This is a very long line that will be truncated",
        "Line 2 is shorter",
        "Line 3 is just right",
        "Line 4 is the last one"};
    int numLines = 4;
    int charsPerLine = 20; // or any other value you want
    simulateLcdDisplay(lines, numLines, charsPerLine);
}

void loop()
{
    // Handle reconnection if Wi-Fi is lost
    wifiManager.handleReconnection();
    if (wifiManager.isReconnected() == true)
    {
        Serial.println("Reconnected to Wi-Fi! Howdy!");
        wifiManager.resetReconnectionFlag();
    }
}
