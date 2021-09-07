#include <QApplication>
#include <QPushButton>


#include "inc/TimeTablePrinter.h"
#include "QtGraphic.h"
void printMenu()
{
    std::cout << "Actions" << std::endl;
    std::cout << "1) Release mode" << std::endl;
    std::cout << "2) Debug mode" << std::endl;
    std::cout << "3) Get graphic" << std::endl;
    std::cout << "4) Exit" << std::endl;
    std::cout << "Enter choose: ";
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    int mainChoose = 0;
    TimeTablePrinter printer;
    while (mainChoose != 3)
    {
        printMenu();
        std::cin >> mainChoose;
        if (mainChoose == 1)
        {
            printer.printTimeTable(0, 1000, 75);
        }
        else if (mainChoose == 2)
        {
            std::string str1, str2;
            std::cout << "Enter str1: ";
            std::cin >> str1;
            std::cout << "Enter str2: ";
            std::cin >> str2;

            auto start = getCPUTime();
            auto res = Levenshtein::withoutRecursion(str1, str2, true);
            auto end = getCPUTime();
            std::cout << "Result = " << res << std::endl;
            std::cout << "Time = " << end - start << std::endl;

            start = getCPUTime();
            res = Levenshtein::recursionWithCash(str1, str2, true);
            end = getCPUTime();
            std::cout << "Result = " << res << std::endl;
            std::cout << "Time = " << end - start << std::endl;

            start = getCPUTime();
            res = Levenshtein::recursionWithoutCash(str1, str2);
            end = getCPUTime();
            std::cout << "Levenshtein recursion without cash" << std::endl;
            std::cout << "Res = " << res << std::endl;
            std::cout << "Time = " << end - start << std::endl;

            start = getCPUTime();
            res = Levenshtein::recursionDamerauWithoutCash(str1, str2);
            end = getCPUTime();
            std::cout << "Damerau Levenshtein with recursion" << std::endl;
            std::cout << "Res = " << res << std::endl;
            std::cout << "Time = " << end - start << std::endl;

        }
        else if (mainChoose == 3)
        {
            std::cout << "1) Len 0..5 inc 1" << std::endl;
            std::cout << "2) Len 0..1000 inc 75" << std::endl;
            std::cout << "Your choose: ";
            int choose;
            std::cin >> choose;
            if (choose == 1)
            {
                auto data = printer.getData(0, 5, 1);
                auto qt = new QtGraphic(data);
                qt->show();
            }
            else if (choose == 2)
            {
                auto data = printer.getData(0, 1000, 75);
                auto qt = new QtGraphic(data);
                qt->show();
            }
            else
                std::cout << "Input Error " << std::endl;
        }
        else if (mainChoose != 4)
            std::cout << "Input Error " << std::endl;
    }
    return QApplication::exec();
}


