#ifndef DATAGRAPH_H
#define DATAGRAPH_H

#define MIN_FLOW_RES 100 //L/min //TODO: this
#define MIN_PRES_RES 100 //mmHg // TODO: this
#define MAX_PAST_S 60 // sec
#define MAX_PAST_VAL 600 // datapoints at 10Hz

#include <QWidget>

#include <QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QLegend>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QStringList>
#include <QString>
#include <QTimer>
#include <QSlider>
#include <QLineEdit>
#include <QDoubleValidator>
#include <QLabel>

#include "parameterinterface.h"

/**
 * @brief The DataGraph class handles all the visual aspects
 * as well as the functionality to plot received data.
 * \author Gijs de Vries
 * \date February 26, 2019
 */
class DataGraph : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief DataGraph The constructor for the DataGraph class.
     * @param parent The parent widget.
     */
    explicit DataGraph(QWidget *parent = nullptr);

    /**
     * @brief setParameterInterface Set the pointer to the ParameterInterface object in memory.
     * @param interface The pointer to the ParameterInterface object.
     */
    void setParameterInterface(ParameterInterface *pInterface);
private:
    // The layouts that are used.
    QVBoxLayout *vbox = new QVBoxLayout();

    // The charts to plot in.
    QChart *flowChart = new QChart(); /**< The QChart used to visualise the flow parameters. */
    QChart *pressureChart = new QChart(); /**< The QChart used to visualise the pressure parameters. */

    // The chart views that are populated with the charts.
    QChartView *flow_chartView = new QChartView(flowChart); /**< The QChartView that contains the flow QChart. */
    QChartView *press_chartView = new QChartView(pressureChart); /**< The QChartView that contains the pressure QChart. */

    QList<QCheckBox*> sensor_enableCheckboxes; /**< The QCheckBox pointers to enable plotting of datapoints. */

    QList<QLineSeries*> lineSeries; /**< A QLineSeries that contains the data of a line. */
    bool isLineSeriesFlow[10] = {false};

    QList<QPointF> recentData; /**< The QPoints containing the data that needs to be plotted. */

    QTimer *plotTimer = new QTimer; /**< The QTimer that triggers a plot at 10Hz. */

    bool plotSensors[10] = {false}; /**< A boolean array that contains true if the sensor is to be plotted.*/

    ParameterInterface *mInterface = nullptr;

    QSlider *flow_x_slider = new QSlider();
    QCheckBox *flow_y_auto = new QCheckBox();

    QLineEdit *flow_y_upper = new QLineEdit();
    QLineEdit *flow_y_lower = new QLineEdit();
    QLabel *flow_y_label_u = new QLabel();
    QLabel *flow_y_label_l = new QLabel();

    QSlider *pres_x_slider = new QSlider();
    QCheckBox *pres_y_auto = new QCheckBox();

    QHBoxLayout *flow_y_widgets = new QHBoxLayout();
    QHBoxLayout *pres_y_widgets = new QHBoxLayout();

    QLineEdit *pres_y_lower = new QLineEdit();
    QLineEdit *pres_y_upper = new QLineEdit();
    QLabel *pres_y_label_u = new QLabel();
    QLabel *pres_y_label_l = new QLabel();

    QVBoxLayout *flow_vbox = new QVBoxLayout();
    QVBoxLayout *pres_vbox = new QVBoxLayout();

    QHBoxLayout *graph_hbox = new QHBoxLayout(); /**< The main QHBoxLayout. */
    QHBoxLayout *checkBox_hbox = new QHBoxLayout();

    QList<QColor> plotColours = {
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
    /**
     * @brief createGuiItems Creates the GUI items that populate the MainWindow.
     */
    void createGuiItems();

    /**
     * @brief createAndFillLayouts Creates and fills the layouts with the widgets created in createGuiItems().
     */
    void createAndFillLayouts();

    void createFlowGraph();

    void createPressureGraph();

    void initialiseLineSeries();

    qreal getMaxFlowYRange();

    qreal getMinFlowYRange();

    qreal getMaxPresYRange();

    qreal getMinPresYRange();

    void removeAndCreateLineSeries();
signals:

public slots:
    /**
     * @brief dataReadyForPlot The callback function that receives the data from the ComPort class.
     * @param data The verified data that needs to be plotted.
     */
    void dataReadyForPlot(QStringList data);

    /**
     * @brief startPlotting The callback function that signals the set-up is ready and plotting needs to start.
     */
    void startPlotting();

    /**
     * @brief stopPlotting The callback function that signals that plotting must stop.
     */
    void stopPlotting();
private slots:
    /**
     * @brief plotData The callback function to periodically call to plot the data that is received.
     */
    void plotData();

    void plotMembersChanged();

    void flowAutoAdjustY(bool state);

    void presAutoAdjustY(bool state);

    void adjustFlowYUpper();

    void adjustFlowYLower();

    void adjustPresYUpper();

    void adjustPresYLower();
};

#endif // DATAGRAPH_H
