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
    QWidget *an2_widget = new QWidget;
    QWidget *an3_widget = new QWidget;
    QWidget *an4_widget = new QWidget;
    QWidget *an5_widget = new QWidget;
    AnalogueSensorMenu *an1_menu = new AnalogueSensorMenu(an1_widget);
    AnalogueSensorMenu *an2_menu = new AnalogueSensorMenu(an2_widget);
    AnalogueSensorMenu *an3_menu = new AnalogueSensorMenu(an3_widget);
    AnalogueSensorMenu *an4_menu = new AnalogueSensorMenu(an4_widget);
    AnalogueSensorMenu *an5_menu = new AnalogueSensorMenu(an5_widget);
};

#endif // MAINWINDOW_H
