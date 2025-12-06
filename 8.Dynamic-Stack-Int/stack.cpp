#include "stack.h"
#include <stdexcept>

// ================== PRIVATE ==================

void Stack::resize(int newCapacity) {
    if (newCapacity <= capacity) return;

    int* newData = new int[newCapacity];

    for (int i = 0; i <= topIndex; ++i) {
        newData[i] = data[i];
    }

    delete[] data;
    data = newData;
    capacity = newCapacity;
}

void Stack::copyFrom(const Stack& other) {
    capacity = other.capacity;
    topIndex = other.topIndex;

    data = new int[capacity];

    for (int i = 0; i <= topIndex; ++i) {
        data[i] = other.data[i];
    }
}

// ================== PUBLIC ===================

// Constructor
Stack::Stack(int cap) {
    if (cap <= 0) cap = 10;

    capacity = cap;
    data = new int[capacity];
    topIndex = -1;
}

// Copy Constructor (Deep Copy)
Stack::Stack(const Stack& other) {
    copyFrom(other);
}

// Assignment Operator (Deep Copy)
Stack& Stack::operator=(const Stack& other) {
    if (this != &other) {
        delete[] data;   //delete old data
        copyFrom(other);   //new deep copy 
    }
    return *this;
}

// Destructor
Stack::~Stack() {
    delete[] data;
}

bool Stack::isEmpty() const {
    return topIndex == -1;
}

bool Stack::isFull() const {
    return topIndex == capacity - 1;
}

int Stack::size() const {
    return topIndex + 1;
}

void Stack::push(int value) {
    if (isFull()) {
        //(resize)
        resize(capacity * 2);
    }
    data[++topIndex] = value;
}

void Stack::pop() {
    if (isEmpty()) {
        throw std::underflow_error("Stack is empty");
    }
    --topIndex;
}

int Stack::top() const {
    if (isEmpty()) {
        throw std::underflow_error("Stack is empty");
    }
    return data[topIndex];
}

void Stack::print() const {
    if (isEmpty()) {
        std::cout << "Stack is empty\n";
        return;
    }

    std::cout << "Stack: ";
    for (int i = 0; i <= topIndex; ++i) {
        std::cout << data[i] << " ";
    }
    std::cout << "\n";
}

// operator<< "print"
std::ostream& operator<<(std::ostream& os, const Stack& s) {
    if (s.isEmpty()) {
        os << "Stack is empty";
        return os;
    }

    os << "Stack: ";
    for (int i = 0; i <= s.topIndex; ++i) {
        os << s.data[i] << " ";
    }
    return os;
}
