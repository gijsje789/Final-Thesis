#include "analoguesensormenu.h"

AnalogueSensorMenu::AnalogueSensorMenu(QWidget *parent) : QWidget(parent)
{
    a_label->setText("a");
    a_val_lineEdit->setValidator(new QDoubleValidator());
    a_val_lineEdit->setText("0");
    a_unit_comboBox->addItem("Test");

    b_label->setText("b");
    b_val_lineEdit->setValidator(new QDoubleValidator());
    b_val_lineEdit->setText("0");
    b_unit_comboBox->addItem("Test2");

    flow_radioButton->setText("Flow");
    pres_radioButton->setText("Pressure");
    flow_radioButton->setChecked(true);

    enable_checkBox->setText("Enable");
    enable_checkBox->setTristate(false);

    radio_vBox->addWidget(flow_radioButton);
    radio_vBox->addWidget(pres_radioButton);

    gridLayout->addWidget(a_label, 1, 1);
    gridLayout->addWidget(a_val_lineEdit, 1, 2, 1, 2);
    gridLayout->addWidget(a_unit_comboBox, 1, 4, 1, 2);

    gridLayout->addWidget(b_label, 2, 1);
    gridLayout->addWidget(b_val_lineEdit, 2, 2, 1, 2);
    gridLayout->addWidget(b_unit_comboBox, 2, 4, 1, 2);

    gridLayout->addLayout(radio_vBox, 3, 1, 2, 3);
    gridLayout->addWidget(enable_checkBox, 3, 4, 2, 2);

    this->setLayout(gridLayout);
}

QGridLayout* AnalogueSensorMenu::getMainLayout()
{
    return gridLayout;
}
