#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QRadioButton>
#include <QCheckBox>

#include <QGridLayout>
#include <QVBoxLayout>

#include <QDoubleValidator>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QWidget *centralWidget = new QWidget;
    QWidget *an1_widget = new QWidget(centralWidget);
    QGridLayout *an1_gridLayout = new QGridLayout(an1_widget);
    QVBoxLayout *an1_radio_vBox = new QVBoxLayout;

    QLabel *an1_a_label = new QLabel;
    QLineEdit *an1_a_val_lineEdit = new QLineEdit;
    QComboBox *an1_a_unit_comboBox = new QComboBox;

    QLabel *an1_b_label = new QLabel;
    QLineEdit *an1_b_val_lineEdit = new QLineEdit;
    QComboBox *an1_b_unit_comboBox = new QComboBox;

    QRadioButton *an1_flow_radioButton = new QRadioButton;
    QRadioButton *an1_pres_radioButton = new QRadioButton;

    QCheckBox *an1_enable_checkBox = new QCheckBox;

};

#endif // MAINWINDOW_H
