// analoguesensormenu.cpp - Implementation file for the AnalogueSensorMenu class.
// This class handles the appearance and functionality of the
// analogue sensor menus. The user can enter the sensors analogue
// characteristics.
// Date: 2019-02-07
// Created by: Gijs de Vries

#include "analoguesensormenu.h"

AnalogueSensorMenu::AnalogueSensorMenu(QString sensorNr, QWidget *parent)
    : QWidget(parent), sensorName(sensorNr)
{
    createGuiItems();
    createAndFillLayouts();

    connect(flow_radioButton, SIGNAL(toggled(bool)), this, SLOT(radiobuttonToggled(bool)));
    connect(enable_checkBox, SIGNAL(toggled(bool)), this, SLOT(enableCheckboxToggled(bool)));
}

// #################### Public functions ####################
// getMainLayout() returns the pointer such that an external widget
// can be filled with the buttons and fields needed to set the
// sensor.
QGridLayout* AnalogueSensorMenu::getMainLayout()
{
    return gridLayout;
}

aParams AnalogueSensorMenu::getParams()
{
    aType type = flow_radioButton->isChecked() ? aFlow : aPressure;
    double a_val = 0;
    double b_val = 0;

    QString a_unit = a_unit_comboBox->currentText();
    QString b_unit = b_unit_comboBox->currentText();

    if(type == aFlow) {
        if(a_unit == "V/L/min" || a_unit == "mV/mL/min") {
            // No conversion needed.
            a_val = a_val_lineEdit->text().toDouble();
        } else if(a_unit == "V/L/s" || a_unit == "mV/mL/s") {
            a_val = a_val_lineEdit->text().toDouble() * (1.0 / 60.0);
        } else if(a_unit == "V/mL/min") {
            a_val = a_val_lineEdit->text().toDouble() * (1000.0);
        } else if(a_unit == "V/mL/s") {
            a_val = a_val_lineEdit->text().toDouble() * (1000.0 / 60.0);
        } else if(a_unit == "mV/L/min") {
            a_val = a_val_lineEdit->text().toDouble() * (1.0 / 1000.0);
        } else if(a_unit == "mV/L/s") {
            a_val = a_val_lineEdit->text().toDouble() * (1.0 / 60000.0);
        } else {
            qDebug() << sensorName << "Unknown a unit";
        }
    } else if(type == aPressure) {
        if(a_unit == "V/psi") {
            a_val = a_val_lineEdit->text().toDouble() * (1.0 / 51.7149326);
        } else if(a_unit == "mV/psi"){
            a_val = a_val_lineEdit->text().toDouble() * (1.0 / 51714.9326);
        } else if(a_unit == "V/bar" || a_unit == "mV/mbar") {
            a_val = a_val_lineEdit->text().toDouble() * (1.0 / 750.061683);
        } else if(a_unit == "V/mbar") {
            a_val = a_val_lineEdit->text().toDouble() * (1000.0 / 750.061683);
        } else if(a_unit == "mV/bar") {
            a_val = a_val_lineEdit->text().toDouble() * (1.0 / 750061.683);
        } else if(a_unit == "V/mmHg") {
            // No conversion needed.
            a_val = a_val_lineEdit->text().toDouble();
        } else if(a_unit == "mV/mmHg") {
            a_val = a_val_lineEdit->text().toDouble() * (1.0 / 1000.0);
        } else {
            qDebug() << sensorName << "Unknown b unit";
        }
    } else {
        qDebug() << sensorName << "Unknown sensor type.";
    }

    if(b_unit == "V") {
        // No conversion needed.
        b_val = b_val_lineEdit->text().toDouble();
    } else if(b_unit == "mV"){
        b_val = b_val_lineEdit->text().toDouble() * (1.0 / 1000.0);
    }

    aParams params = {
        sensorName, enable_checkBox->isChecked(), type, a_val, b_val
    };
    return params;
}
// #################### Private functions ####################
void AnalogueSensorMenu::createGuiItems()
{
    // Create fillable a part.
    a_label->setText("a:");
    a_val_lineEdit->setValidator(new QDoubleValidator());
    a_val_lineEdit->setText("0");
    fillFlowComboBox();
    //fillPresComboBox();
    fillBComboBox();

    // Create fillable b part.
    b_label->setText("b:");
    b_val_lineEdit->setValidator(new QDoubleValidator());
    b_val_lineEdit->setText("0");

    // Create the exclusive radio buttons.
    flow_radioButton->setText("Flow");
    pres_radioButton->setText("Pressure");
    flow_radioButton->setCheckable(true);
    pres_radioButton->setCheckable(true);
    flow_radioButton->setChecked(true);

    // Create the enabled checkbox.
    enable_checkBox->setText("Enable");
    enable_checkBox->setChecked(false);
}

void AnalogueSensorMenu::createAndFillLayouts()
{
    // Add the radio buttons to their own layout.
    radio_vBox->addWidget(flow_radioButton);
    radio_vBox->addWidget(pres_radioButton);

    // Add the a fields to the main gridlayout.
    gridLayout->addWidget(a_label, 0, 0);
    gridLayout->addWidget(a_val_lineEdit, 0, 1, 1, 2);
    gridLayout->addWidget(a_unit_comboBox, 0, 3, 1, 2);

    // Add the b fields to the main gridlayout.
    gridLayout->addWidget(b_label, 1, 0);
    gridLayout->addWidget(b_val_lineEdit, 1, 1, 1, 2);
    gridLayout->addWidget(b_unit_comboBox, 1, 3, 1, 2);

    // Add the radio buttons layout and the checkbox to the main gridlayout.
    gridLayout->addLayout(radio_vBox, 2, 0, 2, 3);
    gridLayout->addWidget(enable_checkBox, 2, 3, 2, 2);

    // Disable the widgets.
    disableFields();

    // Set the layout of the widget to the gridlayout.
    this->setLayout(gridLayout);
}

void AnalogueSensorMenu::fillFlowComboBox()
{
    if(a_unit_comboBox->count() > 0)
        a_unit_comboBox->clear();

    for(const QString &item : a_flowItems) {
        a_unit_comboBox->addItem(item);
    }
}

void AnalogueSensorMenu::fillPresComboBox()
{
    if(a_unit_comboBox->count() > 0)
        a_unit_comboBox->clear();

    for(const QString &item : a_presItems) {
        a_unit_comboBox->addItem(item);
    }
}

void AnalogueSensorMenu::fillBComboBox()
{
    while(b_unit_comboBox->count() > 0) {
        b_unit_comboBox->removeItem(b_unit_comboBox->count());
    }

    for(const QString &item : b_Items) {
        b_unit_comboBox->addItem(item);
    }
}

void AnalogueSensorMenu::disableFields()
{
    // Disable a_fields
    a_label->setEnabled(false);
    a_val_lineEdit->setEnabled(false);
    a_unit_comboBox->setEnabled(false);

    // Disable b_fields
    b_label->setEnabled(false);
    b_val_lineEdit->setEnabled(false);
    b_unit_comboBox->setEnabled(false);

    // Disable radio buttons
    flow_radioButton->setEnabled(false);
    pres_radioButton->setEnabled(false);
}

void AnalogueSensorMenu::enableFields()
{
    // Enable a_fields
    a_label->setEnabled(true);
    a_val_lineEdit->setEnabled(true);
    a_unit_comboBox->setEnabled(true);

    // Enable b_fields
    b_label->setEnabled(true);
    b_val_lineEdit->setEnabled(true);
    b_unit_comboBox->setEnabled(true);

    // Enable radio buttons
    flow_radioButton->setEnabled(true);
    pres_radioButton->setEnabled(true);
}

// #################### Signals ####################
// #################### Private slots ####################
void AnalogueSensorMenu::radiobuttonToggled(bool flow_checked)
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

void AnalogueSensorMenu::enableCheckboxToggled(bool state)
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