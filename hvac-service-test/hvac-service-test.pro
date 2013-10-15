#-------------------------------------------------
#
# Project created by QtCreator 2013-10-13T19:44:31
#
#-------------------------------------------------

###########################
###      QT CONFIG      ###
###########################

QT       += network testlib

QT       -= gui

TARGET = tst_HvacServiceTest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


HEADERS += tst_HvacServiceTest.h
DEFINES += SRCDIR=\\\"$$PWD/\\\"

SOURCES += \
    tst_HvacServiceTest.cpp \
    main.cpp

OTHER_FILES += \
    config.ini \
    zones.ini


###########################################
# Libraries
###########################################

# qtwebapp-lib

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

