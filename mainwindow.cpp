#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Set window size.
    setFixedSize(1024, 768);

    // Set a central widget in order to manipulate layouts.
    this->setCentralWidget(centralWidget);

    // Create widget for analogue sensor 1.
    an1_widget->setGeometry(10, 10, 984/3, 150);
    an1_widget->setLayout(an1_menu->getMainLayout());
}

MainWindow::~MainWindow()
{

}
