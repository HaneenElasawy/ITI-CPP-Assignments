#include <iostream>
#include "headers.h"
using namespace std;

int main() {
    const int SIZE = 100;

    // ============================
    // 1) TEST str_len
    // ============================
    char str1[SIZE] = "Haneen";
    char str2[SIZE] = "Elasawy";

    cout << "=== TEST str_len ===\n";
    cout << "str1 = " << str1 << endl;
    cout << "length = " << str_len(str1) << "\n\n";


    // ============================
    // 2) TEST str_cmp
    // ============================
    // نستخدم نفس str1 و str2
    cout << "=== TEST str_cmp ===\n";
    int result = str_cmp(str1, str2);
     cout<< " Compare result = "<< result << endl;
  
    // ============================
    // 3) TEST tolower_str
    // ============================
    char str3[SIZE] = "HaNeEn";

    cout << "=== TEST tolower_str ===\n";
    cout << "before = " << str3 << endl;
    tolower_str(str3);
    cout << "after  = " << str3 << "\n\n";

    // ============================
    // 4) TEST toupper_str
    // ============================
    char str4[SIZE] = "haneen";

    cout << "=== TEST toupper_str ===\n";
    cout << "before = " << str4 << endl;
    toupper_str(str4);
    cout << "after  = " << str4 << "\n\n";

    // ============================
    // 5) TEST concat
    // ============================
    char first[SIZE] = "Haneen";
    char second[SIZE] = " Elasawy";

    cout << "=== TEST concat ===\n";
    if (str_concat(first, second, SIZE))
        cout << "After concat = " << first << "\n\n";
    else
        cout << "Concat failed\n\n";


    // ============================
    // 6) TEST copy
    // ============================
    char source[SIZE] = "We All Loves Lunix";
    char dest[SIZE];

    cout << "=== TEST copy ===\n";
    str_copy(dest, source);
    cout << "source = " << source << endl;
    cout << "dest   = " << dest << endl;

    return 0;
}
