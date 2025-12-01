#define _CRT_SECURE_NO_WARNINGS
#include "binary_counter.h"

void manualInputStrings()
{
    int n;
    std::cout << "Количество строк: ";
    std::cin >> n;
    std::cin.ignore();
    if (n <= 0)
    {
        std::cout << "Неверный размер!\n";
        return;
    }
    std::vector<char*> arr;
    std::cout << "Введите " << n << " строк:\n";
    for (int i = 0; i < n; i++)
    {
        char buffer[256];
        std::cout << "Строка " << i + 1 << ": ";
        std::cin.getline(buffer, 256);
        char* str = new char[strlen(buffer) + 1];
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
    writeToFileStr(arr, res, "Ручной ввод (строки)");
    freeStringArray(arr);
}

void randomGenerationStrings()
{
    int n;
    std::cout << "Количество строк: ";
    std::cin >> n;
    if (n <= 0)
    {
        std::cout << "Неверный размер!\n";
        return;
    }
    srand(time(0));
    std::vector<char*> arr;
    const char* words[] = { "a", "ab", "abc", "test", "hello", "world", "123", "xyz" };
    const int wordCount = 8;
    std::cout << "Массив: ";
    for (int i = 0; i < n; i++)
    {
        const char* word = words[rand() % wordCount];
        char* str = new char[strlen(word) + 1];
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
    writeToFileStr(arr, res, "Случайная генерация (строки)");
    freeStringArray(arr);
}

void readStringsFromFile()
{
    char filename[256];
    std::cout << "Имя файла: ";
    std::cin >> filename;
    std::ifstream fin(filename);
    if (!CheckInputFile(fin))
    {
        std::cout << "Ошибка файла!\n";
        return;
    }
    std::vector<char*> arr;
    std::string word;
    while (fin >> word)
    {
        char* str = new char[word.length() + 1];
        strcpy(str, word.c_str());
        arr.push_back(str);
    }
    if (arr.empty())
    {
        std::cout << "Нет данных!\n";
        return;
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
    writeToFileStr(arr, res, "Чтение из файла (строки)");
    freeStringArray(arr);
}

void menuStrings()
{
    int choice;
    while (true)
    {
        std::cout << "\n=== СТРОКИ МЕНЮ ===\n";
        std::cout << "1. Ручной ввод\n";
        std::cout << "2. Случайная генерация\n";
        std::cout << "3. Чтение из файла\n";
        std::cout << "4. Назад\n";
        std::cout << "Выбор: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            manualInputStrings();
            break;

        case 2:
            randomGenerationStrings();
            break;

        case 3:
            readStringsFromFile();
            break;

        case 4:
            return;

        default:
            std::cout << "Неверный выбор!\n";
        }
    }
}