#include "datagraph.h"


// #################### Public ####################
DataGraph::DataGraph(QWidget *parent) : QWidget(parent)
{
    createGuiItems();
    createAndFillLayouts();

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

    flowChart->setAnimationOptions(QChart::NoAnimation);

    // Used to display the chart.
    flow_chartView->setRenderHint(QPainter::Antialiasing);

    connect(plotTimer, SIGNAL(timeout()), this, SLOT(plotData()));
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
void DataGraph::dataReadyForPlot(QStringList data)
{
    AN1_data.append(QPoint(data[0].toInt(), data[1].toInt()));

    // Only have to check one pointer's length.
    if(AN1_data.length()>100) {
       AN1_data.removeFirst();
    }
}

void DataGraph::startPlotting()
{
    plotTimer->start(100);
}

void DataGraph::stopPlotting()
{
    plotTimer->stop();
}
// #################### Private slots ##############
void DataGraph::plotData()
{
    if (AN1_data.length()>0) {
        QPoint dataPoint = AN1_data[AN1_data.length()-1];

        lineSeries->append(dataPoint);
        if (lineSeries->count()>500) {
            lineSeries->remove(0);
        }
        flowChart->axisX()->setRange(dataPoint.x()-500, dataPoint.x()+100);
        flowChart->axisY()->setRange(dataPoint.y()-500, dataPoint.y()+500);
    }
}
