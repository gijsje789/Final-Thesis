// comport.h - Header file for the comport class.
// This class handles the appearance and functionality of the
// comport menu. Als implements the communication between
// arduino and pc.
// Date: 2019-02-11
// Created by: Gijs de Vries

#ifndef COMPORT_H
#define COMPORT_H

#include <QSizePolicy>

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

class ComPort : public QWidget
{
    Q_OBJECT
public:
    explicit ComPort(QWidget *parent = nullptr);

private:
    // Layouts that are used.
    QHBoxLayout *hboxLayout = new QHBoxLayout;
    // Input fields.
    QPushButton *selectPort_pushButton = new QPushButton;
    QLabel *selectedPort_label = new QLabel;

    void createGuiItems();
    void createAndFillLayouts();
signals:

private slots:
    void selectComPort();
public slots:
};

#endif // COMPORT_H
