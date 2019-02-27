
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define WINDOW_W 1024
#define WINDOW_H 768
#define WIDGET_SPACE 10
#define SMENU_H 150
#define COM_H 40
#define PLOT_H 398

#include <QMainWindow>
#include <QObject>
#include <QTabWidget>
#include "analoguesensormenu.h"
#include "digitalsensormenu.h"
#include "pumpmenu.h"
#include "comport.h"
#include "fileoperation.h"
#include "maincontrols.h"
#include "parameterinterface.h"
#include "datagraph.h"

/**
 * @brief The MainWindow class
 *
 * The main class that takes care of the population of the main window with widgets.
 * \author Gijs de Vries
 * \date February 7, 2019
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief MainWindow constructor.
     *
     * Creates the main window and populates it with widgets.
     * @param parent Parent of the widget. If the parent is destroyed, so is the MainWindow.
     */
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QWidget *centralWidget = new QWidget; /**< The central widget that is the parent for all other widgets. */

    // Create the tab widgets for the analogue and digital sensors.
    QTabWidget *anSensors_tabWidget = new QTabWidget(centralWidget); /**< The tab-widget where all 5 analogue sensor menus are placed. */
    QTabWidget *dSensors_tabWidget = new QTabWidget(centralWidget); /**< The tab-widget where all 5 digital sensor menus are placed. */
    QTabWidget *pump_tabWidget = new QTabWidget(centralWidget); /**< The tab-widget where all 4 pump menus are placed. */

    QWidget *comport_widget = new QWidget(centralWidget); /**< The COM-port widget where the fields necessary to select the COM port are placed. */
    ComPort *comport_menu = new ComPort(comport_widget); /**< The actual class object that creates the fields and handles all the functionality necessary to select the COM port and communicate with the serial device. */

    QWidget *file_widget = new QWidget(centralWidget); /**< The file widget where the fields necessary to define the output file are placed. */
    FileOperation *file_menu = new FileOperation(file_widget); /**< The actual class object that creates the fields and handles all the functionality necessary to select and use the output file. */

    QWidget *mainControl_widget = new QWidget(centralWidget);
    MainControls *mainControl_menu = new MainControls(mainControl_widget);

    QWidget *plot_widget = new QWidget(centralWidget);
    DataGraph *graphs = new DataGraph(plot_widget);

    // Create the widgets that populate the tab widgets.
    QWidget *an1_widget = new QWidget; /**< The widget that will parent the analogue sensor 1 menu. */
    QWidget *an2_widget = new QWidget; /**< The widget that will parent the analogue sensor 2 menu. */
    QWidget *an3_widget = new QWidget; /**< The widget that will parent the analogue sensor 3 menu. */
    QWidget *an4_widget = new QWidget; /**< The widget that will parent the analogue sensor 4 menu. */
    QWidget *an5_widget = new QWidget; /**< The widget that will parent the analogue sensor 5 menu. */

    QWidget *d1_widget = new QWidget; /**< The widget that will parent the digital sensor 1 menu. */
    QWidget *d2_widget = new QWidget; /**< The widget that will parent the digital sensor 2 menu. */
    QWidget *d3_widget = new QWidget; /**< The widget that will parent the digital sensor 3 menu. */
    QWidget *d4_widget = new QWidget; /**< The widget that will parent the digital sensor 4 menu. */
    QWidget *d5_widget = new QWidget; /**< The widget that will parent the digital sensor 5 menu. */

    QWidget *p1_widget = new QWidget; /**< The widget that will parent the pump 1 menu. */
    QWidget *p2_widget = new QWidget; /**< The widget that will parent the pump 2 menu. */
    QWidget *p3_widget = new QWidget; /**< The widget that will parent the pump 3 menu. */
    QWidget *p4_widget = new QWidget; /**< The widget that will parent the pump 4 menu. */

    // Create the sensor menus.
    AnalogueSensorMenu *an1_menu = new AnalogueSensorMenu("A1", an1_widget); /**< The actual class objects that creates the fields and handles all the functionality to define analogue sensor 1. */
    AnalogueSensorMenu *an2_menu = new AnalogueSensorMenu("A2", an2_widget); /**< The actual class objects that creates the fields and handles all the functionality to define analogue sensor 2. */
    AnalogueSensorMenu *an3_menu = new AnalogueSensorMenu("A3", an3_widget); /**< The actual class objects that creates the fields and handles all the functionality to define analogue sensor 3. */
    AnalogueSensorMenu *an4_menu = new AnalogueSensorMenu("A4", an4_widget); /**< The actual class objects that creates the fields and handles all the functionality to define analogue sensor 4. */
    AnalogueSensorMenu *an5_menu = new AnalogueSensorMenu("A5", an5_widget); /**< The actual class objects that creates the fields and handles all the functionality to define analogue sensor 5. */

    DigitalSensorMenu *d1_menu = new DigitalSensorMenu("D1", d1_widget); /**< The actual class objects that creates the fields and handles all the functionality to define digital sensor 1. */
    DigitalSensorMenu *d2_menu = new DigitalSensorMenu("D2", d2_widget); /**< The actual class objects that creates the fields and handles all the functionality to define digital sensor 2. */
    DigitalSensorMenu *d3_menu = new DigitalSensorMenu("D3", d3_widget); /**< The actual class objects that creates the fields and handles all the functionality to define digital sensor 3. */
    DigitalSensorMenu *d4_menu = new DigitalSensorMenu("D4", d4_widget); /**< The actual class objects that creates the fields and handles all the functionality to define digital sensor 4. */
    DigitalSensorMenu *d5_menu = new DigitalSensorMenu("D5", d5_widget); /**< The actual class objects that creates the fields and handles all the functionality to define digital sensor 5. */

    PumpMenu *p1_menu = new PumpMenu("P1", p1_widget); /**< The actual class objects that creates the fields and handles all the functionality to define pump 1. */
    PumpMenu *p2_menu = new PumpMenu("P2", p2_widget); /**< The actual class objects that creates the fields and handles all the functionality to define pump 2. */
    PumpMenu *p3_menu = new PumpMenu("P3", p3_widget); /**< The actual class objects that creates the fields and handles all the functionality to define pump 3. */
    PumpMenu *p4_menu = new PumpMenu("P4", p4_widget); /**< The actual class objects that creates the fields and handles all the functionality to define pump 4. */

    ParameterInterface *param_interface = new ParameterInterface;

    /**
     * @brief connectWidgets Connects the signals from its children widgets to each other.
     */
    void connectWidgets();

    /**
     * @brief initialiseParamInterface Initialises the ParameterInterface object.
     */
    void initialiseParamInterface();
};

#endif // MAINWINDOW_H
