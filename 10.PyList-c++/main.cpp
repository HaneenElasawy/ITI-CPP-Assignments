#include "list.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
    List lst;

    cout << "Python-like List in C++\n";
    cout << "Enter items (one per line). Type 'done' to finish.\n\n";

    // Input phase
    string input;
    cout << "Item: ";
    getline(cin, input);

    while (cin && input != "done") {
        if (input.empty()) {
            cout << "Error: empty value. Please enter a non-empty item.\n";
        } else {
            lst.append(input.c_str());
        }

        cout << "Item: ";
        getline(cin, input);
    }

    int n = lst.getSize();
    cout << "\nList size = " << n << "\n";

    if (n == 0) {
        cout << "List is empty. No elements to inspect.\n";
        return 0;
    }

    // Show items with indices (without types)
    cout << "Items with indices:\n";
    for (int i = 0; i < n; ++i) {
        cout << "item[" << i << "] = " << lst.toString(i) << "\n";
    }

    // Ask user which index they want to know its type
    cout << "\nEnter an index between 0 and " << (n - 1)
         << " to see its data type: ";

    string indexInput;
    getline(cin, indexInput);

    if (indexInput.empty()) {
        cout << "Error: empty index.\n";
        return 0;
    }

    // Simple numeric check
    bool indexOk = true;
    for (size_t i = 0; i < indexInput.size(); ++i) {
        char c = indexInput[i];
        if (c < '0' || c > '9') {
            indexOk = false;
        }
    }

    if (!indexOk) {
        cout << "Error: invalid index format.\n";
        return 0;
    }

    int index = 0;
    for (size_t i = 0; i < indexInput.size(); ++i) {
        index = index * 10 + (indexInput[i] - '0');
    }

    if (index < 0 || index >= n) {
        cout << "Error: index out of range.\n";
        return 0;
    }

    const char* typeName = lst.getTypeName(index);

    cout << "\nElement at index " << index << ":\n";
    cout << "value = " << lst.toString(index) << "\n";
    cout << "type  = " << typeName << "\n";

    return 0;
}
