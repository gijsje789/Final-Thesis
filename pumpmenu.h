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

#define NO_CHOICE "Pick"

struct pParams {
    QString name;
    bool enabled;
    double rate;
    QString feedback;
};

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
     * @param name The name of the sensor.
     * @param parent The parent of the widget.
     */
    explicit PumpMenu(QString name, QWidget *parent = nullptr);

    /**
     * @brief getMainLayout returns the main layout of the menu. May be obsolete.
     * @return the main layout.
     */
    QGridLayout* getMainLayout();

    /**
     * @brief getParams Getter to get the parameters of the pump menu.
     * @return A pParams struct containing the sensor's parameters.
     */
    pParams getParams();
private:
    QString pumpName = "";
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

    QString prev_item = NO_CHOICE; /**< The previous selected item by the feedback_comboBox. */

    bool ignoreSensorReset = false;

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

    /**
     * @brief checkInputParameters Check if the entered parameters are valid, more specifically, if the feedback is set.
     */
    void checkInputParameters();
signals:
    /**
     * @brief comboBoxCurrentIndexChanged When the feedback_comboBox changes sensor, this signal is emitted to the outside world.
     * @param sensor The currently selected sensor.
     */
    void comboBoxSensorSelected(QString sensor);

    /**
     * @brief comboBoxSensorReset When the feedback_comboBox changes sensor, this signal is emitted when the previous selection is a valid sensor.
     * @param sensor The previously selected sensor.
     */
    void comboBoxSensorReset(QString sensor);

    void updatePumpParameter(QString name, bool enabled, double rate, QString feedback);
private slots:
    /**
     * @brief enableCheckboxToggled The callback function when the enable_checkBox is toggled.
     * @param state
     */
    void enableCheckboxToggled(bool state);

    /**
     * @brief comboBoxSelectionChanged The callback function when the feedback_comboBox changes selection.
     * @param sensor The newly selected sensor.
     */
    void comboBoxSelectionChanged(QString sensor);

    void updatePushButtonPressed();
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
