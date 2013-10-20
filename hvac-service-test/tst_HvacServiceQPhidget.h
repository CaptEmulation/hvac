#ifndef TST_HVACSERVICEQPHIDGET_H
#define TST_HVACSERVICEQPHIDGET_H

#include <QObject>
#include <QTest>
#include <QSignalSpy>


#include "HvacZone.h"
#include "QPMock.h"
#include "QPMock888Device.h"
#include "HSPhidgetDeviceManager.h"

class HvacServiceQPhidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit HvacServiceQPhidgetTest(QObject *parent = 0);

signals:

private slots:

    void initTestCase() {
        mMockIfk = new QPMock888Device(-1, this);
        QPMock::getSingleton()->appendMock(mMockIfk);
        mMockIfk->attach();
    }

    void init() {
        devMgr = new HSPhidgetDeviceManager(this);
    }

    void cleanup() {
        devMgr->deleteLater();
    }

    void sanity() {
        QVERIFY(devMgr);
    }

    void addDevices() {
        QCOMPARE(devMgr->devices().count(), 0);
        QP888Device *ifk888 = new QP888Device(this);
        devMgr->addDevice(ifk888);
        QCOMPARE(devMgr->devices().count(), 1);
        ifk888->deleteLater();
    }

    void devicesAreOpenedWhenServiceIsStarted() {
        QP888Device *ifk888 = new QP888Device(this);
        devMgr->addDevice(ifk888);
        QSignalSpy connectedSpy(ifk888, SIGNAL(connectedChanged(bool)));
        QVERIFY2(!connectedSpy.count(), "Should not connect before starting service");
        devMgr->start();
        QVERIFY2(connectedSpy.count(), "Expected device to be connected");
        ifk888->deleteLater();
    }

    void devicesAreClosedWhenServiceIsDestroyed() {
        QP888Device *ifk888 = new QP888Device(this);
        devMgr->addDevice(ifk888);
        QSignalSpy connectedSpy(ifk888, SIGNAL(connectedChanged(bool)));
        devMgr->start();
        devMgr->stop();
        QVERIFY2(!connectedSpy.takeLast().at(0).toBool(), "Expected last spy to have disconnected");
        QVERIFY2(connectedSpy.takeLast().at(0).toBool(), "Expected first spy to have connected");
        ifk888->deleteLater();
    }

    void resourcesAfterFirstDeviceAppended() {
        QP888Device *ifk888 = new QP888Device(this);
        QSignalSpy resourcesSpy(devMgr, SIGNAL(resourceChanged(ResourceInformation)));
        devMgr->addDevice(ifk888);
        QVERIFY2(resourcesSpy.count(), "Expect resourceChanged signal");
        ResourceInformation rscInfo = resourcesSpy.takeLast().at(0).value<ResourceInformation>();
        QCOMPARE(rscInfo.phidgetDevices, 1);
        QCOMPARE(rscInfo.unusedPhidgetDevices, 1);
        QCOMPARE(rscInfo.phidgetInputs, 8);
        QCOMPARE(rscInfo.phidgetOutputs, 8);
        QCOMPARE(rscInfo.unsuedPhidgetInputs, 8);
        QCOMPARE(rscInfo.unsuedPhidgetOutputs, 8);
        ifk888->deleteLater();
    }

    void resourcesAfterAddingZone() {
        QP888Device *ifk888 = new QP888Device(this);
        QSignalSpy resourcesSpy(devMgr, SIGNAL(resourceChanged(ResourceInformation)));
        devMgr->addDevice(ifk888);

        // Add zone
        HvacZone *zone = new HvacZone(ifk888);
        devMgr->addZone(zone);

        ResourceInformation rscInfo = resourcesSpy.takeLast().at(0).value<ResourceInformation>();
        QCOMPARE(rscInfo.phidgetDevices, 1);
        QCOMPARE(rscInfo.unusedPhidgetDevices, 0);
        QCOMPARE(rscInfo.phidgetInputs, 8);
        QCOMPARE(rscInfo.phidgetOutputs, 8);
        QCOMPARE(rscInfo.unsuedPhidgetInputs, 5);
        QCOMPARE(rscInfo.unsuedPhidgetOutputs, 7);
        QCOMPARE(rscInfo.supportedZones, 2);
        QCOMPARE(rscInfo.supportedEmptyZones, 1);

        ifk888->deleteLater();
    }

    void resourcesAfterAddingMoreZones() {
        QP888Device *ifk888 = new QP888Device(this);
        QSignalSpy resourcesSpy(devMgr, SIGNAL(resourceChanged(ResourceInformation)));
        devMgr->addDevice(ifk888);
        devMgr->addDevice(new QP888Device(ifk888));

        ResourceInformation rscInfo;

        // Add zone
        QVERIFY2(devMgr->addZone(new HvacZone(ifk888)), "Expect to be able to add frist zone");
        rscInfo = resourcesSpy.takeLast().at(0).value<ResourceInformation>();
        QCOMPARE(rscInfo.unusedPhidgetDevices, 1);
        QCOMPARE(rscInfo.unsuedPhidgetInputs, 13);
        QCOMPARE(rscInfo.unsuedPhidgetOutputs, 15);
        QCOMPARE(rscInfo.supportedEmptyZones, 4);
        QVERIFY2(devMgr->addZone(new HvacZone(ifk888)), "Expect to be able to add second zone");
        rscInfo = resourcesSpy.takeLast().at(0).value<ResourceInformation>();
        QCOMPARE(rscInfo.unusedPhidgetDevices, 1);
        QCOMPARE(rscInfo.unsuedPhidgetInputs, 10);
        QCOMPARE(rscInfo.unsuedPhidgetOutputs, 14);
        QCOMPARE(rscInfo.supportedEmptyZones, 3);
        QVERIFY2(devMgr->addZone(new HvacZone(ifk888)), "Expect to be able to add third zone");
        rscInfo = resourcesSpy.takeLast().at(0).value<ResourceInformation>();
        QCOMPARE(rscInfo.unusedPhidgetDevices, 0);
        QCOMPARE(rscInfo.unsuedPhidgetInputs, 7);
        QCOMPARE(rscInfo.unsuedPhidgetOutputs, 13);
        QCOMPARE(rscInfo.supportedEmptyZones, 2);
        QVERIFY2(devMgr->addZone(new HvacZone(ifk888)), "Expect to be able to add forth zone");
        rscInfo = resourcesSpy.takeLast().at(0).value<ResourceInformation>();
        QCOMPARE(rscInfo.unusedPhidgetDevices, 0);
        QCOMPARE(rscInfo.unsuedPhidgetInputs, 4);
        QCOMPARE(rscInfo.unsuedPhidgetOutputs, 12);
        QCOMPARE(rscInfo.supportedEmptyZones, 1);
        QVERIFY2(devMgr->addZone(new HvacZone(ifk888)), "Expect to be able to add fifth zone");
        rscInfo = resourcesSpy.takeLast().at(0).value<ResourceInformation>();
        QCOMPARE(rscInfo.unusedPhidgetDevices, 0);
        QCOMPARE(rscInfo.unsuedPhidgetInputs, 1);
        QCOMPARE(rscInfo.unsuedPhidgetOutputs, 11);
        QCOMPARE(rscInfo.supportedEmptyZones, 0);
        QVERIFY2(!devMgr->addZone(new HvacZone(ifk888)), "Expect sixth zone to fail to add");

        ifk888->deleteLater();
    }

private:

    HSPhidgetDeviceManager *devMgr;
    QPMock888Device *mMockIfk;
};

#endif // TST_HVACSERVICEQPHIDGET_H
