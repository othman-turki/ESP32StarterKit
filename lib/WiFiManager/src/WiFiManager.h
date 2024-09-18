#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <WiFiMulti.h>

class WiFiManager
{
public:
    /**
     * @brief Constructor to initialize the Wi-Fi manager.
     *
     * @details
     * This constructor initializes the Wi-Fi manager with the given parameters.
     * These parameters are used to control how the Wi-Fi manager behaves when
     * connecting to a Wi-Fi network.
     *
     * @param maxAttempts The maximum number of connection attempts to make
     * before restarting the ESP32. If the Wi-Fi manager is not able to connect
     * to a network after this many attempts, it will restart the ESP32 to try
     * again.
     *
     * @param delayBetweenAttempts The delay in milliseconds between connection
     * attempts. If a connection attempt fails, the Wi-Fi manager will wait for
     * this amount of time before trying again.
     *
     * @param reconnectInterval The interval in milliseconds between reconnection
     * attempts after the Wi-Fi connection is lost. This is used to detect when
     * the Wi-Fi connection is lost and to reattempt connecting to a network.
     */
    WiFiManager(uint8_t maxAttempts, uint32_t delayBetweenAttempts,
                uint16_t reconnectInterval);

    /**
     * @brief Default constructor to initialize the Wi-Fi manager with default
     * connection parameters.
     *
     * @details
     * This constructor initializes the Wi-Fi manager with default parameters
     * that control the behavior of the Wi-Fi manager when connecting to a
     * Wi-Fi network. These parameters are used to control how the Wi-Fi manager
     * behaves when connecting to a Wi-Fi network.
     *
     * @note
     * This constructor is equivalent to calling the other constructor with the
     * following default values:
     *
     * - maxAttempts: `MAX_CONNECTION_ATTEMPTS` (defined in `project_macros.h`)
     *
     * - delayBetweenAttempts: `DELAY_BETWEEN_CONNECTION_ATTEMPTS_MS` (defined in `project_macros.h`)
     *
     * - reconnectInterval: `RECONNECTION_INTERVAL_MS` (defined in `project_macros.h`)
     */
    WiFiManager();

    /**
     * @brief Add a Wi-Fi network to the list of available networks.
     *
     * @param ssid The SSID of the Wi-Fi network.
     * @param password The password for the Wi-Fi network.
     */
    void addNetwork(const char *ssid, const char *password);

    void connect();
    bool isConnected();
    void handleReconnection();

private:
    /**
     * @brief Maximum number of connection attempts to make before restarting
     * the ESP32.
     *
     * @details
     * This property controls how many times the Wi-Fi manager should attempt to
     * connect to a Wi-Fi network before restarting the ESP32. This is used to
     * prevent the ESP32 from going into an infinite loop when the Wi-Fi network
     * is not available.
     */
    uint8_t _maxAttempts;

    /**
     * @brief Delay in milliseconds between connection attempts.
     *
     * @details
     * This property controls the delay in milliseconds between each
     * connection attempt. This is used to prevent the ESP32 from making too
     * many connection attempts in a short period of time, which can cause the
     * ESP32 to crash.
     */
    uint32_t _delayBetweenAttempts;

    /**
     * @brief Interval in milliseconds between reconnection attempts after Wi-Fi
     * connection is lost.
     *
     * @details
     * This property controls the interval in milliseconds between each
     * reconnection attempt after the Wi-Fi connection is lost. This is used to
     * detect when the Wi-Fi connection is lost and to reattempt connecting to a
     * network.
     */
    uint16_t _reconnectInterval;

    /**
     * @brief Timestamp of the last reconnection attempt.
     *
     * @details
     * This property is used to keep track of the last time the Wi-Fi manager
     * attempted to reconnect to a network. This is used to prevent the ESP32
     * from making too many reconnection attempts in a short period of time,
     * which can cause the ESP32 to crash.
     */
    unsigned long _lastReconnectAttempt = 0;

    /**
     * @brief Instance of the WiFiMulti class used to manage multiple Wi-Fi
     * networks.
     *
     * @details
     * This property is an instance of the WiFiMulti class, which is used to
     * manage multiple Wi-Fi networks. The Wi-Fi manager uses this instance to
     * connect to the best available network.
     */
    WiFiMulti _wifiMulti;

    void restartESP();
    void tryToConnect();
};

#endif // WIFI_MANAGER_H
