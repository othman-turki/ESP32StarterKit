#include <Arduino.h>
#include <WiFiManager.h>

WiFiManager wifiManager;

void setup()
{
    Serial.begin(115200);

    // Add your Wi-Fi networks
    wifiManager.addNetwork("o-turki", "01234567");
    wifiManager.addNetwork("ooredoo_8E1780", "3E7TNX74K9N9P");

    // Connect to the strongest available network
    wifiManager.connect();
}

void loop()
{
    // Handle reconnection if Wi-Fi is lost
    wifiManager.handleReconnection();
}
