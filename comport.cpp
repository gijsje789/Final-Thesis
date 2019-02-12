// comport.cpp - Implementation file for the comport class.
// This class handles the appearance and functionality of the
// comport menu. Als implements the communication between
// arduino and pc.
// Date: 2019-02-11
// Created by: Gijs de Vries

#include "comport.h"

#include <QDebug>
#include <QtSerialPort/QSerialPortInfo>
#include <QList>

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
    selectedPort_label->setFixedWidth(100);

    createAndFillLayouts();
}

void ComPort::createAndFillLayouts()
{
    // Fill the horizontal layout.
    hboxLayout->addWidget(selectPort_pushButton);
    hboxLayout->addWidget(selectedPort_label);

    // Set the horizontal layout as the main layout.
    this->setLayout(hboxLayout);
}

// #################### Signals ####################
// #################### Private slots ####################
void ComPort::selectComPort()
{
    QWidget *SelectWindow = new QWidget;
    SelectWindow->setFixedSize(500, 500);
    ComPortSelectWindow *select = new ComPortSelectWindow(SelectWindow);
    SelectWindow->show();
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

    QSerialPortInfo *info = new QSerialPortInfo;
    QList<QSerialPortInfo> list = info->availablePorts();
    qDebug() << "List" << list.length();
    for(int i = 0; i < list.length(); i++){
        selected_port_comboBox->addItem(list[i].portName());
    }
    if (list.length()>0) {
        portName_label->setText("Port: " + list[0].portName());
        manuName_label->setText("Manufacturer: " + list[0].manufacturer());
        descript_label->setText("Description: " + list[0].description());
    }
}

void ComPortSelectWindow::createGuiItems()
{
    // Create the push button.
    select_port_pushButton->setText("Select port");

    // Create the labels.
    portName_label->setText("Port: ");
    manuName_label->setText("Manufacturer: ");
    descript_label->setText("Description: ");
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
