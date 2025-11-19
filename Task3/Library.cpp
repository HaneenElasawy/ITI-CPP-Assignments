#include "headers.h"
#include <iostream>
#include <string>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

using namespace std;

// -----------------------------------------------------
// Move cursor to row, col
// -----------------------------------------------------
void moveCursor(int row, int col) {
#ifdef _WIN32
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { (SHORT)col, (SHORT)row };
    SetConsoleCursorPosition(h, pos);
#else
    printf("\033[%d;%dH", row + 1, col + 1);
#endif
}

// -----------------------------------------------------
// Set text color 
// -----------------------------------------------------
void setColor(int colorCode) {
    cout << "\033[" << colorCode << "m";
}

// -----------------------------------------------------
// Reset color
// -----------------------------------------------------
void resetColor() {
    cout << "\033[0m";
}

// -----------------------------------------------------
// Clear terminal screen
// -----------------------------------------------------
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    cout << "\033[2J\033[H";
#endif
}

// -----------------------------------------------------
// Print at specific location WITHOUT color
// Compatible with magicbox.cpp exactly
// -----------------------------------------------------
void printAt(int row, int col, const string& text) {
    moveCursor(row, col);
    cout << text << flush;
}

// -----------------------------------------------------
// Cross-platform delay in milliseconds
// -----------------------------------------------------
void delay(int milliseconds) {
#ifdef _WIN32
    Sleep(milliseconds);
#else
    usleep(milliseconds * 1000);
#endif
}
