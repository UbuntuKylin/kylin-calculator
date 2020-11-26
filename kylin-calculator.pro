
QT       += core gui network KWindowSystem dbus

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += \
    c++11 \
    link_pkgconfig

PKGCONFIG += \
    gsl

TARGET = kylin-calculator

VERSION = 1.0.4

target.path = /usr/bin
target.source += $$TARGET

icon.path = /usr/share/icons/ukui-icon-theme-default/64x64/apps
icon.files = calc.png

desktop.path = /usr/share/applications/
desktop.files = kylin-calculator.desktop

appdesktop.path = /usr/share/applications/
appdesktop.files = kylin-calculator.desktop




INSTALLS += \
    target     \
    icon       \
    desktop    \
    appdesktop

TRANSLATIONS += ./data/kylin-calculator_zh_CN.ts

#TEMPLATE = app

INCLUDEPATH += \
    $$PWD/src/cal/      \
    $$PWD/src/BigFloat/ \
    $$PWD/src/input/    \
    $$PWD/src/symbols/

SOURCES += \
    $$PWD/src/symbols/InputSymbols.cpp     \
    $$PWD/src/BigFloat/BigFloat.cpp        \
    $$PWD/src/cal/QStringCalculator.cpp    \
    $$PWD/src/input/InputJudgmentGraph.cpp \
    $$PWD/src/input/InputTools.cpp         \
    $$PWD/src/input/InputProcess.cpp       \
    $$PWD/src/main.cpp                     \
    $$PWD/src/mainwindow.cpp               \
    $$PWD/src/titlebar.cpp                 \
    $$PWD/src/widgetstyle.cpp              \
    $$PWD/src/funclist.cpp                 \
    $$PWD/src/standardmodel.cpp            \
    $$PWD/src/scientificmodel.cpp          \
    $$PWD/src/toolmodel.cpp                \
    $$PWD/src/basicbutton.cpp              \
    $$PWD/src/daemonipcdbus.cpp            


HEADERS += \
    $$PWD/src/symbols/InputSymbols.h       \
    $$PWD/src/BigFloat/BigFloat.h          \
    $$PWD/src/cal/QStringCalculator.h      \
    $$PWD/src/input/InputJudgmentGraph.h   \
    $$PWD/src/input/InputTools.h           \
    $$PWD/src/input/InputProcess.h         \
    $$PWD/src/mainwindow.h                 \
    $$PWD/src/titlebar.h                   \
    $$PWD/src/widgetstyle.h                \
    $$PWD/src/scientificmodel.h            \
    $$PWD/src/funclist.h                   \
    $$PWD/src/standardmodel.h              \
    $$PWD/src/toolmodel.h                  \
    $$PWD/src/basicbutton.h                \
    $$PWD/src/cal.h                        \
    $$PWD/src/daemonipcdbus.h

RESOURCES += \
    image.qrc
