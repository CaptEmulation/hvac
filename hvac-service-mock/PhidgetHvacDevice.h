#ifndef PHIDGETHVACDEVICE_H
#define PHIDGETHVACDEVICE_H

#include <QObject>
#include <QP888Device.h>
#include <HvacZone.h>

class HSPhidgetDeviceManagerPrivate;

class HSPhidgetDeviceManager : public QObject
{
    Q_OBJECT
public:
    explicit HSPhidgetDeviceManager(QObject *parent = 0);
    ~HSPhidgetDeviceManager();

signals:

public slots:

    // Add devices first
    void addDevice(QP888Device *device);

    // Then add zones
    void addZone(HvacZone *zone);

private:
    QScopedPointer<HSPhidgetDeviceManagerPrivate> p;
};

#endif // PHIDGETHVACDEVICE_H
