#include <Arduino.h>
#include "project_macros.h"
#include "WiFiManager.h"

WiFiManager wifiManager;

void setup()
{
    Serial.begin(PROJECT_BAUD_RATE);

    // Add your Wi-Fi networks
    // wifiManager.addNetwork("SSID", "PASSWORD"); // Replace with your network's SSID and password
    wifiManager.addNetwork("o-turki", "01234567");
    // wifiManager.addNetwork("ooredoo_8E1780", "3E7TNX74K9N9P");

    // Connect to the strongest available network
    wifiManager.connect();
}

void loop()
{
    // Handle reconnection if Wi-Fi is lost
    wifiManager.handleReconnection();
}
