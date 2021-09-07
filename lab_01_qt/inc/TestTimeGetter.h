//
// Created by denis on 07.09.2021.
//

#ifndef LAB_01_TESTTIMEGETTER_H
#define LAB_01_TESTTIMEGETTER_H

#include "functional"
#include "GetCPUTime.h"
#include "Levenshtein.h"
class TestTimeGetter
{
public:

    static double getAverageTime(size_t str_len, const std::function<size_t(const std::string& str1, const std::string& str2)>& func);
    static double getAverageTime(size_t str_len, const std::function<size_t(const std::string& str1, const std::string& str2, bool debugMode)>& func);
};

double
TestTimeGetter::getAverageTime(size_t str_len, const std::function<size_t(const std::string &, const std::string &)>& func) {
    std::string testStr1;
    std::string testStr2;
    for(auto i = 0; i < str_len; i++)
    {
        if (i%2)
        {
            testStr1.push_back('a');
            testStr2.push_back('b');
        }
        else
        {
            testStr1.push_back('b');
            testStr2.push_back('a');
        }
    }

    double sum = 0;
    if (str_len == 0)
        str_len++;
    for (auto time = 0; time < static_cast<int>(100/str_len) + 2; time++)
    {
        auto start = getCPUTime();
        func(testStr1, testStr2);
        auto end = getCPUTime();
        sum += end - start;
    }
    sum /= static_cast<int>(100/str_len) + 2;
    return sum;
}

double TestTimeGetter::getAverageTime(size_t str_len,
                                      const std::function<size_t(const std::string &, const std::string &,
                                                                 bool)> &func) {
    std::string testStr1;
    std::string testStr2;
    for(auto i = 0; i < str_len; i++)
    {
        if (i%2)
        {
            testStr1.push_back('a');
            testStr2.push_back('b');
        }
        else
        {
            testStr1.push_back('b');
            testStr2.push_back('a');
        }
    }

    double sum = 0;
    if (str_len == 0)
        str_len++;
    for (auto time = 0; time < static_cast<int>(100/str_len) + 2; time++)
    {
        auto start = getCPUTime();
        func(testStr1, testStr2, false);
        auto end = getCPUTime();
        sum += end - start;
    }
    sum /= static_cast<int>(100/str_len) + 2;
    return sum;
}

#endif //LAB_01_TESTTIMEGETTER_H
