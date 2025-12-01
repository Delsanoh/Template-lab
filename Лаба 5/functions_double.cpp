#define _CRT_SECURE_NO_WARNINGS
#include "binary_counter.h"

void manualInputDouble()
{
    int n;
    std::cout << "Количество элементов: ";
    std::cin >> n;
    if (n <= 0)
    {
        std::cout << "Неверный размер!\n";
        return;
    }
    std::vector<double> arr(n);
    std::cout << "Введите " << n << " чисел: ";
    for (int i = 0; i < n; i++)
    {
        std::cin >> arr[i];
    }
    auto res = findMinOnesElements(arr);
    std::cout << "Результат: ";
    for (double val : res)
    {
        std::cout << val << " ";
    }
    std::cout << "\n";
    writeToFile(arr, res, "Ручной ввод (double)");
}

void randomGenerationDouble()
{
    int n;
    double minVal;
    double maxVal;
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
    std::vector<double> arr(n);
    std::cout << "Массив: ";
    for (int i = 0; i < n; i++)
    {
        arr[i] = minVal + (double)rand() / RAND_MAX * (maxVal - minVal);
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
    auto res = findMinOnesElements(arr);
    std::cout << "Результат: ";
    for (double val : res)
    {
        std::cout << val << " ";
    }
    std::cout << "\n";
    writeToFile(arr, res, "Случайная генерация (double)");
}

void readFromFileDouble()
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
    std::vector<double> arr;
    double value;
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
    for (double val : arr)
    {
        std::cout << val << " ";
    }
    std::cout << "\n";
    auto res = findMinOnesElements(arr);
    std::cout << "Результат: ";
    for (double val : res)
    {
        std::cout << val << " ";
    }
    std::cout << "\n";
    writeToFile(arr, res, "Чтение из файла (double)");
}

void menuDouble()
{
    int choice;
    while (true)
    {
        std::cout << "\n=== DOUBLE МЕНЮ ===\n";
        std::cout << "1. Ручной ввод\n";
        std::cout << "2. Случайная генерация\n";
        std::cout << "3. Чтение из файла\n";
        std::cout << "4. Назад\n";
        std::cout << "Выбор: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            manualInputDouble();
            break;

        case 2:
            randomGenerationDouble();
            break;

        case 3:
            readFromFileDouble();
            break;

        case 4:
            return;

        default:
            std::cout << "Неверный выбор!\n";
        }
    }
}