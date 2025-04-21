#include <iostream>
#include "MyCalc.h"
#include "getNumber.h"

using namespace std;



int main() {

    double num1, num2;

    // Запрос у пользователя двух вещественных чисел
    cout << "Enter the first number: ";
    while (!getNumber(num1)) {
        cout << "Error: The entered number is not a number. Please enter a number: ";
    }
    cout << "Enter the second number: ";
    while (!getNumber(num2)) {
        cout << "Error: The entered number is not a number. Please enter a number: ";
    }

    // Выполнение и вывод результатов математических операций
    cout << "Addition: " << add(num1, num2) << endl;
    cout << "Subtraction: " << subtract(num1, num2) << endl;
    cout << "Multiplication: " << multiply(num1, num2) << endl;
    cout << "Division: " << divide(num1, num2) << endl;

    return 0;
}
