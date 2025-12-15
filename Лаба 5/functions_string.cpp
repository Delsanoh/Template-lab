#define _CRT_SECURE_NO_WARNINGS
#include "binary_counter.h"
#include <stdexcept>
#include <limits>

void manualInputStrings()
{
    int32_t n;
    std::cout << "Количество строк: ";
    if (!(std::cin >> n)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw std::invalid_argument("Ошибка: введено не число для количества строк!");
    }
    std::cin.ignore();

    if (n <= 0)
    {
        throw std::invalid_argument("Ошибка: количество строк должно быть положительным!");
    }

    std::vector<char*> arr;
    std::cout << "Введите " << n << " строк:\n";

    for (size_t i = 0; i < n; i++)
    {
        char buffer[256];
        std::cout << "Строка " << i + 1 << ": ";

        if (!std::cin.getline(buffer, 256)) {
            // Очищаем уже выделенную память перед выбрасыванием исключения
            for (char* str : arr) {
                delete[] str;
            }

            if (std::cin.eof()) {
                throw std::runtime_error("Ошибка: достигнут конец ввода (EOF)!");
            }

            std::cin.clear();
            throw std::runtime_error("Ошибка чтения строки!");
        }

        char* str = new char[strlen(buffer) + 1];
        if (!str) {
            // Очищаем уже выделенную память
            for (char* str : arr) {
                delete[] str;
            }
            throw std::bad_alloc();
        }

        strcpy(str, buffer);
        arr.push_back(str);
    }

    auto res = findMinOnesElementsStr(arr);
    std::cout << "Результат: ";
    for (char* str : res)
    {
        std::cout << "\"" << str << "\" ";
    }
    std::cout << "\n";

    try {
        writeToFileStr(arr, res, "Ручной ввод (строки)");
    }
    catch (...) {
        freeStringArray(arr);
        throw; // Пробрасываем исключение дальше
    }

    freeStringArray(arr);
}

void randomGenerationStrings()
{
    int32_t n;
    std::cout << "Количество строк: ";
    if (!(std::cin >> n)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw std::invalid_argument("Ошибка: введено не число для количества строк!");
    }

    if (n <= 0)
    {
        throw std::invalid_argument("Ошибка: количество строк должно быть положительным!");
    }

    srand(time(0));
    std::vector<char*> arr;
    const char* words[] = { "a", "ab", "abc", "test", "hello", "world", "123", "xyz" };
    const int32_t wordCount = 8;
    std::cout << "Массив: ";

    for (size_t i = 0; i < n; i++)
    {
        const char* word = words[rand() % wordCount];
        char* str = new char[strlen(word) + 1];
        if (!str) {
            // Очищаем уже выделенную память
            for (char* str : arr) {
                delete[] str;
            }
            throw std::bad_alloc();
        }

        strcpy(str, word);
        arr.push_back(str);
        std::cout << "\"" << str << "\" ";
    }
    std::cout << "\n";

    auto res = findMinOnesElementsStr(arr);
    std::cout << "Результат: ";
    for (char* str : res)
    {
        std::cout << "\"" << str << "\" ";
    }
    std::cout << "\n";

    try {
        writeToFileStr(arr, res, "Случайная генерация (строки)");
    }
    catch (...) {
        freeStringArray(arr);
        throw;
    }

    freeStringArray(arr);
}

void readStringsFromFile()
{
    char filename[256];
    std::cout << "Имя файла: ";
    if (!(std::cin >> filename)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw std::runtime_error("Ошибка чтения имени файла!");
    }

    std::ifstream fin(filename);
    if (!CheckInputFile(fin))
    {
        throw std::runtime_error("Ошибка открытия файла или файл пустой!");
    }

    std::vector<char*> arr;
    std::string word;

    try {
        while (fin >> word)
        {
            char* str = new char[word.length() + 1];
            if (!str) {
                // Очищаем уже выделенную память
                for (char* str : arr) {
                    delete[] str;
                }
                throw std::bad_alloc();
            }

            strcpy(str, word.c_str());
            arr.push_back(str);
        }
    }
    catch (...) {
        // Очищаем память при ошибке чтения
        for (char* str : arr) {
            delete[] str;
        }
        throw;
    }

    if (arr.empty())
    {
        throw std::runtime_error("Файл не содержит данных!");
    }

    std::cout << "Прочитано " << arr.size() << " строк: ";
    for (char* str : arr)
    {
        std::cout << "\"" << str << "\" ";
    }
    std::cout << "\n";

    auto res = findMinOnesElementsStr(arr);
    std::cout << "Результат: ";
    for (char* str : res)
    {
        std::cout << "\"" << str << "\" ";
    }
    std::cout << "\n";

    try {
        writeToFileStr(arr, res, "Чтение из файла (строки)");
    }
    catch (...) {
        freeStringArray(arr);
        throw;
    }

    freeStringArray(arr);
}

void menuStrings()
{
    int32_t choice;
    while (true)
    {
        std::cout << "\n=== СТРОКИ МЕНЮ ===\n";
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
                manualInputStrings();
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
                randomGenerationStrings();
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
                readStringsFromFile();
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