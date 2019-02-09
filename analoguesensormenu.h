#ifndef ANALOGUESENSORMENU_H
#define ANALOGUESENSORMENU_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QRadioButton>
#include <QCheckBox>

#include <QGridLayout>
#include <QVBoxLayout>

#include <QDoubleValidator>

#include <QDebug>
#include <QString>

class AnalogueSensorMenu : public QWidget
{
    Q_OBJECT
public:
    explicit AnalogueSensorMenu(QWidget *parent = nullptr);
    QGridLayout* getMainLayout();
private:
    // Layouts that are used.
    QGridLayout *gridLayout = new QGridLayout;
    QVBoxLayout *radio_vBox = new QVBoxLayout;
    // A fields.
    QLabel *a_label = new QLabel;
    QLineEdit *a_val_lineEdit = new QLineEdit;
    QComboBox *a_unit_comboBox = new QComboBox;
    // B fields.
    QLabel *b_label = new QLabel;
    QLineEdit *b_val_lineEdit = new QLineEdit;
    QComboBox *b_unit_comboBox = new QComboBox;
    // Radio buttons.
    QRadioButton *flow_radioButton = new QRadioButton;
    QRadioButton *pres_radioButton = new QRadioButton;
    // Enabled checkbox.
    QCheckBox *enable_checkBox = new QCheckBox;

    const QString a_flowItems[8] = {"V/L/min", "V/L/s", "V/mL/min",
                                  "V/mL/s", "mV/L/min", "mV/L/s",
                                  "mV/mL/min", "mV/mL/s"};
    const QString b_Items[2] = {"V", "mV"};
    const QString a_presItems[8] = {"V/psi", "mV/psi", "V/bar",
                                    "V/mbar", "mV/bar", "mV/mbar",
                                    "V/mmHg", "mV/mmHg"};
    void createGuiItems();
    void createAndFillLayouts();
    void fillFlowComboBox();
    void fillPresComboBox();
    void fillBComboBox();
signals:

private slots:
    void radiobuttonToggled(bool flow_checked);
    void enableCheckboxStateChanged(int state);

public slots:
};

#endif // ANALOGUESENSORMENU_H
