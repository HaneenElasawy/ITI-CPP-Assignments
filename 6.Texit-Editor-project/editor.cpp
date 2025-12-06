// editor.cpp
#include "editor.h"
#include <fstream>
using namespace std;

TextBuffer::TextBuffer(int initialCapacity)
    : lines(nullptr),
      lineCount(0),
      capacity(initialCapacity),
      cursorX(0),
      cursorY(0)
{
    if (capacity < 1) capacity = 1;
    lines = new std::string[capacity];
    lineCount = 1;
    lines[0] = "";
}

TextBuffer::~TextBuffer() {
    delete[] lines;
}

void TextBuffer::ensureCapacity() {
    if (lineCount < capacity) return;

    int newCap = capacity * 2;
    if (newCap < 1) newCap = 1;

    std::string* newLines = new std::string[newCap];
    for (int i = 0; i < lineCount; ++i) {
        newLines[i] = lines[i];
    }
    delete[] lines;
    lines = newLines;
    capacity = newCap;
}

void TextBuffer::clear() {
    delete[] lines;
    capacity = 16;
    lines = new std::string[capacity];
    lineCount = 1;
    lines[0].clear();
    cursorX = cursorY = 0;
}

void TextBuffer::insertChar(char c) {
    if (cursorY < 0 || cursorY >= lineCount) return;

    string& line = lines[cursorY];
    if (cursorX < 0) cursorX = 0;
    if (cursorX > (int)line.size()) cursorX = (int)line.size();

    line.insert(line.begin() + cursorX, c);
    cursorX++;
}

void TextBuffer::insertNewLine() {
    if (cursorY < 0 || cursorY >= lineCount) return;

    string& line = lines[cursorY];

    if (cursorX < 0) cursorX = 0;
    if (cursorX > (int)line.size()) cursorX = (int)line.size();

    // split current line at cursor: left part stays, right part goes to new line
    string rest = line.substr(cursorX);
    line.erase(cursorX);

    ensureCapacity();

    // shift lines down
    for (int i = lineCount; i > cursorY + 1; --i) {
        lines[i] = lines[i - 1];
    }
    lines[cursorY + 1] = rest;
    lineCount++;

    cursorY++;
    cursorX = 0;
}

void TextBuffer::deleteChar() {
    if (cursorY < 0 || cursorY >= lineCount) return;

     string& line = lines[cursorY];

    if (cursorX > 0) {
        // delete character before cursor within same line
        line.erase(line.begin() + cursorX - 1);
        cursorX--;
    } else if (cursorY > 0) {
        // at beginning of line: merge with previous line
         string& prev = lines[cursorY - 1];
        int oldLen = (int)prev.size();

        prev += line; // append current to previous

        // shift lines up
        for (int i = cursorY; i < lineCount - 1; ++i) {
            lines[i] = lines[i + 1];
        }
        lineCount--;
        cursorY--;
        cursorX = oldLen;
    }
}

void TextBuffer::moveLeft() {
    if (cursorY < 0 || cursorY >= lineCount) return;

    if (cursorX > 0) {
        cursorX--;
    } else if (cursorY > 0) {
        cursorY--;
        cursorX = (int)lines[cursorY].size();
    }
}

void TextBuffer::moveRight() {
    if (cursorY < 0 || cursorY >= lineCount) return;

    int len = (int)lines[cursorY].size();
    if (cursorX < len) {
        cursorX++;
    } else if (cursorY + 1 < lineCount) {
        cursorY++;
        cursorX = 0;
    }
}

void TextBuffer::moveUp() {
    if (cursorY > 0) {
        cursorY--;
        int len = (int)lines[cursorY].size();
        if (cursorX > len) cursorX = len;
    }
}

void TextBuffer::moveDown() {
    if (cursorY + 1 < lineCount) {
        cursorY++;
        int len = (int)lines[cursorY].size();
        if (cursorX > len) cursorX = len;
    }
}

bool TextBuffer::saveToFile(const std::string& fileName) const {
     ofstream out(fileName);
    if (!out) {
        return false;
    }
    for (int i = 0; i < lineCount; ++i) {
        out << lines[i];
        if (i + 1 < lineCount) out << '\n';
    }
    return true;
}

bool TextBuffer::loadFromFile(const string& fileName) {
    std::ifstream in(fileName);
    if (!in) {
        return false; 
    }
 
    delete[] lines;
    capacity = 16;
    lines = new string[capacity];
    lineCount = 0;
    cursorX = cursorY = 0;

    string temp;
    while (getline(in, temp)) {
        if (lineCount >= capacity) {
            ensureCapacity();
        }
        lines[lineCount++] = temp;
    }

    // Empity File
    if (lineCount == 0) {
        lineCount = 1;
        lines[0] = "";
    }

    cursorX = 0;
    cursorY = 0;
    return true;
}
