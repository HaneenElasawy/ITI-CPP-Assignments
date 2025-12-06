// app.cpp
#include "app.h"
#include "editor.h"
#include <iostream>
#include <limits>
#include <termios.h>
#include <unistd.h>
#include <cstdio>
#include <cstring>

using namespace std;

// ---------- Raw mode helpers ----------
static termios origTermios;

static void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &origTermios);
}

static void enableRawMode() {
    tcgetattr(STDIN_FILENO, &origTermios);
    termios raw = origTermios;

    // no echo, no canonical mode, no signals (Ctrl+C, Ctrl+Z)
    raw.c_lflag &= ~(ECHO | ICANON | ISIG);
    // no Ctrl+S/Ctrl+Q flow control
    raw.c_iflag &= ~(IXON);

    // allow read() to timeout so we can detect ESC alone
    raw.c_cc[VMIN]  = 0;   // minimum bytes
    raw.c_cc[VTIME] = 1;   // tenths of a second (0.1s)

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

// ---------- Key codes ----------
enum {
    KEY_ARROW_LEFT  = 1000,
    KEY_ARROW_RIGHT = 1001,
    KEY_ARROW_UP    = 1002,
    KEY_ARROW_DOWN  = 1003,
    KEY_UNKNOWN     = -1
};

// read one key (normal char or arrow)
static int readKey() {
    char c;
    ssize_t n = read(STDIN_FILENO, &c, 1);
    if (n <= 0) return KEY_UNKNOWN;

    if (c == '\x1b') { // ESC sequence or ESC alone
        char seq[2];
          
        if (read(STDIN_FILENO, &seq[0], 1) == 0) return 27;
        if (read(STDIN_FILENO, &seq[1], 1) == 0) return 27;

        if (seq[0] == '[') {
            switch (seq[1]) {
                case 'A': return KEY_ARROW_UP;
                case 'B': return KEY_ARROW_DOWN;
                case 'C': return KEY_ARROW_RIGHT;
                case 'D': return KEY_ARROW_LEFT;
            }
        }
                 
        return 27;
    }

    return static_cast<unsigned char>(c);
}

// clear screen and move cursor to top-left
static void clearScreen() {
    // \x1b[2J = clear screen, \x1b[H = move cursor home
    write(STDOUT_FILENO, "\x1b[2J\x1b[H", 7);
}

// render all lines + status bar + move cursor to its logical position
static void render(const TextBuffer& buffer,
                   const std::string& fileName,
                   bool dirty)
{
    clearScreen();

    int lineCount = buffer.getLineCount();
    for (int i = 0; i < lineCount; ++i) {
        const std::string& line = buffer.getLine(i);
        write(STDOUT_FILENO, line.c_str(), line.size());
        write(STDOUT_FILENO, "\r\n", 2);
    }

    // status bar: file name + modified + cursor position
    int cy = buffer.getCursorY();
    int cx = buffer.getCursorX();

    std::string status = "-- " + fileName +
        (dirty ? " (modified)" : " (saved)") +
        " | Ln " + std::to_string(cy + 1) +
        ", Col " + std::to_string(cx + 1) +
        " | Ctrl+S: Save | Ctrl+Q: Quit | Esc: Exit insert --";

    write(STDOUT_FILENO, status.c_str(), status.size());
    write(STDOUT_FILENO, "\r\n", 2);

    // move cursor to logical position (1-based in ANSI)
    char buf[64];
    snprintf(buf, sizeof(buf), "\x1b[%d;%dH", cy + 1, cx + 1);
    write(STDOUT_FILENO, buf, strlen(buf));
}

// insert-mode loop: multi-line editing
static void run_insert_mode(TextBuffer& buffer, const std::string& fileName) {
    enableRawMode();

    bool running = true;
    bool dirty   = false;

    // first render
    render(buffer, fileName, dirty);

    while (running) {
        int key = readKey();
        if (key == KEY_UNKNOWN) continue;

        // Ctrl+Q → exit whole program
        if (key == 17) { // Ctrl+Q
            disableRawMode();
            clearScreen();
            cout << "Exiting editor...\n";
            _exit(0);    
        }

        if (key == 27) { // ESC →  exite from insert mode
            running = false;
        }
        else if (key == 19) { // Ctrl+S
            if (buffer.saveToFile(fileName)) {
                dirty = false;
            }
        }
        else if (key == '\r' || key == '\n') { // Enter
            buffer.insertNewLine();
            dirty = true;
        }
        else if (key == 127 || key == 8) { // Backspace
            buffer.deleteChar();
            dirty = true;
        }
        else if (key == KEY_ARROW_LEFT) {
            buffer.moveLeft();
        }
        else if (key == KEY_ARROW_RIGHT) {
            buffer.moveRight();
        }
        else if (key == KEY_ARROW_UP) {
            buffer.moveUp();
        }
        else if (key == KEY_ARROW_DOWN) {
            buffer.moveDown();
        }
        else if (key >= 32 && key <= 126) {
            // printable characters
            buffer.insertChar(static_cast<char>(key));
            dirty = true;
        }
        // ignore other keys

        render(buffer, fileName, dirty);
    }

    disableRawMode();
    clearScreen();
}

// ----- Application menu -----
void app_run() {
    TextBuffer buffer;
    std::string fileName = "document.txt";

    int choice = -1;
    while (choice != 0) {
        cout << "\n===== Simple Text Editor =====\n";
        cout << "1. New / Edit document\n";
        cout << "2. Display file content\n";
        cout << "0. Exit\n";
        cout << "Choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear line

        if (choice == 1) {
            cout << "Enter file name to edit/save (e.g. notes.txt): ";
            std::getline(cin, fileName);
            if (fileName.empty())
                fileName = "document.txt";

            buffer.clear();          // start fresh document
            run_insert_mode(buffer, fileName);
        }
        else if (choice == 2) {
            std::string name;
            cout << "Enter file name to display: ";
            std::getline(cin, name);

            TextBuffer temp;
            if (!temp.loadFromFile(name)) {
                cout << "Error: cannot open file '" << name << "'\n";
            } else {
                cout << "\n--- File Content (" << name << ") ---\n";
                int n = temp.getLineCount();
                for (int i = 0; i < n; ++i) {
                    cout << temp.getLine(i) << "\n";
                }
                cout << "-------------------------------\n";
            }
        }
        else if (choice == 0) {
            cout << "Exiting...\n";
        }
        else {
            cout << "Invalid choice.\n";
        }
    }
}
