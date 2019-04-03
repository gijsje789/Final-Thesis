// fileoperation.cpp - Implementation file for the FileOperation class.
// This class handles the appearance and functionality of the
// file menu. This will also take care of the writing to file.
// Date: 2019-02-12
// Created by: Gijs de Vries
#include "fileoperation.h"

FileOperation::FileOperation(QWidget *parent) : QWidget(parent)
{
    createGuiItems();
    createAndFillLayouts();

    connect(renameLast_pushButton, SIGNAL(clicked()), this, SLOT(renameLastFile()));
}

FileOperation::~FileOperation()
{
    closeOutputFile();
}

void FileOperation::setParameterInterface(ParameterInterface *pInterface)
{
    mInterface = pInterface;
}

// #################### Private functions ####################
void FileOperation::createGuiItems()
{
    // Create input fields.
    fileName_label->setText("File name: ");
    fileName_lineEdit->setText("sensorData");
    renameLast_pushButton->setText("Rename last");
}

void FileOperation::createAndFillLayouts()
{
    // Fill the horizontal layout.
    hbox_main->addWidget(fileName_label);
    hbox_main->addWidget(fileName_lineEdit);
    hbox_main->addWidget(renameLast_pushButton);

    // Set main layout.
    this->setLayout(hbox_main);
}

void FileOperation::createNewOutputFile()
{
    // Create new file in an output folder which is one level up.
    outputFile = new QFile(createFileName());
}

void FileOperation::openOutputFile()
{
    if (outputFile != nullptr) {
        if(outputFile->open(QIODevice::WriteOnly)) {
            qDebug() << outputFile->fileName() << "successfully opened.";
            lastFile = outputFile->fileName();
        }
    }
}

QString FileOperation::createFileName(bool newDateTime)
{
    QString dateTimeFormat = "yyyyMMdd_hhmmss_";
    if (newDateTime) {
        QDateTime *datetime = new QDateTime;
        return FILE_LOC + datetime->currentDateTime().toString(dateTimeFormat)
                + fileName_lineEdit->text() + ".csv";
    } else {
        int fileLoc_length = strlen(FILE_LOC);
        int dateTime_length = dateTimeFormat.length();
        return lastFile.left(fileLoc_length + dateTime_length)
                + fileName_lineEdit->text() + ".csv";
    }
}

void FileOperation::closeOutputFile()
{
    if (outputFile != nullptr) {
        if (outputFile->isOpen()) {
            qDebug() << "Closing file.";
            outputFile->close();
        }
        outputFile = nullptr;
    }
}
// #################### Signals ##########################
// #################### Public slots #####################
void FileOperation::startRecording()
{
    if (outputFile == nullptr)
        createNewOutputFile();

    if (!outputFile->isOpen())
        openOutputFile();

    if (outputFile->isWritable() && outputFile->isOpen()) {
        QList<aParams> a_sensor_params = mInterface->getAnalogueSensorParams();
        QList<dParams> d_sensor_params = mInterface->getDigitalSensorParams();
        QList<pParams> p_params = mInterface->getPumpParams();

        QString message = "";

        for(aParams &param : a_sensor_params) {
            message = QString("%1 %2 %3 %4 %5").
                    arg(param.name, QString::number(param.type), QString::number(param.enabled),
                        QString::number(param.aVal),
                        QString::number(param.bVal));
            outputFile->write(message.toUtf8());
        }
        for(dParams &param : d_sensor_params) {
            message = QString("%1 %2 %3 %4").
                    arg(param.name, QString::number(param.type),
                        QString::number(param.enabled),
                        QString::number(param.output));
            outputFile->write(message.toUtf8());
        }

        for(pParams &param : p_params) {
            message = QString("%1 %2 %3 %4").
                    arg(param.name, QString::number(param.enabled),
                        QString::number(param.rate), param.feedback);
            outputFile->write(message.toUtf8());
        }
        outputFile->write("\n");

        emit readyToRecord();
    }
    else if (outputFile == nullptr)
        emit fileFailure("FERR-004");
    else if (!outputFile->isOpen())
        emit fileFailure("FERR-005");
    else if (!outputFile->isWritable())
        emit fileFailure("FERR-006");
    else
        emit fileFailure("FERR-999");
}

void FileOperation::writeToOutputFile(QString data)
{
    QByteArray byteArray = data.toLocal8Bit();
    if (outputFile != nullptr) {
        if (outputFile->isOpen()) {
            if (outputFile->isWritable()) {
                outputFile->write(byteArray);
            } else {
                emit fileFailure("FERR-003");
            }
        } else {
            emit fileFailure("FERR-002");
        }
    } else {
        emit fileFailure("FERR-001");
    }
}

void FileOperation::disconnect()
{
    closeOutputFile();
    emit recordingStopped();
}
// #################### Private slots ####################
void FileOperation::renameLastFile()
{
    if (!lastFile.isEmpty()) {
        if (outputFile != nullptr && lastFile == outputFile->fileName()) {
            emit fileFailure("FERR-010");
        } else {
            QFile *renameFile = new QFile(lastFile);
            QString newFileName = createFileName(false);
            if (renameFile->exists()) {
                if (renameFile->rename(newFileName)) {
                    qDebug() << "File" << lastFile << "renamed to" << newFileName;
                    lastFile = newFileName;
                } else {
                    emit fileFailure("FERR-008");
                }
            } else {
                emit fileFailure("FERR-009");
            }
        }
    } else {
        emit fileFailure("FERR-007");
    }
}
