
QT       += core gui network KWindowSystem

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += \
    c++11 \
    link_pkgconfig

PKGCONFIG += \
    gsl

TARGET = input


INCLUDEPATH += \
    $$PWD/../cal/      \
    $$PWD/../BigFloat/ \
    $$PWD/../input/    \
    $$PWD/../symbols/

SOURCES += \
    $$PWD/../symbols/InputSymbols.cpp     \
    $$PWD/../BigFloat/BigFloat.cpp        \
    $$PWD/../cal/QStringCalculator.cpp    \
    $$PWD/../input/InputJudgmentGraph.cpp \
    $$PWD/../input/InputTools.cpp         \
    $$PWD/../input/InputProcess.cpp\
    main.cpp

HEADERS += \
    $$PWD/../symbols/InputSymbols.h       \
    $$PWD/../BigFloat/BigFloat.h          \
    $$PWD/../cal/QStringCalculator.h      \
    $$PWD/../input/InputJudgmentGraph.h   \
    $$PWD/../input/InputTools.h           \
    $$PWD/../input/InputProcess.h
