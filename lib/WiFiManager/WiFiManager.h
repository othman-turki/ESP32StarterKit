// WiFiManager.h: Header file for the WiFiManager class

#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <WiFiMulti.h>

class WiFiManager
{
public:
    /**
     * @brief Constructor for WiFiManager class.
     *
     * Initializes a WiFiMulti object for managing multiple Wi-Fi networks.
     */
    WiFiManager();

    /**
     * @brief Adds a network to the list of available networks.
     *
     * @param ssid The network's SSID.
     * @param password The network's password.
     */
    void addNetwork(const char *ssid, const char *password);

    /**
     * @brief Connects to the best available network.
     *
     * If connection fails, the ESP32 will restart.
     */
    void connect();

    /**
     * @brief Checks if the device is connected.
     *
     * @return true if connected, false otherwise.
     */
    bool isConnected();

    /**
     * @brief Handles reconnection if Wi-Fi is lost.
     */
    void handleReconnection();

private:
    /// @brief Max attempts for connecting before restart
    int _maxAttempts = 20;

    /// @brief Time between reconnection attempts
    long _reconnectInterval = 10000;

    /// @brief Last time a reconnection attempt was made
    unsigned long _lastReconnectAttempt = 0;

    /// @brief WiFiMulti object for managing multiple networks
    WiFiMulti _wifiMulti;

    /**
     * @brief Restart ESP32 if connection fails in connect()
     */
    void restartESP();

    /**
     * @brief Attempt to connect to Wi-Fi
     */
    void tryToConnect();
};

#endif // WIFI_MANAGER_H
