#-------------------------------------------------
#
# Project created by QtCreator 2013-10-06T10:00:05
#
#-------------------------------------------------


###########################
###    SETUP OUTPUT     ###
###########################

DEBUG_TARGET = hvac-serviced
RELEASE_TARGET = hvac-service
OUTDIR = ../..

CONFIG(debug, debug|release){
    TARGET = $$DEBUG_TARGET
}

CONFIG(release, debug|release){
    TARGET = $$RELEASE_TARGET
    DEFINES += QT_NO_DEBUG_OUTPUT
}

DESTDIR = $$OUTDIR/lib/$$RELEASE_TARGET

QT       += network serviceframework

QT       -= gui

TARGET = hvac-service-lib
TEMPLATE = lib

DEFINES += HVACSERVICELIB_LIBRARY

SOURCES += HvacServiceLib.cpp \
    HvacZone.cpp \
    HvacZoneRequestHandler.cpp \
    HvacZoneMapper.cpp \
    PhidgetHvacUnit.cpp

HEADERS += HvacServiceLib.h\
        hvac-service-lib_global.h \
    HvacZone.h \
    HvacZoneRequestHandler.h \
    HvacZoneMapper.h


RESOURCES += \
    resources.qrc

OTHER_FILES += \
    defaults.ini \
    zones.ini


unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

# QtWebApp-lib

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../lib/QWebServer/ -lQWebServerd
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../lib/QWebServer/ -lQWebServerdd
else:unix: LIBS += -L$$PWD/../../lib/QWebServer/ -lQWebServerd

INCLUDEPATH += $$PWD/../../include/QWebServer
DEPENDPATH += $$PWD/../../include/QWebServer



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
