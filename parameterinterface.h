#ifndef PARAMETERINTERFACE_H
#define PARAMETERINTERFACE_H

#include "analoguesensormenu.h"
#include "digitalsensormenu.h"
#include "pumpmenu.h"

#include <QList>

class ParameterInterface
{
public:
    /**
     * @brief ParameterInterface Constructor for the ParameterInterface class.
     */
    ParameterInterface();
    /**
     * @brief ~ParaMeterInterface Destructor for the ParameterInterface class.
     */
    ~ParameterInterface();

    /**
     * @brief addAnalogueSensor Add an analogue sensor menu to the memory.
     * @param sensor The pointer to the analogue sensor menu.
     */
    void addAnalogueSensor(AnalogueSensorMenu *sensor);

    /**
     * @brief addDigitalSensor Add a digital sensor menu to the memory.
     * @param sensor The pointer to the digital sensor menu.
     */
    void addDigitalSensor(DigitalSensorMenu *sensor);

    /**
     * @brief addPump Add a pump menu to the memory.
     * @param pump The pointer to the pump menu.
     */
    void addPump(PumpMenu *pump);

    /**
     * @brief getAnalogueSensorParams Gets the parameters for all analogue sensors.
     * @return a QList of aParams containing all the parameters for all the analogue sensors.
     */
    QList<aParams> getAnalogueSensorParams();

    /**
     * @brief getDigitalSensorParams Gets the parameters for all digital sensors.
     * @return  a QList of dParams containing all the parameters for all the digital sensors.
     */
    QList<dParams> getDigitalSensorParams();

    /**
     * @brief getPumpParams Gets the parameters for all the pumps.
     * @return  a QList of pParams containing all the parameters for all the pumps.
     */
    QList<pParams> getPumpParams();

private:
    QList<AnalogueSensorMenu*> a_sensors; /**< The QList that contains the pointers to the analogue sensor menus. */
    QList<DigitalSensorMenu*> d_sensors; /**< The QList that contains the pointers to the digital sensor menus. */
    QList<PumpMenu*> pumps; /**< The QList that contains the pointers to the pump menus. */
};

#endif // PARAMETERINTERFACE_H
