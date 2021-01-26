/*
 * Copyright (C) 2020, KylinSoft Co., Ltd.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <QApplication>
#include <QStringList>
#include <QTranslator>
#include <QLocale>
#include <QStandardPaths>
#include <QLibraryInfo>
#include <QDir>
#include <fcntl.h>
#include <syslog.h>
#include <QTranslator>
#include <QLocale>

#include "mainwindow.h"
#include "xatom-helper.h"

int main(int argc, char *argv[])
{
    // 适配4K屏
    #if (QT_VERSION >= QT_VERSION_CHECK(5, 12, 0))
        QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
        QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    #endif

    #if (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
        QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    #endif

    QApplication a(argc, argv);
    a.setApplicationVersion("1.0.30");

    // 实现VNC单例
    QStringList homePath = QStandardPaths::standardLocations(QStandardPaths::HomeLocation);
    //需要给文件锁加一个DISPLAY标识  QtSingleApplication-Name改为kylin-calculator
    int fd = open(QString(homePath.at(0) + "/.config/kylin-calculator%1.lock").arg(getenv("DISPLAY")).toUtf8().data(), O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd < 0)
    {
        exit(1);
    }
    if (lockf(fd, F_TLOCK, 0))
    {
        syslog(LOG_ERR, "Can't lock single file, kylin-calculator is already running!");
        exit(0);
    }

    // 国际化
    QString qtTranslationsPath;
    qtTranslationsPath = QLibraryInfo::location(QLibraryInfo::TranslationsPath);// /usr/share/qt5/translations
    QString kylinCalculatorTranslationsPath;
    if (QDir("/usr/share/kylin-calculator/translations").exists()) {
        kylinCalculatorTranslationsPath = "/usr/share/kylin-calculator/translations";
    }
    else {
        kylinCalculatorTranslationsPath = qApp->applicationDirPath() + "/.qm";
    }

    QString locale = QLocale::system().name();
    QTranslator trans_global, trans_menu;
    if (locale == "zh_CN") {
        if(!trans_global.load(QLocale(), "kylin-calculator", "_", kylinCalculatorTranslationsPath))
            qDebug() << "Load translations file" <<QLocale() << "failed!";
        else
            a.installTranslator(&trans_global);

        if(!trans_menu.load(QLocale(), "qt", "_", qtTranslationsPath))
            qDebug() << "Load translations file" <<QLocale() << "failed!";
        else
            a.installTranslator(&trans_menu);
    }
    // QString translatorFileName = QLatin1String("qt_");
    // translatorFileName += QLocale::system().name();
    // QTranslator *translator = new QTranslator();
    // if (translator->load(translatorFileName, QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
    // {
    //     a.installTranslator(translator);
    // }
    // else
    // {
    //     qDebug() << "加载中文失败";
    // }

    MainWindow w;

#ifndef __V10__
    // 添加窗管协议
    MotifWmHints hints;
    hints.flags = MWM_HINTS_FUNCTIONS | MWM_HINTS_DECORATIONS;
    hints.functions = MWM_FUNC_ALL;
    hints.decorations = MWM_DECOR_BORDER;
    XAtomHelper::getInstance()->setWindowMotifHint(w.winId(), hints);
#endif

    w.show();
    return a.exec();
}
