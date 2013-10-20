#include "HSConnector.h"

class HSConnectorPrivate {
public:
    HSConnector *self;

};

HSConnector::HSConnector(QObject *parent) :
    QObject(parent),
    p(new HSConnectorPrivate)
{
    p->self = this;
}
