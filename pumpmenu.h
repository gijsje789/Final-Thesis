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

/**
 * @brief The PumpMenu class handles the appearance and functionality of the pump menus.
 * The user can enter the flow rate and the feedback sensor.
 * \author Gijs de Vries
 * \date Febuary 9, 2019
 */
class PumpMenu : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief PumpMenu The constructor for the Pump Menu.
     * @param parent The parent of the widget.
     */
    explicit PumpMenu(QWidget *parent = nullptr);

    /**
     * @brief getMainLayout returns the main layout of the menu. May be obsolete.
     * @return the main layout.
     */
    QGridLayout* getMainLayout();
private:
    // Layouts that are used.
    QGridLayout *gridLayout = new QGridLayout; /**< The grid layout used to organise the input fields. */
    // Pump rate fields.
    QLabel *pumpRate_label = new QLabel; /**< The QLabel to identiefy the pump rate input field. */
    QLineEdit *pumpRate_lineEdit = new QLineEdit; /**< The QLineEdit where the user can input the pumps flow rate. */
    QLabel *pumpRate_unit_label = new QLabel; /**< The QLabel with the flowe rate unit. */
    // Feedback field.
    QLabel *feedback_label = new QLabel; /**< The QLabel to identify the feedback sensor comboBox. */
    QComboBox *feedback_comboBox = new QComboBox; /**< The QComboBox where the user can select the available flow sensors. */
    // Update pump rate button
    QPushButton *update_pushButton = new QPushButton; /**< The QPushButton to update the pump rate while the system is operational. */
    QCheckBox *enable_checkBox = new QCheckBox; /**< The QCheckBox to enable or disable the pump. */

    QSpacerItem *empty_row = new QSpacerItem(10, 11, QSizePolicy::Fixed); /**< Empty item to organise the entire menu. */

    /**
     * @brief createGuiItems Creates all the widgets for the pump menu.
     */
    void createGuiItems();

    /**
     * @brief createAndFillLayouts Fills the layouts with the widgets created by the createGuiItems().
     */
    void createAndFillLayouts();

    /**
     * @brief disableFields Disables all the input fields of the pump menu.
     */
    void disableFields();

    /**
     * @brief enableFields Enables all the input fields of the pump menu.
     */
    void enableFields();
signals:
private slots:
    /**
     * @brief enableCheckboxToggled The callback function when the enable_checkBox is toggled.
     * @param state
     */
    void enableCheckboxToggled(bool state);
public slots:
    /**
     * @brief addSensorToComboBox The callback function when a flow sensor is defined and it must be added to the feedback_comboBox.
     * @param sensor
     */
    void addSensorToComboBox(QString sensor);

    /**
     * @brief removeSensorFromComboBox The callback function when a flow sensor is deleted and it must be removed from the feedback_comboBox.
     * @param sensor
     */
    void removeSensorFromComboBox(QString sensor);
};

#endif // PUMPMENU_H
