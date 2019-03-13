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

    for (int i = 0; i < 10; i++) {
        sensor_enableCheckboxes.append(new QCheckBox);
        sensor_enableCheckboxes[i]->setChecked(false);

        pixmap.fill(plotColours[i]);
        QIcon temp2 = QIcon(pixmap);
        sensor_enableCheckboxes[i]->setIcon(temp2);

        if(i <= 4)
            sensor_enableCheckboxes[i]->setText(QString("A%1").arg(i+1));
        else
            sensor_enableCheckboxes[i]->setText(QString("D%1").arg(i-4));
    }

    // Create a line series for each sensor.
    for(int i = 0; i < 10; i++) lineSeries.append(new QLineSeries());
    for(int i = 0; i < 10; i++) recentData.append(QPointF(0,0));

    createFlowGraph();
    createPressureGraph();
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

void DataGraph::createFlowGraph()
{
    flow_chartView->setFixedSize(490, 350);

    // Create chart and add data
    flowChart->legend()->hide();
    flowChart->addSeries(lineSeries[0]);
    flowChart->createDefaultAxes();

    // Customize the title font
    QFont font;
    font.setPixelSize(18);
    flowChart->setTitleFont(font);
    flowChart->setTitleBrush(QBrush(Qt::black));
    flowChart->setTitle("Flow graph");

    flowChart->setAnimationOptions(QChart::NoAnimation);

    // Used to display the chart.
    flow_chartView->setRenderHint(QPainter::Antialiasing);

}

void DataGraph::createPressureGraph()
{
    press_chartView->setFixedSize(490, 350);

    // Create chart and add data
    pressureChart->legend()->hide();
    pressureChart->addSeries(lineSeries[9]);
    pressureChart->createDefaultAxes();

    // Customize the title font
    QFont font;
    font.setPixelSize(18);
    pressureChart->setTitleFont(font);
    pressureChart->setTitleBrush(QBrush(Qt::black));
    pressureChart->setTitle("Pressure graph");

    pressureChart->setAnimationOptions(QChart::NoAnimation);

    // Used to display the chart.
    press_chartView->setRenderHint(QPainter::Antialiasing);

}

void DataGraph::initialiseLineSeries()
{
    // Change the line color and wieght.
    for(int i = 0; i < plotColours.size(); i++) {
        QPen pen(QBrush(plotColours[i]), 2);
        lineSeries[i]->setPen(pen);
        lineSeries[i]->setColor(plotColours[i]);
    }
}

void DataGraph::setParameterInterface(ParameterInterface *pInterface)
{
    mInterface = pInterface;
}
// #################### Signals ###################
// #################### Public slots ###############
void DataGraph::dataReadyForPlot(QStringList data)
{
    // qDebug() << data[0] << data[1] << data[2] << data[3] << data[4] << data[5];
    for(int i = 0; i < recentData.size(); i++) {
        recentData[i] = (QPointF(static_cast<double>(data[0].toInt())/1000.0,
                         static_cast<double>(data[i+1].toInt())));
    }
    // qDebug() << recentData[0] << recentData[1] << recentData[2] << recentData[3];
}

void DataGraph::startPlotting()
{
    QList<aParams> a_sensor_params = mInterface->getAnalogueSensorParams();
    QList<dParams> d_sensor_params = mInterface->getDigitalSensorParams();

    //flowChart->removeAllSeries();
    //pressureChart->removeAllSeries();

    for(int i = 0; i < a_sensor_params.size(); i++) {
        if(a_sensor_params[i].enabled && a_sensor_params[i].type == aFlow) {
            plotSensors[i] = true;
            sensor_enableCheckboxes[i]->setChecked(true);
            flowChart->addSeries(lineSeries[i]);
        } else {
            plotSensors[i] = false;
            sensor_enableCheckboxes[i]->setChecked(false);
            pressureChart->addSeries(lineSeries[i]);
        }
    }

    for(int i = 0; i < d_sensor_params.size(); i++) {
        if(d_sensor_params[i].enabled && d_sensor_params[i].type == dFlow) {
            plotSensors[i+5] = true;
            sensor_enableCheckboxes[i+5]->setChecked(true);
            flowChart->addSeries(lineSeries[i+5]);
        } else {
            plotSensors[i+5] = false;
            sensor_enableCheckboxes[i+5]->setChecked(false);
            pressureChart->addSeries(lineSeries[i+5]);
        }
    }
    flowChart->createDefaultAxes();
    pressureChart->createDefaultAxes();

    qDebug() << flowChart->series().size();
    plotTimer->start(100);
    for(QLineSeries* series : lineSeries) {
        series->clear();
    }

    initialiseLineSeries();
}

void DataGraph::stopPlotting()
{
    plotTimer->stop();
}
// #################### Private slots ##############
void DataGraph::plotData()
{
    for(int i = 0; i < recentData.size(); i++) {
        if(plotSensors[i]) lineSeries[i]->show();
        else lineSeries[i]->hide();

        if (!recentData[i].isNull()) {
            // qDebug() << "plotting: " << i << recentData[i];
            lineSeries[i]->append(recentData[i]);
            //qDebug() << lineSeries[i]->count() << i;
            if (lineSeries[i]->count()>500) {
                lineSeries[i]->remove(0);
            }
        }
    }
    flowChart->axisX()->setRange(recentData[0].x()-100, recentData[0].x());
    flowChart->axisY()->setRange(0, 1024);
}

void DataGraph::plotMembersChanged(bool state)
{
    int i = 0;
    for(QCheckBox *item : sensor_enableCheckboxes) {
        plotSensors[i] = item->isChecked();
        i++;
    }
}
