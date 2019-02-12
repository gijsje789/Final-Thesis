// fileoperation.h - Header file for the FileOperation class.
// This class handles the appearance and functionality of the
// file menu. This will also take care of the writing to file.
// Date: 2019-02-12
// Created by: Gijs de Vries
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

#include <QtDebug>

class FileOperation : public QWidget
{
    Q_OBJECT
public:
    explicit FileOperation(QWidget *parent = nullptr);
    ~FileOperation();
private:
    // Layouts that are used.
    QHBoxLayout *hbox_main = new QHBoxLayout;
    // Input fields
    QLabel *fileName_label = new QLabel;
    QLineEdit *fileName_lineEdit = new QLineEdit;
    QPushButton *renameLast_pushButton = new QPushButton;

    QFile *outputFile = nullptr;
    QString lastFile = "";

    bool temp = false;

    void createGuiItems();
    void createAndFillLayouts();

signals:

private slots:
    void createNewOutputFile();
    void renameLastFile();
    void closeOutputFile();

};

#endif // FILEOPERATION_H
