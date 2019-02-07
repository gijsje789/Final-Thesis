#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedSize(1024, 768);
    this->setCentralWidget(centralWidget);
    an1_widget->setGeometry(10, 10, 984/3, 150);

    an1_a_label->setText("a");
    an1_a_val_lineEdit->setValidator(new QDoubleValidator());
    an1_a_val_lineEdit->setText("0");
    an1_a_unit_comboBox->addItem("Test");

    an1_b_label->setText("b");
    an1_b_val_lineEdit->setValidator(new QDoubleValidator());
    an1_b_val_lineEdit->setText("0");
    an1_b_unit_comboBox->addItem("Test2");

    an1_flow_radioButton->setText("Flow");
    an1_pres_radioButton->setText("Pressure");

    an1_enable_checkBox->setText("Enable");
    an1_enable_checkBox->setTristate(false);

    an1_radio_vBox->addWidget(an1_flow_radioButton);
    an1_radio_vBox->addWidget(an1_pres_radioButton);

    an1_gridLayout->addWidget(an1_a_label, 1, 1);
    an1_gridLayout->addWidget(an1_a_val_lineEdit, 1, 2, 1, 2);
    an1_gridLayout->addWidget(an1_a_unit_comboBox, 1, 4, 1, 2);

    an1_gridLayout->addWidget(an1_b_label, 2, 1);
    an1_gridLayout->addWidget(an1_b_val_lineEdit, 2, 2, 1, 2);
    an1_gridLayout->addWidget(an1_b_unit_comboBox, 2, 4, 1, 2);

    an1_gridLayout->addLayout(an1_radio_vBox, 3, 1, 2, 3);
    an1_gridLayout->addWidget(an1_enable_checkBox, 3, 4, 2, 2);

    an1_widget->setLayout(an1_gridLayout);
}

MainWindow::~MainWindow()
{

}
