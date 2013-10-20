#ifndef HSCONNECTOR_H
#define HSCONNECTOR_H

#include <QObject>

class HSConnectorPrivate;

class HSConnector : public QObject
{
    Q_OBJECT
public:
    explicit HSConnector(QObject *parent = 0);

signals:

public slots:

private:
    QScopedPointer<HSConnectorPrivate> p;
};

#endif // HSCONNECTOR_H
