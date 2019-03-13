// comport.cpp - Implementation file for the comport class.
// This class handles the appearance and functionality of the
// comport menu. Als implements the communication between
// arduino and pc.
// Date: 2019-02-11
// Created by: Gijs de Vries

#include "comport.h"

#include <QDebug>

ComPort::ComPort(QWidget *parent) : QWidget(parent)
{
    createGuiItems();
    createAndFillLayouts();

    connect(selectPort_pushButton, SIGNAL(clicked()), this, SLOT(selectComPort()));
}

void ComPort::setParameterInterface(ParameterInterface *interface)
{
    param_interface = interface;
}

// #################### Private functions ####################
void ComPort::createGuiItems()
{
    // Create the push button.
    selectPort_pushButton->setText("Select COM port");
    selectPort_pushButton->setGeometry(0,0, 200, 50);
    selectPort_pushButton->setFixedWidth(150);

    // Create the label.
    selectedPort_label->setText("Selected port: ");
    selectedPort_label->setFixedWidth(150);
}

void ComPort::createAndFillLayouts()
{
    // Fill the horizontal layout.
    hboxLayout->addWidget(selectedPort_label);
    hboxLayout->addWidget(selectPort_pushButton);

    // Set the horizontal layout as the main layout.
    this->setLayout(hboxLayout);
}

void ComPort::deleteComPort()
{
    delete serial_port;
    serial_port = nullptr;
    selectedPort_label->setText("Selected port: ");
    qDebug() << "COM-port is deleted.";
}

void ComPort::deleteTimer()
{
    if (timer->isActive())
        timer->stop();
    delete timer;
    timer = new QTimer(this);
    qDebug() << "COM-port timer is deleted.";
}

void ComPort::extractSensorValues(QString data)
{
    // qDebug() << data;
    // Split the string into all its values.
    // data contains more than just 10 sensor values.
    QString allData = "";
    if(oldData.isEmpty())
        allData = data;
    else
        allData = oldData + data;

    qDebug() << allData;
    oldData.clear();
    QString message = "";
    QStringList splitted;
    for(int i = 0; i < allData.size(); i++){
        bool dataGood = false;

        if(allData[i] == '\n') {
            splitted = message.split(' ');
            if(splitted.size() == DATA_INPUT_LENGTH) {
                dataGood = true;
            } else {
                // Just ignore data that is incorrect.
               // qDebug() << "Data no good." << i << message;
            }
            message.clear();
        } else {
            message.append(allData[i]);
        }

        if(i == allData.size() -1) {
            // Save the remaining data for the next iteration.
            //qDebug() << "data too short" << message;
            oldData = message;
            message.clear();
        }

        if (dataGood) {
            // qDebug() << splitted;
            emit dataReadyForPlot(splitted);
            // qDebug() output for visual verification.
            QString combinedSensorValues = "";
            for (QString &character : splitted) {
                combinedSensorValues.append(character);
                combinedSensorValues.append(" ");
            }
            //qDebug() << combinedSensorValues;
        }
    }
}

bool ComPort::getAnalogueSensorParams(QList<aParams> *params)
{
    QList<aParams> temp = param_interface->getAnalogueSensorParams();
    if (temp.length() != 5)
        return false;
    else {
        *params = temp;
        return true;
    }
}

bool ComPort::getDigitalSensorParams(QList<dParams> *params)
{
    QList<dParams> temp = param_interface->getDigitalSensorParams();
    if (temp.length() != 5)
        return false;
    else {
        *params = temp;
        return true;
    }
}

bool ComPort::getPumpParams(QList<pParams> *params)
{
    QList<pParams> temp = param_interface->getPumpParams();
    if (temp.length() != 4)
        return false;
    else {
        *params = temp;
        return true;
    }
}

bool ComPort::sendParametersToDevice()
{
    QList<aParams> *a_params = new QList<aParams>;
    QList<dParams> *d_params = new QList<dParams>;
    QList<pParams> *p_params = new QList<pParams>;

    // Retrieve all the parameters
    if (!getAnalogueSensorParams(a_params)) {
        emit comPortFailure("CPERR-005");
        return false;
    }
    if (!getDigitalSensorParams(d_params)) {
        emit comPortFailure("CPERR-006");
        return false;
    }
    if (!getPumpParams(p_params)) {
        emit comPortFailure("CPERR-007");
        return false;
    }

    QString message = "";
    for (aParams &sensor : *a_params) {
        if (sensor.enabled)
            message = QString("%1 %2 %3 %4\n").
                    arg(sensor.name, QString::number(sensor.enabled),
                        QString::number(sensor.aVal, 'f', 10),
                        QString::number(sensor.bVal, 'f', 10));
        else
            message = QString("%1 0\n").arg(sensor.name);

        qDebug() << "writing: " << message;
        serial_port->write(message.toUtf8());
        while(serial_port->waitForBytesWritten(-1)) {}
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    for (dParams &sensor : *d_params) {
        if (sensor.enabled)
            message = QString("%1 %2 %3 %4\n").
                    arg(sensor.name, QString::number(sensor.enabled),
                        QString::number(sensor.output, 'f', 10));
        else
            message = QString("%1 0\n").arg(sensor.name);

        qDebug() << "writing: " << message;
        serial_port->write(message.toUtf8());
        while(serial_port->waitForBytesWritten(-1)) {}
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    for (pParams &pump : *p_params) {
        if (pump.enabled)
            message = QString("%1 %2 %3 %4\n").
                    arg(pump.name, QString::number(pump.enabled),
                        QString::number(pump.rate, 'f', 10),
                        pump.feedback);
        else
            message = QString("%1 0\n").arg(pump.name);

        qDebug() << "writing: " << message;
        serial_port->write(message.toUtf8());
        while(serial_port->waitForBytesWritten(-1)) {}
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return true;
}

void ComPort::sendStartSignalToDevice()
{
    QString message = "Q\n";
    qDebug() << "writing:" << message;
    serial_port->write(message.toUtf8());
    emit startPlotting();
    while(serial_port->waitForBytesWritten(-1)){}
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}
// #################### Signals ####################
// #################### Public slots ###############
void ComPort::initialiseComPort()
{
    if (serial_port != nullptr) {
        if (serial_port->open(QIODevice::ReadWrite)) {
            if (serial_port->setBaudRate(BAUDRATE)) {
                deleteTimer(); // Restart the timer.
                timer->start(POLL_INPUT_TIME);
                connect(timer, SIGNAL(timeout()), this, SLOT(checkInputBuffer()));
                connect(serial_port, SIGNAL(errorOccurred(QSerialPort::SerialPortError)), this, SLOT(serialErrorOccurred(QSerialPort::SerialPortError)));
                if (sendParametersToDevice()) {
                    sendStartSignalToDevice();
                    comPortSuccess("Connected");
                } else {
                    disconnect(true);
                }
            } else {
                emit comPortFailure("CPERR-003");
            }
        } else {
            emit comPortFailure("CPERR-002");
        }
    } else {
        emit comPortFailure("CPERR-001");
    }
}

void ComPort::disconnect(bool failure)
{
    deleteTimer();
    if (serial_port != nullptr && serial_port->isOpen())
        serial_port->close();

    if (!failure) {
        deleteComPort();
        comPortSuccess("disconnected");
    }
}
// #################### Private slots ####################
void ComPort::selectComPort()
{
    SelectWindow->setFixedSize(500, 250);
    ComPortSelectWindow *window = new ComPortSelectWindow(SelectWindow);
    connect(window, SIGNAL(ComPortSelected(QSerialPortInfo)), this, SLOT(setComPort(QSerialPortInfo)));
    SelectWindow->show();
}

void ComPort::setComPort(QSerialPortInfo comport)
{
    serial_port = new QSerialPort(comport, this);
    selectedPort_label->setText("Selected port: " + serial_port->portName());

    qDebug() << "COM-port set: " << serial_port->portName();

    connect(timer, SIGNAL(timeout()), this, SLOT(checkComPortStatus()));
    timer->start(500);
    qDebug() << "COM-port will be periodically checked.";

    // Delete the dialog window.
    delete SelectWindow;
    SelectWindow = new QWidget;
}

void ComPort::checkComPortStatus()
{
    QSerialPortInfo *info = new QSerialPortInfo;
    QList<QSerialPortInfo> list = info->availablePorts();
    bool port_still_available = false;

    for (QSerialPortInfo &port : list) {
        if (port.portName() == serial_port->portName())
            port_still_available = true;
    }

    if (!port_still_available) {
        qDebug() << "Selected COM-port," << serial_port->portName() << ", no longer available!";

        deleteComPort();
        deleteTimer();

        selectedPort_label->setText("Error, disconnected");
    }
}

void ComPort::checkInputBuffer()
{
    if (serial_port->bytesAvailable() > 0) {
        QString *data = new QString(serial_port->readAll());
        emit recordData(*data);
        //qDebug() << *data;
        extractSensorValues(*data);
    }
}

void ComPort::serialErrorOccurred(QSerialPort::SerialPortError error)
{
    qDebug() << "Error occured in COM-port: " << error;
    emit comPortFailure("CPERR-004");

    deleteComPort();
    deleteTimer();

    selectedPort_label->setText("Error, disconnected");
}
// #################### Public slots ####################

// #########################################################
// #########################################################
// #################### ComPortSelectWindow ################
// #########################################################
// #########################################################
ComPortSelectWindow::ComPortSelectWindow(QWidget *parent)
    : QWidget(parent)
{
    createGuiItems();
    createAndFillLayouts();

    connect(selected_port_comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updatePortInformation(int)));
    connect(timer, SIGNAL(timeout()), this, SLOT(refreshComPortList()));
    connect(select_port_pushButton, SIGNAL(clicked()), this, SLOT(selectPortButtonPressed()));
    timer->start(500);

    getAvailablePorts();
}

// #################### Private functions ####################
void ComPortSelectWindow::createGuiItems()
{
    // Create the push button.
    select_port_pushButton->setText("Select port");

    // Create the labels.
    portName_label->setText("Port: ");
    portName_label->setFixedSize(400, 40);
    manuName_label->setText("Manufacturer: ");
    manuName_label->setFixedSize(400, 40);
    descript_label->setText("Description: ");
    descript_label->setFixedSize(400, 40);
}

void ComPortSelectWindow::createAndFillLayouts()
{
    // Fill the horizontal layout
    hbox_pushCombo->addWidget(selected_port_comboBox);
    hbox_pushCombo->addWidget(select_port_pushButton);

    // Fill the vertical layout
    vbox_main->addLayout(hbox_pushCombo);
    vbox_main->addWidget(portName_label);
    vbox_main->addWidget(manuName_label);
    vbox_main->addWidget(descript_label);

    this->setLayout(vbox_main);
}

void ComPortSelectWindow::getAvailablePorts()
{
    QSerialPortInfo *info = new QSerialPortInfo;
    serial_list = info->availablePorts();

    selected_port_comboBox->clear();
    for(QSerialPortInfo &item :  serial_list){
        selected_port_comboBox->addItem(item.portName());
    }

    emit updatePortInformation(selected_port_comboBox->currentIndex());
}
// #################### Signals ##########################
// #################### Public slots #####################
// #################### Private slots ####################
void ComPortSelectWindow::updatePortInformation(int index)
{
    if (index < serial_list.length() && index >= 0) {
        portName_label->setText("Port: " + serial_list[index].portName());
        manuName_label->setText("Manufacturer: " + serial_list[index].manufacturer());
        descript_label->setText("Description: " + serial_list[index].description());
    }
    else {
        portName_label->setText("Port: ");
        manuName_label->setText("Manufacturer: ");
        descript_label->setText("Description: ");
    }
}

void ComPortSelectWindow::refreshComPortList()
{
    QSerialPortInfo *info = new QSerialPortInfo;
    QList<QSerialPortInfo> temp = info->availablePorts();

    if (temp.length() != serial_list.length()) {
        getAvailablePorts();
    }
}

void ComPortSelectWindow::selectPortButtonPressed()
{
    if (serial_list.length()>0)
        emit ComPortSelected(serial_list[selected_port_comboBox->currentIndex()]);
    else
        portName_label->setText("Port: ERROR NO PORT SELECTED!");
}
