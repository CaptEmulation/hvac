#include "HvacZone.h"

#include <QMutex>

class HvacZonePrivate {
public:
    HvacZone *self;

    QMutex m_mutex;
    QString m_name;
    QString m_mode;
    QString m_fanMode;

    QString name() const
    {
        return m_name;
    }

    void setName(QString arg)
    {
        lock();
        if (m_name != arg) {
            m_name = arg;
            unlock();
            emit self->nameChanged(arg);
        } else {
            unlock();
        }
    }

    QString mode() const
    {
        return m_mode;
    }

    void setMode(QString arg)
    {
        lock();
        if (m_mode != arg) {
            m_mode = arg;
            unlock();
            emit self->modeChanged(arg);
        } else {
            unlock();
        }
    }

    QString fanMode() const
    {
        return m_fanMode;
    }


    void setFanMode(QString arg)
    {
        lock();
        if (m_fanMode != arg) {
            m_fanMode = arg;
            unlock();
            emit self->fanModeChanged(arg);
        } else {
            unlock();
        }
    }

    void lock() {
        m_mutex.lock();
    }

    void unlock() {
        m_mutex.unlock();
    }
};

HvacZone::HvacZone(QObject *parent) :
    QObject(parent),
    p(new HvacZonePrivate)
{
    p->self = this;
}

HvacZone::~HvacZone()
{

}

void HvacZone::lock()
{
    p->lock();
}

void HvacZone::unlock()
{
    p->unlock();
}

QString HvacZone::name() const
{
    return p->name();
}

QString HvacZone::mode() const
{
    return p->mode();
}

QString HvacZone::fanMode() const
{
    return p->fanMode();
}

void HvacZone::setName(QString arg)
{
    p->setName(arg);
}

void HvacZone::setMode(QString arg)
{
    p->setMode(arg);
}

void HvacZone::setFanMode(QString arg)
{
    p->setFanMode(arg);
}
