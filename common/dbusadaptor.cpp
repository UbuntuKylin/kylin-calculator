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

#include "dbusadaptor.h"

DbusAdaptor::DbusAdaptor(QObject *parent)
    : QObject(parent)
{
    QDBusConnection connection = QDBusConnection::sessionBus();
    if (!connection.registerService(KYLIN_CALCULATOR_SERVICE)) {
        return ;
    }
    connection.registerObject(KYLIN_CALCULATOR_PATH, this, QDBusConnection::ExportAllSlots);
}

DbusAdaptor::~DbusAdaptor()
{
}

// 显示应用主界面
void DbusAdaptor::showMainWindow()
{
    // qDebug() << "showMainWindow";
    MainWindow::getInstance()->pullUpWindow();
}

