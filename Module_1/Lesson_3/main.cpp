#include <iostream>
#include <algorithm>  // для функции shuffle
#include <random>     // для генерации случайных чисел
#include <array>      // для использования std::array
#include <chrono>

#define SIZE 17 // Размер массива

int findMissingNumber(const std::array<int,SIZE>& arr);

int main()
{    
    std::array<int,SIZE> array; // Создаем массив размера SIZE

    // Заполняем массив числами от 1 до SIZE
    for(int i = 0; i < SIZE; i++)
    {
        array[i] = i + 1;
    }

    // Генератор случайных чисел
    std::mt19937 g(std::chrono::system_clock::now().time_since_epoch().count());


    // Перемешиваем массив
    std::shuffle(array.begin(), array.end(), g);

    // Выводим первые 16 элементов массива (без повторений)
    std::cout << "Array of 16 unique numbers (from 1 to 17):\n";
    for (int i = 0; i < 16; ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << "\n";

    // Находим пропущенное число
    int missingNumber = findMissingNumber(array);
    std::cout << "Missing number: " << missingNumber << "\n";

    return 0;
}

// Функция для поиска пропущенного числа
int findMissingNumber(const std::array<int,SIZE>& arr) {
    // Сумма чисел от 1 до 17
    int totalSum = (SIZE * (SIZE + 1)) / 2;  // Формула суммы арифметической прогрессии

    // Сумма элементов массива
    int arraySum = 0;
    for (int i = 0; i < SIZE - 1; i++) {
        arraySum += arr[i];
    }

    // Пропущенное число
    return totalSum - arraySum;
}
