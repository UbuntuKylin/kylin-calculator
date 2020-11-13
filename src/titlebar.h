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

#ifndef TITLE_BAR
#define TITLE_BAR

#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>

#include "funclist.h"

class QLabel;
class QPushButton;

class TitleBar : public QWidget
{
    Q_OBJECT

public:
    explicit TitleBar(QWidget *parent = 0);
    ~TitleBar();

    FuncList *funcList;
    QLabel *m_pIconLabel;           // 左上角应用图标
    QLabel *m_pFuncLabel;           // 界面标识
    QPushButton *m_pTopButton;      // 界面置顶按钮

    // 模式和功能列表按钮
    QPushButton *funcListButton;

    // 设置模式或功能名称
    void setFuncLabel(QString label);

    // 初始化组件
    void setWidgetUi();

    // 设置组件样式
    void setWidgetStyle();

protected:

    // 进行鼠标界面的拖动
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

signals:
    void iconButtonSignal();

private slots:

    // 进行置顶、最小化、关闭操作
    void onClicked();

    // 窗口置顶操作
    void stayTop();

private:

    // 最大化/还原
//    void updateMaximize();

private:

    QPushButton *m_pMinimizeButton; // 最小化按钮
    QPushButton *m_pCloseButton;    // 关闭按钮

    QPoint m_start;                 // 起始点
    QPoint m_end;                   // 结束点
    bool m_leftButtonPressed;       // 鼠标左键按下标记
};

#endif // TITLE_BAR
