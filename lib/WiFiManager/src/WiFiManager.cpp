#include "WiFiManager.h"
#include "project_macros.h"
#include <Arduino.h>
#include <WiFi.h>

WiFiManager::WiFiManager(uint8_t maxAttempts, uint32_t delayBetweenAttempts,
                         uint16_t reconnectInterval, uint16_t maxReconnectInterval)
    : _maxAttempts(maxAttempts),
      _delayBetweenAttempts(delayBetweenAttempts),
      _reconnectInterval(reconnectInterval),
      _maxReconnectInterval(maxReconnectInterval)
{
}

WiFiManager::WiFiManager()
    : WiFiManager(MAX_CONNECTION_ATTEMPTS,
                  DELAY_BETWEEN_CONNECTION_ATTEMPTS_MS,
                  RECONNECTION_INTERVAL_MS,
                  MAX_RECONNECT_INTERVAL_MS)
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
    // Handles reconnection to the Wi-Fi network with exponential backoff and random delay.
    // Suitable for a system managing 300-500 devices, minimizing congestion and preserving real-time performance.
    //
    // Steps:
    // 1. Check if Wi-Fi is disconnected.
    // 2. If disconnected, ensure the reconnection interval has passed.
    // 3. Attempt reconnection using an exponentially increasing interval with random jitter.
    // 4. Upon successful reconnection, reset the interval and status flags.

    if (!isConnected()) // Wi-Fi is currently disconnected.
    {
        if (!_isConnectionLost)
        {
            // First disconnection detected. Initialize the backoff interval.
            _isConnectionLost = true;
            _currentReconnectInterval = _reconnectInterval; // Start with the base interval.
        }

        // Check if the reconnection interval has passed since the last attempt.
        if ((millis() - _lastReconnectAttempt) >= _currentReconnectInterval)
        {
            _lastReconnectAttempt = millis();
            PROJECT_DEBUG_PRINTLN("Wi-Fi disconnected. Attempting reconnection...");

            // Attempt to reconnect to the Wi-Fi network.
            if (_wifiMulti.run() != WL_CONNECTED)
            {
                // If reconnection fails, exponentially increase the interval and add random jitter.
                uint16_t randomDelay = random(0, 1000); // Add up to 1000 ms of random delay
                _currentReconnectInterval = min((uint16_t)(_currentReconnectInterval * 2.5 + randomDelay), _maxReconnectInterval);
                PROJECT_DEBUG_PRINTF("Reconnection failed. Next attempt in %u ms\n", _currentReconnectInterval);
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
            isReconnected = true;
            _currentReconnectInterval = _reconnectInterval; // Reset to the base interval.
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

bool WiFiManager::isConnected() const
{
    return WiFi.status() == WL_CONNECTED;
}

void WiFiManager::restartESP()
{
    PROJECT_DEBUG_PRINTLN("Restarting ESP32...");
    delay(1000); // Optional: Give some time for logs to print
    ESP.restart();
}
