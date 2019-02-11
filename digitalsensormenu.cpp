// digitalsensormenu.cpp - Implementation file for the DigitalSensorMenu class.
// This class handles the appearance and functionality of the
// digital sensor menus. The user can enter the digital sensor
// characteristics.
// Date: 2019-02-09
// Created by: Gijs de Vries

#include "digitalsensormenu.h"

DigitalSensorMenu::DigitalSensorMenu(QString sensorNr, QWidget *parent)
    : QWidget(parent), sensorName(sensorNr)
{
    createGuiItems();
    createAndFillLayout();

    connect(flow_radioButton, SIGNAL(toggled(bool)), this, SLOT(radiobuttonToggled(bool)));
    connect(enable_checkBox, SIGNAL(toggled(bool)), this, SLOT(enableCheckboxToggled(bool)));
}

// #################### Public functions ####################
// getMainLayout() returns the pointer such that an external widget
// can be filled with the buttons and fields needed to set the
// sensor.
QGridLayout* DigitalSensorMenu::getMainLayout()
{
    return gridLayout;
}

// #################### Private functions ####################
void DigitalSensorMenu::createGuiItems()
{
    // Create input part.
    input_label->setText("Output:");
    input_lineEdit->setValidator(new QDoubleValidator());
    input_lineEdit->setText("0");
    fillFlowComboBox();

    // Create the exclusive radio buttons.
    flow_radioButton->setText("Flow");
    pres_radioButotn->setText("Pressure");
    flow_radioButton->setCheckable(true);
    pres_radioButotn->setCheckable(true);
    flow_radioButton->setChecked(true);

    // Create the enabled checkbox.
    enable_checkBox->setText("Enable");
    enable_checkBox->setChecked(false);
}

void DigitalSensorMenu::createAndFillLayout()
{
    // Add the radio buttons to their own layout.
    radio_vBox->addWidget(flow_radioButton);
    radio_vBox->addWidget(pres_radioButotn);

    // Add the input fields to the main gridlayout.
    gridLayout->addWidget(input_label, 0, 0);
    gridLayout->addWidget(input_lineEdit, 0, 1, 1, 2);
    gridLayout->addWidget(input_comboBox, 0, 3, 1, 2);
    // Add a spacer to ensure empty row.
    gridLayout->addItem(empty_row, 1, 0, 1, 5);
    // Add the radio buttons layout and the checkbox to the main layout.
    gridLayout->addLayout(radio_vBox, 2, 0, 2, 3);
    gridLayout->addWidget(enable_checkBox, 2, 3, 2, 2);
    // Disable the widgets.
    disableFields();

    // Set the layout of the widget to the gridlayout. TODO: Needed?
    this->setLayout(gridLayout);
}

void DigitalSensorMenu::fillFlowComboBox()
{
    if(input_comboBox->count() > 0)
        input_comboBox->clear();

    for(const QString &item : flowItems) {
        input_comboBox->addItem(item);
    }
}

void DigitalSensorMenu::fillPresComboBox()
{
    if(input_comboBox->count() > 0)
        input_comboBox->clear();

    for(const QString &item : presItems) {
        input_comboBox->addItem(item);
     }
}

void DigitalSensorMenu::disableFields()
{
    // Disable input fields.
    input_label->setEnabled(false);
    input_lineEdit->setEnabled(false);
    input_comboBox->setEnabled(false);

    // Disable radio buttons.
    flow_radioButton->setEnabled(false);
    pres_radioButotn->setEnabled(false);
}

void DigitalSensorMenu::enableFields()
{
    // Enable input fields.
    input_label->setEnabled(true);
    input_lineEdit->setEnabled(true);
    input_comboBox->setEnabled(true);

    // Enable radio buttons.
    flow_radioButton->setEnabled(true);
    pres_radioButotn->setEnabled(true);
}

// #################### Signals ####################
// #################### Private slots ####################
void DigitalSensorMenu::radiobuttonToggled(bool flow_checked)
{
    if (flow_checked) {
        fillFlowComboBox();
        emit flowSensorCreated(sensorName);
    }
    else {
        fillPresComboBox();
        emit flowSensorDeleted(sensorName);
    }
}

void DigitalSensorMenu::enableCheckboxToggled(bool state)
{
    if (state) {
        enableFields();
        if (flow_radioButton->isChecked())
                    emit flowSensorCreated(sensorName);
        else
                    emit flowSensorDeleted(sensorName);
    }
    else {
        disableFields();
        if (flow_radioButton->isChecked())
                    emit flowSensorDeleted(sensorName);
    }
}

// #################### Public slots ####################
