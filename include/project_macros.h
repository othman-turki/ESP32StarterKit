#ifndef PROJECT_MACROS_H
#define PROJECT_MACROS_H

#define PROJECT_BAUD_RATE 115200

#define PROJECT_DEBUG_PRINT_FLAG 1

#if PROJECT_DEBUG_PRINT_FLAG
#define PROJECT_DEBUG_PRINT(...)   \
    do                             \
    {                              \
        Serial.print("[DEBUG] ");  \
        Serial.print(__VA_ARGS__); \
    } while (false)
#else
#define PROJECT_DEBUG_PRINT(...)
#endif

#if PROJECT_DEBUG_PRINT_FLAG
#define PROJECT_DEBUG_PRINTLN(...)   \
    do                               \
    {                                \
        Serial.print("[DEBUG] ");    \
        Serial.println(__VA_ARGS__); \
    } while (false)
#else
#define PROJECT_DEBUG_PRINTLN(...)
#endif

#if PROJECT_DEBUG_PRINT_FLAG
#define PROJECT_DEBUG_PRINTF(fmt, ...)     \
    do                                     \
    {                                      \
        Serial.print("[DEBUG] ");          \
        Serial.printf(fmt, ##__VA_ARGS__); \
    } while (false)
#else
#define PROJECT_DEBUG_PRINTF(fmt, ...)
#endif

#define WIFI_MAX_CONNECTION_ATTEMPTS 10

#define WIFI_CONNECTION_ATTEMPT_DELAY_MS 500

#define WIFI_RECONNECTION_INTERVAL_MS 3000

#define WIFI_MAX_RECONNECTION_INTERVAL_MS 30000

#endif // PROJECT_MACROS_H
