#ifndef HEADERS_HPP
#define HEADERS_HPP

#include <string>

void moveCursor(int row, int col);
void setColor(int colorCode);
void resetColor();
void clearScreen();
void printAt(int row, int col, const std::string& text);
void delay(int milliseconds);

#endif
