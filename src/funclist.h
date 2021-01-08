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

#ifndef FUNLIST_H
#define FUNLIST_H

#include <QLabel>
#include <QWidget>
#include <QListWidget>
#include <QKeyEvent>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMenu>
#include <QAction>

#include "widgetstyle.h"

class FuncList : public QWidget
{
    Q_OBJECT

public:
    explicit FuncList(QWidget *parent = 0);
    ~FuncList();

    QLabel *funcModelLabel;
    QLabel *funcToolLabel;

    QListWidget *funcModelWid;
    QListWidget *funcToolWid;

    QPushButton *darkTheme;
    QPushButton *lightTheme;

    QPushButton *helpBtn;
    QPushButton *aboutBtn;

    // 初始化组件
    void setWidgetUi();

    // 设置组件样式
    void setWidgetStyle();

signals:


private:
};

#endif // FUNLIST_H
