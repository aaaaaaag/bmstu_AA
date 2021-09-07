//
// Created by denis on 06.09.2021.
//

#ifndef LAB_01_LEVENSHTEIN_H
#define LAB_01_LEVENSHTEIN_H

#include "Matrix.h"
#include "string"

class Levenshtein {
public:


    static size_t withoutRecursion(const std::string& str1, const std::string& str2, bool debugMode = false);

    static size_t recursionWithoutCash(const std::string& str1, const std::string& str2);

    static size_t recursionWithCash(const std::string& str1, const std::string& str2, bool debugMode = false);

    static size_t recursionDamerauWithoutCash(const std::string& str1, const std::string& str2);

private:

    static size_t _recursionWithoutCash(const char* str1, size_t i, const char* str2, size_t j);

    static size_t _recursionWithCash(const char* str1, size_t i, const char* str2, size_t j, Matrix& matrix);

    static size_t _recursionDamerauWithoutCash(const char* str1, size_t i, const char* str2, size_t j);

};


#endif //LAB_01_LEVENSHTEIN_H
