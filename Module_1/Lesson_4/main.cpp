#include <iostream>
#include <fstream>  // Для работы с файлами
#include <vector>   // Для использования std::vector
#include <string>   // Для работы со строками



// Структура для хранения информации о радиоэлементе
struct RadioElement {
    std::string name;          // Название элемента
    std::string type;          // Тип элемента (резистор, конденсатор и т.д.)
    double value;              // Номинальное значение (например, сопротивление или ёмкость)
    std::string unit;          // Единица измерения (Ом, Ф, Гн и т.д.)
    int quantity;              // Количество элементов в наличии
    std::string manufacturer;  // Производитель
    std::string description;   // Описание элемента
};

// Прототип Функци для записи данных в файл
void writeToFile(const std::string& filename, const std::vector<RadioElement>& elements);

// Прототип Функци для чтения данных из файла
std::vector<RadioElement> readFromFile(const std::string& filename);

int main()
{
    // Создаем вектор структур и заполняем его данными
    std::vector<RadioElement> elements = {
        {"Resistor R1", "Resistor", 100.0, "Ohm", 50, "Texas Instruments", "Resistor 100 Ohm, 1%"},
        {"Capacitor C1", "Capacitor", 0.01, "F", 30, "Murata", "Ceramic capacitor 10 uF"},
        {"Coil L1", "Inductance", 0.001, "H", 20, "Coilcraft", "Inductance 1 mH"}
    };

    // Имя файла
    std::string filename = "radio_elements.txt";

    // Записываем данные в файл
    writeToFile(filename, elements);

    // Читаем данные из файла в новый вектор структур
    std::vector<RadioElement> loadedElements = readFromFile(filename);

    // Выводим прочитанные данные
    std::cout << "\nRead data:\n";
    for (const auto& element : loadedElements) {
        std::cout << "Name: " << element.name << "\n";
        std::cout << "Type: " << element.type << "\n";
        std::cout << "Value: " << element.value << " " << element.unit << "\n";
        std::cout << "Quantity: " << element.quantity << "\n";
        std::cout << "Manufacturer: " << element.manufacturer << "\n";
        std::cout << "Descriptio: " << element.description << "\n";
        std::cout << "------------------\n";
    }

    return 0;
}

// Функция для записи данных в файл
    void writeToFile(const std::string& filename, const std::vector<RadioElement>& elements) {
    std::ofstream file(filename);  // Открываем файл для записи
    if (file.is_open()) {
        for (const auto& element : elements) {
            file << element.name << "\n";          // Записываем название
            file << element.type << "\n";          // Записываем тип
            file << element.value << "\n";         // Записываем номинальное значение
            file << element.unit << "\n";          // Записываем единицу измерения
            file << element.quantity << "\n";      // Записываем количество
            file << element.manufacturer << "\n";  // Записываем производителя
            file << element.description << "\n";   // Записываем описание
        }
        file.close();  // Закрываем файл
        std::cout << "The data was successfully written to the file.\n";
    } else {
        std::cerr << "Error opening file for writing.\n";
    }
}

    // Функция для чтения данных из файла
    std::vector<RadioElement> readFromFile(const std::string& filename) {
        std::vector<RadioElement> elements;
        std::ifstream file(filename);  // Открываем файл для чтения
        if (file.is_open()) {
            RadioElement element;
            while (std::getline(file, element.name)) {  // Читаем название
                std::getline(file, element.type);       // Читаем тип
                file >> element.value;                 // Читаем номинальное значение
                file.ignore();                         // Игнорируем символ новой строки
                std::getline(file, element.unit);      // Читаем единицу измерения
                file >> element.quantity;              // Читаем количество
                file.ignore();                         // Игнорируем символ новой строки
                std::getline(file, element.manufacturer);  // Читаем производителя
                std::getline(file, element.description);   // Читаем описание
                elements.push_back(element);               // Добавляем элемент в вектор
            }
            file.close();  // Закрываем файл
            std::cout << "Data was successfully read from the file.\n";
        } else {
            std::cerr << "Error opening file for reading.\n";
        }
        return elements;
    }
