#include "HvacZoneMapper.h"
#include "HvacZoneRequestHandler.h"

#include <QStringList>

class HvacZoneMapperPrivate {
public:
    HvacZoneMapper *self;
    QList<HvacZoneRequestHandler *> mZones;

    void addZone(HvacZone *zone) {
        HvacZoneRequestHandler *handler = new HvacZoneRequestHandler(self);
        QObject::connect(handler, SIGNAL(operationOnObject(QByteArray,QObject*,QByteArray)), self, SIGNAL(operationOnObject(QByteArray,QObject*,QByteArray)));
        handler->setZone(zone);
        mZones.append(handler);
    }

    bool isResource(QByteArray path, HvacZoneRequestHandler *handler) {
        QStringList paths = QString(path).split("/", QString::SkipEmptyParts);
        QString subPath = paths.length() ? paths.at(0) : "";
        if (handler->zone()->name() == subPath) {
            return true;
        }
        return false;
    }

    void service(HttpRequest &request, HttpResponse &response) {
        bool handled = false;
        foreach (HvacZoneRequestHandler *handler, mZones) {
            if (isResource(request.getPath(), handler)) {
                handler->service(request, response);
                handled = true;
                break;
            }
        }
        if (!handled) {
            response.setStatus(404,"not found");
            response.write("404 not found",true);
        }
    }

    QList<HvacZone *> zones() {
        QList<HvacZone *> zones;
        foreach (HvacZoneRequestHandler *handler, mZones) {
            zones.append(handler->zone());
        }
        return zones;
    }
};

HvacZoneMapper::HvacZoneMapper(QObject *parent) :
    HttpRequestHandler(parent),
    p(new HvacZoneMapperPrivate)
{
    p->self = this;
}

HvacZoneMapper::~HvacZoneMapper()
{
}

void HvacZoneMapper::addZone(HvacZone *zone)
{
    p->addZone(zone);
}

QList<HvacZone *> HvacZoneMapper::zones()
{
    return p->zones();
}

void HvacZoneMapper::service(HttpRequest &request, HttpResponse &response)
{
    p->service(request, response);
}
