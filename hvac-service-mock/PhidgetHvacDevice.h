#ifndef PHIDGETHVACDEVICE_H
#define PHIDGETHVACDEVICE_H

#include <QObject>
#include <QP888Device.h>
#include <HvacZone.h>

class PhidgetHvacDevicePrivate;

class PhidgetHvacDevice : public QObject
{
    Q_OBJECT
public:
    explicit PhidgetHvacDevice(QObject *parent = 0);
    ~PhidgetHvacDevice();

signals:

public slots:

    // Add devices first
    void addDevice(QP888Device *device);

    // Then add zones
    void addZone(HvacZone *zone);

private:
    QScopedPointer<PhidgetHvacDevicePrivate> p;
};

#endif // PHIDGETHVACDEVICE_H
