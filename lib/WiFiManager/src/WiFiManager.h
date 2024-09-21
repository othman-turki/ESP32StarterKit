#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <WiFiMulti.h>

class WiFiManager
{
public:
    WiFiManager();

    void addNetwork(const char *ssid, const char *password);

    void connect();

    void handleReconnection();

    bool isReconnected() const;

    void resetReconnectionFlag();

private:
    WiFiManager(uint8_t maxAttempts, uint32_t delayBetweenAttempts,
                uint16_t reconnectInterval, uint16_t maxReconnectInterval);

    void tryToConnect();

    bool isConnected() const;

    void restartESP();

    WiFiMulti _wifiMulti;

    uint8_t _maxConnectionAttempts;
    uint32_t _connectionAttemptDelay;
    uint16_t _reconnectionInterval;
    uint16_t _currentReconnectionInterval;
    uint16_t _maxReconnectionInterval;
    unsigned long _lastReconnectAttempt = 0;
    bool _isConnectionLost = false;
    bool _isReconnected = false;
};

#endif // WIFI_MANAGER_H
