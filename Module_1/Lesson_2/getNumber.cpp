#include "getNumber.h"


// Функция для проверки ввода числа
bool getNumber(double &number) {
    std::cin >> number;
    if (std::cin.fail()) {  // Если ввод не удался (например, введена буква)
        std::cin.clear();  // Сбрасываем флаг ошибки
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Очищаем буфер ввода
        return false;  // Возвращаем false, если ввод некорректен
    }
    return true;  // Возвращаем true, если ввод корректен
}
