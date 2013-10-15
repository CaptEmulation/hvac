#include "HvacServiceLib.h"
#include "HvacZoneMapper.h"
#include <httplistener.h>
#include <QDir>
#include <QFile>
#include <QMutex>
#include <QSettings>

class HvacServiceLibPrivate {
public:

    HvacServiceLib *self;
    QString mWorkPath;
    HvacZoneMapper *mHandler;
    QScopedPointer<HttpListener> mListener;

    void checkWorkPath() {
        QDir path = QDir(mWorkPath);
        bool isNew = false;
        if (!path.exists()) {
            path.mkpath(".");
            isNew = true;
        }
        if (isNew) {
            QFile::copy(":/config/defaults.ini", mWorkPath + "/config.ini");
            QFile::copy(":/config/zones.ini", mWorkPath + "/zones.ini");
        }
    }

    void initializeHvac() {
        mHandler = new HvacZoneMapper(self);
        QObject::connect(mHandler, SIGNAL(operationOnObject(QByteArray,QObject*,QByteArray)), self, SIGNAL(operationOnObject(QByteArray,QObject*,QByteArray)));
        QSettings zones(mWorkPath + "/zones.ini", QSettings::IniFormat);
        foreach(QString zoneName, zones.childGroups()) {
            HvacZone *zone = new HvacZone(mHandler);
            zones.beginGroup(zoneName);
            zone->setName(zoneName);
            zone->setMode(zones.value("mode").toString());
            zone->setFanMode(zones.value("fanMode").toString());
            mHandler->addZone(zone);
            zones.endGroup();
        }
    }

    void initializeWebService() {
        QSettings *listenerSettings = new QSettings(mWorkPath + "/config.ini", QSettings::IniFormat, self);
        listenerSettings->beginGroup("listener");
        mListener.reset(new HttpListener(listenerSettings, mHandler));
    }

    void start() {
        checkWorkPath();
        initializeHvac();
        initializeWebService();

    }

    QList<HvacZone *> zones() {
        return mHandler->zones();
    }

};

HvacServiceLib::HvacServiceLib(QObject *parent) :
    HvacServiceLib("", parent)
{
}

HvacServiceLib::HvacServiceLib(QString workPath, QObject *parent) :
    QObject(parent),
    p(new HvacServiceLibPrivate)
{
    p->self = this;
    p->mWorkPath = workPath;
}

HvacServiceLib::~HvacServiceLib()
{

}

void HvacServiceLib::start()
{
    p->start();
}

QList<HvacZone *> HvacServiceLib::zones()
{
    return p->zones();
}
