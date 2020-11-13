
QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += \
    c++11 \
    link_pkgconfig

PKGCONFIG += \
    gsl

TARGET = BigFloat


INCLUDEPATH += \
    $$PWD/../BigFloat/ \
    $$PWD/../symbols/

SOURCES += \
    $$PWD/../symbols/InputSymbols.cpp     \
    $$PWD/../BigFloat/BigFloat.cpp        \
    main.cpp

HEADERS += \
    $$PWD/../symbols/InputSymbols.h  \
    $$PWD/../BigFloat/BigFloat.h     \
          
    
