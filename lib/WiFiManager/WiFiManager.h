#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <WiFiMulti.h>

class WiFiManager
{
public:
    WiFiManager();

    void addNetwork(const char *ssid, const char *password); // Add multiple networks
    void connect();                                          // Initiate connection to the best network with restart if it fails
    bool isConnected();                                      // Check if the device is connected
    void handleReconnection();                               // Reconnect if disconnected, no restart

private:
    WiFiMulti _wifiMulti;  // Use WiFiMulti for managing multiple networks
    int _maxAttempts = 20; // Max attempts for connecting before restart
    void restartESP();     // Restart ESP32 if connection fails in connect()
    void tryToConnect();   // Attempt to connect to Wi-Fi

    long _reconnectInterval = 10000; // Time between reconnection attempts
    unsigned long _lastReconnectAttempt = 0;
};

#endif /* WIFI_MANAGER_H */
