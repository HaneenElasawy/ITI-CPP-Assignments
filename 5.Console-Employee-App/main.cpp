#include <iostream>
#include <string>
#include "employee.h"
using namespace std;



Key readKey();
void showMenu(int current) {
    clearScreen();
    string items[3] = {"New", "Display", "Exit"};

    for (int i = 0; i < 3; ++i) {
        if (i == current)
            printAt(5 + i, 10, "> " + items[i], 32);
        else
            printAt(5 + i, 10, "  " + items[i], 37);
    }
}
void page(const 
    string& name) {

    if (name == "New") {

            addEmployee();  
        }
     else if (name == "Display") {

        displayEmployees();

        printAt(18, 10, "Press Backspace or Home to return", 36);
        printAt(19, 10, "Press ESC to exit program", 31);
     }
        else if( name == "Exit") {
            clearScreen();
            exit(0);
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

    if (c == 0 || c == -32) {
        char c2 = getch_cross();
        if (c2 == 72)      // Up arrow
            return KEY_UP;
        if (c2 == 80)      // Down arrow
            return KEY_DOWN;
        if (c2 == 71)      // Home في Windows
            return KEY_BACK;   
    }
    return KEY_NONE;

#else
    // ======= Linux =======
    // Backspace ( 127 || 8)
    if (c == 127 || c == 8)  return KEY_BACK;
    if (c == '\n')           return KEY_ENTER;
    if (c == 27) {       // ESC sequence
        char c1 = getch_cross();

        // ESC  ( sequence )
        if (c1 != '[') {
            return KEY_ESC;
        }
        char c2 = getch_cross();
        // أسهم
        if (c2 == 'A')  return KEY_UP;     // Up
        if (c2 == 'B')  return KEY_DOWN;  // Down
        // Home ==> ESC [ 1 ~ 
        if (c2 == '1') {
            char c3 = getch_cross();
            if (c3 == '~')
                return KEY_BACK;   
        }
        // Home ==>  ESC [ H
        if (c2 == 'H') {
            return KEY_BACK;      
        }
    
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
if (k == KEY_UP) {

    if (current == 0)
        current = 2;
    else
        current--;
}
else if (k == KEY_DOWN) {
    
    if (current == 2)
        current = 0;
    else
        current++;
}
else if (k == KEY_ENTER) {
    if (current == 0)       page("New");
    else if (current == 1)  page("Display");
    else if (current == 2) { 
        clearScreen(); 
        return 0; 
    }
}
else if (k == KEY_ESC) {
    clearScreen();
    return 0;
}

    }
}
