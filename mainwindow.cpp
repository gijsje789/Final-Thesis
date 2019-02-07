#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Set window size.
    setFixedSize(1024, 768);

    // Set a central widget in order to manipulate layouts.
    this->setCentralWidget(centralWidget);

    // Create widget for analogue sensor 1.
    //an1_widget->setLayout(an1_menu->getMainLayout());

    // Create tab widget and populate with analogue sensors.
    anSensors_tabWidget->setGeometry(10, 10, 984/3, 150);
    anSensors_tabWidget->addTab(an1_widget, "AN1");
    anSensors_tabWidget->addTab(an2_widget, "AN2");
    anSensors_tabWidget->addTab(an3_widget, "AN3");
    anSensors_tabWidget->addTab(an4_widget, "AN4");
    anSensors_tabWidget->addTab(an5_widget, "AN5");
}

MainWindow::~MainWindow()
{

}
