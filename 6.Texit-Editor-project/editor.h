#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <string>

class TextEditor {
private:
    std::string* lines;
    int lineCount;
    int capacity;
    std::string fileName;

    void ensureCapacity(int newCount);

public:
    TextEditor();
    ~TextEditor();

    bool loadFile(const std::string& name);
    bool saveFile() const;

    void edit();      // main editing loop
};

#endif
