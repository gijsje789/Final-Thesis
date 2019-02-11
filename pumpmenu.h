// pumpmenu.h - Header file for the PumpMeny class.
// This class handles the appearance and functionality of the
// pump menus. The user can enter the flow rate and feedback
// sensor.
// Date: 2019-02-09
// Created by: Gijs de Vries

#ifndef PUMPMENU_H
#define PUMPMENU_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QRadioButton>
#include <QCheckBox>
#include <QPushButton>
#include <QSpacerItem>

#include <QGridLayout>
#include <QVBoxLayout>

#include <QDoubleValidator>

#include <QDebug>
#include <QString>

class PumpMenu : public QWidget
{
    Q_OBJECT
public:
    explicit PumpMenu(QWidget *parent = nullptr);
    QGridLayout* getMainLayout();
private:
    // Layouts that are used.
    QGridLayout *gridLayout = new QGridLayout;
    // Pump rate fields.
    QLabel *pumpRate_label = new QLabel;
    QLineEdit *pumpRate_lineEdit = new QLineEdit;
    QLabel *pumpRate_unit_label = new QLabel;
    // Feedback field.
    QLabel *feedback_label = new QLabel;
    QComboBox *feedback_comboBox = new QComboBox;
    // Update pump rate button
    QPushButton *update_pushButton = new QPushButton;
    QCheckBox *enable_checkBox = new QCheckBox;

    QSpacerItem *empty_row = new QSpacerItem(10, 11);

    void createGuiItems();
    void createAndFillLayouts();
    void disableFields();
    void enableFields();
signals:
private slots:
    void enableCheckboxToggled(bool state);
public slots:
    void addSensorToComboBox(QString sensor);
    void removeSensorFromComboBox(QString sensor);
};

#endif // PUMPMENU_H
