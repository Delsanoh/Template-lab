#define _CRT_SECURE_NO_WARNINGS
#include "binary_counter.h"

void manualInputInt()
{
    int n;
    std::cout << "Количество элементов: ";
    std::cin >> n;
    if (n <= 0)
    {
        std::cout << "Неверный размер!\n";
        return;
    }
    std::vector<int> arr(n);
    std::cout << "Введите " << n << " чисел: ";
    for (int i = 0; i < n; i++)
    {
        std::cin >> arr[i];
    }
    auto res = findMinOnesElements(arr);
    std::cout << "Результат: ";
    for (int val : res)
    {
        std::cout << val << " ";
    }
    std::cout << "\n";
    writeToFile(arr, res, "Ручной ввод (int)");
}

void randomGenerationInt()
{
    int n;
    int minVal;
    int maxVal;
    std::cout << "Количество: ";
    std::cin >> n;
    std::cout << "Минимум: ";
    std::cin >> minVal;
    std::cout << "Максимум: ";
    std::cin >> maxVal;
    if (n <= 0 || minVal > maxVal)
    {
        std::cout << "Неверные параметры!\n";
        return;
    }
    srand(time(0));
    std::vector<int> arr(n);
    std::cout << "Массив: ";
    for (int i = 0; i < n; i++)
    {
        arr[i] = minVal + rand() % (maxVal - minVal + 1);
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
    auto res = findMinOnesElements(arr);
    std::cout << "Результат: ";
    for (int val : res)
    {
        std::cout << val << " ";
    }
    std::cout << "\n";
    writeToFile(arr, res, "Случайная генерация (int)");
}

void readFromFileInt()
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
    std::vector<int> arr;
    int value;
    while (fin >> value)
    {
        arr.push_back(value);
    }
    if (arr.empty())
    {
        std::cout << "Нет данных!\n";
        return;
    }
    std::cout << "Прочитано " << arr.size() << " чисел: ";
    for (int val : arr)
    {
        std::cout << val << " ";
    }
    std::cout << "\n";
    auto res = findMinOnesElements(arr);
    std::cout << "Результат: ";
    for (int val : res)
    {
        std::cout << val << " ";
    }
    std::cout << "\n";
    writeToFile(arr, res, "Чтение из файла (int)");
}

void menuInt()
{
    int choice;
    while (true)
    {
        std::cout << "\n=== INT МЕНЮ ===\n";
        std::cout << "1. Ручной ввод\n";
        std::cout << "2. Случайная генерация\n";
        std::cout << "3. Чтение из файла\n";
        std::cout << "4. Назад\n";
        std::cout << "Выбор: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            manualInputInt();
            break;

        case 2:
            randomGenerationInt();
            break;

        case 3:
            readFromFileInt();
            break;

        case 4:
            return;

        default:
            std::cout << "Неверный выбор!\n";
        }
    }
}