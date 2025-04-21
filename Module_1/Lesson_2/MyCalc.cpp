#include "MyCalc.h"


// Функция для сложения двух чисел
double add(double a, double b) {
    return a + b;
}

// Функция для вычитания двух чисел
double subtract(double a, double b) {
    return a - b;
}

// Функция для умножения двух чисел
double multiply(double a, double b) {
    return a * b;
}

// Функция для деления двух чисел
double divide(double a, double b) {
    if (b != 0) {
        return a / b;
    } else {
        std::cout << "Error: division by zero!" << std::endl;
        return 0;
    }
}
