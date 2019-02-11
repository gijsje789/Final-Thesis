// mainwindow.cpp - Implementation file for the main window of the app.
// Date: 2019-02-07
// Created by: Gijs de Vries

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Set window size.
    setFixedSize(WINDOW_W, WINDOW_H);

    // Set a central widget in order to manipulate layouts.
    this->setCentralWidget(centralWidget);

    // Create tab widget and populate with analogue sensors.
    anSensors_tabWidget->setGeometry(WIDGET_SPACE, WIDGET_SPACE, (WINDOW_W-4*WIDGET_SPACE)/3, 150);
    anSensors_tabWidget->addTab(an1_widget, "AN1");
    anSensors_tabWidget->addTab(an2_widget, "AN2");
    anSensors_tabWidget->addTab(an3_widget, "AN3");
    anSensors_tabWidget->addTab(an4_widget, "AN4");
    anSensors_tabWidget->addTab(an5_widget, "AN5");

    dSensors_tabWidget->setGeometry(2*WIDGET_SPACE + ((WINDOW_W-4*WIDGET_SPACE)/3), WIDGET_SPACE, (WINDOW_W-4*WIDGET_SPACE)/3, 150);
    dSensors_tabWidget->addTab(d1_widget, "D1");
    dSensors_tabWidget->addTab(d2_widget, "D2");
    dSensors_tabWidget->addTab(d3_widget, "D3");
    dSensors_tabWidget->addTab(d4_widget, "D4");
    dSensors_tabWidget->addTab(d5_widget, "D5");

    pump_tabWidget->setGeometry(3*WIDGET_SPACE + 2*((WINDOW_W-4*WIDGET_SPACE)/3), WIDGET_SPACE, (WINDOW_W-4*WIDGET_SPACE)/3, 150);
    pump_tabWidget->addTab(p1_widget, "P1");
    pump_tabWidget->addTab(p2_widget, "P2");
    pump_tabWidget->addTab(p3_widget, "P3");
    pump_tabWidget->addTab(p4_widget, "P4");

    connect(d1_menu, SIGNAL(flowSensorCreated(QString)), p1_menu, SLOT(addSensorToComboBox(QString)));
}

MainWindow::~MainWindow()
{

}
