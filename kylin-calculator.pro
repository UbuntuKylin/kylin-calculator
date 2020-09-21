
QT       += core gui network

VERSION = 1.0.1

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = kylin-calculator

VERSION = 1.0.0

target.path = /usr/bin
target.source += $$TARGET

icon.path = /usr/share/icons/ukui-icon-theme-default/64x64/apps
icon.files = calc.png

desktop.path = /usr/share/applications/
desktop.files = kylin-calculator.desktop

appdesktop.path = /usr/share/applications/
appdesktop.files = kylin-calculator.desktop


INSTALLS += target \
    icon \
    desktop \
    appdesktop

#TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    titlebar.cpp \
    cal.cpp \
    widgetstyle.cpp \
    funclist.cpp \
    standardmodel.cpp \
    scientificmodel.cpp \
    toolmodel.cpp

HEADERS += \
    mainwindow.h \
    titlebar.h \
    widgetstyle.h \
    cal.h \
    scientificmodel.h \
    funclist.h \
    standardmodel.h \
    parentbutton.h \
    toolmodel.h

RESOURCES += \
    image.qrc
