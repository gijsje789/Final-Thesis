// comport.h - Header file for the comport class.
// This class handles the appearance and functionality of the
// comport menu. Als implements the communication between
// arduino and pc.
// Date: 2019-02-11
// Created by: Gijs de Vries

#ifndef COMPORT_H
#define COMPORT_H

#include <QSizePolicy>

#include <QWidget>
#include <QWindow>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>

#include <QtSerialPort/QSerialPortInfo>
#include <QList>
#include <QTimer>

class ComPort : public QWidget
{
    Q_OBJECT
public:
    explicit ComPort(QWidget *parent = nullptr);

private:
    // Layouts that are used.
    QHBoxLayout *hboxLayout = new QHBoxLayout;
    // Input fields.
    QPushButton *selectPort_pushButton = new QPushButton;
    QLabel *selectedPort_label = new QLabel;

    void createGuiItems();
    void createAndFillLayouts();
signals:

private slots:
    void selectComPort();
public slots:
};

class ComPortSelectWindow : public QWidget{
    Q_OBJECT
public:
    explicit ComPortSelectWindow(QWidget *parent = nullptr);
private:
    // Layouts to be used.
    QHBoxLayout *hbox_pushCombo = new QHBoxLayout;
    QVBoxLayout *vbox_main = new QVBoxLayout;
    // User widgets
    QComboBox *selected_port_comboBox = new QComboBox;
    QPushButton *select_port_pushButton = new QPushButton;
    // Information widgets.
    QLabel *portName_label = new QLabel;
    QLabel *manuName_label = new QLabel;
    QLabel *descript_label = new QLabel;
    // List containing all devices.
    QList<QSerialPortInfo> serial_list;
    // Timer to refresh serial list.
    QTimer *timer = new QTimer(this);

    void createGuiItems();
    void createAndFillLayouts();
    void getAvailablePorts();
private slots:
    void updatePortInformation(int index);
    void refreshComPortList();
};

#endif // COMPORT_H
