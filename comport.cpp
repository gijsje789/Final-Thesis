// comport.cpp - Implementation file for the comport class.
// This class handles the appearance and functionality of the
// comport menu. Als implements the communication between
// arduino and pc.
// Date: 2019-02-11
// Created by: Gijs de Vries

#include "comport.h"

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

}
// #################### Public slots ####################
