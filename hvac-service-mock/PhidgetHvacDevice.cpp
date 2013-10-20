#include "PhidgetHvacDevice.h"

class HSPhidgetDeviceManagerPrivate {
public:
    HSPhidgetDeviceManager *self;

    QList<QP888Device *> mDevices;
    qint16 mLastDeviceIndex;
    qint16 mLastInputIndex;

    QList<HvacZone *> mZones;

    void addDevice(QP888Device *device) {
        mDevices.append(device);
    }

    void connectToDevice(HvacZone *zone) {
        qint16 index = mLastInputIndex + 1;
        //QObject::connect(mDevices.at(index)->outputs().at(mLastInputIndex++), SIGNAL(stateChanged(bool))
    }

    void addZone(HvacZone *zone) {
        if (mLastInputIndex > (mDevices.length() * 8) - 3) {
            connectToDevice(zone);
        } else {
            exit(-1);
        }
    }
};

HSPhidgetDeviceManager::HSPhidgetDeviceManager(QObject *parent) :
    QObject(parent),
    p(new HSPhidgetDeviceManagerPrivate)
{
    p->self = this;
    p->mLastInputIndex = 0;
    p->mLastDeviceIndex = 0;
}

HSPhidgetDeviceManager::~HSPhidgetDeviceManager()
{

}


void HSPhidgetDeviceManager::addDevice(QP888Device *device)
{
    p->addDevice(device);
}

void HSPhidgetDeviceManager::addZone(HvacZone *zone)
{
    p->addZone(zone);
}
