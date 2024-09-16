#include <WiFiManager.h>
#include <Arduino.h>
#include <WiFi.h>

WiFiManager::WiFiManager() {}

void WiFiManager::addNetwork(const char *ssid, const char *password)
{
    _wifiMulti.addAP(ssid, password);
}

void WiFiManager::connect()
{
    Serial.println("Connecting to the best available Wi-Fi network...");
    tryToConnect();
}

bool WiFiManager::isConnected()
{
    return WiFi.status() == WL_CONNECTED;
}

void WiFiManager::handleReconnection()
{
    if (!isConnected())
    {
        if (millis() - _lastReconnectAttempt >= _reconnectInterval)
        {
            _lastReconnectAttempt = millis();
            Serial.println("Wi-Fi disconnected. Attempting reconnection...");
            _wifiMulti.run(); // Attempt to reconnect without restarting the ESP32
        }
    }
}

void WiFiManager::tryToConnect()
{
    int attempt = 0;
    while (attempt < _maxAttempts && _wifiMulti.run() != WL_CONNECTED)
    {
        delay(1000); // Delay between attempts
        Serial.print("Attempting to connect to the strongest Wi-Fi... Attempt ");
        Serial.println(attempt + 1);
        attempt++;
    }

    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println("Connected to Wi-Fi!");
    }
    else
    {
        Serial.println("Failed to connect to Wi-Fi after 20 attempts. Restarting ESP32...");
        restartESP(); // Restart only after max failed attempts in connect
    }
}

void WiFiManager::restartESP()
{
    delay(1000); // Optional: Give some time for logs to print
    ESP.restart();
}
