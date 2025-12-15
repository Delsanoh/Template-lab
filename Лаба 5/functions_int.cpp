#define _CRT_SECURE_NO_WARNINGS
#include "binary_counter.h"
#include <stdexcept>
#include <limits>

void manualInputInt()
{
    int32_t n;
    std::cout << "Количество элементов: ";
    if (!(std::cin >> n)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw std::invalid_argument("Ошибка: введено не число для количества элементов!");
    }

    if (n <= 0)
    {
        throw std::invalid_argument("Ошибка: количество элементов должно быть положительным!");
    }

    std::vector<int32_t> arr(n);
    std::cout << "Введите " << n << " чисел: ";
    for (int32_t i = 0; i < n; i++)
    {
        if (!(std::cin >> arr[i])) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            throw std::invalid_argument("Ошибка: введено не число в позиции " + std::to_string(i + 1) + "!");
        }
    }

    auto res = findMinOnesElements(arr);
    std::cout << "Результат: ";
    for (int32_t val : res)
    {
        std::cout << val << " ";
    }
    std::cout << "\n";

    writeToFile(arr, res, "Ручной ввод (int32_t)");
}

void randomGenerationInt()
{
    int32_t n;
    int32_t minVal;
    int32_t maxVal;

    std::cout << "Количество: ";
    if (!(std::cin >> n)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw std::invalid_argument("Ошибка: введено не число для количества!");
    }

    std::cout << "Минимум: ";
    if (!(std::cin >> minVal)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw std::invalid_argument("Ошибка: введено не число для минимума!");
    }

    std::cout << "Максимум: ";
    if (!(std::cin >> maxVal)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw std::invalid_argument("Ошибка: введено не число для максимума!");
    }

    if (n <= 0)
    {
        throw std::invalid_argument("Ошибка: количество должно быть положительным!");
    }

    if (minVal > maxVal)
    {
        throw std::invalid_argument("Ошибка: минимум не может быть больше максимума!");
    }

    srand(time(0));
    std::vector<int32_t> arr(n);
    std::cout << "Массив: ";

    for (size_t i = 0; i < n; i++)
    {
        // Безопасное вычисление диапазона
        int32_t range = maxVal - minVal + 1;
        if (range <= 0) {
            throw std::runtime_error("Ошибка: некорректный диапазон значений!");
        }

        arr[i] = minVal + rand() % range;
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";

    auto res = findMinOnesElements(arr);
    std::cout << "Результат: ";
    for (int32_t val : res)
    {
        std::cout << val << " ";
    }
    std::cout << "\n";

    writeToFile(arr, res, "Случайная генерация (int32_t)");
}

void readFromFileInt()
{
    char filename[256];
    std::cout << "Имя файла: ";
    if (!(std::cin >> filename)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw std::runtime_error("Ошибка чтения имени файла!");
    }

    std::ifstream fin(filename);
    if (!fin.is_open())
    {
        throw std::runtime_error("Ошибка: не удалось открыть файл '" + std::string(filename) + "'!");
    }

    if (!CheckInputFile(fin))
    {
        fin.close();
        throw std::runtime_error("Ошибка: файл пустой или содержит неверные данные!");
    }

    std::vector<int32_t> arr;
    int32_t value;

    // Возвращаем указатель на начало файла для чтения
    fin.clear();
    fin.seekg(0);

    while (fin >> value)
    {
        arr.push_back(value);
    }

    fin.close();

    if (arr.empty())
    {
        throw std::runtime_error("Файл не содержит числовых данных!");
    }

    std::cout << "Прочитано " << arr.size() << " чисел: ";
    for (int32_t val : arr)
    {
        std::cout << val << " ";
    }
    std::cout << "\n";

    auto res = findMinOnesElements(arr);
    std::cout << "Результат: ";
    for (int32_t val : res)
    {
        std::cout << val << " ";
    }
    std::cout << "\n";

    writeToFile(arr, res, "Чтение из файла (int32_t)");
}

void menuInt()
{
    int32_t choice;
    while (true)
    {
        std::cout << "\n=== INT МЕНЮ ===\n";
        std::cout << "1. Ручной ввод\n";
        std::cout << "2. Случайная генерация\n";
        std::cout << "3. Чтение из файла\n";
        std::cout << "4. Назад\n";
        std::cout << "Выбор: ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка: введено не число!\n";
            continue;
        }

        switch (choice)
        {
        case 1:
            try {
                manualInputInt();
            }
            catch (const std::exception& e) {
                std::cout << "Ошибка в ручном вводе: " << e.what() << "\n";
            }
            catch (...) {
                std::cout << "Неизвестная ошибка в ручном вводе!\n";
            }
            break;

        case 2:
            try {
                randomGenerationInt();
            }
            catch (const std::exception& e) {
                std::cout << "Ошибка в генерации: " << e.what() << "\n";
            }
            catch (...) {
                std::cout << "Неизвестная ошибка в генерации!\n";
            }
            break;

        case 3:
            try {
                readFromFileInt();
            }
            catch (const std::exception& e) {
                std::cout << "Ошибка при чтении из файла: " << e.what() << "\n";
            }
            catch (...) {
                std::cout << "Неизвестная ошибка при чтении из файла!\n";
            }
            break;

        case 4:
            return;

        default:
            std::cout << "Неверный выбор!\n";
        }
    }
}