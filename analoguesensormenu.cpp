#include "analoguesensormenu.h"

AnalogueSensorMenu::AnalogueSensorMenu(QWidget *parent) : QWidget(parent)
{
    // Create fillable a part.
    a_label->setText("a");
    a_val_lineEdit->setValidator(new QDoubleValidator());
    a_val_lineEdit->setText("0");

    // Create fillable b part.
    b_label->setText("b");
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
    enable_checkBox->setTristate(false);

    // Add the radio buttons to their own layout.
    radio_vBox->addWidget(flow_radioButton);
    radio_vBox->addWidget(pres_radioButton);

    // Add the a fields to the main gridlayout.
    gridLayout->addWidget(a_label, 1, 1);
    gridLayout->addWidget(a_val_lineEdit, 1, 2, 1, 2);
    gridLayout->addWidget(a_unit_comboBox, 1, 4, 1, 2);

    // Add the b fields to the main gridlayout.
    gridLayout->addWidget(b_label, 2, 1);
    gridLayout->addWidget(b_val_lineEdit, 2, 2, 1, 2);
    gridLayout->addWidget(b_unit_comboBox, 2, 4, 1, 2);

    // Add the radio buttons layout and the checkbox to the main gridlayout.
    gridLayout->addLayout(radio_vBox, 3, 1, 2, 3);
    gridLayout->addWidget(enable_checkBox, 3, 4, 2, 2);

    // Set the layout of the widget to the gridlayout.
    this->setLayout(gridLayout);

    connect(flow_radioButton, SIGNAL(toggled(bool)), this, SLOT(radiobuttonToggled(bool)));
    connect(enable_checkBox, SIGNAL(stateChanged(int)), this, SLOT(enableCheckboxStateChanged(int)));
}

QGridLayout* AnalogueSensorMenu::getMainLayout()
{
    return gridLayout;
}

void AnalogueSensorMenu::radiobuttonToggled(bool flow_checked)
{
    qDebug() << "radiobutton toggled." << this << flow_checked;
}

void AnalogueSensorMenu::enableCheckboxStateChanged(int state)
{
    qDebug() << "Checkbox state change." << state;
}
