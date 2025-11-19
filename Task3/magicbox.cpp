#include <iostream>
#include <string>
#include "headers.h"
using namespace std;


void magicBox(int n) {
    clearScreen(); 
    int i = 0;      
    int j = n / 2;      
    int num = 1;       
    while (num <= n * n) {

        
        moveCursor(i, j * 4);
        printAt(i, j * 4, to_string(num));

    
        int new_i = (i - 1 + n) % n;       // فوق
        int new_j = (j + 1) % n;           // يمين

        if (num % n == 0) {
            i = (i + 1) % n;
        } 
        else {
            i = new_i;
            j = new_j;
        }

        num++;
        delay(200);
    }
}
int getValidOddNumber() {
    int n;

    while (true) {
        cout << "Enter a positive ODD number: ";

        if (n <= 0) {
            cout << "Number must be POSITIVE.\n";
        }
        else if (n % 2 == 0) {
            cout << " Number must be ODD.\n";
        }
        else {
            
            return n;
        }

    }
}

int main() {
    int n = getValidOddNumber();
    magicBox(n);
    return 0;
}

