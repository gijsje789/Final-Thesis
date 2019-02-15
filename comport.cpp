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

// #################### Signals ####################
// #################### Private slots ####################
void ComPort::selectComPort()
{
    SelectWindow = SelectWindow == nullptr ? new QWidget : SelectWindow;
    SelectWindow->setFixedSize(500, 250);
    ComPortSelectWindow *window = new ComPortSelectWindow(SelectWindow);
    connect(window, SIGNAL(ComPortSelected(QSerialPortInfo)), this, SLOT(setComPort(QSerialPortInfo)));
    SelectWindow->show();
}

void ComPort::setComPort(QSerialPortInfo comport)
{
    serial_port = new QSerialPort(comport, this);
    selectedPort_label->setText("Selected port: " + serial_port->portName());

    qDebug() << "Comport set: " << serial_port->portName();

    // Delete the dialog window.
    delete SelectWindow;
    SelectWindow = nullptr;
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
    for(int i = 0; i < serial_list.length(); i++){
        selected_port_comboBox->addItem(serial_list[i].portName());
    }

    emit updatePortInformation(selected_port_comboBox->currentIndex());
}
// #################### Signals ####################
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
