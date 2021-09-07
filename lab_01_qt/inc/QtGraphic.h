//
// Created by denis on 07.09.2021.
//

#ifndef LAB_01_QTGRAPHIC_H
#define LAB_01_QTGRAPHIC_H

#include <QtCharts/QLogValueAxis>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include "QMainWindow"
#include "QWidget"
#include "vector"

typedef std::vector<std::pair<std::string, std::vector<std::pair<double, size_t>>>> drawData;

class QtGraphic: public QMainWindow {
public:

    explicit QtGraphic(const drawData& timeData)
    {

        for (const auto& method: timeData)
        {
            auto curSeries = new QtCharts::QLineSeries();
            for (auto data: method.second)
            {
                curSeries->append(data.second, data.first);
            }
            curSeries->setName(method.first.data());
            _series.push_back(curSeries);

        }

        auto *chart = new QtCharts::QChart();
        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignLeft);
        for (auto series: _series)
            chart->addSeries(series);
        chart->createDefaultAxes();
        chart->axisX()->setTitleText("str_len");
        chart->axisY()->setTitleText("time, sec");
        chart->setTitle("time cmp");

        auto *chart_view = new QtCharts::QChartView(chart);
        chart_view->setRenderHint(QPainter::Antialiasing);
        setCentralWidget(chart_view);
        setGeometry(0, 0, 1000, 600);
    }

private:

    std::vector<QtCharts::QLineSeries*> _series;

};


#endif //LAB_01_QTGRAPHIC_H
