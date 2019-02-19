// comport.cpp - Implementation file for the comport class.
// This class handles the appearance and functionality of the
// comport menu. Als implements the communication between
// arduino and pc.
// Date: 2019-02-11
// Created by: Gijs de Vries

#include "comport.h"

#include <QDebug>

ComPort::ComPort(QWidget *parent) : QWidget(parent)
{
    createGuiItems();

    connect(selectPort_pushButton, SIGNAL(clicked()), this, SLOT(selectComPort()));
}

// #################### Private functions ####################
void ComPort::createGuiItems()
{
    // Create the push button.
    selectPort_pushButton->setText("Select COM port");
    selectPort_pushButton->setGeometry(0,0, 200, 50);
    selectPort_pushButton->setFixedWidth(150);

    // Create the label.
    selectedPort_label->setText("Selected port: ");
    selectedPort_label->setFixedWidth(150);

    createAndFillLayouts();
}

void ComPort::createAndFillLayouts()
{
    // Fill the horizontal layout.
    hboxLayout->addWidget(selectedPort_label);
    hboxLayout->addWidget(selectPort_pushButton);

    // Set the horizontal layout as the main layout.
    this->setLayout(hboxLayout);
}

void ComPort::deleteComPort()
{
    delete serial_port;
    serial_port = nullptr;
    qDebug() << "COM-port is deleted.";
}

void ComPort::deleteTimer()
{
    delete timer;
    timer = new QTimer(this);
    qDebug() << "COM-port timer is deleted.";
}

// #################### Signals ####################
// #################### Public slots ###############
void ComPort::initialiseComPort()
{
    if (serial_port != nullptr) {
        if (serial_port->open(QIODevice::ReadWrite)) {
            if (serial_port->setBaudRate(BAUDRATE)) {
                timer->stop();
                delete timer;
                timer = new QTimer(this);
                timer->start(POLL_INPUT_TIME);
                connect(timer, SIGNAL(timeout()), this, SLOT(checkInputBuffer()));
                connect(serial_port, SIGNAL(errorOccurred(QSerialPort::SerialPortError)), this, SLOT(serialErrorOccurred(QSerialPort::SerialPortError)));
                comPortSuccess("Connected");
            } else {
                emit comPortFailure("CPERR-003");
            }
        } else {
            emit comPortFailure("CPERR-002");
        }
    } else {
        emit comPortFailure("CPERR-001");
    }
}
// #################### Private slots ####################
void ComPort::selectComPort()
{
    SelectWindow->setFixedSize(500, 250);
    ComPortSelectWindow *window = new ComPortSelectWindow(SelectWindow);
    connect(window, SIGNAL(ComPortSelected(QSerialPortInfo)), this, SLOT(setComPort(QSerialPortInfo)));
    SelectWindow->show();
}

void ComPort::setComPort(QSerialPortInfo comport)
{
    serial_port = new QSerialPort(comport, this);
    selectedPort_label->setText("Selected port: " + serial_port->portName());

    qDebug() << "COM-port set: " << serial_port->portName();

    connect(timer, SIGNAL(timeout()), this, SLOT(checkComPortStatus()));
    timer->start(500);
    qDebug() << "COM-port will be periodically checked.";

    // Delete the dialog window.
    delete SelectWindow;
    SelectWindow = new QWidget;
}

void ComPort::checkComPortStatus()
{
    QSerialPortInfo *info = new QSerialPortInfo;
    QList<QSerialPortInfo> list = info->availablePorts();
    bool port_still_available = false;

    for (QSerialPortInfo &port : list) {
        if (port.portName() == serial_port->portName())
            port_still_available = true;
    }

    if (!port_still_available) {
        qDebug() << "Selected COM-port," << serial_port->portName() << ", no longer available!";

        deleteComPort();
        deleteTimer();

        selectedPort_label->setText("Error: disconnected");
    }
}

void ComPort::checkInputBuffer()
{
    if (serial_port->bytesAvailable() > 0) {
        qDebug() << serial_port->bytesAvailable();
        QString *data = new QString(serial_port->readAll());
        qDebug() << serial_port->bytesAvailable();
        emit recordData(*data);
    }
    //qDebug() << "Checking input buffer: " << serial_port->bytesAvailable();
}

void ComPort::serialErrorOccurred(QSerialPort::SerialPortError error)
{
    qDebug() << "Error occured in COM-port: " << error;
    emit comPortFailure("CPERR-004");

    deleteComPort();
    deleteTimer();

    selectedPort_label->setText("Error: disconnected");
}
// #################### Public slots ####################

// #########################################################
// #########################################################
// #################### ComPortSelectWindow ################
// #########################################################
// #########################################################
ComPortSelectWindow::ComPortSelectWindow(QWidget *parent)
    : QWidget(parent)
{
    createGuiItems();
    createAndFillLayouts();

    connect(selected_port_comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updatePortInformation(int)));
    connect(timer, SIGNAL(timeout()), this, SLOT(refreshComPortList()));
    connect(select_port_pushButton, SIGNAL(clicked()), this, SLOT(selectPortButtonPressed()));
    timer->start(500);

    getAvailablePorts();
}

// #################### Private functions ####################
void ComPortSelectWindow::createGuiItems()
{
    // Create the push button.
    select_port_pushButton->setText("Select port");

    // Create the labels.
    portName_label->setText("Port: ");
    portName_label->setFixedSize(400, 40);
    manuName_label->setText("Manufacturer: ");
    manuName_label->setFixedSize(400, 40);
    descript_label->setText("Description: ");
    descript_label->setFixedSize(400, 40);
}

void ComPortSelectWindow::createAndFillLayouts()
{
    // Fill the horizontal layout
    hbox_pushCombo->addWidget(selected_port_comboBox);
    hbox_pushCombo->addWidget(select_port_pushButton);

    // Fill the vertical layout
    vbox_main->addLayout(hbox_pushCombo);
    vbox_main->addWidget(portName_label);
    vbox_main->addWidget(manuName_label);
    vbox_main->addWidget(descript_label);

    this->setLayout(vbox_main);
}

void ComPortSelectWindow::getAvailablePorts()
{
    QSerialPortInfo *info = new QSerialPortInfo;
    serial_list = info->availablePorts();

    selected_port_comboBox->clear();
    for(QSerialPortInfo &item :  serial_list){
        selected_port_comboBox->addItem(item.portName());
    }

    emit updatePortInformation(selected_port_comboBox->currentIndex());
}
// #################### Signals ##########################
// #################### Public slots #####################
// #################### Private slots ####################
void ComPortSelectWindow::updatePortInformation(int index)
{
    if (index < serial_list.length() && index >= 0) {
        portName_label->setText("Port: " + serial_list[index].portName());
        manuName_label->setText("Manufacturer: " + serial_list[index].manufacturer());
        descript_label->setText("Description: " + serial_list[index].description());
    }
    else {
        portName_label->setText("Port: ");
        manuName_label->setText("Manufacturer: ");
        descript_label->setText("Description: ");
    }
}

void ComPortSelectWindow::refreshComPortList()
{
    QSerialPortInfo *info = new QSerialPortInfo;
    QList<QSerialPortInfo> temp = info->availablePorts();

    if (temp.length() != serial_list.length()) {
        getAvailablePorts();
    }
}

void ComPortSelectWindow::selectPortButtonPressed()
{
    if (serial_list.length()>0)
        emit ComPortSelected(serial_list[selected_port_comboBox->currentIndex()]);
    else
        portName_label->setText("Port: ERROR NO PORT SELECTED!");
}
