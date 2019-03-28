#include "datagraph.h"

//TODO: presure graphing
// TODO: limits based on slider
// #################### Public ####################
DataGraph::DataGraph(QWidget *parent) : QWidget(parent)
{
    createGuiItems();
    createAndFillLayouts();

    connect(plotTimer, SIGNAL(timeout()), this, SLOT(plotData()));
    for(QCheckBox *item : sensor_enableCheckboxes) {
        connect(item, SIGNAL(toggled(bool)), this, SLOT(plotMembersChanged(bool)));
    }
    connect(flow_y_auto, SIGNAL(toggled(bool)), this, SLOT(flowAutoAdjustY(bool)));
    connect(pres_y_auto, SIGNAL(toggled(bool)), this, SLOT(presAutoAdjustY(bool)));
    connect(flow_y_upper, SIGNAL(editingFinished()), this, SLOT(adjustFlowYUpper()));
    connect(flow_y_lower, SIGNAL(editingFinished()), this, SLOT(adjustFlowYLower()));
    connect(pres_y_upper, SIGNAL(editingFinished()), this, SLOT(adjustPresYUpper()));
    connect(pres_y_lower, SIGNAL(editingFinished()), this, SLOT(adjustPresYLower()));
    connect(flow_x_slider, SIGNAL(valueChanged(int)), this, SLOT(adjustFlowXAxis(int)));
    connect(pres_x_slider, SIGNAL(valueChanged(int)), this, SLOT(adjustPresXAxis(int)));
}

// #################### Private ###################
void DataGraph::createGuiItems()
{
    flow_x_slider->setOrientation(Qt::Horizontal);
    flow_x_slider->setRange(-100, -1);
    flow_x_slider->setValue(50);
    flow_y_auto->setChecked(true);

    flow_y_upper->setValidator(new QDoubleValidator());
    flow_y_lower->setValidator(new QDoubleValidator());
    flow_y_label_u->setText("Upper lim");
    flow_y_label_l->setText("Lower lim");
    flow_y_upper->hide();
    flow_y_lower->hide();

    pres_x_slider->setOrientation(Qt::Horizontal);
    pres_x_slider->setRange(-100, -1);
    pres_x_slider->setValue(50);
    pres_y_auto->setChecked(true);

    pres_y_upper->setValidator(new QDoubleValidator());
    pres_y_lower->setValidator(new QDoubleValidator());
    pres_y_label_u->setText("Upper lim");
    pres_y_label_l->setText("Lower lim");
    pres_y_upper->hide();
    pres_y_lower->hide();


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
    flow_y_widgets->addWidget(flow_y_lower);
    flow_y_widgets->addWidget(flow_y_label_l);
    flow_y_widgets->addWidget(flow_y_auto);
    flow_y_widgets->addWidget(flow_y_label_u);
    flow_y_widgets->addWidget(flow_y_upper);

    pres_y_widgets->addWidget(pres_y_lower);
    pres_y_widgets->addWidget(pres_y_label_l);
    pres_y_widgets->addWidget(pres_y_auto);
    pres_y_widgets->addWidget(pres_y_label_u);
    pres_y_widgets->addWidget(pres_y_upper);

    flow_vbox->addWidget(flow_x_slider);
    flow_vbox->addLayout(flow_y_widgets);
    flow_vbox->addWidget(flow_chartView);

    pres_vbox->addWidget(pres_x_slider);
    pres_vbox->addLayout(pres_y_widgets);
    pres_vbox->addWidget(press_chartView);

    graph_hbox->addLayout(flow_vbox);
    graph_hbox->addLayout(pres_vbox);

    for(QCheckBox *item : sensor_enableCheckboxes) {
        checkBox_hbox->addWidget(item);
    }

    vbox->addLayout(checkBox_hbox);
    vbox->addLayout(graph_hbox);

    this->setLayout(vbox);
}

void DataGraph::createFlowGraph()
{
    flow_chartView->setFixedSize(490, 310);

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
    press_chartView->setFixedSize(490, 310);

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

qreal DataGraph::getMaxFlowYRange()
{
    qreal maxVal = 0;
    for(int i = 0; i < 10; i++) {
        if(isLineSeriesFlow[i] && lineSeries[i]->isVisible()) {
            for(QPointF &val : lineSeries[i]->points()) {
                if (val.y() > maxVal) {
                    maxVal = val.y();
                }
            }
        }
    }
    return maxVal;
}

qreal DataGraph::getMinFlowYRange()
{
    qreal minVal = 1.7e300;
    for(int i = 0; i < 10; i++) {
        if(isLineSeriesFlow[i] && lineSeries[i]->isVisible()) {
            for(QPointF &val : lineSeries[i]->points()) {
                if (val.y() < minVal) {
                    minVal = val.y();
                }
            }
        }
    }
    return minVal;
}

qreal DataGraph::getMaxPresYRange()
{
    qreal maxVal = 0;
    for(int i = 0; i < 10; i++) {
        if(!isLineSeriesFlow[i] && lineSeries[i]->isVisible()) {
            for(QPointF &val : lineSeries[i]->points()) {
                if (val.y() > maxVal) {
                    maxVal = val.y();
                }
            }
        }
    }
    return maxVal;
}

qreal DataGraph::getMinPresYRange()
{
    qreal minVal = 1.7e300;
    for(int i = 0; i < 10; i++) {
        if(!isLineSeriesFlow[i] && lineSeries[i]->isVisible()) {
            for(QPointF &val : lineSeries[i]->points()) {
                if (val.y() < minVal) {
                    minVal = val.y();
                }
            }
        }
    }
    return minVal;
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
            isLineSeriesFlow[i] = true;
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
            isLineSeriesFlow[i+5] = true;
        } else {
            plotSensors[i+5] = false;
            sensor_enableCheckboxes[i+5]->setChecked(false);
            pressureChart->addSeries(lineSeries[i+5]);
        }
    }
    flowChart->createDefaultAxes();
    pressureChart->createDefaultAxes();

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
            lineSeries[i]->append(recentData[i]);
            if (lineSeries[i]->count()>500) {
                lineSeries[i]->remove(0);
            }
        }
    }
    flowChart->axisX()->setRange(recentData[0].x()+flow_x_slider->value(),
            recentData[0].x()+2);

    if(flow_y_auto->isChecked())
        flowAutoAdjustY(true);

    if(pres_y_auto->isChecked())
        presAutoAdjustY(true);
}

void DataGraph::plotMembersChanged(bool state)
{
    int i = 0;
    for(QCheckBox *item : sensor_enableCheckboxes) {
        plotSensors[i] = item->isChecked();
        i++;
    }
}

void DataGraph::flowAutoAdjustY(bool state)
{
    qreal max = getMaxFlowYRange();
    qreal min = getMinFlowYRange();

    if(max - min < MIN_FLOW_RES) {
        qreal avg = ((min + max) / 2.0);
        min = avg - 0.5 * static_cast<qreal>(MIN_FLOW_RES);
        max = avg + 0.5 * static_cast<qreal>(MIN_FLOW_RES);
    }

    if(state) {
        flow_y_upper->hide();
        flow_y_lower->hide();
    } else {
        flow_y_upper->show();
        flow_y_lower->show();
    }
    flow_y_upper->setText(QString::number(max));
    flow_y_lower->setText(QString::number(min));
    flowChart->axisY()->setRange(min, max);
}

void DataGraph::presAutoAdjustY(bool state)
{
    qreal max = getMaxPresYRange();
    qreal min = getMinPresYRange();

    if(max - min < MIN_PRES_RES) {
        qreal avg = ((min + max) / 2.0);
        min = avg - 0.5 * MIN_PRES_RES;
        max = avg + 0.5 * MIN_PRES_RES;
    }

    if(state) {
        pres_y_upper->hide();
        pres_y_lower->hide();
    } else {
        pres_y_upper->show();
        pres_y_lower->show();
    }

    pres_y_upper->setText(QString::number(max));
    pres_y_lower->setText(QString::number(min));
    pressureChart->axisY()->setRange(pres_y_lower->text().toDouble(), pres_y_upper->text().toDouble());
}

void DataGraph::adjustFlowYUpper()
{
    if(flow_y_upper->text().toDouble() < flow_y_lower->text().toDouble()) {
        flow_y_lower->setText(QString::number(flow_y_upper->text().toDouble() - 10));
    }
    flowChart->axisY()->setRange(flow_y_lower->text().toDouble(), flow_y_upper->text().toDouble());
}

void DataGraph::adjustFlowYLower()
{
    if(flow_y_lower->text().toDouble() > flow_y_upper->text().toDouble()) {
        flow_y_upper->setText(QString::number(flow_y_lower->text().toDouble() + 10));
    }
    flowChart->axisY()->setRange(flow_y_lower->text().toDouble(), flow_y_upper->text().toDouble());
}

void DataGraph::adjustPresYUpper()
{
    if(pres_y_upper->text().toDouble() < pres_y_lower->text().toDouble()) {
        pres_y_lower->setText(QString::number(pres_y_upper->text().toDouble() - 10));
    }
    pressureChart->axisY()->setRange(pres_y_lower->text().toDouble(), pres_y_upper->text().toDouble());
}

void DataGraph::adjustPresYLower()
{
    if(pres_y_lower->text().toDouble() > pres_y_upper->text().toDouble()) {
        pres_y_upper->setText(QString::number(pres_y_lower->text().toDouble() + 10));
    }
    pressureChart->axisY()->setRange(pres_y_lower->text().toDouble(), pres_y_upper->text().toDouble());
}
