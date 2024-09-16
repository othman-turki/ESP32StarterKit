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
    DEBUG_PRINT("Hello, world!");

    // Print a message with a variable
    int x = 5;
    DEBUG_PRINT("The value of x is: ");
    DEBUG_PRINT(x);

    // Print a message with a newline
    DEBUG_PRINTLN("This is a debug message with newline");

    // Print a message with multiple variables
    int y = 10;
    float z = 3.14;
    DEBUG_PRINT("The values are: x = ");
    DEBUG_PRINT(x);
    DEBUG_PRINT(", y = ");
    DEBUG_PRINT(y);
    DEBUG_PRINT(", z = ");
    DEBUG_PRINT(z);
}

void loop()
{
    // // Handle reconnection if Wi-Fi is lost
    // wifiManager.handleReconnection();
}
