#include <iostream>
#include "headers.h"
// هنا بنعمل include بناءً على نوع النظام
#if defined(_WIN32)
    #include <conio.h>
#else
    #include <termios.h>
    #include <unistd.h>
#endif

// ====== Basic terminal helpers (Task 1) ======

// Move cursor to (row, col)
void moveCursor(int row, int col) {
    std::cout << "\033[" << row << ";" << col << "H";
}

// Set color using ANSI code (31 = red, 32 = green, ...)
void setColor(int colorCode) {
    std::cout << "\033[" << colorCode << "m";
}

// Reset color/formatting
void resetColor() {
    std::cout << "\033[0m";
}

// Clear screen and move cursor to home
void clearScreen() {
    std::cout << "\033[2J\033[H";
}

// High level print: go to position, set color, print, reset
void printAt(int row, int col, const std::string& text, int colorCode) {
    moveCursor(row, col);
    setColor(colorCode);
    std::cout << text << std::flush;
    resetColor();
}

// ====== Cross-platform getch (Task 2) ======
char getch_cross() {

#if defined(_WIN32)

    // على ويندوز نستخدم _getch الجاهزة من conio.h
    return _getch();

#else

    // على لينكس نستخدم termios + read لقراءة حرف واحد بدون Enter
    char c = 0;

    termios oldAttr{};
    if (tcgetattr(STDIN_FILENO, &oldAttr) < 0) {
        return 0;
    }

    termios newAttr = oldAttr;
    newAttr.c_lflag &= ~(ICANON | ECHO); // no line buffering, no echo
    newAttr.c_cc[VMIN]  = 1;             // نقرأ حرف واحد
    newAttr.c_cc[VTIME] = 0;

    if (tcsetattr(STDIN_FILENO, TCSANOW, &newAttr) < 0) {
        return 0;
    }

    if (read(STDIN_FILENO, &c, 1) < 0) {
        c = 0;
    }

    // رجّع الإعدادات القديمة
    tcsetattr(STDIN_FILENO, TCSANOW, &oldAttr);

    return c;

#endif
}
