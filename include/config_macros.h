#ifndef CONFIG_MACROS_H
#define CONFIG_MACROS_H

// Define a flag to enable or disable debug printing
#define DEBUG_PRINT_FLAG 1

// Define a macro for debug printing
#if DEBUG_PRINT_FLAG
#define DEBUG_PRINT(...)      \
    Serial.print("[DEBUG] "); \
    Serial.print(__VA_ARGS__)
#else
#define DEBUG_PRINT(...)
#endif

// Define a macro for debug printing with newline
#if DEBUG_PRINT_FLAG
#define DEBUG_PRINTLN(...)    \
    Serial.print("[DEBUG] "); \
    Serial.println(__VA_ARGS__)
#else
#define DEBUG_PRINTLN(...)
#endif

#define CONFIG_BAUD_RATE 115200

// // Wi-Fi configurations
// #define WIFI_SSID "YourSSID"
// #define WIFI_PASSWORD "YourPassword"

// // Pin configurations
// #define LED_PIN 2 // Built-in LED for ESP32
// // #define SENSOR_PIN 4 // Example sensor pin

// // Timeout settings
// #define WIFI_TIMEOUT 10000 // Wi-Fi connection timeout in milliseconds

// // Reconnection settings
// #define MAX_RETRIES 20 // Maximum retries for connecting to Wi-Fi

#endif // CONFIG_MACROS_H
