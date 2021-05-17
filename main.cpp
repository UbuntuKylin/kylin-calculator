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

#include <QDebug>
#include <QFile>
#include <QMutex>
#include <QDateTime>
#include <sys/inotify.h>

#include <ukui-log4qt.h>

#include "mainwindow.h"
#include "xatom-helper.h"
#include "common/dbusadaptor.h"

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    // 加锁
    static QMutex mutex;
    mutex.lock();

    QByteArray localMsg = msg.toLocal8Bit();

    QString strMsg("");
    switch (type)
    {
    case QtDebugMsg:
    default:
        strMsg = QString("Debug:");
        break;
    case QtWarningMsg:
        strMsg = QString("Warning:");
        break;
    case QtCriticalMsg:
        strMsg = QString("Critical:");
        break;
    case QtFatalMsg:
        strMsg = QString("Fatal:");
        break;
        
    }

    // 设置输出信息格式
    QString strDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd");
    QString strMessage = QString(QString() +
                                 "Message:%1"
                                 // +"        File:%2\n"
                                 // +"        Line:%3\n"
                                 // +"        Function:%4\n"
                                 // +"        DateTime:%5"
                                 )
                             .arg(localMsg.constData());
    // .arg(context.file).arg(context.line).arg(context.function).arg(strDateTime);

    // 输出信息至文件中（读写、追加形式）
    QString dirPath = "/tmp/kylin-calculator/log";
    QDir dir;
    QFile file;
    if (dir.mkpath(dirPath)) {
        dirPath = dirPath + "/" + strDateTime + ".txt" ;
        file.setFileName(dirPath);
    }

    file.open(QIODevice::ReadWrite | QIODevice::Append);
    QTextStream stream(&file);
    stream << strMessage << "\r\n";
    file.flush();
    file.close();

    // 解锁
    mutex.unlock();
}

int main(int argc, char *argv[])
{
    initUkuiLog4qt("kylin-calculator");
    printf("Program start ...\n");
    // qInstallMessageHandler(myMessageOutput);

    // 适配4K屏
    #if (QT_VERSION >= QT_VERSION_CHECK(5, 12, 0))
        QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
        QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    #endif

    #if (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
        QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    #endif

    QApplication a(argc, argv);
    a.setApplicationVersion("1.0.31");
    a.setWindowIcon(QIcon::fromTheme("kylin-calculator"));

    // 连接DBus服务
    QDBusInterface interface(KYLIN_CALCULATOR_SERVICE, 
                             KYLIN_CALCULATOR_PATH,
                             KYLIN_CALCULATOR_INTERFACE,
                             QDBusConnection::sessionBus());
    if (interface.isValid()) {
        // 调用拉起主界面的method
        qDebug() << "showMainWindow";
        interface.call("showMainWindow");
    }

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
#ifdef QT_NO_DEBUG
    if (QDir("/usr/share/kylin-calculator/translations").exists()) {
        kylinCalculatorTranslationsPath = "/usr/share/kylin-calculator/translations";
    }
    else {
        kylinCalculatorTranslationsPath = qApp->applicationDirPath() + "/.qm";
    }
#else
    kylinCalculatorTranslationsPath = "translations";
#endif

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

    MainWindow::getInstance();

#ifndef __V10__
    // 添加窗管协议
    MotifWmHints hints;
    hints.flags = MWM_HINTS_FUNCTIONS | MWM_HINTS_DECORATIONS;
    hints.functions = MWM_FUNC_ALL;
    hints.decorations = MWM_DECOR_BORDER;
    XAtomHelper::getInstance()->setWindowMotifHint(MainWindow::getInstance()->winId(), hints);
#endif

    MainWindow::getInstance()->show();

    // 创建DBus服务
    DbusAdaptor adaptor;
    Q_UNUSED(adaptor);

    return a.exec();
}
