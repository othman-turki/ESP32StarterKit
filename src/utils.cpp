#include <vector>
#include <string>
#include <Arduino.h> // For Serial functions

void simulateLcdDisplay(const char *const lines[], int numLines,
                        int charsPerLine, int padding = 4)
{
    if (lines == nullptr)
    {
        Serial.println("Error: Null pointer passed to the function.");
        return;
    }

    if (numLines <= 0 || charsPerLine <= 0)
    {
        Serial.println("Error: Invalid number of lines or characters per line.");
        return;
    }

    // Create a vector of strings to hold the LCD buffer
    std::vector<std::string> lcdBuffer(numLines);

    for (int i = 0; i < numLines; i++)
    {
        if (lines[i] == nullptr)
        {
            Serial.print("Error: Line ");
            Serial.print(i);
            Serial.println(" is a null pointer.");
            lcdBuffer[i] = std::string(charsPerLine, ' '); // Empty line with spaces
            continue;
        }

        std::string line = lines[i]; // Convert C-string to std::string
        if (line.length() > charsPerLine)
        {
            line = line.substr(0, charsPerLine); // Truncate if necessary
        }
        else
        {
            line += std::string(charsPerLine - line.length(), ' '); // Pad with spaces
        }
        lcdBuffer[i] = line; // Store the formatted line in the buffer
    }

    // Print the lcdBuffer with a bordered box
    Serial.println("\n\n--- LCD SIMULATION START ---");

    // Calculate total width: content width + padding on both sides + 2 for borders
    int totalWidth = charsPerLine + (padding * 2);

    // Print the top border
    Serial.print("+");
    for (int i = 0; i < totalWidth; i++)
    {
        Serial.print("-");
    }
    Serial.println("+");

    // Print each line inside the border
    for (const auto &line : lcdBuffer)
    {
        Serial.print("|");
        for (int j = 0; j < padding; j++)
            Serial.print(" ");      // Left padding
        Serial.print(line.c_str()); // The content of the line
        for (int j = 0; j < padding; j++)
            Serial.print(" "); // Right padding
        Serial.println("|");
    }

    // Print the bottom border
    Serial.print("+");
    for (int i = 0; i < totalWidth; i++)
    {
        Serial.print("-");
    }
    Serial.println("+");

    Serial.println("--- LCD SIMULATION END ---\n\n");
}
