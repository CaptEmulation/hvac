#-------------------------------------------------
#
# Project created by QtCreator 2013-10-17T21:17:17
#
#-------------------------------------------------

###########################
###    SETUP OUTPUT     ###
###########################

DEBUG_TARGET = hvac-service-qphidgetd
RELEASE_TARGET = hvac-service-qphidget
OUTDIR = ../..

CONFIG(debug, debug|release){
    TARGET = $$DEBUG_TARGET
}

CONFIG(release, debug|release){
    TARGET = $$RELEASE_TARGET
    DEFINES += QT_NO_DEBUG_OUTPUT
}

DESTDIR = $$OUTDIR/lib/$$RELEASE_TARGET


QT       -= gui

TARGET = hvac-service-qphidget
TEMPLATE = lib

DEFINES += HVACSERVICEQPHIDGET_LIBRARY

SOURCES += HSConnector.cpp \
    HSPhidgetDeviceManager.cpp

HEADERS += $$PWD/HSConnector.h\
    $$PWD/hvac-service-qphidget_global.h \
    $$PWD/HSPhidgetDeviceManager.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}



###########################
###       INSTALL       ###
###########################

OUTINCLUDE = $$PWD/../../include

win32 {
    OUTINCLUDE ~= s,/,\\,g
    QMAKE_POST_LINK += $$quote(if not exist $$OUTINCLUDE\\$$RELEASE_TARGET mkdir $$OUTINCLUDE\\$$RELEASE_TARGET)

    for(header, HEADERS) {
        header ~= s,/,\\,g
        QMAKE_POST_LINK += $$quote(xcopy $$header $$OUTINCLUDE\\$$RELEASE_TARGET /y)
    }
}

unix {
    QMAKE_POST_LINK += $$quote(mkdir -p $$OUTINCLUDE/$$RELEASE_TARGET$$escape_expand(\\n\\t))

    for(header, HEADERS) {
       QMAKE_POST_LINK += $$quote(cp -u $$header $$OUTINCLUDE/$$RELEASE_TARGET$$escape_expand(\\n\\t))
    }
}


# QtWebApp-lib

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../lib/QWebServer/ -lQWebServerd
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../lib/QWebServer/ -lQWebServerdd
else:unix: LIBS += -L$$PWD/../../lib/QWebServer/ -lQWebServerd

INCLUDEPATH += $$PWD/../../include/QWebServer
DEPENDPATH += $$PWD/../../include/QWebServer

# hvac-service-lib

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../lib/hvac-service/ -lhvac-service-lib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../lib/hvac-service/ -lhvac-service-libd
else:unix: LIBS += -L$$PWD/../../lib/hvac-service/ -lhvac-service-lib

INCLUDEPATH += $$PWD/../../include/hvac-service
DEPENDPATH += $$PWD/../../include/hvac-service

# Using the qphidget-mock library for eraly development
#   switch over to qphidget-lib for real device usage

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../lib/qphidget-mock/ -lqphidget-mock
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../lib/qphidget-mock/ -lqphidget-mockd
else:unix: LIBS += -L$$PWD/../../lib/qphidget-mock/ -lqphidget-mock

INCLUDEPATH += $$PWD/../../include/qphidget-mock
DEPENDPATH += $$PWD/../../include/qphidget-mock
