// digitalsensormenu.h - Header file for the DigitalSensorMenu class.
// This class handles the appearance and functionality of the
// digital sensor menus. The user can enter the digital sensor
// characteristics.
// Date: 2019-02-09
// Created by: Gijs de Vries

#ifndef DIGITALSENSORMENU_H
#define DIGITALSENSORMENU_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QRadioButton>
#include <QCheckBox>
#include <QSpacerItem>

#include <QGridLayout>
#include <QVBoxLayout>

#include <QDoubleValidator>

#include <QDebug>
#include <QString>

class DigitalSensorMenu : public QWidget
{
    Q_OBJECT
public:
    explicit DigitalSensorMenu(QString sensorNr, QWidget *parent = nullptr);
    QGridLayout* getMainLayout();
private:
    // Identifier for the sensor.
    QString sensorName = "";
    // Layouts that are used.
    QGridLayout *gridLayout = new QGridLayout;
    QVBoxLayout *radio_vBox = new QVBoxLayout;
    // Input fields.
    QLabel *input_label = new QLabel;
    QLineEdit *input_lineEdit = new QLineEdit;
    QComboBox *input_comboBox = new QComboBox;
    // Radio buttons
    QRadioButton *flow_radioButton = new QRadioButton;
    QRadioButton *pres_radioButotn = new QRadioButton;
    // Enable checkbox
    QCheckBox *enable_checkBox = new QCheckBox;
    // Spacer item to insert an empty row.
    //QLineEdit * empty_row = new QLineEdit;
    QSpacerItem *empty_row = new QSpacerItem(10, 31);

    const QString flowItems[4] = {"P/L/min", "P/L/s",
                                  "P/mL/min", "P/mL/s"};
    const QString presItems[4] = {"P/psi", "P/bar",
                                  "P/mbar", "P/mmHg"};

    void createGuiItems();
    void createAndFillLayout();
    void fillFlowComboBox();
    void fillPresComboBox();
    void disableFields();
    void enableFields();
signals:
    // Signal to emit that is emited to the outside world when
    // the sensor (if enabled) is set to "flow".
    void flowSensorCreated(QString sensor);

    // Signal to emit that is emited to the outside world when
    // the flow sensor is disabled or set to "Pressure".
    void flowSensorDeleted(QString sensor);

private slots:
    void radiobuttonToggled(bool flow_checked);
    void enableCheckboxToggled(bool state);
};

#endif // DIGITALSENSORMENU_H
