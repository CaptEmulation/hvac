#ifndef TST_HVACSERVICETEST_H
#define TST_HVACSERVICETEST_H

#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QSettings>
#include <QJsonDocument>

#include "HvacServiceLib.h"

class HvacServiceTest : public QObject
{
    Q_OBJECT

public:
    HvacServiceTest();

    QNetworkAccessManager qnam;
    HvacServiceLib *service;

private Q_SLOTS:
    void initTestCase() {
        QString src(SRCDIR);
        QDir tmp(src + "/tmp");
        if (!tmp.exists()) {
            tmp.mkdir(".");
        }
        tmp.setNameFilters(QStringList() << "*.ini");
        tmp.setFilter(QDir::Files);
        foreach(QString dirFile, tmp.entryList())
        {
            tmp.remove(dirFile);
        }
        QFile::copy(src + "/config.ini", src + "/tmp/config.ini");
        QFile::copy(src + "/zones.ini", src + "/tmp/zones.ini");

        service = new HvacServiceLib(src + "/tmp", this);
        service->start();
    }

    void cleanupTestCase() {
        deleteLater();
    }

    void getZoneMatchesSettings() {
        QNetworkReply *reply = qnam.get(QNetworkRequest(getUrl() + "/upstairs"));
        QSignalSpy replyFinishedSpy(reply, SIGNAL(finished()));
        QTRY_VERIFY(replyFinishedSpy.count());
        QString actual = reply->readAll();
        QCOMPARE(actual, QString(jsonZone("upstairs")));
    }


    void postZoneEmitsOperationChanged() {
        // Setup
        QSignalSpy objectPostedSpy(service, SIGNAL(operationOnObject(QByteArray,QObject*,QByteArray)));
        QNetworkRequest request(getUrl() + "/upstairs");
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        QVariantMap zoneMap;
        zoneMap["mode"] = QString("heat");

        // Post
        QByteArray postRequestData = QJsonDocument::fromVariant(zoneMap).toJson();
        QNetworkReply *reply = qnam.post(request, postRequestData);
        QSignalSpy replyFinishedSpy(reply, SIGNAL(finished()));

        // Wait
        QTRY_VERIFY(objectPostedSpy.count());
        QTRY_VERIFY(replyFinishedSpy.count());

        // Verify
        QByteArray actual = objectPostedSpy.first().at(2).toByteArray();
        QCOMPARE(actual, postRequestData);
        QCOMPARE(objectPostedSpy.first().at(1).value<QObject *>()->property("mode"), zoneMap["mode"]);
    }

    void zoneEmitsChangesOnPost() {
        // Setup
        HvacZone *zone = Q_NULLPTR;
        foreach(HvacZone *z, service->zones()) {
            if (z->name() == "zoneEmitsChangesOnPost") {
                zone = z;
            }
        }
        QVERIFY(zone);
        QSignalSpy zoneModeChanged(zone, SIGNAL(modeChanged(QString)));
        QSignalSpy zoneFanModeChanged(zone, SIGNAL(fanModeChanged(QString)));
        QNetworkRequest request(getUrl() + "/zoneEmitsChangesOnPost");
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        QVariantMap zoneMap;
        zoneMap["mode"] = "heat";
        zoneMap["fanMode"] = "on";

        // Post
        QByteArray postRequestData = QJsonDocument::fromVariant(zoneMap).toJson();
        QNetworkReply *reply = qnam.post(request, postRequestData);
        QSignalSpy replyFinishedSpy(reply, SIGNAL(finished()));

        // Wait
        QTRY_VERIFY(replyFinishedSpy.count());

        // Verify
        QVERIFY(zoneFanModeChanged.count());
        QVERIFY(zoneModeChanged.count());
        QString fanMode = zoneFanModeChanged.takeFirst().at(0).toString();
        QCOMPARE(fanMode, zone->fanMode());
        QCOMPARE(fanMode, zoneMap["fanMode"].toString());
        QString mode = zoneModeChanged.takeFirst().at(0).toString();
        QCOMPARE(mode, zone->mode());
        QCOMPARE(mode, zoneMap["mode"].toString());
    }

    void getUpdatesToZone() {
        // Setup
        HvacZone *zone = Q_NULLPTR;
        foreach(HvacZone *z, service->zones()) {
            if (z->name() == "zoneEmitsChangesOnPost") {
                zone = z;
            }
        }
        QVERIFY(zone);
        zone->setMode("cool");
        zone->setFanMode("on");

        // Get
        QNetworkReply *reply = qnam.get(QNetworkRequest(getUrl() + "/zoneEmitsChangesOnPost"));
        QSignalSpy replyFinishedSpy(reply, SIGNAL(finished()));
        QTRY_VERIFY(replyFinishedSpy.count());
        QString actual = reply->readAll();
        QCOMPARE(actual, QString(QJsonDocument::fromVariant(zone->toMap()).toJson()));
    }



private:

    HvacZone *zone(QString name) {
        QSettings settings(QString(SRCDIR) + "/tmp/zones.ini", QSettings::IniFormat);
        settings.beginGroup(name);
        HvacZone *zone = new HvacZone(this);
        zone->setName(name);
        zone->setMode(settings.value("mode").toString());
        zone->setFanMode(settings.value("fanMode").toString());
        return zone;
    }

    QByteArray jsonZone(QString name) {
        HvacZone *z = zone(name);
        return QJsonDocument::fromVariant(z->toMap()).toJson();
    }

    QString getUrl() {
        return QString("http://localhost:15412");
    }
};


#endif
