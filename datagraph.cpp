#include "datagraph.h"


// #################### Public ####################
DataGraph::DataGraph(QWidget *parent) : QWidget(parent)
{
    createGuiItems();
    createAndFillLayouts();
    connect(plotTimer, SIGNAL(timeout()), this, SLOT(plotData()));
    for(QCheckBox *item : sensor_enableCheckboxes) {
        connect(item, SIGNAL(toggled(bool)), this, SLOT(plotMembersChanged(bool)));
    }
}

// #################### Private ###################
void DataGraph::createGuiItems()
{
    QPixmap pixmap = QPixmap(100,100);
    QList<QColor> colours = {
        QColor(255, 0, 0),
        QColor(255, 0, 255),
        QColor(255, 255, 0),
        QColor(0, 255, 0),
        QColor(0, 255, 255),
        QColor(0, 0, 255),
        QColor(0, 0, 0),
        QColor(48, 46, 142),
        QColor(237, 175, 33),
        QColor(165, 165, 165),
    };
    for (int i = 0; i < 10; i++) {
        sensor_enableCheckboxes.append(new QCheckBox);
        sensor_enableCheckboxes[i]->setChecked(true);

        pixmap.fill(colours[i]);
        QIcon temp2 = QIcon(pixmap);
        sensor_enableCheckboxes[i]->setIcon(temp2);

        if(i <= 4)
            sensor_enableCheckboxes[i]->setText(QString("A%1").arg(i+1));
        else
            sensor_enableCheckboxes[i]->setText(QString("D%1").arg(i-4));
    }

    flow_chartView->setFixedSize(490, 350);
    press_chartView->setFixedSize(490, 350);

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
}

void DataGraph::createAndFillLayouts()
{
    for(QCheckBox *item : sensor_enableCheckboxes) {
        checkBox_hbox->addWidget(item);
    }
    graph_hbox->addWidget(flow_chartView);
    graph_hbox->addWidget(press_chartView);

    vbox->addLayout(checkBox_hbox);
    vbox->addLayout(graph_hbox);

    this->setLayout(vbox);
}
// #################### Signals ###################
// #################### Public slots ###############
void DataGraph::dataReadyForPlot(QStringList data)
{
    qDebug() << data[0] << data[1];
    AN1_data.append(QPointF(static_cast<double>(data[0].toInt())/1000.0,
                            static_cast<double>(data[1].toInt())));
    // qDebug() << AN1_data[AN1_data.length()-1];
    // Only have to check one pointer's length.
    if(AN1_data.length()>100) {
       AN1_data.removeFirst();
    }
}

void DataGraph::startPlotting()
{
    plotTimer->start(100);
    lineSeries->clear();
}

void DataGraph::stopPlotting()
{
    plotTimer->stop();
}
// #################### Private slots ##############
void DataGraph::plotData()
{
    if (AN1_data.length()>0) {
        QPointF dataPoint = AN1_data[AN1_data.length()-1];

        lineSeries->append(dataPoint);
        if (lineSeries->count()>500) {
            lineSeries->remove(0);
        }
        flowChart->axisX()->setRange(dataPoint.x()-10, dataPoint.x()+10);
        flowChart->axisY()->setRange(dataPoint.y()-250, dataPoint.y()+250);
    }
}

void DataGraph::plotMembersChanged(bool state)
{
    int i = 0;
    for(QCheckBox *item : sensor_enableCheckboxes) {
        enabled_sensors[i] = item->isChecked();
        i++;
    }

    for(int i = 0; i< 10; i++) {
        qDebug() << enabled_sensors[i];
    }
}
