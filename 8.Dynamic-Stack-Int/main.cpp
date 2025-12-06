#include <iostream>
#include "stack.h"
using namespace std;

int main() {
    Stack s(3);     //old size
    Stack copied;   //deep copy 

    int choice;
    while (true) {
        cout << "\n=============================\n";
        cout << "        STACK MENU\n";
        cout << "=============================\n";
        cout << "1) Push\n";
        cout << "2) Pop\n";
        cout << "3) Top\n";
        cout << "4) Print Stack\n";
        cout << "5) Get Size\n";
        cout << "6) Check isEmpty\n";
        cout << "7) Check isFull\n";
        cout << "8) Make a copy of the stack (Deep Copy)\n";
        cout << "9) Modify ORIGINAL stack (push)\n";
        cout << "10) Print COPIED stack\n";
        cout << "0) Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (!cin) {
            cout << "Invalid input.\n";
            return 0;
        }

        if (choice == 0) {
            cout << "Exiting...\n";
            break;
        }

        switch (choice) {

        case 1: { // PUSH
            int value;
            cout << "Enter value to push: ";
            cin >> value;

            if (s.isFull()) {
                cout << "Stack is full — resizing now...\n";
            }

            s.push(value);
            cout << "Pushed " << value << " successfully.\n";
            break;
        }

        case 2: { // POP
            if (s.isEmpty()) {
                cout << "Stack is empty — cannot pop.\n";
            } else {
                s.pop();
                cout << "Popped top element.\n";
            }
            break;
        }

        case 3: { // TOP
            if (s.isEmpty()) {
                cout << "Stack is empty — no top element.\n";
            } else {
                cout << "Top element = " << s.top() << "\n";
            }
            break;
        }

        case 4: { // PRINT ORIGINAL
            cout << "ORIGINAL STACK: " << s << "\n";
            break;
        }

        case 5: { // SIZE
            cout << "Size = " << s.size() << "\n";
            break;
        }

        case 6: { // isEmpty
            cout << (s.isEmpty() ? "Stack is EMPTY\n" : "Stack is NOT empty\n");
            break;
        }

        case 7: { // isFull
            cout << (s.isFull() ? "Stack is FULL\n" : "Stack is NOT full\n");
            break;
        }

        case 8: { // COPY
            copied = s;  //  operator= (Deep Copy)
            cout << "Copied stack created successfully.\n";
            break;
        }

        case 9: { // MODIFY ORIGINAL →  
            int val;
            cout << "Enter value to push into ORIGINAL stack: ";
            cin >> val;
            s.push(val);
            cout << "Original stack modified.\n";
            break;
        }

        case 10: { // SHOW copied
            cout << "COPIED STACK: " << copied << "\n";
            break;
        }

        default:
            cout << "Invalid choice.\n";
        }
    }

    return 0;
}
