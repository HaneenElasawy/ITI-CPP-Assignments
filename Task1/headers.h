#ifndef HEADERS_HPP
#define HEADERS_HPP

#include <string>

// Move cursor to coordinate
void moveCursor(int row, int col);

// Set color
void setColor(int colorCode);

// Reset terminal formatting
void resetColor();

// Clear entire screen
void clearScreen();

// Print text at specific location + color
void printAt(int row, int col, const std::string& text, int colorCode);

void delay(int milliseconds);



#endif