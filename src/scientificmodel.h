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

#ifndef SCIENTIFICMODEL_H
#define SCIENTIFICMODEL_H

#include <QLabel>
#include <QWidget>
#include <QListWidget>
#include <QKeyEvent>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFont>
#include <QColor>
#include <QDebug>

#include "basicbutton.h"
#include "widgetstyle.h"
#include "data_warehouse.h"

class ScientificOutput : public QWidget
{
    Q_OBJECT

public:
    explicit ScientificOutput(QWidget *parent = 0);
    ~ScientificOutput() {}

    // 显示输出组件
    QLabel *sciLabLastL;
    QLabel *sciLabLastR;
    QLabel *sciLabPre;
    QLabel *sciLabNow;

    // 输出界面布局
    QHBoxLayout *sciOutputLayout;

    // 初始化组件
    void setWidgetUi();

    // 设置组件样式
    void setWidgetStyle(bool resetFontSize = true);

    //void createIntelOutput(void);

};


class ScientificModel : public QWidget
{
    Q_OBJECT

public:
    explicit ScientificModel(QWidget *parent = 0);

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

    BasicButton *btnInd;
    BasicButton *btnUndo;
    BasicButton *btnBracketLeft;
    BasicButton *btnBracketRight;

//    QPushButton *btnReci;
//    QPushButton *btnXPower2;
//    QPushButton *btnXPower3;
//    QPushButton *btnYPowerX;

    BasicButton *btnReci;
    BasicButton *btnXPower2;
    BasicButton *btnXPower3;
    BasicButton *btnYPowerX;

//    QPushButton *btnFac;
//    QPushButton *btnXSquare2;
//    QPushButton *btnXSquare3;
//    QPushButton *btnYSquareX;

    BasicButton *btnFac;
    BasicButton *btnXSquare2;
    BasicButton *btnXSquare3;
    BasicButton *btnYSquareX;

//    QPushButton *btnSin;
//    QPushButton *btnCos;
//    QPushButton *btnTan;
//    QPushButton *btnLog;

    BasicButton *btnSin;
    BasicButton *btnCos;
    BasicButton *btnTan;
    BasicButton *btnLog;

//    QPushButton *btnRad;
//    QPushButton *btnPi;
//    QPushButton *btnExp;
//    QPushButton *btnLn;

    BasicButton *btnRad;
    BasicButton *btnPi;
    BasicButton *btnExp;
    BasicButton *btnLn;

    // 格式化输入表达式
    QString sciFormatInput(QString text);

    // 初始化组件
    void setWidgetUi();

    // 设置组件样式
    void setWidgetStyle();

    /* intel stand model ui */
    void createIntelModel(void);
    void createIntelStyle(void);
    
    // 切换三角函数和反三角函数显示
    void changeBtnSinDisplay();

    // 更新三角函数图片
    void updateBtnSinDisplay();

    // 切换角度弧度显示
    void changeBtnRadDisplay();

    // 更新角度弧度图片
    void updateBtnRadDisplay();

//    QPushButton *XPower2Button;
//    QPushButton *PowerButton;
//    QPushButton *SinButton;
//    QPushButton *CosButton;
//    QPushButton *TanButton;
//    QPushButton *SinhButton;
//    QPushButton *CoshButton;
//    QPushButton *TanhButton;
//    QPushButton *XPower3Button;
//    QPushButton *YSquareRootButton;
//    QPushButton *InvsinButton;
//    QPushButton *InvcosButton;
//    QPushButton *InvtanButton;
//    QPushButton *InvsinhButton;
//    QPushButton *InvcoshButton;
//    QPushButton *InvtanhButton;
//    QPushButton *SquareRootButton;
//    QPushButton *PowerOf10Button;
//    QPushButton *LogBase10Button;
//    QPushButton *ExpButton;
//    QPushButton *ModButton;

//    QPushButton *InvertButton;
//    QPushButton *PowerOfEButton;
//    QPushButton *LogBaseEButton;

//    QPushButton *PiButton;

public slots:
    // 键盘响应事件
    void keyPressEvent(QKeyEvent *event);
};

#endif // SCIENTIFICMODEL_H
