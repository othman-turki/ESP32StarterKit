#include "WiFiManager.h"
#include "project_macros.h"
#include <Arduino.h>
#include <WiFi.h>

WiFiManager::WiFiManager(uint8_t maxAttempts, uint32_t delayBetweenAttempts,
                         uint16_t reconnectInterval)
    : _maxAttempts(maxAttempts),
      _delayBetweenAttempts(delayBetweenAttempts),
      _reconnectInterval(reconnectInterval)
{
}

WiFiManager::WiFiManager()
    : WiFiManager(MAX_CONNECTION_ATTEMPTS,
                  DELAY_BETWEEN_CONNECTION_ATTEMPTS_MS,
                  RECONNECTION_INTERVAL_MS)
{
}

void WiFiManager::addNetwork(const char *ssid, const char *password)
{
    _wifiMulti.addAP(ssid, password);
}

void WiFiManager::connect()
{
    PROJECT_DEBUG_PRINTLN("Connecting to the best available Wi-Fi network...");
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
        if ((millis() - _lastReconnectAttempt) >=
            (unsigned long)_reconnectInterval)
        {
            _lastReconnectAttempt = millis();
            PROJECT_DEBUG_PRINTLN("Wi-Fi disconnected. Attempting reconnection...");
            _wifiMulti.run();
        }
    }
}

void WiFiManager::tryToConnect()
{
    int attempt = 0;
    while (attempt < _maxAttempts && _wifiMulti.run() != WL_CONNECTED)
    {
        delay(_delayBetweenAttempts);
        PROJECT_DEBUG_PRINT("Attempting to connect to the strongest Wi-Fi... Attempt ");
        PROJECT_DEBUG_PRINTLN(attempt + 1);
        attempt++;
    }

    if (WiFi.status() == WL_CONNECTED)
    {
        PROJECT_DEBUG_PRINTLN("Connected to Wi-Fi!");
    }
    else
    {
        PROJECT_DEBUG_PRINTLN("Failed to connect to Wi-Fi after max attempts.");
        restartESP();
    }
}

void WiFiManager::restartESP()
{
    PROJECT_DEBUG_PRINTLN("Restarting ESP32...");
    delay(1000); // Optional: Give some time for logs to print
    ESP.restart();
}
