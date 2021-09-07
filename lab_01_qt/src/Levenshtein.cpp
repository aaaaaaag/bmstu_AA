//
// Created by denis on 06.09.2021.
//

#include <iostream>
#include "Levenshtein.h"

size_t Levenshtein::withoutRecursion(const std::string& str1, const std::string& str2, bool debugMode) {
    auto len1 = str1.length();
    auto len2 = str2.length();
    auto matrix = Matrix(len1 + 1, len2 + 1);

    for (size_t i = 0; i <= len1; i++)
        matrix[i][0] = i;
    for (size_t j = 0; j <= len2; j++)
        matrix[0][j] = j;

    for (auto i = 1; i <= len1; i++)
    {
        for (auto j = 1; j <= len2; j++)
        {
            auto m = 1;
            if (str1[i - 1] == str2[j - 1])
                m = 0;

            matrix[i][j] = std::min(matrix[i - 1][j] + 1,
                     std::min(matrix[i][j - 1] + 1,
                     matrix[i - 1][j - 1] + m));
        }
    }
    if (debugMode) {
        std::cout << "Levenshtein without recursion" << std::endl;
        matrix.print();
    }
    return matrix[len1][len2];
}


size_t Levenshtein::_recursionWithoutCash(const char* str1, size_t i, const char* str2, size_t j) {
    size_t res;
    if (i)
    {
        if (j)
        {
            auto m = 1;
            if (str1[i - 1] == str2[j - 1])
                m = 0;

            auto a = _recursionWithoutCash(str1, i, str2, j - 1) + 1;
            auto b = _recursionWithoutCash(str1, i - 1, str2, j) + 1;
            auto c = _recursionWithoutCash(str1, i - 1, str2, j - 1) + m;
            res = std::min(a, std::min(b, c));
        }
        else
            res = i;
    }
    else
        res = j;
    return res;
}

size_t Levenshtein::recursionWithoutCash(const std::string &str1, const std::string &str2) {
    auto i = str1.length();
    auto j = str2.length();
    return _recursionWithoutCash(str1.data(), i, str2.data(), j);
}

size_t Levenshtein::recursionWithCash(const std::string &str1, const std::string &str2, bool debugMode) {
    auto n = str1.length();
    auto m = str2.length();

    auto matrix = Matrix(n + 1, m + 1);
    for (size_t i = 0; i <= n; i++)
    {
        for (size_t j = 0; j <= m; j++)
            matrix[i][j] = -1;
    }

    auto res = _recursionWithCash(str1.data(), n, str2.data(), m, matrix);
    if (debugMode) {
        std::cout << "Levenshtein recursion with cash" << std::endl;
        matrix.print();
    }
    return res;
}

size_t Levenshtein::_recursionWithCash(const char* str1, size_t i, const char* str2, size_t j, Matrix& matrix) {

    if (!i)
        matrix[i][j] = j;
    else if (!j)
        matrix[i][j] = i;
    else
    {
        if (matrix[i][j - 1] == -1)
            matrix[i][j - 1] = _recursionWithCash(str1, i, str2, j - 1, matrix);
        if (matrix[i - 1][j] == -1)
            matrix[i - 1][j] = _recursionWithCash(str1, i - 1, str2, j, matrix);
        if (matrix[i - 1][j - 1] == -1)
            matrix[i - 1][j - 1] = _recursionWithCash(str1, i - 1, str2, j - 1, matrix);
        matrix[i][j] = std::min(std::min(matrix[i][j - 1], matrix[i - 1][j]) + 1,
                                matrix[i - 1][j - 1] + (str1[i - 1] != str2[j - 1]));
    }

    return matrix[i][j];
}


size_t Levenshtein::recursionDamerauWithoutCash(const std::string &str1, const std::string &str2) {
    auto i = str1.length();
    auto j = str2.length();

    return _recursionDamerauWithoutCash(str1.data(), i, str2.data(), j);
}

size_t Levenshtein::_recursionDamerauWithoutCash(const char* str1, size_t i, const char* str2, size_t j) {
    size_t res;
    if (i)
    {
        if (j)
        {
            auto m = 1;
            if (str1[i - 1] == str2[j - 1])
                m = 0;

            auto a = _recursionWithoutCash(str1, i, str2, j - 1) + 1;
            auto b = _recursionWithoutCash(str1, i - 1, str2, j) + 1;
            auto c = _recursionWithoutCash(str1, i - 1, str2, j - 1) + m;
            res = std::min(a, std::min(b, c));
            if (i > 1 && j > 1 &&
                str1[i - 1] == str2[j - 2] && str1[i - 2] == str2[j - 1])
                res = std::min(res, _recursionWithoutCash(str1, i - 2, str2, j - 2) + 1);
        }
        else
            res = i;
    }
    else
        res = j;
    return res;
}




