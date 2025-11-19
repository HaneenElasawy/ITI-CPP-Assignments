#include <iostream>
#include <string>
#include "headers.h"
#include <unistd.h>

#if defined(_WIN32)
    #include <conio.h>
#else
    #include <termios.h>
    #include <unistd.h>
#endif

// Move cursor to a specific row/col
void moveCursor(int row, int col) {
    std::cout << "\033[" << row << ";" << col << "H";
}

// Change text color
void setColor(int colorCode) {
    std::cout << "\033[" << colorCode << "m";
}

// Reset text formatting
void resetColor() {
    std::cout << "\033[0m";
}

// Clear screen
void clearScreen() {
    std::cout << "\033[2J\033[H";
}

// High-level print function
void printAt(int row, int col, const std::string& text, int colorCode) {
    moveCursor(row, col);
    setColor(colorCode);
    std::cout << text << std::flush;
    resetColor();
}
void delay(int milliseconds)
{
#if defined(_WIN32)
    Sleep(milliseconds);
#else
    usleep(milliseconds * 1000);
#endif
}