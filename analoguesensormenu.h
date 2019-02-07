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

class AnalogueSensorMenu : public QWidget
{
    Q_OBJECT
public:
    explicit AnalogueSensorMenu(QWidget *parent = nullptr);
    QGridLayout* getMainLayout();
private:
    QGridLayout *gridLayout = new QGridLayout;
    QVBoxLayout *radio_vBox = new QVBoxLayout;

    QLabel *a_label = new QLabel;
    QLineEdit *a_val_lineEdit = new QLineEdit;
    QComboBox *a_unit_comboBox = new QComboBox;

    QLabel *b_label = new QLabel;
    QLineEdit *b_val_lineEdit = new QLineEdit;
    QComboBox *b_unit_comboBox = new QComboBox;

    QRadioButton *flow_radioButton = new QRadioButton;
    QRadioButton *pres_radioButton = new QRadioButton;

    QCheckBox *enable_checkBox = new QCheckBox;
signals:

public slots:
};

#endif // ANALOGUESENSORMENU_H
