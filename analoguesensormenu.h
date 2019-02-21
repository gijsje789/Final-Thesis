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

enum aType {aFlow, aPressure};
struct aParams {
    bool enabled;
    aType type;
    double aVal;
    double bVal;
};
/**
 * @brief The analogue sensor menu class
 *
 * This class handles the appearance and functionality of the
 * analogue sensor menus. The user can enter the analogue sensor characteristics:
 * the "a"-value (in Volt per unit), the "b"-value (in Volt), whether it is a flow or pressure sensor,
 * and to enable or disable the sensor.
 * \author Gijs de Vries
 * \date February 7, 2019
 */
class AnalogueSensorMenu : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief AnalogueSensorMenu The constructor of the analogue sensor menu.
     * @param sensorNr A QString such the menu knows which sensor it is.
     * @param parent The parent of the sensor menu.
     */
    explicit AnalogueSensorMenu(QString sensorNr, QWidget *parent = nullptr);

    /**
     * @brief getMainLayout returns the main layout of the menu. May be obsolete.
     * @return the main layout.
     */
    QGridLayout* getMainLayout();

    /**
     * @brief getParams Getter to get the parameters of the analogue sensor menu.
     * @return A aParams struct containing the sensor's parameters.
     */
    aParams getParams();
private:
    // Analogue sensor name.
    QString sensorName; /**< The self-identifier of which sensor it is; e.g. digital sensor 3. */
    // Layouts that are used.
    QGridLayout *gridLayout = new QGridLayout; /**< The grid layout used to organise the widgets. */
    QVBoxLayout *radio_vBox = new QVBoxLayout; /**< The vertical layout used to organise, and make excluse, the radio buttons that allow the user to specify if sensor is a flow or pressure sensor. */
    // A fields.
    QLabel *a_label = new QLabel; /**< The label that names the input field for the "a"-value. */
    QLineEdit *a_val_lineEdit = new QLineEdit; /**< The QLineEdit for the "a"-value. The "a"-value is typically refered to as the slope. */
    QComboBox *a_unit_comboBox = new QComboBox; /**< The QComboBox for the unit of the "a"-value". */
    // B fields.
    QLabel *b_label = new QLabel; /**< The label that names the input field for the "b"-value. */
    QLineEdit *b_val_lineEdit = new QLineEdit; /**< The QLineEdit for the "b"-value. The "b"-value is typically refered to as the elevation. */
    QComboBox *b_unit_comboBox = new QComboBox; /**< The QComboBox for the unit of the "b"-value. */
    // Radio buttons.
    QRadioButton *flow_radioButton = new QRadioButton; /**< The QRadioButton where the user can select whether or not the sensor is a flow sensor. */
    QRadioButton *pres_radioButton = new QRadioButton; /**< The QRadioButton where the user can select whether or not the sensor is a pressure sensor. */
    // Enabled checkbox.
    QCheckBox *enable_checkBox = new QCheckBox; /**< The QCheckBox where the user can enable or disable the sensor. */

    const QString a_flowItems[8] = {"V/L/min", "V/L/s", "V/mL/min",
                                  "V/mL/s", "mV/L/min", "mV/L/s",
                                  "mV/mL/min", "mV/mL/s"}; /**< The choices the user has to select the units for the "a"-value when the sensor is defined as a flow sensor. */
    const QString b_Items[2] = {"V", "mV"}; /**< The choices the user has to select the units for the "b"-value.*/
    const QString a_presItems[8] = {"V/psi", "mV/psi", "V/bar",
                                    "V/mbar", "mV/bar", "mV/mbar",
                                    "V/mmHg", "mV/mmHg"}; /**< The choices the user has to select the units for the "a"-value when the sensor is defined as a pressure sensor. */
    /**
     * @brief createGuiItems Creates the widgets for the digital sensor menu.
     */
    void createGuiItems();

    /**
     * @brief createAndFillLayout Fills the layouts with the widgets created in createGuiItems().
     */
    void createAndFillLayouts();

    /**
     * @brief fillFlowComboBox Fills the a_unit_comboBox with flow units specified in a_flowItems.
     */
    void fillFlowComboBox();

    /**
     * @brief fillPresComboBox Fills the a_unit_comboBox with pressure units specified in a_flowItems.
     */
    void fillPresComboBox();

    /**
     * @brief fillBComboBox Fills the b_unit_comboBox with volt units specified in b_Items.
     */
    void fillBComboBox();

    /**
     * @brief disableFields Disables all the input fields of the analogue sensor menu when the checkbox enable_checkBox is unchecked.
     */
    void disableFields();

    /**
     * @brief enableFields Enables all the input fields of the analogue sensor menu when  the checkbox enable_checkBox is checked.
     */
    void enableFields();
signals:
    /**
     * @brief flowSensorCreated The signal that is emitted when the analogue sensor is specified as being a "Flow" sensor (when enabled).
     * @param sensor The self-identifier QString sensorName.
     */
    void flowSensorCreated(QString sensor);

    /**
     * @brief flowSensorDeleted The signal that is emitted when the analogue sensor is specified as being a "Pressure" sensor or when disabled.
     * @param sensor The self-identifier QString sensorName.
     */
    void flowSensorDeleted(QString sensor);

private slots:
    /**
     * @brief radiobuttonToggled The slot that should be called when the radio buttons are toggled. Checks which radio button is selected and that takes appropriate action.
     * @param flow_checked The status of the QRadioButton flow_radioButton (checked or unchecked).
     */
    void radiobuttonToggled(bool flow_checked);

    /**
     * @brief enableCheckboxToggled The slot that should be called when the enable_checkBox is toggled. Checks its status and enables or disables the input fields.
     * @param state
     */
    void enableCheckboxToggled(bool state);

public slots:
};

#endif // ANALOGUESENSORMENU_H
