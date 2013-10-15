#include "PhidgetHvacDevice.h"

class PhidgetHvacDevicePrivate {
public:
    PhidgetHvacDevice *self;

    QList<QP888Device *> mDevices;
    qint16 mIoIndex;

    QList<HvacZone *> mZones;

    void addDevice(QP888Device *device) {
        mDevices.append(device);
    }

    void connectToDevice(HvacZone *zone) {
        qint16 index = mIoIndex + 1;
        //QObject::connect(mDevices.at(index)->outputs())
    }

    void addZone(HvacZone *zone) {
        if (mIoIndex > (mDevices.length() * 8) - 3) {
            connectToDevice(zone);
        } else {
            exit(-1);
        }
    }
};

PhidgetHvacDevice::PhidgetHvacDevice(QObject *parent) :
    QObject(parent),
    p(new PhidgetHvacDevicePrivate)
{
    p->self = this;
    p->mIoIndex = 0;
}

PhidgetHvacDevice::~PhidgetHvacDevice()
{

}


void PhidgetHvacDevice::addDevice(QP888Device *device)
{
    p->addDevice(device);
}

void PhidgetHvacDevice::addZone(HvacZone *zone)
{
    p->addZone(zone);
}
