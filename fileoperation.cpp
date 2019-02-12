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
    if (outputFile != nullptr) {
        if (outputFile->isOpen()) {
            qDebug() << "Closing file.";
            outputFile->close();
        }
    }
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
    QDateTime *datetime = new QDateTime;
    QString tempString = FILE_LOC
            + datetime->currentDateTime().toString("yyyyMMdd_hhmmss")
            + fileName_lineEdit->text() + ".csv";
    outputFile = new QFile(tempString);
    outputFile->open(QIODevice::WriteOnly);
}

// #################### Signals ####################
// #################### Private slots ####################
void FileOperation::renameLastFile()
{
    qDebug() << "Im pressed";
    createNewOutputFile();
}
// #################### Public slots ####################
