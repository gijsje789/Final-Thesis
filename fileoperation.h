#ifndef FILEOPERATION_H
#define FILEOPERATION_H

#define FILE_LOC "../UserInterface_outputFiles/"

#include <QWidget>
#include <QDateTime>

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include <QFile>
#include <QString>
#include <QByteArray>

#include <QtDebug>

/**
 * @brief The FileOperation class handles the appearance and functionality of the file menu.
 * This class will also take care of the writing to file.
 * \author Gijs de Vries
 * \date February 12, 2019
 */
class FileOperation : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief FileOperation The constructor for the FileOperation menu.
     * @param parent The parent of the widget.
     */
    explicit FileOperation(QWidget *parent = nullptr);

    ~FileOperation();
private:
    // Layouts that are used.
    QHBoxLayout *hbox_main = new QHBoxLayout; /**< The main layout to organise the input fields. */
    // Input fields
    QLabel *fileName_label = new QLabel; /**< The QLabel that contains the label for the input fields. */
    QLineEdit *fileName_lineEdit = new QLineEdit; /**< The QLineEdit for the user to enter its custom name. Note: the name is always preceded with a date/time stamp. */
    QPushButton *renameLast_pushButton = new QPushButton; /**< The QPushButton the user can press to rename the last file. */

    QFile *outputFile = nullptr; /**< The pointer to the output file. */
    QString lastFile = ""; /**< The last file created by the GUI. */

    bool temp = false; /**< Temporary boolean, will be removed. */

    /**
     * @brief createGuiItems Creates the widgets for the FileOperation menu.
     */
    void createGuiItems();

    /**
     * @brief createAndFillLayouts Fills the layouts with the widgets created by createGuiItems().
     */
    void createAndFillLayouts();

    /**
     * @brief createNewOutputFile The function to create a new output file.
     */
    void createNewOutputFile();

    /**
     * @brief openOutputFile The function to open the output file. This function also emits the signal readyToRecord().
     */
    void openOutputFile();

    /**
     * @brief createFileName The function that creates a custom string for the file based on the input lineedit.
     * @param newDateTime When set to false, the function is forced to use the dateTime from lastFile. When ommited or set to true, complete new file name is created.
     */
    QString createFileName(bool newDateTime = true);
signals:
    /**
     * @brief readyToRecord The emition of this signal indicates that the output file has been made and it can receive data.
     */
    void readyToRecord();

    /**
     * @brief fileFailure The emition of this signal indicates that an error occured while trying to perform file operations.
     * @param message The failure message.
     */
    void fileFailure(QString message);
public slots:
    /**
     * @brief startRecording The callback function that checks the starting conditions and initialises recording.
     */
    void startRecording();

    /**
     * @brief writeToOutputFile The callback function that writes data to the output file.
     * @param data The data that must be written to the outputFile.
     */
    void writeToOutputFile(QString data);
private slots:
    /**
     * @brief renameLastFile The callback function to rename the last file.
     */
    void renameLastFile();

    /**
     * @brief closeOutputFile The callback function to close the output file.
     */
    void closeOutputFile();

};

#endif // FILEOPERATION_H
