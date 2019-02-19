#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Set window size.
    setFixedSize(WINDOW_W, WINDOW_H);

    // Set a central widget in order to manipulate layouts.
    this->setCentralWidget(centralWidget);

    // Create tab widget and populate with analogue sensors.
    anSensors_tabWidget->setGeometry(WIDGET_SPACE, WIDGET_SPACE, (WINDOW_W-4*WIDGET_SPACE)/3, SMENU_H);
    anSensors_tabWidget->addTab(an1_widget, "AN1");
    anSensors_tabWidget->addTab(an2_widget, "AN2");
    anSensors_tabWidget->addTab(an3_widget, "AN3");
    anSensors_tabWidget->addTab(an4_widget, "AN4");
    anSensors_tabWidget->addTab(an5_widget, "AN5");

    dSensors_tabWidget->setGeometry(2*WIDGET_SPACE + ((WINDOW_W-4*WIDGET_SPACE)/3), WIDGET_SPACE, (WINDOW_W-4*WIDGET_SPACE)/3, SMENU_H);
    dSensors_tabWidget->addTab(d1_widget, "D1");
    dSensors_tabWidget->addTab(d2_widget, "D2");
    dSensors_tabWidget->addTab(d3_widget, "D3");
    dSensors_tabWidget->addTab(d4_widget, "D4");
    dSensors_tabWidget->addTab(d5_widget, "D5");

    pump_tabWidget->setGeometry(3*WIDGET_SPACE + 2*((WINDOW_W-4*WIDGET_SPACE)/3), WIDGET_SPACE, (WINDOW_W-4*WIDGET_SPACE)/3, SMENU_H);
    pump_tabWidget->addTab(p1_widget, "P1");
    pump_tabWidget->addTab(p2_widget, "P2");
    pump_tabWidget->addTab(p3_widget, "P3");
    pump_tabWidget->addTab(p4_widget, "P4");

    comport_widget->setGeometry(WIDGET_SPACE, 2*WIDGET_SPACE+SMENU_H, (WINDOW_W-4*WIDGET_SPACE)/3, COM_H);

    file_widget->setGeometry(WIDGET_SPACE, 3*WIDGET_SPACE+SMENU_H+COM_H, (WINDOW_W-4*WIDGET_SPACE)/3, COM_H);

    mainControl_widget->setGeometry(WIDGET_SPACE, 4*WIDGET_SPACE+SMENU_H+2*COM_H, (WINDOW_W-4*WIDGET_SPACE)/3, 2*COM_H);
    connectWidgets();
}

MainWindow::~MainWindow()
{

}

void MainWindow::connectWidgets()
{
    DigitalSensorMenu *dMenu[5] = {d1_menu, d2_menu, d3_menu, d4_menu, d5_menu};
    AnalogueSensorMenu *aMenu[5] = {an1_menu, an2_menu, an3_menu, an4_menu, an5_menu};
    PumpMenu *pMenu[4] = {p1_menu, p2_menu, p3_menu, p4_menu};
    // Connect digital sensors to pumps.
    for (DigitalSensorMenu *menu : dMenu) {
        for (PumpMenu *pump : pMenu) {
            connect(menu, SIGNAL(flowSensorCreated(QString)), pump, SLOT(addSensorToComboBox(QString)));
            connect(menu, SIGNAL(flowSensorDeleted(QString)), pump, SLOT(removeSensorFromComboBox(QString)));
        }
    }

    for (AnalogueSensorMenu *menu : aMenu) {
        for (PumpMenu *pump : pMenu) {
            connect(menu, SIGNAL(flowSensorCreated(QString)), pump, SLOT(addSensorToComboBox(QString)));
            connect(menu, SIGNAL(flowSensorDeleted(QString)), pump, SLOT(removeSensorFromComboBox(QString)));
        }
    }

    for (PumpMenu *send : pMenu) {
        for (PumpMenu *rec : pMenu) {
            if (send != rec) {
                connect(send, SIGNAL(comboBoxSensorSelected(QString)), rec, SLOT(removeSensorFromComboBox(QString)));
                connect(send, SIGNAL(comboBoxSensorReset(QString)), rec, SLOT(addSensorToComboBox(QString)));
            }
        }
    }

    connect(mainControl_menu, SIGNAL(startRecording()), file_menu, SLOT(startRecording()));
    connect(file_menu, SIGNAL(readyToRecord()), mainControl_menu, SLOT(recordingReady()));
    connect(file_menu, SIGNAL(fileFailure(QString)), mainControl_menu, SLOT(recordingFail(QString)));
    connect(mainControl_menu, SIGNAL(recordData(QString)), file_menu, SLOT(writeToOutputFile(QString)));

    connect(mainControl_menu, SIGNAL(initSetup()), comport_menu, SLOT(initialiseComPort()));
    connect(comport_menu, SIGNAL(comPortFailure(QString)), mainControl_menu, SLOT(comPortFail(QString)));
    connect(comport_menu, SIGNAL(comPortSuccess(QString)), mainControl_menu, SLOT(comPortSuccess(QString)));
    connect(comport_menu, SIGNAL(recordData(QString)), file_menu, SLOT(writeToOutputFile(QString)));
}
