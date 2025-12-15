#define _CRT_SECURE_NO_WARNINGS
#include "binary_counter.h"
#include <limits> // для std::numeric_limits

int main()
{
    std::setlocale(LC_ALL, "Russian");
    std::ofstream("out.txt").close();

    while (true)
    {
        std::cout << "\n=== ГЛАВНОЕ МЕНЮ ===\n";
        std::cout << "1. int\n";
        std::cout << "2. double\n";
        std::cout << "3. Строки\n";
        std::cout << "4. Выход\n";
        std::cout << "Выбор типа: ";

        int32_t type;

        try {
            if (!(std::cin >> type)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::invalid_argument("Ошибка: введено не число!");
            }

            switch (type)
            {
            case 1:
                menuInt();
                break;

            case 2:
                menuDouble();
                break;

            case 3:
                menuStrings();
                break;

            case 4:
                std::cout << "Программа завершена. Результаты в файле out.txt\n";
                return 0;

            default:
                std::cout << "Неверный выбор!\n";
            }
        }
        catch (const std::invalid_argument& e) {
            std::cout << e.what() << std::endl;
        }
        catch (const std::exception& e) {
            std::cout << "Произошла ошибка: " << e.what() << std::endl;
        }
        catch (...) {
            std::cout << "Неизвестная ошибка!" << std::endl;
        }
    }

    return 0;
}