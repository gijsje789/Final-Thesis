// mainwindow.cpp - Implementation file for the main window of the app.
// Date: 2019-02-07
// Created by: Gijs de Vries

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Set window size.
    setFixedSize(1024, 768);

    // Set a central widget in order to manipulate layouts.
    this->setCentralWidget(centralWidget);

    // Create tab widget and populate with analogue sensors.
    anSensors_tabWidget->setGeometry(10, 10, 984/3, 150);
    anSensors_tabWidget->addTab(an1_widget, "AN1");
    anSensors_tabWidget->addTab(an2_widget, "AN2");
    anSensors_tabWidget->addTab(an3_widget, "AN3");
    anSensors_tabWidget->addTab(an4_widget, "AN4");
    anSensors_tabWidget->addTab(an5_widget, "AN5");

    dSensors_tabWidget->setGeometry(348, 10, 984/3, 150);
    dSensors_tabWidget->addTab(d1_widget, "D1");
    dSensors_tabWidget->addTab(d2_widget, "D2");
    dSensors_tabWidget->addTab(d3_widget, "D3");
    dSensors_tabWidget->addTab(d4_widget, "D4");
    dSensors_tabWidget->addTab(d5_widget, "D5");
}

MainWindow::~MainWindow()
{

}
