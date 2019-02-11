// mainwindow.h - Header file for the main window of the app.
// Date: 2019-02-07
// Created by: Gijs de Vries

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define WINDOW_W 1024
#define WINDOW_H 768
#define WIDGET_SPACE 10

#include <QMainWindow>
#include <QObject>
#include <QTabWidget>
#include "analoguesensormenu.h"
#include "digitalsensormenu.h"
#include "pumpmenu.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QWidget *centralWidget = new QWidget;

    // Create the tab widgets for the analogue and digital sensors.
    QTabWidget *anSensors_tabWidget = new QTabWidget(centralWidget);
    QTabWidget *dSensors_tabWidget = new QTabWidget(centralWidget);
    QTabWidget *pump_tabWidget = new QTabWidget(centralWidget);

    // Create the widgets that populate the tab widget.
    QWidget *an1_widget = new QWidget;
    QWidget *an2_widget = new QWidget;
    QWidget *an3_widget = new QWidget;
    QWidget *an4_widget = new QWidget;
    QWidget *an5_widget = new QWidget;

    QWidget *d1_widget = new QWidget;
    QWidget *d2_widget = new QWidget;
    QWidget *d3_widget = new QWidget;
    QWidget *d4_widget = new QWidget;
    QWidget *d5_widget = new QWidget;

    QWidget *p1_widget = new QWidget;
    QWidget *p2_widget = new QWidget;
    QWidget *p3_widget = new QWidget;
    QWidget *p4_widget = new QWidget;

    // Create the sensor menus.
    AnalogueSensorMenu *an1_menu = new AnalogueSensorMenu(an1_widget);
    AnalogueSensorMenu *an2_menu = new AnalogueSensorMenu(an2_widget);
    AnalogueSensorMenu *an3_menu = new AnalogueSensorMenu(an3_widget);
    AnalogueSensorMenu *an4_menu = new AnalogueSensorMenu(an4_widget);
    AnalogueSensorMenu *an5_menu = new AnalogueSensorMenu(an5_widget);

    DigitalSensorMenu *d1_menu = new DigitalSensorMenu("D1", d1_widget);
    DigitalSensorMenu *d2_menu = new DigitalSensorMenu("D2", d2_widget);
    DigitalSensorMenu *d3_menu = new DigitalSensorMenu("D3", d3_widget);
    DigitalSensorMenu *d4_menu = new DigitalSensorMenu("D4", d4_widget);
    DigitalSensorMenu *d5_menu = new DigitalSensorMenu("D5", d5_widget);

    PumpMenu *p1_menu = new PumpMenu(p1_widget);
    PumpMenu *p2_menu = new PumpMenu(p2_widget);
    PumpMenu *p3_menu = new PumpMenu(p3_widget);
    PumpMenu *p4_menu = new PumpMenu(p4_widget);

    void connectWidgets();
};

#endif // MAINWINDOW_H
