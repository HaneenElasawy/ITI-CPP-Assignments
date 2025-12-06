// editor.h
#ifndef EDITOR_H
#define EDITOR_H

#include <string>

class TextBuffer {
private:
    std::string* lines;  // dynamic array of lines
    int lineCount;       // how many lines are used
    int capacity;        // how many lines are allocated

    int cursorX;         // column (0-based)
    int cursorY;         // row    (0-based)

    void ensureCapacity(); // grow lines array when needed

public:
    TextBuffer(int initialCapacity = 16);
    ~TextBuffer();

    // forbid copy
    TextBuffer(const TextBuffer&) = delete;
    TextBuffer& operator=(const TextBuffer&) = delete;

    // editing operations
    void insertChar(char c);  // insert character at cursor
    void insertNewLine();     // split line at cursor (Enter)
    void deleteChar();        // backspace-style delete

    // cursor movement
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();

    // accessors
    int  getLineCount() const { return lineCount; }
    const std::string& getLine(int i) const { return lines[i]; }

    int  getCursorX() const { return cursorX; }
    int  getCursorY() const { return cursorY; }

    void clear(); // reset document to one empty line

    // file operations
    bool saveToFile(const std::string& fileName) const;
    bool loadFromFile(const std::string& fileName);
};

#endif 
