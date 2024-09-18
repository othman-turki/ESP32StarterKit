#ifndef PROJECT_MACROS_H
#define PROJECT_MACROS_H

/**
 * @def PROJECT_BAUD_RATE
 * @brief Default baud rate for serial communication.
 */
#define PROJECT_BAUD_RATE 115200

/**
 * @def PROJECT_DEBUG_PRINT_FLAG
 * @brief Flag to enable or disable debug printing.
 *
 * Set to 1 to enable debug printing, or 0 to disable it.
 */
#define PROJECT_DEBUG_PRINT_FLAG 1

/**
 * @def PROJECT_DEBUG_PRINT
 * @brief Prints debug messages.
 *
 * Prints the given message to the serial console with a "[DEBUG] " prefix.
 * If PROJECT_DEBUG_PRINT_FLAG is 0, the macro expands to nothing.
 */
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

/**
 * @def PROJECT_DEBUG_PRINTLN
 * @brief Prints debug messages with a newline.
 *
 * Prints the given message to the serial console with a "[DEBUG] " prefix
 * and a newline at the end. If PROJECT_DEBUG_PRINT_FLAG is 0, the macro
 * expands to nothing.
 */
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

/**
 * @def MAX_CONNECTION_ATTEMPTS
 * @brief Maximum number of connection attempts to make before restarting
 * the ESP32.
 */
#define MAX_CONNECTION_ATTEMPTS 20

/**
 * @def DELAY_BETWEEN_CONNECTION_ATTEMPTS_MS
 * @brief Delay in milliseconds between connection attempts.
 */
#define DELAY_BETWEEN_CONNECTION_ATTEMPTS_MS 1000

/**
 * @def RECONNECTION_INTERVAL_MS
 * @brief Interval in milliseconds between reconnection attempts after Wi-Fi
 * connection is lost.
 */
#define RECONNECTION_INTERVAL_MS 10000

#endif // PROJECT_MACROS_H
