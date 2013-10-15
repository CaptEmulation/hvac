#include <QtGui/QGuiApplication>
#include <QSettings>
#include <httplistener.h>

#include "qtquick2applicationviewer.h"
#include "HvacServiceLib.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    HvacServiceLib serviceLib(QGuiApplication::applicationDirPath() + "/service");
    serviceLib.start();



    QtQuick2ApplicationViewer viewer;
    viewer.setMainQmlFile(QStringLiteral("qml/hvac-service-mock/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
