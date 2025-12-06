#ifndef STACK_TEMPLATE_H
#define STACK_TEMPLATE_H

#include <iostream>
#include <stdexcept>

template <typename T>
class StackTemplate {
private:
    T* data;
    int topIndex;
    int capacity;

    
    void resize(int newCap) {
        if (newCap <= capacity) return;

        T* newData = new T[newCap];
        for (int i = 0; i <= topIndex; ++i) {
            newData[i] = data[i];
        }

        delete[] data;
        data = newData;
        capacity = newCap;
    }

    // deep copy helper
    void copyFrom(const StackTemplate<T>& other) {
        capacity = other.capacity;
        topIndex = other.topIndex;
        data = new T[capacity];
        for (int i = 0; i <= topIndex; ++i) {
            data[i] = other.data[i];
        }
    }

public:
    // ctor
    StackTemplate(int cap = 5) {
        if (cap <= 0) cap = 5;
        capacity = cap;
        data = new T[capacity];
        topIndex = -1;
    }

    // copy ctor (deep copy)
    StackTemplate(const StackTemplate<T>& other) {
        copyFrom(other);
    }

    // operator= (deep copy)
    StackTemplate<T>& operator=(const StackTemplate<T>& other) {
        if (this != &other) {
            delete[] data;
            copyFrom(other);
        }
        return *this;
    }

    // dtor
    ~StackTemplate() {
        delete[] data;
    }

    // basic ops
    bool isEmpty() const { return topIndex == -1; }
    bool isFull()  const { return topIndex == capacity - 1; }
    int  size()    const { return topIndex + 1; }
    int  getCapacity() const { return capacity; }

    
    void push(const T& value) {
        if (isFull()) {
            resize(capacity * 2);   
        }
        data[++topIndex] = value;
    }

    // POP
    void pop() {
        if (isEmpty())
            throw std::underflow_error("STACK UNDERFLOW: empty stack.");
        --topIndex;
    }

    // TOP
    T top() const {
        if (isEmpty())
            throw std::underflow_error("STACK UNDERFLOW: no top.");
        return data[topIndex];
    }

    // print <<
    template <typename U>
    friend std::ostream& operator<<(std::ostream& os,
                                    const StackTemplate<U>& s);
};

// operator<< implementation
template <typename U>
std::ostream& operator<<(std::ostream& os, const StackTemplate<U>& s) {
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

#endif
