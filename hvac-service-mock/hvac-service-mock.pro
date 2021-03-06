
###########################
###    SETUP OUTPUT     ###
###########################

DEBUG_TARGET = hvac-service-mockd
RELEASE_TARGET = hvac-service-mock
OUTDIR = ../..

CONFIG(debug, debug|release){
    TARGET = $$DEBUG_TARGET
}

CONFIG(release, debug|release){
    TARGET = $$RELEASE_TARGET
    DEFINES += QT_NO_DEBUG_OUTPUT
}

DESTDIR = $$OUTDIR/lib/$$RELEASE_TARGET

###########################
###      QT CONFIG      ###
###########################

# Add more folders to ship with the application, here
folder_01.source = qml/hvac-service-mock
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    PhidgetHvacDevice.cpp \
    HSConnector.cpp

HEADERS += \
    PhidgetHvacDevice.h \
    HSConnector.h

# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()

# hvac-service-lib

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../lib/hvac-service/ -lhvac-service-lib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../lib/hvac-service/ -lhvac-service-libd
else:unix: LIBS += -L$$PWD/../../lib/hvac-service/ -lhvac-service-lib

INCLUDEPATH += $$PWD/../../include/hvac-service
DEPENDPATH += $$PWD/../../include/hvac-service

# QtWebApp-lib

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../lib/QWebServer/ -lQWebServerd
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../lib/QWebServer/ -lQWebServerdd
else:unix: LIBS += -L$$PWD/../../lib/QWebServer/ -lQWebServerd

INCLUDEPATH += $$PWD/../../include/QWebServer
DEPENDPATH += $$PWD/../../include/QWebServer


#######################
# Deploy
#######################

QMAKE_POST_LINK += $$quote(cp -u $$PWD/config.ini $$OUT_PWD$$escape_expand(\\n\\t))
