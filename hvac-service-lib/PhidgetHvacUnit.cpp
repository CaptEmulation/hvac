//#include "PhidgetHvacUnit.h"

//class PhidgetHvacUnitPrivate {
//public:
//    PhidgetHvacUnit *self;

//    QList<QP888Device *> mDevices;
//    qint16 mIoIndex;

//    QList<HvacZone *> mZones;

//    void addDevice(QP888Device *device) {
//        mDevices.append(device);
//    }

//    void connectToDevice(HvacZone *zone) {
//        qint16 index = mIoIndex + 1;
//        //QObject::connect(mDevices.at(index)->outputs())
//    }

//    void addZone(HvacZone *zone) {
//        if (mIoIndex > (mDevices.length() * 8) - 3) {
//            connectToDevice(zone);
//        } else {
//            exit(-1);
//        }
//    }
//};

//PhidgetHvacUnit::PhidgetHvacUnit(QObject *parent) :
//    QObject(parent),
//    p(new PhidgetHvacUnitPrivate)
//{
//    p->self = this;
//    p->mIoIndex = 0;
//}

//PhidgetHvacUnit::~PhidgetHvacUnit()
//{

//}


//void PhidgetHvacUnit::addDevice(QP888Device *device)
//{
//    p->addDevice(device);
//}

//void PhidgetHvacUnit::addZone(HvacZone *zone)
//{
//    p->addZone(zone);
//}
