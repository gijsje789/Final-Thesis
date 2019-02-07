#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include "analoguesensormenu.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QWidget *centralWidget = new QWidget;
    QTabWidget *anSensors_tabWidget = new QTabWidget(centralWidget);
    QWidget *an1_widget = new QWidget;
    AnalogueSensorMenu *an1_menu = new AnalogueSensorMenu(an1_widget);
};

#endif // MAINWINDOW_H
