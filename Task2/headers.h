#ifndef HEADERS_HPP
#define HEADERS_HPP
#include <string>

// ====== Basic terminal helpers (Task 1) ======

// Move cursor to (row, col)
void moveCursor(int row, int col);

// Set text color using ANSI color code
void setColor(int colorCode);

// Reset terminal colors / attributes
void resetColor();

// Clear entire screen and move cursor to home
void clearScreen();

// Print text at specific location with color
void printAt(int row, int col, const std::string& text, int colorCode);

// ====== Cross-platform single key input (Task 2) ======
char getch_cross();

// ====== Menu task functions (Task 2) ======
void showMenu(int current);
void page(const std::string& name);


#endif