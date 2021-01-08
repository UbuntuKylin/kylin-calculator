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

#include "scientificmodel.h"

ScientificOutput::ScientificOutput(QWidget *parent)
    : QWidget(parent)
{
    // 初始化组件
    setWidgetUi();

    // 设置组件样式
    setWidgetStyle();
}

// 初始化组件
void ScientificOutput::setWidgetUi()
{
    this->sciLabLastL = new QLabel(this);
    this->sciLabLastR = new QLabel(this);
    this->sciLabPre = new QLabel(this);
    this->sciLabNow = new QLabel(this);

//    sciLabLastL->setWordWrap(true);
//    sciLabLastR->setWordWrap(true);
//    sciLabPre->setWordWrap(true);
//    sciLabNow->setWordWrap(true);

    QFont labLastFont("SourceHanSansCN-Light", 40, 15);
    this->sciLabLastL->setAlignment(Qt::AlignRight | Qt::AlignTop);
    this->sciLabLastL->setFont(labLastFont);
    this->sciLabLastL->setText("left");

    this->sciLabLastR->setAlignment(Qt::AlignRight | Qt::AlignTop);
    this->sciLabLastR->setFont(labLastFont);
    this->sciLabLastR->setText("right");

    QFont sciLabPreFont("SourceHanSansCN-Light", 40, 15);
    this->sciLabPre->setAlignment(Qt::AlignRight | Qt::AlignTop);
    this->sciLabPre->setFont(sciLabPreFont);
    this->sciLabPre->setText("0");
    this->sciLabPre->setFixedHeight(35);

    QFont sciLabNowFont("SourceHanSansCN-Normal", 50, 15);
    this->sciLabNow->setAlignment(Qt::AlignRight);
    this->sciLabNow->setFont(sciLabNowFont);
    this->sciLabNow->setText("0");
    this->sciLabNow->setFixedHeight(65);
    this->sciLabNow->setContentsMargins(0, 0, 0, 0);

    this->sciLabLastL->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->sciLabLastR->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->sciLabPre->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->sciLabNow->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *rightLayout = new QVBoxLayout(this);
    rightLayout->addWidget(this->sciLabLastR);
    rightLayout->addWidget(this->sciLabPre);
    rightLayout->addWidget(this->sciLabNow);
    rightLayout->setStretchFactor(this->sciLabLastR, 14);
    rightLayout->setStretchFactor(this->sciLabPre, 1);
    rightLayout->setStretchFactor(this->sciLabNow, 1);
    rightLayout->setSpacing(0);
    rightLayout->setMargin(0);

    QWidget *outputRWid = new QWidget(this);
    outputRWid->setLayout(rightLayout);

    sciOutputLayout = new QHBoxLayout(this);

    sciOutputLayout->addWidget(sciLabLastL);
    sciOutputLayout->addWidget(outputRWid);

    this->setLayout(sciOutputLayout);
    this->setFixedHeight(270);
    //    this->setContentsMargins(1, 0, 1, 0);

    this->sciLabLastR->show();
    this->sciLabPre->show();
    this->sciLabNow->show();

    sciLabLastL->hide();
}

// 设置组件样式
void ScientificOutput::setWidgetStyle()
{
    this->sciLabLastL->setStyleSheet("color:#8C8C8C;font-size:20px;margin:0 7px 0 7px;");

    this->sciLabLastR->setStyleSheet("color:#8C8C8C;font-size:20px;margin:0 7px 0 7px;");

    this->sciLabPre->setStyleSheet("color:#FB9119;font-size:20px;margin:0 7px 0 7px;");

    this->sciLabNow->setStyleSheet("color:white;font-size:48px;font-weight:15px;margin:0 0 0 7px;");
}

ScientificModel::ScientificModel(QWidget *parent)
    : QWidget(parent)
{
    // 初始化组件
    this->setWidgetUi();

    // 设置组件样式
    this->setWidgetStyle();
}

// 初始化组件
void ScientificModel::setWidgetUi()
{
    // 计算器按钮
    // 布局按钮
    for (int i = 0; i < 10; i++) {
        btnNum[i] = new BasicButton(this);
        btnNum[i]->setText(QString::number(i));
        btnNum[i]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        btnNum[i]->setIcon(QIcon(":/image/standard/btnNum"+ QString::number(i) +".png"));
        btnNum[i]->setIconSize(QSize(106, 62));
    }

    btnDZero = new BasicButton(this);
    btnDZero->setText("00");
    btnDZero->setIcon(QIcon(":/image/standard/btnNum00.png"));
    btnDZero->setIconSize(QSize(106, 62));

    btnClear  = new BasicButton(this);
    btnPer    = new BasicButton(this);
    btnDelete = new BasicButton(this);

    btnDiv   = new BasicButton(this);
    btnMulti = new BasicButton(this);
    btnSub   = new BasicButton(this);
    btnAdd   = new BasicButton(this);
    btnEqual = new BasicButton(this);

    btnPoint = new BasicButton(this);

    btnInd  = new BasicButton(this);
    btnUndo = new BasicButton(this);
    btnBracketLeft  = new BasicButton(this);
    btnBracketRight = new BasicButton(this);

    btnReci    = new BasicButton(this);
    btnXPower2 = new BasicButton(this);
    btnXPower3 = new BasicButton(this);
    btnYPowerX = new BasicButton(this);

    btnFac      = new BasicButton(this);
    btnXSquare2 = new BasicButton(this);
    btnXSquare3 = new BasicButton(this);
    btnYSquareX = new BasicButton(this);

    btnSin = new BasicButton(this);
    btnCos = new BasicButton(this);
    btnTan = new BasicButton(this);
    btnLog = new BasicButton(this);

    btnRad = new BasicButton(this);
    btnPi  = new BasicButton(this);
    btnExp = new BasicButton(this);
    btnLn  = new BasicButton(this);

    // 设置按钮的显示文本
    // ！！！！！！减号不是ascII码 减号不是ascII码 减号不是ascII码 减号不是ascII码 减号不是ascII码
    QString btnList = "C,÷,×,B,ｰ,+,=,%,.";
    // ！！！！！！减号不是ascII码 减号不是ascII码 减号不是ascII码 减号不是ascII码 减号不是ascII码
    QStringList btnNameList= btnList.split(",");
    int index = 0;

    btnClear->setText(btnNameList[index++]);
    btnDiv->setText(btnNameList[index++]);
    btnMulti->setText(btnNameList[index++]);
    btnDelete->setText(btnNameList[index++]);
    btnSub->setText(btnNameList[index++]);
    btnAdd->setText(btnNameList[index++]);
    btnEqual->setText(btnNameList[index++]);
    btnPer->setText(btnNameList[index++]);
    btnPoint->setText(btnNameList[index++]);

    btnClear->setIcon(QIcon(":/image/standard/btnClear.png"));
    btnDiv->setIcon(QIcon(":/image/standard/btnDiv.png"));
    btnMulti->setIcon(QIcon(":/image/standard/btnMulti.png"));
    btnDelete->setIcon(QIcon(":/image/standard/btnDelete.png"));
    btnSub->setIcon(QIcon(":/image/standard/btnSub.png"));
    btnAdd->setIcon(QIcon(":/image/standard/btnAdd.png"));
    btnEqual->setIcon(QIcon(":/image/standard/btnEqual.png"));
    btnPer->setIcon(QIcon(":/image/standard/btnPer.png"));
    btnPoint->setIcon(QIcon(":/image/standard/btnPoint.png"));

    btnClear->setIconSize(QSize(106, 62));
    btnDiv->setIconSize(QSize(106, 62));
    btnMulti->setIconSize(QSize(106, 62));
    // 删除键按钮大小调整
    btnDelete->setIconSize(QSize(85,  50));
    btnSub->setIconSize(QSize(106, 62));
    btnAdd->setIconSize(QSize(106, 62));
    btnEqual->setIconSize(QSize(106, 62));
    btnPer->setIconSize(QSize(106, 62));
    btnPoint->setIconSize(QSize(106, 62));


    btnList = "2nd,ANS,(,),1/x,x²,x³,y^x,x!,√x,³√x,x√y,sin,cos,tan,log,rad,PI,E,ln";
    btnNameList= btnList.split(",");
    index = 0;

    btnInd->setText(btnNameList[index++]);
    btnUndo->setText(btnNameList[index++]);
    btnBracketLeft->setText(btnNameList[index++]);
    btnBracketRight->setText(btnNameList[index++]);

    btnReci->setText(btnNameList[index++]);
    btnXPower2->setText(btnNameList[index++]);
    btnXPower3->setText(btnNameList[index++]);
    btnYPowerX->setText(btnNameList[index++]);

    btnFac->setText(btnNameList[index++]);
    btnXSquare2->setText(btnNameList[index++]);
    btnXSquare3->setText(btnNameList[index++]);
    btnYSquareX->setText(btnNameList[index++]);

    btnSin->setText(btnNameList[index++]);
    btnCos->setText(btnNameList[index++]);
    btnTan->setText(btnNameList[index++]);
    btnLog->setText(btnNameList[index++]);

    btnRad->setText(btnNameList[index++]);
    btnPi->setText(btnNameList[index++]);
    btnExp->setText(btnNameList[index++]);
    btnLn->setText(btnNameList[index++]);

    QString btnIconStr = "btn2nd,btnAns,btnLbra,btnRbra,btnReci,btnXPower2,btnXPower3,btnYPowerX,btnFac,btnXSquare2,btnXSquare3,btnYSquareX,btnSin,btnCos,btnTan,btnLog,btnRad,btnPi,btnE,btnLn";
    QStringList btnIconList = btnIconStr.split(",");
    int iconIdx = 0;

    btnInd->setIcon(QIcon(":/image/scientific/" + btnIconList[iconIdx++] + ".png"));
    btnUndo->setIcon(QIcon(":/image/scientific/" + btnIconList[iconIdx++] + ".png"));
    btnBracketLeft->setIcon(QIcon(":/image/scientific/" + btnIconList[iconIdx++] + ".png"));
    btnBracketRight->setIcon(QIcon(":/image/scientific/" + btnIconList[iconIdx++] + ".png"));

    btnReci->setIcon(QIcon(":/image/scientific/" + btnIconList[iconIdx++] + ".png"));
    btnXPower2->setIcon(QIcon(":/image/scientific/" + btnIconList[iconIdx++] + ".png"));
    btnXPower3->setIcon(QIcon(":/image/scientific/" + btnIconList[iconIdx++] + ".png"));
    btnYPowerX->setIcon(QIcon(":/image/scientific/" + btnIconList[iconIdx++] + ".png"));

    btnFac->setIcon(QIcon(":/image/scientific/" + btnIconList[iconIdx++] + ".png"));
    btnXSquare2->setIcon(QIcon(":/image/scientific/" + btnIconList[iconIdx++] + ".png"));
    btnXSquare3->setIcon(QIcon(":/image/scientific/" + btnIconList[iconIdx++] + ".png"));
    btnYSquareX->setIcon(QIcon(":/image/scientific/" + btnIconList[iconIdx++] + ".png"));

    btnSin->setIcon(QIcon(":/image/scientific/" + btnIconList[iconIdx++] + ".png"));
    btnCos->setIcon(QIcon(":/image/scientific/" + btnIconList[iconIdx++] + ".png"));
    btnTan->setIcon(QIcon(":/image/scientific/" + btnIconList[iconIdx++] + ".png"));
    btnLog->setIcon(QIcon(":/image/scientific/" + btnIconList[iconIdx++] + ".png"));

    btnRad->setIcon(QIcon(":/image/scientific/" + btnIconList[iconIdx++] + ".png"));
    btnPi->setIcon(QIcon(":/image/scientific/" + btnIconList[iconIdx++] + ".png"));
    btnExp->setIcon(QIcon(":/image/scientific/" + btnIconList[iconIdx++] + ".png"));
    btnLn->setIcon(QIcon(":/image/scientific/" + btnIconList[iconIdx++] + ".png"));

    btnInd->setIconSize(QSize(106, 62));
    btnUndo->setIconSize(QSize(106, 62));
    btnBracketLeft->setIconSize(QSize(106, 62));
    btnBracketRight->setIconSize(QSize(106, 62));

    btnReci->setIconSize(QSize(106, 62));
    btnXPower2->setIconSize(QSize(106, 62));
    btnXPower3->setIconSize(QSize(106, 62));
    btnYPowerX->setIconSize(QSize(106, 62));

    btnFac->setIconSize(QSize(106, 62));
    btnXSquare2->setIconSize(QSize(106, 62));
    btnXSquare3->setIconSize(QSize(106, 62));
    btnYSquareX->setIconSize(QSize(106, 62));

    btnSin->setIconSize(QSize(106, 62));
    btnCos->setIconSize(QSize(106, 62));
    btnTan->setIconSize(QSize(106, 62));
    btnLog->setIconSize(QSize(106, 62));

    btnRad->setIconSize(QSize(106, 62));
    btnPi->setIconSize(QSize(106, 62));
    btnExp->setIconSize(QSize(106, 62));
    btnLn->setIconSize(QSize(106, 62));

    // 设置按钮自适应放缩
    btnClear->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btnDiv->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btnMulti->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btnDelete->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btnSub->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btnAdd->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btnEqual->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btnPer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btnPoint->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // 将科学计算器按钮进行网格布局
    QGridLayout *btnSciLayout = new QGridLayout(this);
    btnSciLayout->addWidget(btnInd, 0, 0, 1, 1);
    btnSciLayout->addWidget(btnUndo, 0, 1, 1, 1);
    btnSciLayout->addWidget(btnBracketLeft, 0, 2, 1, 1);
    btnSciLayout->addWidget(btnBracketRight, 0, 3, 1, 1);

    btnSciLayout->addWidget(btnReci, 1, 0, 1, 1);
    btnSciLayout->addWidget(btnXPower2, 1, 1, 1, 1);
    btnSciLayout->addWidget(btnXPower3,1, 2, 1, 1);
    btnSciLayout->addWidget(btnYPowerX,1, 3, 1, 1);

    btnSciLayout->addWidget(btnFac, 2, 0, 1, 1);
    btnSciLayout->addWidget(btnXSquare2, 2, 1, 1, 1);
    btnSciLayout->addWidget(btnXSquare3, 2, 2, 1, 1);
    btnSciLayout->addWidget(btnYSquareX, 2, 3, 1, 1);

    btnSciLayout->addWidget(btnSin, 3, 0, 1, 1);
    btnSciLayout->addWidget(btnCos, 3, 1, 1, 1);
    btnSciLayout->addWidget(btnTan, 3, 2, 1, 1);
    btnSciLayout->addWidget(btnLog, 3, 3, 1, 1);

    btnSciLayout->addWidget(btnRad, 4, 0, 1, 1);
    btnSciLayout->addWidget(btnPi, 4, 1, 1, 1);
    btnSciLayout->addWidget(btnExp, 4, 2, 1, 1);
    btnSciLayout->addWidget(btnLn, 4, 3, 1, 1);

    // 设置间距和背景样式
    btnSciLayout->setSpacing(2);
    btnSciLayout->setMargin(1);

    // 将按钮进行网格布局
    QGridLayout *btnLayout = new QGridLayout(this);
    btnLayout->addWidget(btnClear, 0, 0, 1, 1);
    btnLayout->addWidget(btnPer, 0, 1, 1, 1);
    btnLayout->addWidget(btnDelete, 0, 2, 1, 1);
    btnLayout->addWidget(btnDiv, 0, 3, 1, 1);
    btnLayout->addWidget(btnMulti, 1, 3, 1, 1);
    btnLayout->addWidget(btnSub, 2, 3, 1, 1);
    btnLayout->addWidget(btnAdd, 3, 3, 1, 1);
    btnLayout->addWidget(btnPoint, 4, 2, 1, 1);
    btnLayout->addWidget(btnEqual, 4, 3, 1, 1);

    // 数字按钮布局
    btnLayout->addWidget(btnDZero, 4, 0, 1, 1);
    btnLayout->addWidget(btnNum[0], 4, 1, 1, 1);
    for (int i = 1; i < 10; i++) {
        btnLayout->addWidget(btnNum[i], 3 - (i - 1)/3, (i - 1) % 3, 1, 1);
    }

    // 设置间距和背景样式
    btnLayout->setSpacing(2);
    btnLayout->setMargin(1);

    QHBoxLayout *btnAllLayout = new QHBoxLayout(this);

    QWidget *btnLWid = new QWidget(this);
    QWidget *btnRWid = new QWidget(this);

    btnLWid->setLayout(btnSciLayout);
    btnRWid->setLayout(btnLayout);

    btnAllLayout->addWidget(btnLWid);
    btnAllLayout->addWidget(btnRWid);

    btnAllLayout->setSpacing(0);
    btnAllLayout->setMargin(0);

    this->setFixedHeight(320);
    this->setLayout(btnAllLayout);

    connect(btnInd, &BasicButton::clicked, this, &ScientificModel::changeBtnDisplay);
    connect(btnRad, &BasicButton::clicked, this, &ScientificModel::changeBtnRadDisplay);
}

// 设置组件样式
void ScientificModel::setWidgetStyle()
{
    QString btnStyle = "QPushButton{"
                       "width:106px;height:62px;opacity:0.95;"
                       "background-color:#272A2D;border-radius:4px;"
                       "font-size:42px;font-family:HelveticaNeueLTPro-UltLt;color:#FFFFFF;"
                       "}"
                       "QPushButton:hover{background-color:rgb(180,180,180);}";

    QString btnOpStyle = "QPushButton{"
                         "width:106px;height:62px;opacity:1;"
                         "background-color:#222E36;border-radius:4px;"
                         "font-size:35px;font-family:HelveticaNeueLTPro-UltLt;color:#FFFFFF;}"
                         "QPushButton:hover{background-color:rgba(82,87,217,1);}";

    QString btnAddStyle = "QPushButton{"
                          "width:106px;height:62px;opacity:1;"
                          "background-color:#222E36;border-radius:4px;"
                          "font-size:50px;font-family:HelveticaNeueLTPro-UltLt;color:#FFFFFF;"
                          "}"
                          "QPushButton:hover{background-color:rgba(82,87,217,1);}";

    QString btnEqualStyle = "QPushButton{"
                            "width:106px;height:126px;opacity:1;"
                            "background-color:#E64A19;border-radius:4px;"
                            "font-size:48px;font-family:HelveticaNeueLTPro-UltLt;color:#FFFFFF;"
                            "}"
                            "QPushButton:hover{background-color:rgba(82,87,217,1);}";

    QString btnPerStyle = "QPushButton{"
                          "width:106px;height:62px;opacity:1;"
                          "background-color:#272A2D;border-radius:4px;"
                          "font-size:31px;font-family:HelveticaNeueLTPro-UltLt;color:#FFFFFF;"
                          "}"
                          "QPushButton:hover{background-color:rgb(180,180,180);}";

    QString btnSciStyle = "QPushButton{"
                          "width:106px;height:62px;opacity:1;"
                          "background-color:#272A2D;border-radius:4px;"
                          "font-size:31px;font-family:HelveticaNeueLTPro-UltLt;color:#FFFFFF;"
                          "}"
                          "QPushButton:hover{background-color:rgb(180,180,180);}";

    QFont btnFont("HelveticaNeueLTPro-UltLt", 30, 10);

    for (int i = 0; i < 10; i++) {
        btnNum[i]->setStyleSheet(btnStyle);
        btnNum[i]->setFont(btnFont);
    }

    btnDZero->setStyleSheet(btnStyle);
    btnDZero->setFont(btnFont);

    // 设置按钮字体
    btnClear->setFont(btnFont);
    btnDiv->setFont(btnFont);
    btnMulti->setFont(btnFont);
    btnDelete->setFont(btnFont);
    btnSub->setFont(btnFont);
    btnAdd->setFont(btnFont);
    btnEqual->setFont(btnFont);
    btnPer->setFont(btnFont);
    btnPoint->setFont(btnFont);

    btnInd->setFont(btnFont);
    btnUndo->setFont(btnFont);
    btnBracketLeft->setFont(btnFont);
    btnBracketRight->setFont(btnFont);

    btnReci->setFont(btnFont);
    btnXPower2->setFont(btnFont);
    btnXPower3->setFont(btnFont);
    btnYPowerX->setFont(btnFont);

    btnFac->setFont(btnFont);
    btnXSquare2->setFont(btnFont);
    btnXSquare3->setFont(btnFont);
    btnYSquareX->setFont(btnFont);

    btnSin->setFont(btnFont);
    btnCos->setFont(btnFont);
    btnTan->setFont(btnFont);
    btnLog->setFont(btnFont);

    btnRad->setFont(btnFont);
    btnPi->setFont(btnFont);
    btnExp->setFont(btnFont);
    btnLn->setFont(btnFont);

    // 设置按钮样式standardModel
    //    btnClear->setStyleSheet(btnOpStyle);
    btnClear->setStyleSheet(btnStyle);

    btnDiv->setStyleSheet(btnOpStyle);
    btnMulti->setStyleSheet(btnOpStyle);

    //    btnDelete->setStyleSheet(btnOpStyle);
    btnDelete->setStyleSheet(btnStyle);

    btnSub->setStyleSheet(btnOpStyle);
    btnAdd->setStyleSheet(btnAddStyle);
    btnEqual->setStyleSheet(btnEqualStyle);
    btnPer->setStyleSheet(btnPerStyle);
    btnPoint->setStyleSheet(btnPerStyle);

    btnInd->setStyleSheet(btnSciStyle);
    btnUndo->setStyleSheet(btnSciStyle);
    btnBracketLeft->setStyleSheet(btnSciStyle);
    btnBracketRight->setStyleSheet(btnSciStyle);

    btnReci->setStyleSheet(btnSciStyle);
    btnXPower2->setStyleSheet(btnSciStyle);
    btnXPower3->setStyleSheet(btnSciStyle);
    btnYPowerX->setStyleSheet(btnSciStyle);

    btnFac->setStyleSheet(btnSciStyle);
    btnXSquare2->setStyleSheet(btnSciStyle);
    btnXSquare3->setStyleSheet(btnSciStyle);
    btnYSquareX->setStyleSheet(btnSciStyle);

    btnSin->setStyleSheet(btnSciStyle);
    btnCos->setStyleSheet(btnSciStyle);
    btnTan->setStyleSheet(btnSciStyle);
    btnLog->setStyleSheet(btnSciStyle);

    btnRad->setStyleSheet(btnSciStyle);
    btnPi->setStyleSheet(btnSciStyle);
    btnExp->setStyleSheet(btnSciStyle);
    btnLn->setStyleSheet(btnSciStyle);

}

// 格式化输入表达式
QString ScientificModel::sciFormatInput(QString text)
{
//    btnList = "2nd,Ans,(,),1/x,x²,x³,y^x,x!,√x,³√x,x√y,sin,cos,tan,log,Rad,π,e,ln";
    if (text == "(")
        return "(";
    else if (text == ")")
        return ")";
    else if (text == "1/x")
        return "^(-1)";
    else if (text == "x²")
        return "^2";
    else if (text == "x³")
        return "^3";
    else if (text == "y^x")
        return "^(";
    else if (text == "x!")
        return "!";
    else if (text == "√x")
        return "√(";
    else if (text == "³√x")
        return "^(1÷3)";
    else if (text == "x√y")
        return "^(1÷";
    else if (text == "π")
        return "π";
    else if (text == "e")
        return "e";
    else
        return text + "(";
}

// 切换角度弧度显示
void ScientificModel::changeBtnDisplay()
{
    qDebug() << "btnSin->text()" << btnSin->text();
    // 切换文字显示和图片显示
    if (btnSin->text() == "sin") {
        btnSin->setText("asin");
        btnCos->setText("acos");
        btnTan->setText("atan");

        btnSin->setIcon(QIcon(":/image/scientific/btnAsin.png"));
        btnCos->setIcon(QIcon(":/image/scientific/btnAcos.png"));
        btnTan->setIcon(QIcon(":/image/scientific/btnAtan.png"));
    }
    else {
        btnSin->setText("sin");
        btnCos->setText("cos");
        btnTan->setText("tan");

        btnSin->setIcon(QIcon(":/image/scientific/btnSin.png"));
        btnCos->setIcon(QIcon(":/image/scientific/btnCos.png"));
        btnTan->setIcon(QIcon(":/image/scientific/btnTan.png"));
    }
}

// 切换角度弧度显示
void ScientificModel::changeBtnRadDisplay()
{
    // 切换文字显示和图片显示
    if (btnRad->text() == "rad") {
        btnRad->setText("deg");

        btnRad->setIcon(QIcon(":/image/scientific/btnDeg.png"));

        // 调整Deg按钮大小
        btnRad->setIconSize(QSize(95, 55));
    }
    else {
        btnRad->setText("rad");

        btnRad->setIcon(QIcon(":/image/scientific/btnRad.png"));
        btnRad->setIconSize(QSize(106, 62));
    }
}

void ScientificModel::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Period:
        btnPoint->click();
        break;
    case Qt::Key_0:
        btnNum[0]->click();
        break;
    case Qt::Key_1:
        btnNum[1]->click();
        break;
    case Qt::Key_2:
        btnNum[2]->click();
        break;
    case Qt::Key_3:
        btnNum[3]->click();
        break;
    case Qt::Key_4:
        btnNum[4]->click();
        break;
    case Qt::Key_5:
        btnNum[5]->click();
        break;
    case Qt::Key_6:
        btnNum[6]->click();
        break;
    case Qt::Key_7:
        btnNum[7]->click();
        break;
    case Qt::Key_8:
        btnNum[8]->click();
        break;
    case Qt::Key_9:
        btnNum[9]->click();
        break;
    case Qt::Key_Plus:
        btnAdd->click();
        break;
    case Qt::Key_Minus:
        btnSub->click();
        break;
    case Qt::Key_Asterisk:
        btnMulti->click();
        break;
    case Qt::Key_Slash:
        btnDiv->click();
        break;
    case Qt::Key_Escape:
        btnClear->click();
        break;
    case Qt::Key_Percent:
        btnPer->click();
        break;
    case Qt::Key_Backspace:
        btnDelete->click();
        break;
    case Qt::Key_Enter:
        btnEqual->click();
        break;
    case 16777220:
        btnEqual->click();
        break;
    case 0x3d:
        btnEqual->click();
        break;
    default:
        break;
    }
}
