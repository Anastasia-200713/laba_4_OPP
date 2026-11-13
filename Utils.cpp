#include "Utils.h"
#include <iostream>
#include <limits>

using namespace std;

int inputInt() {
    int val;
    while (true) {
        cin >> val;
        if (cin.fail()) {
            cin.clear(); 
            cin.ignore((numeric_limits<streamsize>::max)(), '\n'); 
            cout << "Ошибка! Введите целое число: ";
        }
        else {
          
            cin.ignore((numeric_limits<streamsize>::max)(), '\n');
            return val;
        }
    }
}

double inputDouble() {
    double val;
    while (true) {
        cin >> val;
        if (cin.fail()) {
            cin.clear();
            cin.ignore((numeric_limits<streamsize>::max)(), '\n'); 
            cout << "Ошибка! Введите число: ";
        }
        else {
   
            cin.ignore((numeric_limits<streamsize>::max)(), '\n');
            return val;
        }
    }
}

string inputLine() {
    string s;
    getline(cin, s);
    while (s.empty()) {
        cout << "Ошибка! Строка не может быть пустой. Введите заново: ";
        getline(cin, s);
    }
    return s;
}