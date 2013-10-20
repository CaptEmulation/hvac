#ifndef HSPHIDGETDEVICEMANAGER_H
#define HSPHIDGETDEVICEMANAGER_H

#include <QObject>
#include <QP888Device.h>
#include <HvacZone.h>

/**
 * @brief The ResourceInformation struct encapsulates status information on the number of devices, zones and their utilization
 */
struct ResourceInformation {
    // Number of devices connected
    int phidgetDevices;
    // Number of completely unused devices
    int unusedPhidgetDevices;
    // Number of phidget digital inputs
    int phidgetInputs;
    // Number of unused and available digital inputs
    int unsuedPhidgetInputs;
    // Number of phidget digital outputs
    int phidgetOutputs;
    // Number of unused and available phidget outputs
    int unsuedPhidgetOutputs;
    // Number of zones supported by the current number of connected phidgets
    int supportedZones;
    // Number of zones available to be assigned
    int supportedEmptyZones;
};

class HSPhidgetDeviceManagerPrivate;

class HSPhidgetDeviceManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<QP888Device *> devices READ devices)
public:
    explicit HSPhidgetDeviceManager(QObject *parent = 0);
    ~HSPhidgetDeviceManager();



    QList<QP888Device *> devices() const;

    /****************************************************************************************************
      * The following three methods (addDevice, addZone, start) should always been called in that order *
      ***************************************************************************************************/

    // Add devices first
    void addDevice(QP888Device *device);

    // Then add zones
    bool addZone(HvacZone *zone);

    // Then start the service
    void start();

    // Optionally, later (why??)-- stop the service
    void stop();

signals:
    void resourceChanged(ResourceInformation resourceInfo);
    void unableToAddZone(ResourceInformation resourceInfo);

private:
    QScopedPointer<HSPhidgetDeviceManagerPrivate> p;
};

Q_DECLARE_METATYPE(ResourceInformation)

#endif // HSPHIDGETDEVICEMANAGER_H
