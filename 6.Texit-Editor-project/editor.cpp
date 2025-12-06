#include "TextEditor.h"

#include <iostream>
#include <fstream>
#include <termios.h>
#include <unistd.h>
#include <cstring>

using namespace std;

// ======== terminal helpers (raw mode) ========

static termios origTermios;

static void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &origTermios);
}

static void enableRawMode() {
    tcgetattr(STDIN_FILENO, &origTermios);
    termios raw = origTermios;

    raw.c_lflag &= ~(ECHO | ICANON); // no echo, no line buffering
    raw.c_lflag &= ~(ISIG);          // disable Ctrl-C signals etc.
    raw.c_iflag &= ~(IXON);          // disable Ctrl-S / Ctrl-Q flow control

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
    atexit(disableRawMode);
}

static char readKey() {
    char c;
    ssize_t n = read(STDIN_FILENO, &c, 1);
    if (n <= 0) return 0;
    return c;
}

static void clearScreen() {
    write(STDOUT_FILENO, "\x1b[2J", 4);
    write(STDOUT_FILENO, "\x1b[H", 3);
}

static void moveCursor(int row, int col) {
    char buf[32];
    snprintf(buf, sizeof(buf), "\x1b[%d;%dH", row + 1, col + 1);
    write(STDOUT_FILENO, buf, strlen(buf));
}

// ======== TextEditor implementation ========

TextEditor::TextEditor()
    : lines(nullptr), lineCount(0), capacity(0), fileName("") {}

TextEditor::~TextEditor() {
    delete[] lines;
}

void TextEditor::ensureCapacity(int newCount) {
    if (newCount <= capacity) return;

    int newCap = (capacity == 0) ? 4 : capacity * 2;
    while (newCap < newCount) newCap *= 2;

    string* newLines = new string[newCap];
    for (int i = 0; i < lineCount; ++i) {
        newLines[i] = lines[i];
    }

    delete[] lines;
    lines = newLines;
    capacity = newCap;
}

bool TextEditor::loadFile(const string& name) {
    fileName = name;

    ifstream in(name);
    if (!in) {
        // file does not exist -> start with empty buffer
        ensureCapacity(1);
        lineCount = 1;
        lines[0] = "";
        return false;
    }

    string line;
    lineCount = 0;
    while (getline(in, line)) {
        ensureCapacity(lineCount + 1);
        lines[lineCount++] = line;
    }

    if (lineCount == 0) {
        ensureCapacity(1);
        lineCount = 1;
        lines[0] = "";
    }

    return true;
}

bool TextEditor::saveFile() const {
    if (fileName.empty()) return false;

    ofstream out(fileName);
    if (!out) return false;

    for (int i = 0; i < lineCount; ++i) {
        out << lines[i];
        if (i + 1 < lineCount) out << '\n';
    }
    return true;
}

void TextEditor::edit() {
    enableRawMode();
    clearScreen();

    int row = 0;
    int col = 0;

    bool running = true;

    while (running) {
        clearScreen();

        cout << "Simple Text Editor (student version)\n";
        cout << "File: " << (fileName.empty() ? "(no name)" : fileName) << "\n";
        cout << "Arrows: move | Enter: new line | Backspace: delete\n";
        cout << "Ctrl+S: save & exit | Ctrl+Q: exit without save\n";
        cout << "----------------------------------------------\n";

        for (int i = 0; i < lineCount; ++i) {
            cout << lines[i] << "\n";
        }

        if (row >= lineCount) row = lineCount - 1;
        if (row < 0) row = 0;
        if (col > (int)lines[row].size()) col = lines[row].size();
        if (col < 0) col = 0;

        moveCursor(4 + row, col);

        char c = readKey();
        if (c == 0) continue;

        if (c == 17) { // Ctrl-Q
            running = false;
        } else if (c == 19) { // Ctrl-S
            saveFile();
            running = false;
        } else if (c == '\r' || c == '\n') {
            string current = lines[row];
            string left = current.substr(0, col);
            string right = current.substr(col);

            lines[row] = left;

            ensureCapacity(lineCount + 1);
            for (int i = lineCount; i > row + 1; --i) {
                lines[i] = lines[i - 1];
            }
            lines[row + 1] = right;
            lineCount++;

            row++;
            col = 0;
        } else if (c == 127 || c == 8) { // Backspace
            if (col > 0) {
                lines[row].erase(col - 1, 1);
                col--;
            } else if (row > 0) {
                int oldLen = lines[row - 1].size();
                lines[row - 1] += lines[row];
                for (int i = row; i < lineCount - 1; ++i) {
                    lines[i] = lines[i + 1];
                }
                lineCount--;
                row--;
                col = oldLen;
            }
        } else if (c == '\x1b') {
            char c1 = readKey();
            char c2 = readKey();
            if (c1 == '[') {
                if (c2 == 'A') {
                    if (row > 0) row--;
                } else if (c2 == 'B') {
                    if (row < lineCount - 1) row++;
                } else if (c2 == 'C') {
                    if (col < (int)lines[row].size()) col++;
                    else if (row < lineCount - 1) {
                        row++;
                        col = 0;
                    }
                } else if (c2 == 'D') {
                    if (col > 0) col--;
                    else if (row > 0) {
                        row--;
                        col = lines[row].size();
                    }
                }
            }
        } else if (c >= 32 && c <= 126) {
            lines[row].insert(lines[row].begin() + col, c);
            col++;
        }
    }

    disableRawMode();
    clearScreen();
}
