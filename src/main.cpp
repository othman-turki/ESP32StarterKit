#include <Arduino.h>
#include <config_macros.h>
#include <WiFiManager.h>

WiFiManager wifiManager;

void setup()
{
    Serial.begin(CONFIG_BAUD_RATE);

    // // Add your Wi-Fi networks
    // wifiManager.addNetwork("o-turki", "01234567");
    // wifiManager.addNetwork("ooredoo_8E1780", "3E7TNX74K9N9P");

    // // Connect to the strongest available network
    // wifiManager.connect();

    // Print a simple message
    DEBUG_PRINTLN("Hello, world!");
}

void loop()
{
    // // Handle reconnection if Wi-Fi is lost
    // wifiManager.handleReconnection();
}
