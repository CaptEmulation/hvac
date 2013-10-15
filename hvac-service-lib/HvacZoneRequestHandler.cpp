#include "HvacZoneRequestHandler.h"

#include <httpresponse.h>
#include <QJsonDocument>

class HvacZoneRequestHandlerPrivate {
public:
    HvacZoneRequestHandler *self;
    HvacZone * mZone;

    HvacZone *zone() {
        return mZone;
    }

    void setZone(HvacZone *zone) {
        if (mZone != zone) {
            mZone = zone;
            emit self->zoneChanged(zone);
        }
    }

    void service(HttpRequest &request, HttpResponse &response) {
        QByteArray data(request.getBody());
        QByteArray method = request.getMethod();
        bool handled = false;

        if (method == QByteArray("GET")) {
            QJsonDocument document = QJsonDocument::fromVariant(mZone->toMap());
            data = document.toJson();
            response.write(data);
            handled = true;
        } else if (method == QByteArray("POST") || method == QByteArray("PUT")) {
            QJsonDocument document = QJsonDocument::fromJson(data);
            zone()->fromMap(document.toVariant().toMap());
            handled = true;
        } else {
            response.setStatus(500, "not handled");
            response.write("500 not handled");
        }

        if (handled) {
            emit self->operationOnObject(method, mZone, data);
        }
    }
};


HvacZoneRequestHandler::HvacZoneRequestHandler(QObject *parent) :
    HttpRequestHandler(parent),
    p(new HvacZoneRequestHandlerPrivate)
{
    p->self = this;
}

HvacZoneRequestHandler::~HvacZoneRequestHandler()
{

}

void HvacZoneRequestHandler::service(HttpRequest &request, HttpResponse &response)
{
    p->service(request, response);
}

HvacZone *HvacZoneRequestHandler::zone()
{
    return p->zone();
}

void HvacZoneRequestHandler::setZone(HvacZone *zone)
{
    p->setZone(zone);
}
