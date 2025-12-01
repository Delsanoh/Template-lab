#ifndef BINARY_COUNTER_H
#define BINARY_COUNTER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <cstring>

bool CheckInputFile(std::ifstream& fin);
int countBinaryOnesStr(const char* str);
std::vector<char*> findMinOnesElementsStr(const std::vector<char*>& array);
void writeToFileStr(const std::vector<char*>& array, const std::vector<char*>& result, const char* operation);
void freeStringArray(std::vector<char*>& array);
void menuInt();
void menuDouble();
void menuStrings();

template<typename T>
int countBinaryOnes(T value)
{
    int count = 0;
    unsigned char* bytes = (unsigned char*)&value;
    for (size_t i = 0; i < sizeof(T); i++)
    {
        unsigned char byte = bytes[i];
        while (byte)
        {
            count += byte & 1;
            byte >>= 1;
        }
    }
    return count;
}

template<typename T>
std::vector<T> findMinOnesElements(const std::vector<T>& array)
{
    if (array.empty())
    {
        return {};
    }
    std::vector<T> result = { array[0] };
    int minOnes = countBinaryOnes(array[0]);
    for (size_t i = 1; i < array.size(); i++)
    {
        int ones = countBinaryOnes(array[i]);
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

template<typename T>
void writeToFile(const std::vector<T>& array, const std::vector<T>& result, const char* operation)
{
    std::ofstream fout("out.txt", std::ios::app);
    if (!fout)
    {
        return;
    }
    fout << "=== " << operation << " ===\n";
    fout << "Массив (" << array.size() << "): ";
    for (const auto& val : array)
    {
        fout << val << " ";
    }
    fout << "\nРезультат: ";
    for (const auto& val : result)
    {
        fout << val << " ";
    }
    if (!result.empty())
    {
        fout << "\nЕдиниц: " << countBinaryOnes(result[0]);
    }
    fout << "\n\n";
}

#endif