#ifndef HVACSERVICELIB_H
#define HVACSERVICELIB_H

#include "hvac-service-lib_global.h"
#include <QObject>

#include "HvacZone.h"

class HvacServiceLibPrivate;

class HVACSERVICELIBSHARED_EXPORT HvacServiceLib : public QObject
{
    Q_OBJECT

public:
    HvacServiceLib(QObject *parent = 0);
    HvacServiceLib(QString workPath, QObject *parent = 0);
    ~HvacServiceLib();

    void start();

    QList<HvacZone *> zones();

signals:
    void operationOnObject(const QByteArray &method, QObject *obj, const QByteArray &data);

private slots:


private:
    QScopedPointer<HvacServiceLibPrivate> p;
};

#endif // HVACSERVICELIB_H
