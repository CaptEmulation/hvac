#ifndef HVACZONEMAPPER_H
#define HVACZONEMAPPER_H

#include <httprequesthandler.h>
#include "HvacZone.h"

class HvacZoneMapperPrivate;

class HvacZoneMapper : public HttpRequestHandler
{
    Q_OBJECT
public:
    explicit HvacZoneMapper(QObject *parent = 0);
    ~HvacZoneMapper();

    void addZone(HvacZone *zone);
    QList<HvacZone *> zones();

    void service(HttpRequest &request, HttpResponse &response);

signals:
    void operationOnObject(const QByteArray &method, QObject *obj, const QByteArray &data);

public slots:


private:
    QScopedPointer<HvacZoneMapperPrivate> p;
};

#endif // HVACZONEMAPPER_H
