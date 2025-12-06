#include <iostream>
#include <string>
#include "StackTemplate.h"
using namespace std;

int main() {
    int cap;
    cout << "Enter initial stack capacity: ";
    cin >> cap;

    StackTemplate<string> s(cap);        // ORIGINAL
    StackTemplate<string> copied(cap);   // COPY

    int choice;
    while (true) {
        cout << "\n===== TEMPLATE STACK MENU =====\n";
        cout << "1) Push\n";
        cout << "2) Pop\n";
        cout << "3) Top\n";
        cout << "4) Print Stack\n";
        cout << "5) Get Size\n";
        cout << "6) Check isEmpty\n";
        cout << "7) Check isFull\n";
        cout << "8) Make Deep Copy of Stack\n";
        cout << "9) Modify ORIGINAL Stack (push/pop)\n";
        cout << "10) Print COPIED Stack\n";
        cout << "0) Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 0) {
            cout << "Exiting...\n";
            break;
        }

        try {
            switch (choice) {
            case 1: {   // PUSH
                string v;
                cout << "Enter value to push: ";
                cin >> v;

                if (s.isFull()) {
                    cout << "Stack was FULL → will resize now.\n";
                }
                s.push(v);
                cout << "Pushed.\n";
                break;
            }

            case 2: {   // POP
                s.pop();
                cout << "Popped.\n";
                break;
            }

            case 3:     // TOP
                cout << "Top = " << s.top() << "\n";
                break;

            case 4:     // PRINT
                cout << s << "\n";
                break;

            case 5:     // SIZE
                cout << "Size = " << s.size()
                     << " / Capacity = " << s.getCapacity() << "\n";
                break;

            case 6:     // isEmpty
                cout << (s.isEmpty() ? "EMPTY\n" : "NOT EMPTY\n");
                break;

            case 7:     
                cout << (s.isFull() ? "FULL (will resize on next push)\n"
                                   : "NOT FULL\n");
                break;

            case 8:     // DEEP COPY
                copied = s;    // operator= (deep copy)
                cout << "Deep copy DONE (copied = original).\n";
                break;

            case 9: {   // MODIFY ORIGINAL (push or pop)
                int sub;
                cout << "\n=== Modify ORIGINAL Stack ===\n";
                cout << "1) Push new value\n";
                cout << "2) Pop last value\n";
                cout << "Enter choice: ";
                cin >> sub;

                if (sub == 1) {
                    string x;
                    cout << "Enter value to push in ORIGINAL: ";
                    cin >> x;
                    if (s.isFull())
                        cout << "Stack was FULL → will resize now.\n";
                    s.push(x);
                    cout << "Original modified (push).\n";
                } else if (sub == 2) {
                    s.pop();
                    cout << "Original modified (pop).\n";
                } else {
                    cout << "Invalid modify option.\n";
                }
                break;
            }

            case 10:    // PRINT COPY
                cout << "COPIED STACK → " << copied << "\n";
                break;

            default:
                cout << "Invalid choice.\n";
            }
        }
        catch (const exception& ex) {
            cout << "ERROR: " << ex.what() << "\n";
        }
    }

    return 0;
}
