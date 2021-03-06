QT += quick
QT += core
QT += serialport
QT += opengl
win32:LIBS += -lOpengl32
CONFIG += c++11

# Disable macOS version check (it prints a WARNING)
CONFIG += sdk_no_version_check

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QOSC_LIBRARY

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../qosc/contrib/oscpack/OscOutboundPacketStream.cpp \
    ../qosc/contrib/oscpack/OscPrintReceivedElements.cpp \
    ../qosc/contrib/oscpack/OscReceivedElements.cpp \
    ../qosc/contrib/oscpack/OscTypes.cpp \
    ../qosc/oscreceiver.cpp \
    ../qosc/oscsender.cpp \
    kioskconfig.cpp \
    main.cpp \
    rfidreader.cpp \
    screensaver.cpp \
    stick.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    ../qosc/contrib/oscpack/MessageMappingOscPacketListener.h \
    ../qosc/contrib/oscpack/OscException.h \
    ../qosc/contrib/oscpack/OscHostEndianness.h \
    ../qosc/contrib/oscpack/OscOutboundPacketStream.h \
    ../qosc/contrib/oscpack/OscPacketListener.h \
    ../qosc/contrib/oscpack/OscPrintReceivedElements.h \
    ../qosc/contrib/oscpack/OscReceivedElements.h \
    ../qosc/contrib/oscpack/OscTypes.h \
    ../qosc/oscreceiver.h \
    ../qosc/oscsender.h \
    kioskconfig.h \
    rfidreader.h \
    screensaver.h \
    stick.h

INCLUDEPATH += $$PWD/../qosc
INCLUDEPATH += $$PWD/../qosc/contrib/packosc

# Should disable assertions # FIXME: It doesn't
CONFIG(release, debug|release): DEFINES += NDEBUG

# copy static files to build folder

#copydata.commands = $(COPY_DIR) \"$$shell_path($$PWD/resources)\" \"$$shell_path($$OUT_PWD)/static\"
#first.depends = $(first) copydata
#export(first.depends)
#export(copydata.commands)
#QMAKE_EXTRA_TARGETS += first copydata

# # Add the qosc library:
# win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../qosc/release/ -lqosc_release_binary
# else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../qosc/ -lqosc_debug_binary  # FIXME there was a /debug/ directory in the path, but it's gone.
# else:unix: LIBS += -L$$OUT_PWD/../qosc/ -lrelease_binary
#
# INCLUDEPATH += $$PWD/../qosc
# DEPENDPATH += $$PWD/../qosc
#
# win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../qosc/release/libqosc_release_binary.a
# else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../qosc/libqosc_debug_binary.a # FIXME: there was /debug/ in the path as last directory before I removed it
# else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../qosc/release/qosc_release_binary.lib
# else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../qosc/debug/qosc_debug_binary.lib
# else:unix: PRE_TARGETDEPS += $$OUT_PWD/../qosc/libqosc_release_binary.a

DISTFILES +=

