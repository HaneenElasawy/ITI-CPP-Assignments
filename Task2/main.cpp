#include <iostream>
#include <string>
#include "headers.h"

enum Key { KEY_NONE, KEY_UP, KEY_DOWN, KEY_ENTER, KEY_BACK, KEY_ESC };

Key readKey();
void showMenu(int current) {
    clearScreen();
    std::string items[3] = {"New", "Display", "Exit"};

    for (int i = 0; i < 3; ++i) {
        if (i == current)
            printAt(5 + i, 10, "> " + items[i], 32);
        else
            printAt(5 + i, 10, "  " + items[i], 37);
    }
}
void page(const std::string& name) {
    clearScreen();
    printAt(5, 10, "You are inside: " + name, 33);
    printAt(7, 10, "Press Backspace or Home to return", 36);
    printAt(8, 10, "Press ESC to exit program", 31);

    while (true) {
        Key k = readKey();
        if (k == KEY_BACK) return;
        if (k == KEY_ESC) { clearScreen(); exit(0); }
    }
}
Key readKey() {
    char c = getch_cross();

#if defined(_WIN32)

    // ======= Windows =======
    if (c == 27)           // ESC
        return KEY_ESC;
    if (c == '\r')         // Enter
        return KEY_ENTER;
    if (c == 8)            // Backspace
        return KEY_BACK;
    // مفاتيح خاصة: أسهم / Home / End ...
    if (c == 0 || c == -32) {
        char c2 = getch_cross();
        if (c2 == 72)      // Up arrow
            return KEY_UP;
        if (c2 == 80)      // Down arrow
            return KEY_DOWN;
        if (c2 == 71)      // Home في Windows
            return KEY_BACK;   // ← هنا خليه زي الباك سبيس
    }
    return KEY_NONE;

#else
    // ======= Linux =======
    // Backspace (غالباً 127، وأحياناً 8)
    if (c == 127 || c == 8)  return KEY_BACK;
    if (c == '\n')           return KEY_ENTER;
    if (c == 27) {       // ESC sequence
        char c1 = getch_cross();

        // ESC لوحده (مش sequence مفاتيح)
        if (c1 != '[') {
            return KEY_ESC;
        }
        char c2 = getch_cross();
        // أسهم
        if (c2 == 'A')  return KEY_UP;     // Up
        if (c2 == 'B')  return KEY_DOWN;  // Down
        // Home: في بعض التيرمنالات ESC [ 1 ~
        if (c2 == '1') {
            char c3 = getch_cross();
            if (c3 == '~')
                return KEY_BACK;   // ← Home يعمل زي Back
        }
        // Home شكل تاني: ESC [ H
        if (c2 == 'H') {
            return KEY_BACK;       // ← برضه نرجّعه Back
        }
        // لو ESC + حاجة تانية مش محتاجينها دلوقتي
        return KEY_NONE;
    }
    return KEY_NONE;
#endif
}
int main() {
    int current = 0;

    while (true) {
        showMenu(current);
        Key k = readKey();

        if (k == KEY_UP && current > 0) current--;
        else if (k == KEY_DOWN && current < 2) current++;
        else if (k == KEY_ENTER) {
            if (current == 0)      page("New");
            else if (current == 1) page("Display");
            else if (current == 2) { clearScreen(); return 0; }
        }
        else if (k == KEY_ESC) {
            clearScreen();
            return 0;
        }
    }
}
