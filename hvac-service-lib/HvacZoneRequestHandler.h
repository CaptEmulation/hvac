#ifndef HVACZONEREQUESTHANDLER_H
#define HVACZONEREQUESTHANDLER_H

#include <httprequesthandler.h>

#include "HvacZone.h"

class HvacZoneRequestHandlerPrivate;

class HvacZoneRequestHandler : public HttpRequestHandler
{
    Q_OBJECT
    Q_PROPERTY(HvacZone *zone READ zone WRITE setZone NOTIFY zoneChanged)
public:
    explicit HvacZoneRequestHandler(QObject *parent = 0);
    ~HvacZoneRequestHandler();

    void service(HttpRequest &request, HttpResponse &response);

    HvacZone *zone();

signals:
    void zoneChanged(HvacZone *zome);
    void operationOnObject(const QByteArray &method, QObject *obj, const QByteArray &data);

public slots:
    void setZone(HvacZone *zone);

private:
    QScopedPointer<HvacZoneRequestHandlerPrivate> p;
};

#endif // HVACZONEREQUESTHANDLER_H
