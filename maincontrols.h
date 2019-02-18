#ifndef MAINCONTROLS_H
#define MAINCONTROLS_H

#include <QWidget>

#include <QPushButton>
#include <QLabel>

#include <QHBoxLayout>
#include <QVBoxLayout>

/**
 * @brief The MainControls class is responsible for the appearance and functionality of the main controls.
 * The main controls are the buttons to initialise the system and to begin the recording of the variables.
 * \author Gijs de Vries
 * \date February 15, 2019
 */
class MainControls : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief MainControls The constructor of the MainControls class.
     * @param parent The parent of the widget.
     */
    explicit MainControls(QWidget *parent = nullptr);
private:
    // Create the layouts.
    QHBoxLayout *init_hbox = new QHBoxLayout; /**< The QHBoxLayout to hold the initialise set-up QPushButton and QLabel. */
    QHBoxLayout *record_hbox = new QHBoxLayout; /**< The QHBoxLayout to hold the recording QPushButton and QLabel. */
    QVBoxLayout *main_vbox = new QVBoxLayout; /**< The main QVBoxLayout to hold the other layouts. */
    // Create the widgets.
    QPushButton *init_pushButton = new QPushButton; /**< The QPushButton to initialise the set-up. */
    QLabel *init_label = new QLabel; /**< The QLabel to hold the status of the setup. */
    QPushButton *record_pushButton = new QPushButton; /**< The QPushButton to start recording incoming values. */
    QLabel *record_label = new QLabel; /**< The QLabel to hold the status of the recording. */

    /**
     * @brief createGuiItems creates the widgets that are used for the main controls of the GUI.
     */
    void createGuiItems();

    /**
     * @brief createAndFillLayouts fills the widgets that are created by the createGuiItems().
     */
    void createAndFillLayouts();
signals:
    /**
     * @brief startRecording This signal is emitted when the user preses the record_pushButton.
     */
    void startRecording();

    /**
     * @brief recordData This signal is emitted when the class wants to record a message.
     * @param data The data that needs to be written to the outputFile.
     */
    void recordData(QString data);
public slots:
    /**
     * @brief recordingReady The callback function to be called when the FileOperations class successfully readied the output file.
     */
    void recordingReady();

    /**
     * @brief recordingFail The callback function to be called when the FileOperations class could not ready the output file.
     * @param message
     */
    void recordingFail(QString message);
private slots:
    /**
     * @brief recordButtonPressed The callback function when the record_pushButton is pressed.
     */
    void recordButtonPressed();

    /**
     * @brief initButtonPressed The callback function when the init_pushButton is pressed.
     */
    void initButtonPressed();
};

#endif // MAINCONTROLS_H
