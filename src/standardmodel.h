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

#ifndef STANDARDMODEL_H
#define STANDARDMODEL_H

#include <QKeyEvent>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFont>
#include <QLabel>
#include <QWidget>
#include <QListWidget>
#include <QDebug>

#include "basicbutton.h"
#include "widgetstyle.h"

class StandardOutput : public QWidget
{
    Q_OBJECT

public:
    explicit StandardOutput(QWidget *parent = 0);
    ~StandardOutput() {}

    // 显示输出组件
    QLabel *staLabLast;
    QLabel *staLabNow;
    QLabel *staLabPre;

    // 初始化组件
    void setWidgetUi();

    // 设置组件样式
    void setWidgetStyle(bool resetFontSize = true);
};


class StandardModel : public QWidget
{
    Q_OBJECT

public:
    explicit StandardModel(QWidget *parent = 0);

    BasicButton *btnNum[10];

    BasicButton *btnClear;
    BasicButton *btnPer;
    BasicButton *btnDelete;

    BasicButton *btnDiv;
    BasicButton *btnMulti;
    BasicButton *btnSub;
    BasicButton *btnAdd;
    BasicButton *btnEqual;

    // BasicButton *btnDZero;
    BasicButton *btnPoint;

    // 初始化组件
    void setWidgetUi();

    // 设置组件样式
    void setWidgetStyle();

    // 格式化输入表达式
    void StaFormatInput(QString text);

public slots:
    // 键盘响应事件
    void keyPressEvent(QKeyEvent *event);
};

#endif // STANDARDMODEL_H
