
#include <QCoreApplication>
#include <QTest>
#include "tst_HvacServiceTest.h"
#include "tst_HvacServiceQPhidget.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    HvacServiceQPhidgetTest phidgetTests;
    QTest::qExec(&phidgetTests, argc, argv);

    HvacServiceTest *hvacServiceTest = new HvacServiceTest;
    QObject::connect(hvacServiceTest, SIGNAL(destroyed()), &app, SLOT(quit()));
    QTest::qExec(hvacServiceTest, argc, argv);


    return app.exec();
}
