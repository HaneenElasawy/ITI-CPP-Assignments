#ifndef STACK_H
#define STACK_H

#include <iostream>

class Stack {
private:
    int* data;         
    int  topIndex;     
    int  capacity;     

    void resize(int newCapacity);     
    void copyFrom(const Stack& other); // deep copy helper

public:
    // Constructor
    Stack(int cap = 10);

    // Copy Constructor  (Deep Copy)
    Stack(const Stack& other);

    // Assignment Operator  (Deep Copy)
    Stack& operator=(const Stack& other);

    // Destructor
    ~Stack();

    // Operations
    bool isEmpty() const;
    bool isFull()  const;
    int  size()    const;

    void push(int value);
    void pop();
    int  top() const;

    void print() const;

    // Operator overloading
    friend std::ostream& operator<<(std::ostream& os, const Stack& s);
};

#endif
