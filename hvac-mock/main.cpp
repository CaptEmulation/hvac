#include <QApplication>
#include <QQmlApplicationEngine>
#include "qphidget-mock-qml_plugin.h"
#include "qphidget-qml_plugin.h"

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);


    Qphidget_Mock_QmlPlugin mockPlugin;
    mockPlugin.registerTypes("com.captemulation.qphidget.mock");

    Qphidget_QmlPlugin plugin;
    plugin.registerTypes("com.captemulation.qphidget");

    QQmlApplicationEngine engine;
    engine.addImportPath("../qml");
    engine.load("qml/hvac-mock/main.qml");
    Q_UNUSED(engine)
    return app.exec();
}
