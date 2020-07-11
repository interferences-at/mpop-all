QT += websockets
QT += sql
QT += core
# QT -= gui

TARGET = mpop_service
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    facade.cpp \
    main.cpp \
    mpopservice.cpp \
    notification.cpp \
    request.cpp \
    response.cpp

HEADERS += \
    config.h \
    facade.h \
    mpopservice.h \
    notification.h \
    request.h \
    response.h

# EXAMPLE_FILES += exampleclient.html

INSTALLS += TARGET
