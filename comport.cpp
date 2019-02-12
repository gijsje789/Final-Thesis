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
    select_port_pushButton->setText("Select port");

    hbox_layout->addWidget(selected_port_comboBox);
    hbox_layout->addWidget(select_port_pushButton);

    this->setLayout(hbox_layout);
}
