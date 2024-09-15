// Config.h or Macros.h
#ifndef CONFIG_H
#define CONFIG_H

// Wi-Fi configurations
// #define WIFI_SSID "YourSSID"
// #define WIFI_PASSWORD "YourPassword"

// Debugging configurations
#define DEBUG true // Set to false to disable serial debug prints

// Pin configurations
#define LED_PIN 2 // Built-in LED for ESP32
// #define SENSOR_PIN 4 // Example sensor pin

// Timeout settings
#define WIFI_TIMEOUT 10000 // Wi-Fi connection timeout in milliseconds

// Reconnection settings
#define MAX_RETRIES 20 // Maximum retries for connecting to Wi-Fi

#endif /* CONFIG_H */
