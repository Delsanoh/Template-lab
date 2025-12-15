#include "pch.h"

#define _CRT_SECURE_NO_WARNINGS
#include "../Лаба 5/binary_counter.cpp"
#include <fstream>
#include <string>

TEST(BinaryCounterTest, CountBinaryOnesInt)
{
    EXPECT_EQ(countBinaryOnes(0), 0);
    EXPECT_EQ(countBinaryOnes(1), 1);
    EXPECT_EQ(countBinaryOnes(3), 2);
    EXPECT_EQ(countBinaryOnes(7), 3);
    EXPECT_EQ(countBinaryOnes(255), 8);
    EXPECT_EQ(countBinaryOnes(-1), 32);
}

TEST(BinaryCounterTest, CountBinaryOnesDouble)
{
    double zero = 0.0;
    double one = 1.0;

    int32_t onesZero = countBinaryOnes(zero);
    int32_t onesOne = countBinaryOnes(one);

    EXPECT_GE(onesZero, 0);
    EXPECT_GE(onesOne, 0);

    EXPECT_TRUE(onesZero >= 0 && onesZero <= 64);
    EXPECT_TRUE(onesOne >= 0 && onesOne <= 64);
}

TEST(BinaryCounterTest, FindMinOnesElementsInt)
{
    std::vector<int32_t> arr1 = { 1, 2, 3, 4, 5 };
    auto res1 = findMinOnesElements(arr1);

    EXPECT_EQ(res1.size(), 3);
    EXPECT_EQ(res1[0], 1);
    EXPECT_EQ(res1[1], 2);
    EXPECT_EQ(res1[2], 4);

    std::vector<int32_t> arr2 = { 0, 255, 127 };
    auto res2 = findMinOnesElements(arr2);

    EXPECT_EQ(res2.size(), 1);
    EXPECT_EQ(res2[0], 0);

    std::vector<int32_t> arr3 = { 3, 5, 6 };
    auto res3 = findMinOnesElements(arr3);
    EXPECT_EQ(res3.size(), 3);
}

TEST(BinaryCounterTest, FindMinOnesElementsDouble)
{
    std::vector<double> arr = { 0.0, 1.0, 2.0 };
    auto res = findMinOnesElements(arr);

    EXPECT_FALSE(res.empty());
    EXPECT_LE(res.size(), arr.size());

    for (const auto& val : res)
    {
        bool found = false;
        for (const auto& original : arr)
        {
            if (val == original)
            {
                found = true;
                break;
            }
        }
        EXPECT_TRUE(found);
    }
}

TEST(BinaryCounterTest, FindMinOnesElementsStr)
{
    std::vector<char*> arr;

    char* str1 = new char[2];
    strcpy(str1, "a");
    char* str2 = new char[2];
    strcpy(str2, "b");
    char* str3 = new char[2];
    strcpy(str3, "c");
    char* str4 = new char[2];
    strcpy(str4, "d");

    arr.push_back(str1);
    arr.push_back(str2);
    arr.push_back(str3);
    arr.push_back(str4);

    auto res = findMinOnesElementsStr(arr);

    EXPECT_EQ(res.size(), 3);

    bool hasC = false;
    for (const auto& str : res)
    {
        if (strcmp(str, "c") == 0)
        {
            hasC = true;
            break;
        }
    }
    EXPECT_FALSE(hasC);

    for (auto str : arr) delete[] str;
}

TEST(BinaryCounterTest, CheckInputFile)
{
    std::string testFileName = "test_input_file.txt";

    {
        std::ifstream fin("non_existent_file.txt");
        EXPECT_FALSE(CheckInputFile(fin));
    }

    {
        std::ofstream fout(testFileName);
        fout.close();
        std::ifstream fin(testFileName);
        EXPECT_FALSE(CheckInputFile(fin));
        fin.close();
    }

    {
        std::ofstream fout(testFileName);
        fout << "10 20 30\n40 50\n";
        fout.close();

        std::ifstream fin(testFileName);
        EXPECT_TRUE(CheckInputFile(fin));
        fin.close();
    }

    std::remove(testFileName.c_str());
}

TEST(BinaryCounterTest, WriteToFileTemplate)
{
    std::vector<int32_t> arr = { 1, 2, 3 };
    std::vector<int32_t> res = { 1, 2 };

    std::remove("test_output.txt");

    {
        std::ofstream fout("test_output.txt");
        if (!fout) return;

        fout << "=== Тестовая операция ===\n";
        fout << "Массив (" << arr.size() << "): ";
        for (const auto& val : arr) fout << val << " ";
        fout << "\nРезультат: ";
        for (const auto& val : res) fout << val << " ";
        if (!res.empty()) fout << "\nЕдиниц: " << countBinaryOnes(res[0]);
        fout << "\n\n";
    }

    std::ifstream fin("test_output.txt");
    EXPECT_TRUE(fin.good());

    std::string content;
    std::string line;
    while (std::getline(fin, line))
    {
        content += line + "\n";
    }
    fin.close();

    EXPECT_FALSE(content.empty());
    EXPECT_TRUE(content.find("Тестовая операция") != std::string::npos);
    EXPECT_TRUE(content.find("Массив (3):") != std::string::npos);
    EXPECT_TRUE(content.find("1 2 3") != std::string::npos);

    std::remove("test_output.txt");
}

TEST(BinaryCounterTest, WriteToFileStr)
{
    std::vector<char*> arr;
    std::vector<char*> res;

    char* str1 = new char[4];
    strcpy(str1, "abc");
    char* str2 = new char[4];
    strcpy(str2, "def");

    arr.push_back(str1);
    res.push_back(str2);

    std::remove("test_output_str.txt");

    {
        std::ofstream fout("test_output_str.txt");
        if (!fout) return;

        fout << "=== Тестовая операция (строки) ===\n";
        fout << "Массив (" << arr.size() << "): ";
        for (const auto& str : arr) fout << "\"" << str << "\" ";
        fout << "\nРезультат: ";
        for (const auto& str : res) fout << "\"" << str << "\" ";
        if (!res.empty()) fout << "\nЕдиниц: " << countBinaryOnesStr(res[0]);
        fout << "\n\n";
    }

    std::ifstream fin("test_output_str.txt");
    EXPECT_TRUE(fin.good());

    std::string content;
    std::string line;
    while (std::getline(fin, line))
    {
        content += line + "\n";
    }
    fin.close();

    EXPECT_FALSE(content.empty());
    EXPECT_TRUE(content.find("Тестовая операция (строки)") != std::string::npos);
    EXPECT_TRUE(content.find("\"abc\"") != std::string::npos);
    EXPECT_TRUE(content.find("\"def\"") != std::string::npos);

    for (auto str : arr) delete[] str;

    std::remove("test_output_str.txt");
}

TEST(BinaryCounterTest, FreeStringArray)
{
    std::vector<char*> arr;

    for (int32_t i = 0; i < 5; i++)
    {
        char* str = new char[10];
        sprintf(str, "test%d", i);
        arr.push_back(str);
    }

    EXPECT_EQ(arr.size(), 5);

    freeStringArray(arr);

    EXPECT_EQ(arr.size(), 0);
    EXPECT_TRUE(arr.empty());
}

TEST(BinaryCounterTest, EmptyArray)
{
    std::vector<int32_t> emptyArr;
    auto res = findMinOnesElements(emptyArr);

    EXPECT_TRUE(res.empty());
    EXPECT_EQ(res.size(), 0);
}

TEST(BinaryCounterTest, SingleElement)
{
    std::vector<int32_t> arr = { 42 };
    auto res = findMinOnesElements(arr);

    EXPECT_EQ(res.size(), 1);
    EXPECT_EQ(res[0], 42);
}

TEST(BinaryCounterTest, AllSameElements)
{
    std::vector<int32_t> arr = { 7, 7, 7, 7 };
    auto res = findMinOnesElements(arr);

    EXPECT_EQ(res.size(), 4);
    for (const auto& val : res)
    {
        EXPECT_EQ(val, 7);
    }
}

TEST(BinaryCounterTest, IntegrationTestInt)
{
    std::vector<int32_t> arr = { 0, 1, 2, 3, 4, 5 };

    auto res = findMinOnesElements(arr);

    EXPECT_EQ(res.size(), 1);
    EXPECT_EQ(res[0], 0);
    EXPECT_EQ(countBinaryOnes(res[0]), 0);
}

TEST(BinaryCounterTest, BoundaryValues)
{
    int32_t maxInt = 2147483647;
    int32_t minInt = -2147483648;

    int32_t onesMax = countBinaryOnes(maxInt);
    int32_t onesMin = countBinaryOnes(minInt);

    EXPECT_GE(onesMax, 0);
    EXPECT_LE(onesMax, 32);

    EXPECT_GE(onesMin, 0);
    EXPECT_LE(onesMin, 32);
}