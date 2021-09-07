//
// Created by denis on 07.09.2021.
//

#ifndef LAB_01_TIMETABLEPRINTER_H
#define LAB_01_TIMETABLEPRINTER_H

#include "Levenshtein.h"
#include "GetCPUTime.h"
#include "iostream"
#include "TestTimeGetter.h"
#include "iomanip"

typedef std::vector<std::pair<std::string, std::vector<std::pair<double, size_t>>>> drawData;

class TimeTablePrinter
{
public:

    TimeTablePrinter()
    {
        for (auto i = 0; i < width; i++)
            line.push_back('-');

    }

    static drawData getData(size_t start, size_t end, size_t inc);

    void printTimeTable(size_t start, size_t end, size_t inc);

private:
    void printValues(size_t str_len, double levWR, double levRNC, double levRWC, double levDamR) const;

    void printTableTop();
    std::string line;
    size_t width = 115;
    size_t len_width = 15;
    size_t lev_width = 25;
};

drawData TimeTablePrinter::getData(size_t start, size_t end, size_t inc) {

    drawData res;

    std::vector<std::pair<double, size_t>> levNRData;
    std::vector<std::pair<double, size_t>> levRWCData;
    for (auto len = start; len <= end; len+=inc)
    {
        auto levNR = TestTimeGetter::getAverageTime(len, Levenshtein::withoutRecursion);
        levNRData.emplace_back(levNR, len);
        auto levRWC = TestTimeGetter::getAverageTime(len, Levenshtein::recursionWithCash);
        levRWCData.emplace_back(levRWC, len);
    }
    res.emplace_back("levNR", levNRData);
    res.emplace_back("levRWC", levRWCData);

    if (end < 6)
    {
        std::vector<std::pair<double, size_t>> levRNCData;
        std::vector<std::pair<double, size_t>> levDamRData;
        for (auto len = start; len <= end; len+=inc)
        {
            auto levRNC = TestTimeGetter::getAverageTime(len, Levenshtein::recursionWithoutCash);
            auto levDamR = TestTimeGetter::getAverageTime(len, Levenshtein::recursionDamerauWithoutCash);
            levRNCData.emplace_back(levRNC, len);
            levDamRData.emplace_back(levDamR, len);
        }
        res.emplace_back("levRNC", levRNCData);
        res.emplace_back("levDamR", levDamRData);
    }
    return res;
}

void TimeTablePrinter::printTimeTable(size_t start, size_t end, size_t inc) {
    printTableTop();
    for (auto len = start; len <= end; len+=inc)
    {
        auto levNR = TestTimeGetter::getAverageTime(len, Levenshtein::withoutRecursion);
        auto levRWC = TestTimeGetter::getAverageTime(len, Levenshtein::recursionWithCash);
        double levRNC = -1;
        double levDamR = -1;
        if (len < 5) {
            levRNC = TestTimeGetter::getAverageTime(len, Levenshtein::recursionWithoutCash);
            levDamR = TestTimeGetter::getAverageTime(len, Levenshtein::recursionDamerauWithoutCash);
        }
        printValues(len, levNR, levRNC, levRWC, levDamR);
    }
}

void TimeTablePrinter::printTableTop() {
    std::cout << "N - no" << std::endl;
    std::cout << "W - with" << std::endl;
    std::cout << "R - recursion" << std::endl;
    std::cout << "C - cash" << std::endl;
    std::cout << line << std::endl;
    std::cout << '|' << std::setw(len_width - 1) << std::left << "str_len" << '|' <<
              std::setw(lev_width - 1) << std::left << "levNR" << '|' <<
              std::setw(lev_width - 1) << std::left << "levRNC" << '|' <<
              std::setw(lev_width - 1) << std::left << "levRWC" << '|' <<
              std::setw(lev_width - 1) << std::left << "levDamR" << '|' << std::endl;
    std::cout << line << std::endl;
}

void TimeTablePrinter::printValues(size_t str_len, double levWR, double levRNC, double levRWC, double levDamR) const {
    std::cout << '|' << std::setw(len_width - 1) << std::left << str_len << '|' <<
              std::setw(lev_width - 1) << std::left << levWR << '|' <<
              std::setw(lev_width - 1) << std::left << levRNC << '|' <<
              std::setw(lev_width - 1) << std::left << levRWC << '|' <<
              std::setw(lev_width - 1) << std::left << levDamR << '|' << std::endl;
    std::cout << line << std::endl;
}




#endif //LAB_01_TIMETABLEPRINTER_H
