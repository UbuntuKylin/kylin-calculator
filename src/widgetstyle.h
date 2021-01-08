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

#ifndef WIDGETSTYLE_H
#define WIDGETSTYLE_H

#define WINDOWW 432     //窗口宽度
#define WINDOWH 628     //窗口高度
#define TITLEH 38       //标题栏高度
#define OUTPUTWIDH 270  //数据输出界面高度
#define BUTTONWIDH 320  //数据按钮界面高度

#define SHADOW 6        //阴影宽度
#define WIDGETRADIUS 3  //窗口圆角
#define BUTTONRADIUS 4  //按钮圆角
#define SHADOWALPHA 0.16//阴影透明度


#include <QDebug>
//窗口显示在屏幕中心
#include <QApplication>
#include <QScreen>
//控件
#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
//布局
#include <QBoxLayout>
//读取本地字体
#include <QFontDatabase>
//窗体阴影
#include <QPainter>


class WidgetStyle : public QWidget
{
    Q_OBJECT

protected:

    QFont font;             //字体

public:

private:
    QWidget *title = nullptr;   //标题栏
    QLabel *text = nullptr;     //标题
    QWidget *body  = nullptr;   //窗体
    QLabel *icon = nullptr;     //图标
    QPushButton *widgetClose = nullptr; //关闭窗口
    QPushButton *widgetMin = nullptr;   //最小化窗口
//    void handleIconClickedSub();        //在屏幕中央显示
//    void isDiaLog(int w, int h, QString titleText);//会话框
//    void mystyle(); //设定样式
//    void paintEvent(QPaintEvent *event);//重绘窗口
};

#endif // WIDGETSTYLE_H
