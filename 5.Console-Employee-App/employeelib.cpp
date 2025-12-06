#include <iostream>
#include <limits>
#include <cctype> // isdigit
#include "employee.h"
using namespace std;

#if defined(_WIN32)
    #include <conio.h>
#else
    #include <termios.h>
    #include <unistd.h>
#endif
// ====== Basic terminal helpers (Task 1) ======
// Move cursor to (row, col)
void moveCursor(int row, int col) {
    std::cout << "\033[" << row << ";" << col << "H";
}
// Set color using ANSI code (31 = red, 32 = green, ...)
void setColor(int colorCode) {
    std::cout << "\033[" << colorCode << "m";
}
// Reset color/formatting
void resetColor() {
    std::cout << "\033[0m";
}
// Clear screen and move cursor to home
void clearScreen() {
    std::cout << "\033[2J\033[H";
}
// High level print: go to position, set color, print, reset
void printAt(int row, int col, const std::string& text, int colorCode) {
    moveCursor(row, col);
    setColor(colorCode);
    std::cout << text << std::flush;
    resetColor();
}
// ====== Cross-platform getch (Task 2) ======
char getch_cross() {

#if defined(_WIN32)
    //    _getch  from conio.h
    return _getch();
#else

    char c = 0;

    termios oldAttr{};
    if (tcgetattr(STDIN_FILENO, &oldAttr) < 0) {
        return 0;
    }
    termios newAttr = oldAttr;
    newAttr.c_lflag &= ~(ICANON | ECHO); // no line buffering, no echo
    newAttr.c_cc[VMIN]  = 1;             // read one char at least
    newAttr.c_cc[VTIME] = 0;   // without timeout

    if (tcsetattr(STDIN_FILENO, TCSANOW, &newAttr) < 0) {
        return 0;
    }

    if (read(STDIN_FILENO, &c, 1) < 0) {
        c = 0;
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldAttr);

    return c;
}
#endif

//========= Task5 (Employee App) ============ 

Employee employees[MAX_EMPLOYEES];

int employeeCount = 0;

 //======== Iput Validation Helpers =====

int readPositiveInt(const string& label, int row) {
    while (true) {
        moveCursor(row, 5);
        cout << label << ": ";
        cout.flush();

        string s;
        getline(cin, s);

          
        if (s.empty()) {
            moveCursor(row + 1, 5);
            cout << "Empty! Try again? (y/n): ";
            cout.flush();

            string ans;
            getline(cin, ans);
            
            if (ans != "y" && ans != "Y")
                return -1;   

               
            moveCursor(row + 1, 5);
            cout << string(60, ' ');
            cout.flush();
            continue;
        }

        bool allDigits = true;
        for (char c : s) {
            if (!isdigit(static_cast<unsigned char>(c))) {
                allDigits = false;
                break;
            }
        }

        if (!allDigits) {
            moveCursor(row + 1, 5);
            cout << "Invalid " << label << "! Digits only. Try again? (y/n): ";
            cout.flush();

            string ans;
            getline(cin, ans);
            if (ans != "y" && ans != "Y")
                return -1;  

            moveCursor(row + 1, 5);
            cout << string(60, ' ');
            cout.flush();
            continue;
        }

        int v = stoi(s);

        if (v <= 0) {
            moveCursor(row + 1, 5);
            cout << "Invalid " << label << "! Must be positive. Try again? (y/n): ";
            cout.flush();

            string ans;
            getline(cin, ans);
            if (ans != "y" && ans != "Y")
                return -1;

            moveCursor(row + 1, 5);
            cout << string(60, ' ');
            cout.flush();
            continue;
        }

        
        moveCursor(row + 1, 5);
        cout << string(60, ' ');
        cout.flush();
        return v;
    }
}

string readNonEmptyString(const string& label, int row) {
    while (true) {
        moveCursor(row, 5);
        cout << label << ": ";
        cout.flush();

        string s;
        getline(cin, s);

        if (s.empty()) {
            moveCursor(row + 1, 5);
            cout << "Empty! Try again? (y/n): ";
            cout.flush();

            string ans;
            getline(cin, ans);
            if (ans != "y" && ans != "Y")
                return "";  // cancel

            moveCursor(row + 1, 5);
            cout << string(60, ' ');
            cout.flush();
            continue;
        }

        bool allDigits = true;
        for (char c : s) {
            if (!isdigit(static_cast<unsigned char>(c))) {
                allDigits = false;
                break;
            }
        }

        if (allDigits) {
            moveCursor(row + 1, 5);
            cout << "Invalid " << label << "! Name cannot be a pure number. Try again? (y/n): ";
            cout.flush();

            string ans;
            getline(cin, ans);
            if (ans != "y" && ans != "Y")
                return "";   // cancel

            moveCursor(row + 1, 5);
            cout << string(60, ' ');
            cout.flush();
            continue;
        }

        // اسم مقبول
        moveCursor(row + 1, 5);
        cout << string(60, ' ');
        cout.flush();
        return s;
    }
}

void addEmployee() {

    clearScreen();
    printAt(3, 5, "=== Add New Employee ===", 33);

    if (employeeCount >= MAX_EMPLOYEES) {
        printAt(5, 5, "Employee list is full! Cannot add more.", 31);
        printAt(7, 5, "press any key to return ...", 36);
        char c = getch_cross();
        return;
    }

    // before use  getline
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    Employee& e = employees[employeeCount];

    // ===== ID =====
    int id = readPositiveInt("Enter ID", 5);
    if (id == -1) // user chose not to continue
    {
        // moveCursor(11, 5);
        // cout << "Operation cancelled.";
        // moveCursor(13, 5);
        // cout << "press any key to return ...";
        // char c = getch_cross();
        return;
    }   
    e.id = id;
    
    // ===== First Name =====
    string first = readNonEmptyString("Enter First Name", 6);
    if (first.empty()) {
        moveCursor(11, 5);
        cout << "Operation cancelled.";
        moveCursor(13, 5);
        cout << "press any key to return ...";
        char c = getch_cross();
        return;
    }
    e.first_name = first;

    // ===== Second Name =====
    string second = readNonEmptyString("Enter Second Name", 7);
    if (second.empty()) {
        moveCursor(11, 5);
        cout << "Operation cancelled.";
        moveCursor(13, 5);
        cout << "press any key to return ...";
        char c = getch_cross();
        return;
    }
    e.second_name = second;

    // ===== Age =====
    int age = readPositiveInt("Enter Age", 8);
    if (age == -1) {
        moveCursor(11, 5);
        cout << "Operation cancelled.";
        moveCursor(13, 5);
        cout << "press any key to return ...";
        char c = getch_cross();
        return;
    }
    e.age = age;

    // ===== Salary =====
    double salary = readPositiveInt("Enter Salary", 9);
    if (salary < 0) {   
        moveCursor(11, 5);
        cout << "Operation cancelled.";
        moveCursor(13, 5);
        cout << "press any key to return ...";
        char c = getch_cross();
        return;
    }
    e.salary = salary;

    employeeCount++;

    moveCursor(11, 5);
    cout << "Employee Saved Successfully.";
    moveCursor(13, 5);
    cout << "press any key to return ...";
    char c = getch_cross();
}


void displayEmployees() {
    clearScreen();
    printAt(3, 5, "=== Employees List ===", 33);

    if (employeeCount == 0) {
        printAt(5, 5, "No Employee Data To Display.", 31);
        printAt(7,5, "press any key to rerurn ..." , 36);
        char c = getch_cross();
        return;
    }

    int row = 6;

    for (int i = 0; i < employeeCount; ++i) {
        const Employee& e = employees[i];

        moveCursor(row, 5);
        cout << "Employee #" << (i + 1);

        moveCursor(row + 1, 5);
        cout << " ID    : " << e.id;

        moveCursor(row + 2, 5);
        cout << " Name  : " << e.first_name << " " << e.second_name;

        moveCursor(row + 3, 5);
        cout << " Age   : " << e.age;

        moveCursor(row + 4, 5);
        cout << " Salary: " << e.salary;

        row += 6; 
    }
    moveCursor(row,5);
        cout <<"press any key to rerurn ..." ;
        char c = getch_cross();
}

