#define _CRT_SECURE_NO_WARNINGS
#include "binary_counter.h"

bool CheckInputFile(std::ifstream& fin)
{
    if (!fin.good())
    {
        return false;
    }
    if (!fin)
    {
        return false;
    }
    if (fin.peek() == EOF)
    {
        return false;
    }
    return true;
}

int32_t countBinaryOnesStr(const char* str)
{
    int32_t count = 0;
    for (size_t i = 0; str[i] != '\0'; i++)
    {
        unsigned char c = str[i];
        while (c)
        {
            count += c & 1;
            c >>= 1;
        }
    }
    return count;
}

std::vector<char*> findMinOnesElementsStr(const std::vector<char*>& array)
{
    if (array.empty())
    {
        return {};
    }
    std::vector<char*> result = { array[0] };
    int32_t minOnes = countBinaryOnesStr(array[0]);
    for (size_t i = 1; i < array.size(); i++)
    {
        int32_t ones = countBinaryOnesStr(array[i]);
        if (ones < minOnes)
        {
            minOnes = ones;
            result.clear();
            result.push_back(array[i]);
        }
        else if (ones == minOnes)
        {
            result.push_back(array[i]);
        }
    }
    return result;
}

void writeToFileStr(const std::vector<char*>& array, const std::vector<char*>& result, const char* operation)
{
    std::ofstream fout("out.txt", std::ios::app);
    if (!fout)
    {
        return;
    }
    fout << "=== " << operation << " ===\n";
    fout << "Массив (" << array.size() << "): ";
    for (const auto& str : array)
    {
        fout << "\"" << str << "\" ";
    }
    fout << "\nРезультат: ";
    for (const auto& str : result)
    {
        fout << "\"" << str << "\" ";
    }
    if (!result.empty())
    {
        fout << "\nЕдиниц: " << countBinaryOnesStr(result[0]);
    }
    fout << "\n\n";
}

void freeStringArray(std::vector<char*>& array)
{
    for (auto str : array)
    {
        delete[] str;
    }
    array.clear();
}