#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "analoguesensormenu.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QWidget *centralWidget = new QWidget;
    QWidget *an1_widget = new QWidget(centralWidget);
    AnalogueSensorMenu *an1_menu = new AnalogueSensorMenu(an1_widget);
};

#endif // MAINWINDOW_H
