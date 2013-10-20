#include "HSPhidgetDeviceManager.h"

#define IFK_INPUTS 8
#define IFK_OUTPUTS 8

class HSPhidgetDeviceManagerPrivate {
public:
    HSPhidgetDeviceManager *self;

    QList<QP888Device *> mDevices;
    ResourceInformation mResources;
    qint16 mLastDeviceIndex;
    qint16 mLastInputIndex;

    QList<HvacZone *> mZones;

    QList<QP888Device *> devices() const {
        return mDevices;
    }

    void addDevice(QP888Device *device) {
        mDevices.append(device);
        mResources.phidgetDevices++;
        mResources.unusedPhidgetDevices++;
        mResources.phidgetInputs += IFK_INPUTS;
        mResources.unsuedPhidgetInputs += IFK_INPUTS;
        mResources.phidgetOutputs += IFK_OUTPUTS;
        mResources.unsuedPhidgetOutputs += IFK_OUTPUTS;
        int newSupportedZones = mResources.phidgetInputs / 3;
        mResources.supportedEmptyZones += (newSupportedZones - mResources.supportedZones);
        mResources.supportedZones = newSupportedZones;
        emit self->resourceChanged(mResources);
    }


    void connectToDevice(HvacZone *zone) {
        if (mResources.supportedEmptyZones) {

            int startingIndex = (mResources.phidgetInputs - mResources.unsuedPhidgetInputs) % 8;
            for (int i = 0; i < 3 ; i ++) {
                mResources.unsuedPhidgetInputs--;
                int index = mResources.phidgetInputs - mResources.unsuedPhidgetInputs;
                //QObject::connect(mDevices.at(index / 8)->outputs().at(startingIndex + i), SIGNAL(stateChanged(bool))

            }
            mResources.supportedEmptyZones--;
            mResources.unsuedPhidgetOutputs--;


            // Check if need to increment unusedPhidgetCount
            //    First zone case or when crossing input boundary
            if ((mResources.phidgetInputs == (mResources.unsuedPhidgetInputs + 3)) || ((startingIndex % 8) > 5 )) {
                mResources.unusedPhidgetDevices--;
            }

            self->resourceChanged(mResources);
        } else {
            emit self->unableToAddZone(mResources);
        }
    }

    bool addZone(HvacZone *zone) {
        bool success = true;
        if (mResources.supportedEmptyZones > 0) {
            connectToDevice(zone);
        } else {
            success = false;
        }
        return success;
    }

    void start() {
        foreach(QP888Device *d, mDevices) {
            if (!d->connected()) {
                d->open();
            }
        }
    }

    void stop() {
        foreach(QP888Device *d, mDevices) {
            if (d->connected()) {
                d->close();
            }
        }
    }

};

HSPhidgetDeviceManager::HSPhidgetDeviceManager(QObject *parent) :
    QObject(parent),
    p(new HSPhidgetDeviceManagerPrivate)
{
    p->self = this;
    p->mResources = { 0, 0, 0, 0, 0, 0, 0, 0 };
    p->mLastInputIndex = 0;
    p->mLastDeviceIndex = 0;
}

HSPhidgetDeviceManager::~HSPhidgetDeviceManager()
{

}

QList<QP888Device *> HSPhidgetDeviceManager::devices() const
{
    return p->devices();
}


void HSPhidgetDeviceManager::addDevice(QP888Device *device)
{
    p->addDevice(device);
}

bool HSPhidgetDeviceManager::addZone(HvacZone *zone)
{
    return p->addZone(zone);
}

void HSPhidgetDeviceManager::start()
{
    p->start();
}

void HSPhidgetDeviceManager::stop()
{
    p->stop();
}
