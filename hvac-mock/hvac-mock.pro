# Add more folders to ship with the application, here
folder_01.source = qml/hvac-mock
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

QT += widgets

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp

# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()


# qphidget-mock-qml


# qphidget-mock


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../lib/qphidget-mock/ -lqphidget-mock
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../lib/qphidget-mock/ -lqphidget-mockd
else:unix: LIBS += -L$$PWD/../../lib/qphidget-mock/ -lqphidget-mock

INCLUDEPATH += $$PWD/../../include/qphidget-mock
DEPENDPATH += $$PWD/../../include/qphidget-mock


# qphidget-qml

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../lib/qphidget-qml/ -lqphidget-qml
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../lib/qphidget-qml/ -lqphidget-qmld
else:unix: LIBS += -L$$PWD/../../lib/qphidget-qml/ -lqphidget-qml

INCLUDEPATH += $$PWD/../../include/qphidget-qml
DEPENDPATH += $$PWD/../../include/qphidget-qml

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../lib/qphidget-qml/qphidget-qml.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../lib/qphidget-qml/qphidget-qmld.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../lib/qphidget-qml/libqphidget-qml.a


#QPhidget library will be rebuilt from sources linked against the test mock library

INCLUDEPATH += $$PWD/../qphidget-lib/src
HEADERS += $$PWD/../qphidget-lib/src/*.h
SOURCES += $$PWD/../qphidget-lib/src/*.cpp

OTHER_FILES += \
    ../qml/DigitalOutput.qml \
    ../qml/DigitalInput.qml \
    ../qml/DigitalOutput.qml \
    ../qml/IOBox.qml \
    ../qml/Ifk888Tester.qml \
    ../qml/MockIFK888.qml \
    qml/hvac-mock/Zone.qml \
    qml/hvac-mock/Thermostat.qml \
    qml/hvac-mock/Rocker.qml \
    qml/hvac-mock/main.qml \
    qml/hvac-mock/HouseHvac.qml

