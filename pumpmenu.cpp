// pumpmenu.cpp - Implementation file for the PumpMeny class.
// This class handles the appearance and functionality of the
// pump menus. The user can enter the flow rate and feedback
// sensor.
// Date: 2019-02-09
// Created by: Gijs de Vries

#include "pumpmenu.h"

PumpMenu::PumpMenu(QWidget *parent) : QWidget(parent)
{
    createGuiItems();
    createAndFillLayouts();

    connect(enable_checkBox, SIGNAL(toggled(bool)), this, SLOT(enableCheckboxToggled(bool)));
}

// #################### Public functions ####################
// getMainLayout() returns the pointer such that an external widget
// can be filled with the buttons and fields needed to set the
// sensor.
QGridLayout* PumpMenu::getMainLayout()
{
    return gridLayout;
}

// #################### Private functions ####################
void PumpMenu::createGuiItems()
{
    // Create input fields.
    pumpRate_label->setText("Pump rate:");
    pumpRate_lineEdit->setValidator(new QDoubleValidator);
    pumpRate_lineEdit->setText("0");
    pumpRate_unit_label->setText("L/min");

    // Create feedback fields.
    feedback_label->setText("Feedback sensor:");

    // Create push button.
    update_pushButton->setText("Update pump rate");

    // Create enable checkbox.
    enable_checkBox->setText("Enable");
    enable_checkBox->setChecked(false);
}

void PumpMenu::createAndFillLayouts()
{
    // Add the pump rate input fields to gridlayout.
    gridLayout->addWidget(pumpRate_label, 0, 0);
    gridLayout->addWidget(pumpRate_lineEdit, 0, 1, 1, 2);
    gridLayout->addWidget(pumpRate_unit_label, 0, 3, 1, 2);

    // Add the feedbacksensor to gridlayout.
    gridLayout->addWidget(feedback_label, 1, 0, 1, 3);
    gridLayout->addWidget(feedback_comboBox, 1, 2, 1, 1);

    gridLayout->addItem(empty_row, 2, 0, 1, 5);

    // Add the push button to gridlayout.
    gridLayout->addWidget(update_pushButton, 3, 0, 1, 3);

    // Add the enable checkbox.
    gridLayout->addWidget(enable_checkBox, 3, 3, 1, 2);

    // Disable the widgets.
    disableFields();

    // Set the layout of the widget to the gridlayout. TODO: needed?
    this->setLayout(gridLayout);
}

void PumpMenu::disableFields()
{
    // Disable pump rate input fields.
    pumpRate_label->setEnabled(false);
    pumpRate_lineEdit->setEnabled(false);
    pumpRate_unit_label->setEnabled(false);

    // Disable feedback fields.
    feedback_label->setEnabled(false);
    feedback_comboBox->setEnabled(false);

    // Disable push button
    update_pushButton->setEnabled(false);
}

void PumpMenu::enableFields()
{
    // Enable pump rate input fields.
    pumpRate_label->setEnabled(true);
    pumpRate_lineEdit->setEnabled(true);
    pumpRate_unit_label->setEnabled(true);

    // Enable feedback fields.
    feedback_label->setEnabled(true);
    feedback_comboBox->setEnabled(true);

    // Enable push button
    update_pushButton->setEnabled(true);
}

// #################### Signals ####################
// #################### Private slots ####################
void PumpMenu::enableCheckboxToggled(bool state)
{
    if (state)
        enableFields();
    else
        disableFields();
    qDebug() << pumpRate_label->width() << pumpRate_lineEdit->width() << pumpRate_unit_label->width() << gridLayout->horizontalSpacing();
    qDebug() << feedback_label->width() << feedback_comboBox->width();
}
// #################### Public slots ####################
void PumpMenu::addSensorToComboBox(QString sensor)
{
    feedback_comboBox->addItem(sensor);
}

void PumpMenu::removeSensorFromComboBox()
{

}
