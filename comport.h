#ifndef COMPORT_H
#define COMPORT_H

#include <QSizePolicy>

#include <QWidget>
#include <QWindow>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>

#include <QSerialPortInfo>
#include <QSerialPort>
#include <QList>
#include <QTimer>

/**
 * @brief The ComPort class provides the widgets and the functionality to select a COM-port.
 * The window that is used to select from the active COM-ports is a seperate class, ComPortSelectWindow.
 * \author Gijs de Vries
 * \date February 11, 2019
 */
class ComPort : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief ComPort The constructor for the ComPort menu.
     * @param parent The parent of the ComPort menu.
     */
    explicit ComPort(QWidget *parent = nullptr);

private:
    // Layouts that are used.
    QHBoxLayout *hboxLayout = new QHBoxLayout; /**< The main layout used to organise the input fields. */
    // Input fields.
    QPushButton *selectPort_pushButton = new QPushButton; /**< The QPushButton that the user can press to activate the selection window. */
    QLabel *selectedPort_label = new QLabel; /**< The label showing the actual COM-port that is selected. */
    // Have a variable for the serial port.
    QSerialPort *serial_port = nullptr; /**< The actual QSerialPort of the COM-port the user has selected. */

    // Window for the selection of the comport.
    QWidget *SelectWindow = new QWidget; /**< The widget, used as a window, in which the selection widgets are placed. */

    QTimer *timer = new QTimer(this); /**< A QTimer to call the checkComPortStatus() such that a disconnect of the selected device is detected. */

    /**
     * @brief createGuiItems Creates the widgets for the COM-port menu.
     */
    void createGuiItems();

    /**
     * @brief createAndFillLayouts
     */
    void createAndFillLayouts();

signals:

private slots:
    /**
     * @brief selectComPort The slot that is creates the ComPortSelectWindow.
     */
    void selectComPort();

    /**
     * @brief setComPort The callback function when the user selected the COM-port from the ComPortSelectionWindow.
     * @param comport The QSerialPortInfo of the port selected by the user.
     */
    void setComPort(QSerialPortInfo comport);

    /**
     * @brief checkComPortStatus The callback function, based on the timeout() of timer, that checks if the COM-port, that is selected by the user, is still an available port.
     * Only makes sense when the port is not yet opened, QSerialPort emits an error signal if one occurs when port is opened.
     */
    void checkComPortStatus();
public slots:
};

// #############################################################
// #############################################################

/**
 * @brief The ComPortSelectWindow class handles the appearance and functionality of the COM-port selection window.
 */
class ComPortSelectWindow : public QWidget{
    Q_OBJECT
public:
    /**
     * @brief ComPortSelectWindow The constructor for the ComPortSelectWindow.
     * @param parent The parent of the ComPortSelectWindow widget.
     */
    explicit ComPortSelectWindow(QWidget *parent = nullptr);
private:
    // Layouts to be used.
    QHBoxLayout *hbox_pushCombo = new QHBoxLayout; /**< The layout used to organise the selected_port_comboBox and select_port_pushButton. */
    QVBoxLayout *vbox_main = new QVBoxLayout; /**< The layout used to organise all widgets in the selection window. */
    // User widgets
    QComboBox *selected_port_comboBox = new QComboBox; /**< The QComboBox where the user can select from the active COM-ports. */
    QPushButton *select_port_pushButton = new QPushButton; /**< The QPushButton where the user can make his/her choice definitive. */
    // Information widgets.
    QLabel *portName_label = new QLabel; /**< The QLabel that contains the portname of the selected, in the selected_port_comboBox, COM-port. */
    QLabel *manuName_label = new QLabel; /**< The QLabel that contains the manufacturer of the device connected to the selected, in the selected_port_comboBox, COM-port. */
    QLabel *descript_label = new QLabel; /**< The Qlabel that contains the description of the device connected to the selected, in the selected_port_comboBox, COM-port. */
    // List containing all devices.
    QList<QSerialPortInfo> serial_list; /**< The QList that contains all the currently connected COM devices. */
    // Timer to refresh serial list.
    QTimer *timer = new QTimer(this); /**< A QTimer to call the refreshComPortList() such that the serial_list is updated. */

    /**
     * @brief createGuiItems Creates the widgets that are used in the ComPortSelectionwindow.
    */
    void createGuiItems();

    /**
     * @brief createAndFillLayouts Fills the layouts with the widgets created in createGuiItems().
     */
    void createAndFillLayouts();

    /**
     * @brief getAvailablePorts Retrieves the available COM devices and fills the selected_port_comboBox.
     */
    void getAvailablePorts();
signals:
    /**
     * @brief ComPortSelected The signal that is emited when the user selected a COM-port.
     * @param comport The QSerialPortInfo object of the COM-port the user has selected.
     */
    void ComPortSelected(QSerialPortInfo comport);
private slots:
    /**
     * @brief updatePortInformation The callback function to update the portName_label, manuName_label, and descript_label.
     * @param index The index of the item currently selected in the selected_port_comboBox.
     */
    void updatePortInformation(int index);

    /**
     * @brief refreshComPortList The callback function to update the list with available COM devices.
     */
    void refreshComPortList();

    /**
     * @brief selectPortButtonPressed The callback function when the select_port_pushButton is pressed.
     */
    void selectPortButtonPressed();
};

#endif // COMPORT_H
