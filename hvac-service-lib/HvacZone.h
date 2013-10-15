#ifndef HVACZONE_H
#define HVACZONE_H

#include <QVariantMap>
#include <QObject>

class HvacZonePrivate;

class HvacZone : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString mode READ mode WRITE setMode NOTIFY modeChanged)
    Q_PROPERTY(QString fanMode READ fanMode WRITE setFanMode NOTIFY fanModeChanged)

public:
    explicit HvacZone(QObject *parent = 0);
    ~HvacZone();

    void lock();
    void unlock();

    void fromMap(QVariantMap map) {
        if (map.contains("mode")) {
            setMode(map["mode"].toString());
        }

        if (map.contains("fanMode")) {
            setFanMode(map["fanMode"].toString());
        }
    }

    QVariantMap toMap() {
        QVariantMap map;
        map["name"] = name();
        map["mode"] = mode();
        map["fanMode"] = fanMode();
        return map;
    }

QString name() const;
QString mode() const;
QString fanMode() const;

signals:

void nameChanged(QString arg);
void modeChanged(QString arg);
void fanModeChanged(QString arg);

public slots:

void setName(QString arg);
void setMode(QString arg);
void setFanMode(QString arg);

private:
    QScopedPointer<HvacZonePrivate> p;
};

#endif // HVACZONE_H
