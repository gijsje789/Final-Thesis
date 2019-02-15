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

/**
 * @brief The digital sensor menu class
 *
 * This class handles the appearance and functionality of the
 * digital sensor menus. The user can enter the digital sensor characteristics:
 * the output (in pulses per unit), whether it is a flow or pressure sensor,
 * and to enable or disable the sensor.
 * \author Gijs de Vries
 * \date February 9, 2019
 */
class DigitalSensorMenu : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief DigitalSensorMenu The constructor of the digital sensor menu.
     * @param sensorNr A QString such the menu knows which sensor it is.
     * @param parent The parent of the sensor menu.
     */
    explicit DigitalSensorMenu(QString sensorNr, QWidget *parent = nullptr);

    /**
     * @brief getMainLayout returns the main layout of the menu. May be obsolete.
     * @return the main layout.
     */
    QGridLayout* getMainLayout();
private:
    // Identifier for the sensor.
    QString sensorName = ""; /**< The self-identifier of which sensor it is; e.g. digital sensor 3. */
    // Layouts that are used.
    QGridLayout *gridLayout = new QGridLayout; /**< The grid layout used to organise the widgets. */
    QVBoxLayout *radio_vBox = new QVBoxLayout; /**< The vertical layout used to organise, and make excluse, the radio buttons that allow the user to specify if sensor is a flow or pressure sensor. */
    // Input fields.
    QLabel *input_label = new QLabel; /**< The label that names the input QLineEdit. */
    QLineEdit *input_lineEdit = new QLineEdit; /**< The QLineEdit that allows the user to enter the digital sensor's output characteristic. */
    QComboBox *input_comboBox = new QComboBox; /**< The QComboBox that allows the user to select the digital sensor's output unit. */
    // Radio buttons
    QRadioButton *flow_radioButton = new QRadioButton; /**< The radio button that signals the GUI that the sensor is a flow sensor (when checked). */
    QRadioButton *pres_radioButotn = new QRadioButton; /**< The radio button that signals the GUI that the sensor is a pressure sensor (when checked. */
    // Enable checkbox
    QCheckBox *enable_checkBox = new QCheckBox; /**< The QCheckBox that allows the user to turn on, or off, the digital sensor. */
    // Spacer item to insert an empty row.
    //QLineEdit * empty_row = new QLineEdit;
    QSpacerItem *empty_row = new QSpacerItem(10, 31); /**< An empty row to align the radio button and enable checkbox with that of the analogue sensors. */

    const QString flowItems[4] = {"P/L/min", "P/L/s",
                                  "P/mL/min", "P/mL/s"}; /**< The choices the user has when the digital sensor is set to "Flow". Will populate the input_comboBox. */
    const QString presItems[4] = {"P/psi", "P/bar",
                                  "P/mbar", "P/mmHg"}; /**< The choices the user has when the digital sensor is set to "Pressure". Will populate the input_comboBox. */

    /**
     * @brief createGuiItems Creates the widgets for the digital sensor menu.
     */
    void createGuiItems();

    /**
     * @brief createAndFillLayout Fills the layouts with the widgets created in createGuiItems().
     */
    void createAndFillLayout();

    /**
     * @brief fillFlowComboBox Fills the input_comboBox with flow units specified in flowItems.
     */
    void fillFlowComboBox();

    /**
     * @brief fillPresComboBox Fills the input_comboBox with pressure units specified in presItems.
     */
    void fillPresComboBox();

    /**
     * @brief disableFields Disables all the input fields of the digital sensor menu when the checkbox enable_checkBox is unchecked.
     */
    void disableFields();

    /**
     * @brief enableFields Enables all the input fields of the digital sensor menu when  the checkbox enable_checkBox is checked.
     */
    void enableFields();
signals:

    /**
     * @brief flowSensorCreated The signal that is emitted when the digital sensor is specified as being a "Flow" sensor (when enabled).
     * @param sensor The self-identifier QString sensorName.
     */
    void flowSensorCreated(QString sensor);

    /**
     * @brief flowSensorDeleted The signal that is emitted when the digital sensor is specified as being a "Pressure" sensor or when disabled.
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
};

#endif // DIGITALSENSORMENU_H
