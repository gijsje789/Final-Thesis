#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedSize(1024, 768);
    this->setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{

}
