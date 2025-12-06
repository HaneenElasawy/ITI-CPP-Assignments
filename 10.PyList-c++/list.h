#ifndef LIST_H
#define LIST_H

#include <cstring>
#include <string>

enum DataType {
    DT_INT,
    DT_FLOAT,
    DT_STRING,
    DT_CHAR
};

struct Element {
    void* data;
    DataType type;
};

class ElementWrapper {
private:
    void* data;
    DataType type;

public:
    ElementWrapper(void* d = nullptr, DataType t = DT_STRING)
        : data(d), type(t) {}

    DataType getType() const { return type; }

    int         asInt() const;
    float       asFloat() const;
    const char* asString() const;
    char        asChar() const;
};

class List {
private:
    Element* elements;
    int size;
    int capacity;

    void resize();

    bool  isInteger(const char* s) const;
    bool  isFloat(const char* s) const;

    int   safeToInt(const char* s, bool& ok) const;
    float safeToFloat(const char* s, bool& ok) const;

    void appendInt(int v);
    void appendFloat(float v);
    void appendString(const char* s);
    void appendChar(char c);

public:
    List();
    ~List();

    void append(const char* input);   // smart append

    int getSize() const;

    ElementWrapper operator[](int index) const;

    const char*   getTypeName(int index) const;
    std::string   toString(int index) const;   // text version of one element

    void print() const;
    void debugPrint() const;
};

#endif
