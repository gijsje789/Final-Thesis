#ifndef DATAGRAPH_H
#define DATAGRAPH_H

#include <QWidget>

#include <QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QLegend>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>

#include <QHBoxLayout>

#include <QStringList>
#include <QString>

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

private:
    // The layouts that are used.
    QHBoxLayout *hbox = new QHBoxLayout(); /**< The main QHBoxLayout. */

    // The charts to plot in.
    QChart *flowChart = new QChart(); /**< The QChart used to visualise the flow parameters. */
    QChart *pressureChart = new QChart(); /**< The QChart used to visualise the pressure parameters. */

    // The chart views that are populated with the charts.
    QChartView *flow_chartView = new QChartView(flowChart); /**< The QChartView that contains the flow QChart. */
    QChartView *press_chartView = new QChartView(pressureChart); /**< The QChartView that contains the pressure QChart. */

    QLineSeries *lineSeries = new QLineSeries(); /**< A QLineSeries that contains the data of a line. */

    /**
     * @brief createGuiItems Creates the GUI items that populate the MainWindow.
     */
    void createGuiItems();

    /**
     * @brief createAndFillLayouts Creates and fills the layouts with the widgets created in createGuiItems().
     */
    void createAndFillLayouts();
signals:

public slots:
    /**
     * @brief dataReadyForPlot The callback function that receives the data from the ComPort class.
     * @param data The verified data that needs to be plotted.
     */
    void dataReadyForPlot(QStringList data);
};

#endif // DATAGRAPH_H
