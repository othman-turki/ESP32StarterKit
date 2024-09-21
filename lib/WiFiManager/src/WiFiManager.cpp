#include "WiFiManager.h"
#include "project_macros.h"
#include <Arduino.h>
#include <WiFi.h>

WiFiManager::WiFiManager(uint8_t maxConnectionAttempts,
                         uint32_t connectionAttemptDelay,
                         uint16_t reconnectionInterval,
                         uint16_t maxReconnectionInterval)
    : _maxConnectionAttempts(maxConnectionAttempts),
      _connectionAttemptDelay(connectionAttemptDelay),
      _reconnectionInterval(reconnectionInterval),
      _maxReconnectionInterval(maxReconnectionInterval)
{
}

WiFiManager::WiFiManager()
    : WiFiManager(WIFI_MAX_CONNECTION_ATTEMPTS,
                  WIFI_CONNECTION_ATTEMPT_DELAY_MS,
                  WIFI_RECONNECTION_INTERVAL_MS,
                  WIFI_MAX_RECONNECTION_INTERVAL_MS)
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

void WiFiManager::handleReconnection()
{
    if (!isConnected()) // Wi-Fi is currently disconnected.
    {
        if (!_isConnectionLost)
        {
            // First disconnection detected. Initialize the backoff interval.
            _isConnectionLost = true;
            _currentReconnectionInterval = _reconnectionInterval; // Start with the base interval.
        }

        // Check if the reconnection interval has passed since the last attempt.
        if ((millis() - _lastReconnectAttempt) >= _currentReconnectionInterval)
        {
            _lastReconnectAttempt = millis();
            PROJECT_DEBUG_PRINTLN("Wi-Fi disconnected. Attempting reconnection...");

            // Attempt to reconnect to the Wi-Fi network.
            if (_wifiMulti.run() != WL_CONNECTED)
            {
                // If reconnection fails, exponentially increase the interval with random jitter.
                uint16_t newInterval = (uint16_t)(_currentReconnectionInterval * 2);
                uint16_t randomDelay = random(0, 1000); // Up to 1000 ms of random delay.
                _currentReconnectionInterval = min(newInterval, _maxReconnectionInterval) + randomDelay;
                PROJECT_DEBUG_PRINTF("Reconnection failed. Next attempt in %u ms\n", _currentReconnectionInterval);
            }
        }
    }
    else // Wi-Fi is connected.
    {
        if (_isConnectionLost)
        {
            // Successful reconnection detected. Reset the reconnection flags and interval.
            PROJECT_DEBUG_PRINTLN("Wi-Fi reconnected successfully.");
            _isConnectionLost = false;
            _isReconnected = true;
            _currentReconnectionInterval = _reconnectionInterval; // Reset to the base interval.
        }
    }
}

void WiFiManager::tryToConnect()
{
    uint8_t attempt = 0;
    while (attempt < _maxConnectionAttempts && _wifiMulti.run() != WL_CONNECTED)
    {
        PROJECT_DEBUG_PRINTF("Attempting to connect to the strongest Wi-Fi... Attempt %u\n", attempt + 1);
        uint16_t randomDelay = random(0, 500); // Up to 500 ms of random delay.
        delay(_connectionAttemptDelay + randomDelay);
        attempt++;
    }

    if (isConnected())
    {
        PROJECT_DEBUG_PRINTLN("Connected to Wi-Fi!");
    }
    else
    {
        PROJECT_DEBUG_PRINTLN("Failed to connect to Wi-Fi after max attempts.");
        restartESP();
    }
}

bool WiFiManager::isConnected() const
{
    return WiFi.status() == WL_CONNECTED;
}

bool WiFiManager::isReconnected() const
{
    return _isReconnected;
}

void WiFiManager::resetReconnectionFlag()
{
    _isReconnected = false;
}

void WiFiManager::restartESP()
{
    PROJECT_DEBUG_PRINTLN("Restarting ESP32...");
    delay(1000); // Optional: Give some time for logs to print
    ESP.restart();
}
