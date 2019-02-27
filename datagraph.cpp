#include "datagraph.h"


// #################### Public ####################
DataGraph::DataGraph(QWidget *parent) : QWidget(parent)
{
    createGuiItems();
    createAndFillLayouts();

    lineSeries->append(0, 1);
    lineSeries->append(1, 2);
    lineSeries->append(2, 4);
    lineSeries->append(3, 8);
    lineSeries->append(4, 16);
    lineSeries->append(5, 32);
    lineSeries->append(6, 64);
    lineSeries->append(7, 128);

    // Create chart and add data
    flowChart->legend()->hide();
    flowChart->addSeries(lineSeries);
    flowChart->createDefaultAxes();

    // Customize the title font
    QFont font;
    font.setPixelSize(18);
    flowChart->setTitleFont(font);
    flowChart->setTitleBrush(QBrush(Qt::black));
    flowChart->setTitle("Flow graph");

    // Change the line color and wieght.
    QPen pen(QRgb(0x000000));
    pen.setWidth(5);
    lineSeries->setPen(pen);

    flowChart->setAnimationOptions(QChart::AllAnimations);

    // Chang ethe x axis categories
    QCategoryAxis *axisX = new QCategoryAxis();
    axisX->append("1996", 0);
    axisX->append("1997", 1);
    axisX->append("1998", 2);
    axisX->append("1999", 3);
    axisX->append("2000", 4);
    axisX->append("2001", 5);
    axisX->append("2002", 6);
    axisX->append("2003", 7);
    flowChart->setAxisX(axisX, lineSeries);

    // Used to display the chart.
    flow_chartView->setRenderHint(QPainter::Antialiasing);
}

// #################### Private ###################
void DataGraph::createGuiItems()
{
    flow_chartView->setFixedSize(490, 398);
    press_chartView->setFixedSize(490, 398);
}

void DataGraph::createAndFillLayouts()
{
    hbox->addWidget(flow_chartView);
    hbox->addWidget(press_chartView);

    this->setLayout(hbox);
}
// #################### Signals ###################
// #################### Public slots ###############
// #################### Private slots ##############
