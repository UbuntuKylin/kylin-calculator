QT += \ 
    core          \
    gui           \
    network       \
    KWindowSystem \
# 适配窗口管理器圆角阴影
    KWindowSystem \
    dbus          \
    x11extras

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# 适配窗口管理器圆角阴影
LIBS += -lpthread
LIBS += -lX11

# 配置gsettings
CONFIG += link_pkgconfig
PKGCONFIG += gsettings-qt

# v10禁用窗管
lessThan(QT_MAJOR_VERSION, 5) | lessThan(QT_MINOR_VERSION, 9) {
#    message("QT_VERSION ("$$QT_VERSION")")
    DEFINES += __V10__
    QT      -= x11extras
    LIBS    -= -lpthread
    LIBS    -= -lX11
}

CONFIG += \
    c++11 \
    link_pkgconfig

PKGCONFIG += \
    gsl

TARGET = kylin-calculator

# 生成qm文件
message($$system(./translations/generate_translations_qm.sh))

# translations 
TRANSLATIONS += $$PWD/translations/kylin-calculator_zh_CN.ts
QM_FILES_INSTALL_PATH = /usr/share/kylin-calculator/translations/
CONFIG += lrelease

BEFORE_LINK_CMD_LINE = echo Hello world!
QMAKE_PRE_LINK += $$quote($$BEFORE_LINK_CMD_LINE)

target.path += /usr/bin
target.source += $$TARGET

# gsettings
schemes.files += $$PWD/data/org.kylin-calculator-data.gschema.xml
schemes.path = /usr/share/glib-2.0/schemas/

icon.path = /usr/share/pixmaps
icon.files += $$PWD/image/calc.png

desktop.path = /usr/share/applications/
desktop.files += $$PWD/kylin-calculator.desktop

translationsFiles.path = /usr/share/kylin-calculator/translations/
translationsFiles.files += $$PWD/translations/*.qm

INSTALLS += \
    target  \
    icon    \
    desktop \
    schemes \
    translationsFiles

#TEMPLATE = app

RESOURCES += \
    image.qrc

INCLUDEPATH += \
    $$PWD/src/                \
    $$PWD/src/menumodule/     \
    $$PWD/common/             \
    $$PWD/calculate/          \
    $$PWD/calculate/BigFloat/ \
    $$PWD/calculate/input/    \
    $$PWD/calculate/cal/

SOURCES += \
# common
    $$PWD/common/InputSymbols.cpp                \
    $$PWD/common/xatom-helper.cpp                \
    $$PWD/common/daemonipcdbus.cpp               \
# calculate
    $$PWD/calculate/BigFloat/BigFloat.cpp        \
    $$PWD/calculate/cal/QStringCalculator.cpp    \
    $$PWD/calculate/input/InputJudgmentGraph.cpp \
    $$PWD/calculate/input/InputTools.cpp         \
    $$PWD/calculate/input/InputProcess.cpp       \
# src
    $$PWD/src/mainwindow.cpp                     \
    $$PWD/src/titlebar.cpp                       \
    $$PWD/src/widgetstyle.cpp                    \
    $$PWD/src/funclist.cpp                       \
    $$PWD/src/standardmodel.cpp                  \
    $$PWD/src/scientificmodel.cpp                \
    $$PWD/src/toolmodel.cpp                      \
    $$PWD/src/basicbutton.cpp                    \
    $$PWD/src/menumodule/menumodule.cpp          \
# pwd
    $$PWD/main.cpp


HEADERS += \
# common
    $$PWD/common/InputSymbols.h                \
    $$PWD/common/xatom-helper.h                \
    $$PWD/common/highlight-effect.h            \
    $$PWD/common/daemonipcdbus.h               \
# calculate
    $$PWD/calculate/cal.h                      \
    $$PWD/calculate/BigFloat/BigFloat.h        \
    $$PWD/calculate/cal/QStringCalculator.h    \
    $$PWD/calculate/input/InputJudgmentGraph.h \
    $$PWD/calculate/input/InputTools.h         \
    $$PWD/calculate/input/InputProcess.h       \
# src
    $$PWD/src/mainwindow.h                     \
    $$PWD/src/titlebar.h                       \
    $$PWD/src/widgetstyle.h                    \
    $$PWD/src/scientificmodel.h                \
    $$PWD/src/funclist.h                       \
    $$PWD/src/standardmodel.h                  \
    $$PWD/src/toolmodel.h                      \
    $$PWD/src/basicbutton.h                    \
    $$PWD/src/menumodule/menumodule.h
