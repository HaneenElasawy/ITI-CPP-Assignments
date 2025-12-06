#include <iostream>
#include <string>
#include "TextEditor.h"

using namespace std;

int main() {
    TextEditor editor;

    cout << "Enter file name: ";
    string name;
    getline(cin, name);

    bool existed = editor.loadFile(name);
    if (existed)
        cout << "File loaded.\n";
    else
        cout << "File not found. A new file will be created.\n";

    cout << "Press Enter to start editing...";
    cin.ignore(10000, '\n');

    editor.edit();

    cout << "Done.\n";
    return 0;
}
