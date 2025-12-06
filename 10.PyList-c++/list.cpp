#include "list.h"
#include <iostream>
#include <cstdlib>
#include <climits>
#include <string>   // for std::string, std::to_string
#include <stdexcept>

using namespace std;

List::List() {
    capacity = 5;
    size = 0;
    elements = new Element[capacity];
}

List::~List() {
    for (int i = 0; i < size; i++) {
        if (elements[i].type == DT_INT)
            delete (int*)elements[i].data;
        else if (elements[i].type == DT_FLOAT)
            delete (float*)elements[i].data;
        else if (elements[i].type == DT_STRING)
            delete[] (char*)elements[i].data;
        else if (elements[i].type == DT_CHAR)
            delete (char*)elements[i].data;
    }
    delete[] elements;
}

void List::resize() {
    int newCap = capacity * 2;
    Element* newArr = new Element[newCap];

    for (int i = 0; i < size; i++)
        newArr[i] = elements[i];

    delete[] elements;
    elements = newArr;
    capacity = newCap;
}

// ======= Safe checks =======

bool List::isInteger(const char* s) const {
    int i = 0;
    if (s[i] == '+' || s[i] == '-') i++;
    if (s[i] == '\0') return false;

    while (s[i]) {
        if (s[i] < '0' || s[i] > '9') return false;
        i++;
    }
    return true;
}

bool List::isFloat(const char* s) const {
    int i = 0;
    bool dot = false;

    if (s[i] == '+' || s[i] == '-') i++;
    if (s[i] == '\0') return false;

    while (s[i]) {
        if (s[i] == '.') {
            if (dot) return false;
            dot = true;
        } else if (s[i] < '0' || s[i] > '9') {
            return false;
        }
        i++;
    }
    return dot;   // must contain one dot to be float-like
}

// ======= Safe conversions =======

int List::safeToInt(const char* s, bool& ok) const {
    long long val = 0;
    int sign = 1;
    int i = 0;

    ok = true;

    if (s[i] == '-') { sign = -1; i++; }
    else if (s[i] == '+') i++;

    if (s[i] == '\0') { ok = false; return 0; }

    while (s[i]) {
        if (s[i] < '0' || s[i] > '9') { ok = false; return 0; }
        val = val * 10 + (s[i] - '0');

        if (val > INT_MAX) { ok = false; return 0; }
        i++;
    }

    val *= sign;
    if (val < INT_MIN) { ok = false; return 0; }

    return (int)val;
}

float List::safeToFloat(const char* s, bool& ok) const {
    ok = true;
    try {
        return stof(string(s));
    } catch (...) {
        ok = false;
        return 0.0f;
    }
}

// ======= Append helpers =======

void List::appendInt(int v) {
    if (size == capacity) resize();
    int* ptr = new int(v);
    elements[size].data = ptr;
    elements[size].type = DT_INT;
    size++;
}

void List::appendFloat(float v) {
    if (size == capacity) resize();
    float* ptr = new float(v);
    elements[size].data = ptr;
    elements[size].type = DT_FLOAT;
    size++;
}

void List::appendString(const char* s) {
    if (size == capacity) resize();
    int len = strlen(s);
    char* newS = new char[len + 1];
    strcpy(newS, s);
    elements[size].data = newS;
    elements[size].type = DT_STRING;
    size++;
}

void List::appendChar(char c) {
    if (size == capacity) resize();
    char* ptr = new char(c);
    elements[size].data = ptr;
    elements[size].type = DT_CHAR;
    size++;
}

// ======= Public append (Python-like) =======

void List::append(const char* input) {
    bool ok;

    // treat as int if looks like integer and in range
    if (isInteger(input)) {
        int v = safeToInt(input, ok);
        if (ok) {
            appendInt(v);
            return;
        }
    }

    // treat as float if looks like float and conversion works
    if (isFloat(input)) {
        float v = safeToFloat(input, ok);
        if (ok) {
            appendFloat(v);
            return;
        }
    }

    // if none of the above:
    // - weird mix like "123456789ghbak"
    // - very big number out of range
    // - normal text
    // then we stick with string / char
    if (strlen(input) == 1)
        appendChar(input[0]);
    else
        appendString(input);
}

int List::getSize() const {
    return size;
}

ElementWrapper List::operator[](int index) const {
    if (index < 0 || index >= size)
        throw out_of_range("Index out of bounds");
    return ElementWrapper(elements[index].data, elements[index].type);
}

const char* List::getTypeName(int index) const {
    if (index < 0 || index >= size)
        return "invalid";

    switch (elements[index].type) {
        case DT_INT:    return "int";
        case DT_FLOAT:  return "float";
        case DT_STRING: return "string";
        case DT_CHAR:   return "char";
    }
    return "unknown";
}

// return element as text (for printing with index)
std::string List::toString(int index) const {
    if (index < 0 || index >= size)
        throw out_of_range("Index out of bounds");

    Element& e = elements[index];

    switch (e.type) {
        case DT_INT:
            return to_string(*(int*)e.data);
        case DT_FLOAT:
            return to_string(*(float*)e.data);   // may show many decimals, but fine
        case DT_STRING:
            return std::string((char*)e.data);
        case DT_CHAR:
            return std::string(1, *(char*)e.data);
        default:
            return "<?>"; 
    }
}

void List::print() const {
    for (int i = 0; i < size; i++) {
        if (elements[i].type == DT_INT)
            cout << *(int*)elements[i].data;
        else if (elements[i].type == DT_FLOAT)
            cout << *(float*)elements[i].data;
        else if (elements[i].type == DT_STRING)
            cout << (char*)elements[i].data;
        else if (elements[i].type == DT_CHAR)
            cout << *(char*)elements[i].data;

        if (i < size - 1) cout << ",";
    }
}

void List::debugPrint() const {
    for (int i = 0; i < size; i++) {
        cout << i << ": (" << getTypeName(i) << ") ";
        if (elements[i].type == DT_INT)
            cout << *(int*)elements[i].data;
        else if (elements[i].type == DT_FLOAT)
            cout << *(float*)elements[i].data;
        else if (elements[i].type == DT_STRING)
            cout << (char*)elements[i].data;
        else if (elements[i].type == DT_CHAR)
            cout << *(char*)elements[i].data;
        cout << "\n";
    }
}

// ======= ElementWrapper conversions =======

int ElementWrapper::asInt() const {
    return *(int*)data;
}

float ElementWrapper::asFloat() const {
    return *(float*)data;
}

const char* ElementWrapper::asString() const {
    return (char*)data;
}

char ElementWrapper::asChar() const {
    return *(char*)data;
}
