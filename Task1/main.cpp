#include <iostream>
#include <chrono>
#include "headers.h"

int main() {
    printAt(5, 10, "Who's Big Boss", 31); // Red
    delay(2000);
    clearScreen();

    printAt(10, 20, "Eng.Mina Is Big Boss", 32); // Green

    clearScreen();
     delay(2000);
    std::cout << "\nFinished! Press Enter to exit...";
std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
std::cin.get();

    return 0;
}
