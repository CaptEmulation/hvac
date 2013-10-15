
#include <QCoreApplication>
#include <QTest>
#include "tst_HvacServiceTest.h"





int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    HvacServiceTest *hvacServiceTest = new HvacServiceTest;
    QObject::connect(hvacServiceTest, SIGNAL(destroyed()), &app, SLOT(quit()));
    QTest::qExec(hvacServiceTest, argc, argv);


    return app.exec();
}
