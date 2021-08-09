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
    //this->sciLabPre->setFixedHeight(35);

    QFont sciLabNowFont("SourceHanSansCN-Normal", 48, 15);
    this->sciLabNow->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    this->sciLabNow->setFont(sciLabNowFont);
    this->sciLabNow->setText("0");
    //this->sciLabNow->setFixedHeight(65);
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

    // sciOutputLayout->addWidget(sciLabLastL);
    sciOutputLayout->addWidget(outputRWid);

    this->setLayout(sciOutputLayout);
    //this->setFixedHeight(270);
    this->setContentsMargins(0, 0, 0, 0);

    this->sciLabLastR->show();
    this->sciLabPre->show();
    this->sciLabNow->show();

    this->sciLabLastL->hide();
}

// 设置组件样式
void ScientificOutput::setWidgetStyle(bool resetFontSize)
{
    if (WidgetStyle::themeColor == 0){
        this->sciLabLastL->setStyleSheet("color:#8C8C8C;font-size:12px;margin:0 7px 0 7px;");
        this->sciLabLastR->setStyleSheet("color:#8C8C8C;font-size:12px;margin:0 7px 0 7px;");
        this->sciLabPre->setStyleSheet("color:#FB9119;font-size:20px;margin:0 7px 0 7px;");
        
        if (resetFontSize) {
            this->sciLabNow->setStyleSheet("color:#272A2D;font-size:48px;font-weight:15px;margin:0 0 0 7px;");
        }
        else {
            QString fontSizeStr = QString::number(sciLabNow->font().pixelSize());
            this->sciLabNow->setStyleSheet("color:#272A2D;font-size:" + fontSizeStr + "px;font-weight:15px;margin:0 0 0 7px;");
        }
    }
    else if (WidgetStyle::themeColor == 1){
        this->sciLabLastL->setStyleSheet("color:#8C8C8C;font-size:12px;margin:0 7px 0 7px;");
        this->sciLabLastR->setStyleSheet("color:#8C8C8C;font-size:12px;margin:0 7px 0 7px;");
        this->sciLabPre->setStyleSheet("color:#FB9119;font-size:20px;margin:0 7px 0 7px;");

        if (resetFontSize) {
            this->sciLabNow->setStyleSheet("color:#FFFFFF;font-size:48px;font-weight:15px;margin:0 0 0 7px;");
        }
        else {
            QString fontSizeStr = QString::number(sciLabNow->font().pixelSize());
            this->sciLabNow->setStyleSheet("color:#FFFFFF;font-size:" + fontSizeStr + "px;font-weight:15px;margin:0 0 0 7px;");
        }
    }
}


ScientificModel::ScientificModel(QWidget *parent)
    : QWidget(parent)
{
    if (DataWarehouse::getInstance()->platform == QString("intel")) {
        this->createIntelModel();
        this->createIntelStyle();
    } else {
        // 初始化组件
        this->setWidgetUi();
        // 设置组件样式
        this->setWidgetStyle();
    }
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

    // btnDZero = new BasicButton(this);
    // btnDZero->setText("00");
    // btnDZero->setIcon(QIcon(":/image/standard/btnNum00.png"));
    // btnDZero->setIconSize(QSize(106, 62));

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
    //btnDelete->setIconSize(QSize(85,  50));
    btnDelete->setIconSize(QSize(106,  62));
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
    //btnRad->setMinimumSize(106, 62);

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

    btnInd->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btnUndo->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btnBracketLeft->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btnBracketRight->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    btnReci->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btnXPower2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btnXPower3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btnYPowerX->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    btnFac->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btnXSquare2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btnXSquare3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btnYSquareX->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    btnSin->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btnCos->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btnTan->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btnLog->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    btnRad->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btnPi->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btnExp->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btnLn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

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
    // btnLayout->addWidget(btnDZero, 4, 0, 1, 1);
    btnLayout->addWidget(btnNum[0], 4, 0, 1, 2);
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

    //this->setFixedHeight(320);
    this->setLayout(btnAllLayout);

    connect(btnInd, &BasicButton::clicked, this, &ScientificModel::changeBtnSinDisplay);
    connect(btnRad, &BasicButton::clicked, this, &ScientificModel::changeBtnRadDisplay);
}

// 设置组件样式
void ScientificModel::setWidgetStyle()
{
    QString btnStyle;
    QString btnOpStyle;
    QString btnEqualStyle;

    if (WidgetStyle::themeColor == 0) {
        for (int i = 0; i < 10; i++) {
            btnNum[i]->setIcon(QIcon(":/image/light/standard/btnNum"+ QString::number(i) +".png"));
        }

        // btnDZero->setIcon(QIcon(":/image/light/standard/btnNum00.png"));

        btnClear->setIcon(QIcon(":/image/light/standard/btnClear.png"));
        btnDiv->setIcon(QIcon(":/image/light/standard/btnDiv.png"));
        btnMulti->setIcon(QIcon(":/image/light/standard/btnMulti.png"));
        btnDelete->setIcon(QIcon(":/image/light/standard/btnDelete.png"));
        btnSub->setIcon(QIcon(":/image/light/standard/btnSub.png"));
        btnAdd->setIcon(QIcon(":/image/light/standard/btnAdd.png"));
        btnEqual->setIcon(QIcon(":/image/light/standard/btnEqual.png"));
        btnPer->setIcon(QIcon(":/image/light/standard/btnPer.png"));
        btnPoint->setIcon(QIcon(":/image/light/standard/btnPoint.png"));

        QString btnIconStr = "btn2nd,btnAns,btnLbra,btnRbra,btnReci,btnXPower2,btnXPower3,btnYPowerX,btnFac,btnXSquare2,btnXSquare3,btnYSquareX,btnSin,btnCos,btnTan,btnLog,btnRad,btnPi,btnE,btnLn";
        QStringList btnIconList = btnIconStr.split(",");
        int iconIdx = 0;

        btnInd->setIcon(QIcon(":/image/light/scientific/" + btnIconList[iconIdx++] + ".png"));
        btnUndo->setIcon(QIcon(":/image/light/scientific/" + btnIconList[iconIdx++] + ".png"));
        btnBracketLeft->setIcon(QIcon(":/light/image/scientific/" + btnIconList[iconIdx++] + ".png"));
        btnBracketRight->setIcon(QIcon(":/light/image/scientific/" + btnIconList[iconIdx++] + ".png"));

        btnReci->setIcon(QIcon(":/image/light/scientific/" + btnIconList[iconIdx++] + ".png"));
        btnXPower2->setIcon(QIcon(":/image/light/scientific/" + btnIconList[iconIdx++] + ".png"));
        btnXPower3->setIcon(QIcon(":/image/light/scientific/" + btnIconList[iconIdx++] + ".png"));
        btnYPowerX->setIcon(QIcon(":/image/light/scientific/" + btnIconList[iconIdx++] + ".png"));

        btnFac->setIcon(QIcon(":/image/light/scientific/" + btnIconList[iconIdx++] + ".png"));
        btnXSquare2->setIcon(QIcon(":/image/light/scientific/" + btnIconList[iconIdx++] + ".png"));
        btnXSquare3->setIcon(QIcon(":/image/light/scientific/" + btnIconList[iconIdx++] + ".png"));
        btnYSquareX->setIcon(QIcon(":/image/light/scientific/" + btnIconList[iconIdx++] + ".png"));

        btnSin->setIcon(QIcon(":/image/light/scientific/" + btnIconList[iconIdx++] + ".png"));
        btnCos->setIcon(QIcon(":/image/light/scientific/" + btnIconList[iconIdx++] + ".png"));
        btnTan->setIcon(QIcon(":/image/light/scientific/" + btnIconList[iconIdx++] + ".png"));
        btnLog->setIcon(QIcon(":/image/light/scientific/" + btnIconList[iconIdx++] + ".png"));

        btnRad->setIcon(QIcon(":/image/light/scientific/" + btnIconList[iconIdx++] + ".png"));
        btnPi->setIcon(QIcon(":/image/light/scientific/" + btnIconList[iconIdx++] + ".png"));
        btnExp->setIcon(QIcon(":/image/light/scientific/" + btnIconList[iconIdx++] + ".png"));
        btnLn->setIcon(QIcon(":/image/light/scientific/" + btnIconList[iconIdx++] + ".png"));

        btnStyle = "QPushButton{"
                   "background-color:#F3F3F3;border-radius:4px;"
                   "font-size:42px;font-family:HelveticaNeueLTPro-UltLt;color:#FFFFFF;"
                   "}"
                   "QPushButton:hover{background-color:#E8E8E8;}";

        btnOpStyle = "QPushButton{"
                     "background-color:#F5F5F8;border-radius:4px;"
                     "font-size:35px;font-family:HelveticaNeueLTPro-UltLt;color:#FFFFFF;"
                     "}"
                     "QPushButton:hover{background-color:#E8E8E8;}";

        btnEqualStyle = "QPushButton{"
                        "background-color:#E64A19;border-radius:4px;"
                        "font-size:48px;font-family:HelveticaNeueLTPro-UltLt;color:#FFFFFF;"
                        "}"
                        "QPushButton:hover{background-color:#E45E4C;}";

        btnBracketLeft->setIcon(QIcon(":/image/light/scientific/btnLbra.png"));
        btnBracketRight->setIcon(QIcon(":/image/light/scientific/btnRbra.png"));
        btnBracketLeft->show();
        btnBracketRight->show();
    }
    else if (WidgetStyle::themeColor == 1) {
        for (int i = 0; i < 10; i++) {
            btnNum[i]->setIcon(QIcon(":/image/standard/btnNum"+ QString::number(i) +".png"));
        }

        // btnDZero->setIcon(QIcon(":/image/standard/btnNum00.png"));

        btnClear->setIcon(QIcon(":/image/standard/btnClear.png"));
        btnDiv->setIcon(QIcon(":/image/standard/btnDiv.png"));
        btnMulti->setIcon(QIcon(":/image/standard/btnMulti.png"));
        btnDelete->setIcon(QIcon(":/image/standard/btnDelete.png"));
        btnSub->setIcon(QIcon(":/image/standard/btnSub.png"));
        btnAdd->setIcon(QIcon(":/image/standard/btnAdd.png"));
        btnEqual->setIcon(QIcon(":/image/standard/btnEqual.png"));
        btnPer->setIcon(QIcon(":/image/standard/btnPer.png"));
        btnPoint->setIcon(QIcon(":/image/standard/btnPoint.png"));

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

        btnStyle = "QPushButton{"
                   "background-color:#27292C;border-radius:4px;"
                   "font-size:42px;font-family:HelveticaNeueLTPro-UltLt;color:#FFFFFF;"
                   "}"
                   "QPushButton:hover{background-color:#474747;}";

        btnOpStyle = "QPushButton{"
                     "background-color:#222E36;border-radius:4px;"
                     "font-size:35px;font-family:HelveticaNeueLTPro-UltLt;color:#FFFFFF;}"
                     "QPushButton:hover{background-color:#474747;}";

        btnEqualStyle = "QPushButton{"
                        "background-color:#E64A19;border-radius:4px;"
                        "font-size:48px;font-family:HelveticaNeueLTPro-UltLt;color:#FFFFFF;"
                        "}"
                        "QPushButton:hover{background-color:#E45E4C;}";
    }


    for (int i = 0; i < 10; i++) {
        btnNum[i]->setStyleSheet(btnStyle);
    }

    // btnDZero->setStyleSheet(btnStyle);

    // 设置按钮样式standardModel
    btnClear->setStyleSheet(btnStyle);

    btnDiv->setStyleSheet(btnOpStyle);
    btnMulti->setStyleSheet(btnOpStyle);

    btnDelete->setStyleSheet(btnStyle);

    btnSub->setStyleSheet(btnOpStyle);
    btnAdd->setStyleSheet(btnOpStyle);
    btnEqual->setStyleSheet(btnEqualStyle);
    btnPer->setStyleSheet(btnStyle);
    btnPoint->setStyleSheet(btnStyle);

    btnInd->setStyleSheet(btnOpStyle);
    btnUndo->setStyleSheet(btnOpStyle);
    btnBracketLeft->setStyleSheet(btnOpStyle);
    btnBracketRight->setStyleSheet(btnOpStyle);

    btnReci->setStyleSheet(btnOpStyle);
    btnXPower2->setStyleSheet(btnOpStyle);
    btnXPower3->setStyleSheet(btnOpStyle);
    btnYPowerX->setStyleSheet(btnOpStyle);

    btnFac->setStyleSheet(btnOpStyle);
    btnXSquare2->setStyleSheet(btnOpStyle);
    btnXSquare3->setStyleSheet(btnOpStyle);
    btnYSquareX->setStyleSheet(btnOpStyle);

    btnSin->setStyleSheet(btnOpStyle);
    btnCos->setStyleSheet(btnOpStyle);
    btnTan->setStyleSheet(btnOpStyle);
    btnLog->setStyleSheet(btnOpStyle);

    btnRad->setStyleSheet(btnOpStyle);
    btnPi->setStyleSheet(btnOpStyle);
    btnExp->setStyleSheet(btnOpStyle);
    btnLn->setStyleSheet(btnOpStyle);
}

void ScientificModel::createIntelModel()
{
    qDebug() << "Info : create intel scientific mode ui...";
    // 计算器按钮
    // 布局按钮
    for (int i = 0; i < 10; i++) {
        btnNum[i] = new BasicButton(this);
        btnNum[i]->setText(QString::number(i));
        btnNum[i]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        btnNum[i]->setIcon(QIcon(":/image/intelScientific/"+ QString::number(i) +".svg"));
        if (i == 0) {
            btnNum[i]->setIconSize(QSize(297.5, 70));
        } else {
            btnNum[i]->setIconSize(QSize(147.5, 70));
        }
    }

    // btnDZero = new BasicButton(this);
    // btnDZero->setText("00");
    // btnDZero->setIcon(QIcon(":/image/intelScientific/btnNum00.png"));
    // btnDZero->setIconSize(QSize(106, 62));

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

    btnClear->setIcon(QIcon(":/image/intelScientific/btnClear.svg"));
    btnDiv->setIcon(QIcon(":/image/intelScientific/btnDiv.svg"));
    btnMulti->setIcon(QIcon(":/image/intelScientific/btnMulti.svg"));
    btnDelete->setIcon(QIcon(":/image/intelScientific/btnDelete.svg"));
    btnSub->setIcon(QIcon(":/image/intelScientific/btnSub.svg"));
    btnAdd->setIcon(QIcon(":/image/intelScientific/btnAdd.svg"));
    btnEqual->setIcon(QIcon(":/image/intelScientific/btnEqual.svg"));
    btnPer->setIcon(QIcon(":/image/intelScientific/btnPer.svg"));
    btnPoint->setIcon(QIcon(":/image/intelScientific/btnPoint.svg"));

    btnClear->setIconSize(QSize(147.5, 70));
    btnDiv->setIconSize(QSize(147.5, 70));
    btnMulti->setIconSize(QSize(147.5, 70));
    // 删除键按钮大小调整
    //btnDelete->setIconSize(QSize(85,  50));
    btnDelete->setIconSize(QSize(147.5, 70));
    btnSub->setIconSize(QSize(147.5, 70));
    btnAdd->setIconSize(QSize(147.5, 70));
    btnEqual->setIconSize(QSize(147.5, 70));
    btnPer->setIconSize(QSize(147.5, 70));
    btnPoint->setIconSize(QSize(147.5, 70));


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

    btnInd->setIcon(QIcon(":/image/intelScientific/" + btnIconList[iconIdx++] + ".svg"));
    btnUndo->setIcon(QIcon(":/image/intelScientific/" + btnIconList[iconIdx++] + ".svg"));
    btnBracketLeft->setIcon(QIcon(":/image/intelScientific/" + btnIconList[iconIdx++] + ".svg"));
    btnBracketRight->setIcon(QIcon(":/image/intelScientific/" + btnIconList[iconIdx++] + ".svg"));

    btnReci->setIcon(QIcon(":/image/intelScientific/" + btnIconList[iconIdx++] + ".svg"));
    btnXPower2->setIcon(QIcon(":/image/intelScientific/" + btnIconList[iconIdx++] + ".svg"));
    btnXPower3->setIcon(QIcon(":/image/intelScientific/" + btnIconList[iconIdx++] + ".svg"));
    btnYPowerX->setIcon(QIcon(":/image/intelScientific/" + btnIconList[iconIdx++] + ".svg"));

    btnFac->setIcon(QIcon(":/image/intelScientific/" + btnIconList[iconIdx++] + ".svg"));
    btnXSquare2->setIcon(QIcon(":/image/intelScientific/" + btnIconList[iconIdx++] + ".svg"));
    btnXSquare3->setIcon(QIcon(":/image/intelScientific/" + btnIconList[iconIdx++] + ".svg"));
    btnYSquareX->setIcon(QIcon(":/image/intelScientific/" + btnIconList[iconIdx++] + ".svg"));

    btnSin->setIcon(QIcon(":/image/intelScientific/" + btnIconList[iconIdx++] + ".svg"));
    btnCos->setIcon(QIcon(":/image/intelScientific/" + btnIconList[iconIdx++] + ".svg"));
    btnTan->setIcon(QIcon(":/image/intelScientific/" + btnIconList[iconIdx++] + ".svg"));
    btnLog->setIcon(QIcon(":/image/intelScientific/" + btnIconList[iconIdx++] + ".svg"));

    btnRad->setIcon(QIcon(":/image/intelScientific/" + btnIconList[iconIdx++] + ".svg"));
    btnPi->setIcon(QIcon(":/image/intelScientific/" + btnIconList[iconIdx++] + ".svg"));
    btnExp->setIcon(QIcon(":/image/intelScientific/" + btnIconList[iconIdx++] + ".svg"));
    btnLn->setIcon(QIcon(":/image/intelScientific/" + btnIconList[iconIdx++] + ".svg"));

    btnInd->setIconSize(QSize(147.5, 70));
    btnUndo->setIconSize(QSize(147.5, 70));
    btnBracketLeft->setIconSize(QSize(147.5, 70));
    btnBracketRight->setIconSize(QSize(147.5, 70));

    btnReci->setIconSize(QSize(147.5, 70));
    btnXPower2->setIconSize(QSize(147.5, 70));
    btnXPower3->setIconSize(QSize(147.5, 70));
    btnYPowerX->setIconSize(QSize(147.5, 70));

    btnFac->setIconSize(QSize(147.5, 70));
    btnXSquare2->setIconSize(QSize(147.5, 70));
    btnXSquare3->setIconSize(QSize(147.5, 70));
    btnYSquareX->setIconSize(QSize(147.5, 70));

    btnSin->setIconSize(QSize(147.5, 70));
    btnCos->setIconSize(QSize(147.5, 70));
    btnTan->setIconSize(QSize(147.5, 70));
    btnLog->setIconSize(QSize(147.5, 70));

    btnRad->setIconSize(QSize(147.5, 70));
    btnPi->setIconSize(QSize(147.5, 70));
    btnExp->setIconSize(QSize(147.5, 70));
    btnLn->setIconSize(QSize(147.5, 70));
    //btnRad->setMinimumSize(106, 62);

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

    btnInd->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btnUndo->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btnBracketLeft->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btnBracketRight->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    btnReci->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btnXPower2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btnXPower3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btnYPowerX->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    btnFac->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btnXSquare2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btnXSquare3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btnYSquareX->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    btnSin->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btnCos->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btnTan->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btnLog->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    btnRad->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btnPi->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btnExp->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btnLn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

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
    btnLayout->addWidget(btnAdd, 0, 3, 1, 1);
    btnLayout->addWidget(btnSub, 1, 3, 1, 1);
    btnLayout->addWidget(btnMulti, 2, 3, 1, 1);
    btnLayout->addWidget(btnDiv, 3, 3, 1, 1);
    btnLayout->addWidget(btnPoint, 4, 2, 1, 1);
    btnLayout->addWidget(btnEqual, 4, 3, 1, 1);
    // 数字按钮布局
    // btnLayout->addWidget(btnDZero, 4, 0, 1, 1);
    btnLayout->addWidget(btnNum[0], 4, 0, 1, 2);
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

    //this->setFixedHeight(320);
    this->setLayout(btnAllLayout);

    connect(btnInd, &BasicButton::clicked, this, &ScientificModel::changeBtnSinDisplay);
    connect(btnRad, &BasicButton::clicked, this, &ScientificModel::changeBtnRadDisplay);
}

void ScientificModel::createIntelStyle()
{
    QString btnStyle;
    QString btnOpStyle;
    QString btnEqualStyle;

    if (WidgetStyle::themeColor == 0) {
        for (int i = 0; i < 10; i++) {
            btnNum[i]->setIcon(QIcon(":/image/intelScientific/"+ QString::number(i) +".svg"));
        }

        // btnDZero->setIcon(QIcon(":/image/light/standard/btnNum00.svg"));

        btnClear->setIcon(QIcon(":/image/intelScientific/btnClear.svg"));
        btnDiv->setIcon(QIcon(":/image/intelScientific/btnDiv.svg"));
        btnMulti->setIcon(QIcon(":/image/intelScientific/btnMulti.svg"));
        btnDelete->setIcon(QIcon(":/image/intelScientific/btnDelete.svg"));
        btnSub->setIcon(QIcon(":/image/intelScientific/btnSub.svg"));
        btnAdd->setIcon(QIcon(":/image/intelScientific/btnAdd.svg"));
        btnEqual->setIcon(QIcon(":/image/intelScientific/btnEqual.svg"));
        btnPer->setIcon(QIcon(":/image/intelScientific/btnPer.svg"));
        btnPoint->setIcon(QIcon(":/image/intelScientific/btnPoint.svg"));

        QString btnIconStr = "btn2nd,btnAns,btnLbra,btnRbra,btnReci,btnXPower2,btnXPower3,btnYPowerX,btnFac,btnXSquare2,btnXSquare3,btnYSquareX,btnSin,btnCos,btnTan,btnLog,btnRad,btnPi,btnE,btnLn";
        QStringList btnIconList = btnIconStr.split(",");
        int iconIdx = 0;

        btnInd->setIcon(QIcon(":/image/intelScientific/" + btnIconList[iconIdx++] + ".svg"));
        btnUndo->setIcon(QIcon(":/image/intelScientific/" + btnIconList[iconIdx++] + ".svg"));
        btnBracketLeft->setIcon(QIcon(":/image/intelScientific/" + btnIconList[iconIdx++] + ".svg"));
        btnBracketRight->setIcon(QIcon(":/image/intelScientific/" + btnIconList[iconIdx++] + ".svg"));

        btnReci->setIcon(QIcon(":/image/intelScientific/" + btnIconList[iconIdx++] + ".svg"));
        btnXPower2->setIcon(QIcon(":/image/intelScientific/" + btnIconList[iconIdx++] + ".svg"));
        btnXPower3->setIcon(QIcon(":/image/intelScientific/" + btnIconList[iconIdx++] + ".svg"));
        btnYPowerX->setIcon(QIcon(":/image/intelScientific/" + btnIconList[iconIdx++] + ".svg"));

        btnFac->setIcon(QIcon(":/image/intelScientific/" + btnIconList[iconIdx++] + ".svg"));
        btnXSquare2->setIcon(QIcon(":/image/intelScientific/" + btnIconList[iconIdx++] + ".svg"));
        btnXSquare3->setIcon(QIcon(":/image/intelScientific/" + btnIconList[iconIdx++] + ".svg"));
        btnYSquareX->setIcon(QIcon(":/image/intelScientific/" + btnIconList[iconIdx++] + ".svg"));

        btnSin->setIcon(QIcon(":/image/intelScientific/" + btnIconList[iconIdx++] + ".svg"));
        btnCos->setIcon(QIcon(":/image/intelScientific/" + btnIconList[iconIdx++] + ".svg"));
        btnTan->setIcon(QIcon(":/image/intelScientific/" + btnIconList[iconIdx++] + ".svg"));
        btnLog->setIcon(QIcon(":/image/intelScientific/" + btnIconList[iconIdx++] + ".svg"));

        btnRad->setIcon(QIcon(":/image/intelScientific/" + btnIconList[iconIdx++] + ".svg"));
        btnPi->setIcon(QIcon(":/image/intelScientific/" + btnIconList[iconIdx++] + ".svg"));
        btnExp->setIcon(QIcon(":/image/intelScientific/" + btnIconList[iconIdx++] + ".svg"));
        btnLn->setIcon(QIcon(":/image/intelScientific/" + btnIconList[iconIdx++] + ".svg"));

        btnStyle = "QPushButton{"
                   "background-color:#FFFFFF;border-radius:0px;"
                   "font-size:42px;font-family:HelveticaNeueLTPro-UltLt;color:#FFFFFF;"
                   "}"
                   "QPushButton:pressed{background-color:#F6F6F6;}";

        btnOpStyle = "QPushButton{"
                     "background-color:#F6F6F6;border-radius:0px;"
                     "font-size:23px;font-family:HelveticaNeueLTPro-UltLt;color:#FFFFFF;"
                     "}"
                     "QPushButton:pressed{background-color:#FFFFFF;}";

        btnEqualStyle = "QPushButton{"
                        "background-color:#FB7054;border-radius:0px;"
                        "font-size:48px;font-family:HelveticaNeueLTPro-UltLt;color:#FFFFFF;"
                        "}"
                        "QPushButton:pressed{background-color:#EA5E42;}";



        btnBracketLeft->setIcon(QIcon(":/image/intelScientific/btnLbra.svg"));
        btnBracketRight->setIcon(QIcon(":/image/intelScientific/btnRbra.svg"));
        btnBracketLeft->show();
        btnBracketRight->show();
    }
    else if (WidgetStyle::themeColor == 1) {
        for (int i = 0; i < 10; i++) {
            btnNum[i]->setIcon(QIcon(":/image/intelScientificDark/"+ QString::number(i) +".svg"));
        }

        // btnDZero->setIcon(QIcon(":/image/standard/btnNum00.png"));

        btnClear->setIcon(QIcon(":/image/intelScientificDark/btnClear.svg"));
        btnDiv->setIcon(QIcon(":/image/intelScientificDark/btnDiv.svg"));
        btnMulti->setIcon(QIcon(":/image/intelScientificDark/btnMulti.svg"));
        btnDelete->setIcon(QIcon(":/image/intelScientificDark/btnDelete.svg"));
        btnSub->setIcon(QIcon(":/image/intelScientificDark/btnSub.svg"));
        btnAdd->setIcon(QIcon(":/image/intelScientificDark/btnAdd.svg"));
        btnEqual->setIcon(QIcon(":/image/intelScientificDark/btnEqual.svg"));
        btnPer->setIcon(QIcon(":/image/intelScientificDark/btnPer.svg"));
        btnPoint->setIcon(QIcon(":/image/intelScientificDark/btnPoint.svg"));

        QString btnIconStr = "btn2nd,btnAns,btnLbra,btnRbra,btnReci,btnXPower2,btnXPower3,btnYPowerX,btnFac,btnXSquare2,btnXSquare3,btnYSquareX,btnSin,btnCos,btnTan,btnLog,btnRad,btnPi,btnE,btnLn";
        QStringList btnIconList = btnIconStr.split(",");
        int iconIdx = 0;


        btnInd->setIcon(QIcon(":/image/intelScientificDark/" + btnIconList[iconIdx++] + ".svg"));
        btnUndo->setIcon(QIcon(":/image/intelScientificDark/" + btnIconList[iconIdx++] + ".svg"));
        btnBracketLeft->setIcon(QIcon(":/image/intelScientificDark/" + btnIconList[iconIdx++] + ".svg"));
        btnBracketRight->setIcon(QIcon(":/image/intelScientificDark/" + btnIconList[iconIdx++] + ".svg"));

        btnReci->setIcon(QIcon(":/image/intelScientificDark/" + btnIconList[iconIdx++] + ".svg"));
        btnXPower2->setIcon(QIcon(":/image/intelScientificDark/" + btnIconList[iconIdx++] + ".svg"));
        btnXPower3->setIcon(QIcon(":/image/intelScientificDark/" + btnIconList[iconIdx++] + ".svg"));
        btnYPowerX->setIcon(QIcon(":/image/intelScientificDark/" + btnIconList[iconIdx++] + ".svg"));

        btnFac->setIcon(QIcon(":/image/intelScientificDark/" + btnIconList[iconIdx++] + ".svg"));
        btnXSquare2->setIcon(QIcon(":/image/intelScientificDark/" + btnIconList[iconIdx++] + ".svg"));
        btnXSquare3->setIcon(QIcon(":/image/intelScientificDark/" + btnIconList[iconIdx++] + ".svg"));
        btnYSquareX->setIcon(QIcon(":/image/intelScientificDark/" + btnIconList[iconIdx++] + ".svg"));

        btnSin->setIcon(QIcon(":/image/intelScientificDark/" + btnIconList[iconIdx++] + ".svg"));
        btnCos->setIcon(QIcon(":/image/intelScientificDark/" + btnIconList[iconIdx++] + ".svg"));
        btnTan->setIcon(QIcon(":/image/intelScientificDark/" + btnIconList[iconIdx++] + ".svg"));
        btnLog->setIcon(QIcon(":/image/intelScientificDark/" + btnIconList[iconIdx++] + ".svg"));

        btnRad->setIcon(QIcon(":/image/intelScientificDark/" + btnIconList[iconIdx++] + ".svg"));
        btnPi->setIcon(QIcon(":/image/intelScientificDark/" + btnIconList[iconIdx++] + ".svg"));
        btnExp->setIcon(QIcon(":/image/intelScientificDark/" + btnIconList[iconIdx++] + ".svg"));
        btnLn->setIcon(QIcon(":/image/intelScientificDark/" + btnIconList[iconIdx++] + ".svg"));

        btnStyle = "QPushButton{"
                   "background-color:#27292C;border-radius:4px;"
                   "font-size:42px;font-family:HelveticaNeueLTPro-UltLt;color:#FFFFFF;"
                   "}"
                   "QPushButton:hover{background-color:#474747;}";

        btnOpStyle = "QPushButton{"
                     "background-color:#222E36;border-radius:4px;"
                     "font-size:35px;font-family:HelveticaNeueLTPro-UltLt;color:#FFFFFF;}"
                     "QPushButton:hover{background-color:#474747;}";

        btnEqualStyle = "QPushButton{"
                        "background-color:#E64A19;border-radius:4px;"
                        "font-size:48px;font-family:HelveticaNeueLTPro-UltLt;color:#FFFFFF;"
                        "}"
                        "QPushButton:hover{background-color:#E45E4C;}";
    }


    for (int i = 0; i < 10; i++) {
        btnNum[i]->setStyleSheet(btnStyle);
    }

    // btnDZero->setStyleSheet(btnStyle);

    // 设置按钮样式standardModel
    btnClear->setStyleSheet(btnStyle);

    btnDiv->setStyleSheet(btnStyle);
    btnMulti->setStyleSheet(btnStyle);

    btnDelete->setStyleSheet(btnStyle);

    btnSub->setStyleSheet(btnStyle);
    btnAdd->setStyleSheet(btnStyle);
    btnEqual->setStyleSheet(btnEqualStyle);
    btnPer->setStyleSheet(btnStyle);
    btnPoint->setStyleSheet(btnStyle);

    btnInd->setStyleSheet(btnOpStyle);
    btnUndo->setStyleSheet(btnOpStyle);
    btnBracketLeft->setStyleSheet(btnOpStyle);
    btnBracketRight->setStyleSheet(btnOpStyle);

    btnReci->setStyleSheet(btnOpStyle);
    btnXPower2->setStyleSheet(btnOpStyle);
    btnXPower3->setStyleSheet(btnOpStyle);
    btnYPowerX->setStyleSheet(btnOpStyle);

    btnFac->setStyleSheet(btnOpStyle);
    btnXSquare2->setStyleSheet(btnOpStyle);
    btnXSquare3->setStyleSheet(btnOpStyle);
    btnYSquareX->setStyleSheet(btnOpStyle);

    btnSin->setStyleSheet(btnOpStyle);
    btnCos->setStyleSheet(btnOpStyle);
    btnTan->setStyleSheet(btnOpStyle);
    btnLog->setStyleSheet(btnOpStyle);

    btnRad->setStyleSheet(btnOpStyle);
    btnPi->setStyleSheet(btnOpStyle);
    btnExp->setStyleSheet(btnOpStyle);
    btnLn->setStyleSheet(btnOpStyle);
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
void ScientificModel::changeBtnSinDisplay()
{
    // 切换文字显示
    if (btnSin->text() == "sin") {
        btnSin->setText("asin");
        btnCos->setText("acos");
        btnTan->setText("atan");
    }
    else {
        btnSin->setText("sin");
        btnCos->setText("cos");
        btnTan->setText("tan");
    }

    // 更新三角函数图片
    updateBtnSinDisplay();
}

// 更新三角函数图片
void ScientificModel::updateBtnSinDisplay()
{
    // 切换图片显示
    if (btnSin->text() == "sin") {

        if (WidgetStyle::themeColor == 0) {
            if(DataWarehouse::getInstance()->platform == QString("intel"))
            {
                btnSin->setIcon(QIcon(":/image/intelScientific/btnSin.svg"));
                btnCos->setIcon(QIcon(":/image/intelScientific/btnCos.svg"));
                btnTan->setIcon(QIcon(":/image/intelScientific/btnTan.svg"));
            }
            else
            {
                btnSin->setIcon(QIcon(":/image/light/scientific/btnSin.png"));
                btnCos->setIcon(QIcon(":/image/light/scientific/btnCos.png"));
                btnTan->setIcon(QIcon(":/image/light/scientific/btnTan.png"));
            }

        }
        else if (WidgetStyle::themeColor == 1) {
            if (DataWarehouse::getInstance()->platform == QString("intel")) {
                btnSin->setIcon(QIcon(":/image/intelScientificDark/btnSin.svg"));
                btnCos->setIcon(QIcon(":/image/intelScientificDark/btnCos.svg"));
                btnTan->setIcon(QIcon(":/image/intelScientificDark/btnTan.svg"));
            } else {
                btnSin->setIcon(QIcon(":/image/scientific/btnSin.png"));
                btnCos->setIcon(QIcon(":/image/scientific/btnCos.png"));
                btnTan->setIcon(QIcon(":/image/scientific/btnTan.png"));
            }
        }
    }
    else {

        if (WidgetStyle::themeColor == 0) {
            if(DataWarehouse::getInstance()->platform == QString("intel"))
            {
                btnSin->setIcon(QIcon(":/image/intelScientific/btnAsin.svg"));
                btnCos->setIcon(QIcon(":/image/intelScientific/btnAcos.svg"));
                btnTan->setIcon(QIcon(":/image/intelScientific/btnAtan.svg"));
            }
            else
            {
                btnSin->setIcon(QIcon(":/image/light/scientific/btnAsin.png"));
                btnCos->setIcon(QIcon(":/image/light/scientific/btnAcos.png"));
                btnTan->setIcon(QIcon(":/image/light/scientific/btnAtan.png"));
            }

        }
        else if (WidgetStyle::themeColor == 1) {
            if (DataWarehouse::getInstance()->platform == QString("intel")) {
                btnSin->setIcon(QIcon(":/image/intelScientificDark/btnAsin.svg"));
                btnCos->setIcon(QIcon(":/image/intelScientificDark/btnAcos.svg"));
                btnTan->setIcon(QIcon(":/image/intelScientificDark/btnAtan.svg"));
            } else {
                btnSin->setIcon(QIcon(":/image/scientific/btnAsin.png"));
                btnCos->setIcon(QIcon(":/image/scientific/btnAcos.png"));
                btnTan->setIcon(QIcon(":/image/scientific/btnAtan.png"));
            }
        }
    }
}

// 切换角度弧度显示
void ScientificModel::changeBtnRadDisplay()
{
    // 切换文字显示和图片显示
    if (btnRad->text() == "rad") {
        btnRad->setText("deg");
    }
    else {
        btnRad->setText("rad");
    }

    // 更新角度弧度图片
    updateBtnRadDisplay();
}

// 更新角度弧度图片
void ScientificModel::updateBtnRadDisplay()
{
    // 切换图片显示
    if (btnRad->text() == "rad") {

        if (WidgetStyle::themeColor == 0) {
            if(DataWarehouse::getInstance()->platform == QString("intel"))
            {
                btnRad->setIcon(QIcon(":/image/intelScientific/btnRad.svg"));
            }
            else
            {
                btnRad->setIcon(QIcon(":/image/light/scientific/btnRad.png"));
            }

        }
        else if (WidgetStyle::themeColor == 1) {
            if (DataWarehouse::getInstance()->platform == QString("intel")) {
                btnRad->setIcon(QIcon(":/image/intelScientificDark/btnRad.svg"));
            } else {
                btnRad->setIcon(QIcon(":/image/scientific/btnRad.png"));
            }
        }
        
        btnRad->setIconSize(QSize(106, 62)); 
    }
    else {
        
        if (WidgetStyle::themeColor == 0) {
            if(DataWarehouse::getInstance()->platform == QString("intel"))
            {
                btnRad->setIcon(QIcon(":/image/intelScientific/btnDeg.svg"));
            }
            else
            {
                btnRad->setIcon(QIcon(":/image/light/scientific/btnDeg.png"));
            }

        }
        else if (WidgetStyle::themeColor == 1) {
            if (DataWarehouse::getInstance()->platform == QString("intel")) {
                btnRad->setIcon(QIcon(":/image/intelScientificDark/btnDeg.svg"));
            } else {
                btnRad->setIcon(QIcon(":/image/scientific/btnDeg.png"));
            }
        }

        // 调整Deg按钮大小
        btnRad->setIconSize(QSize(95, 55));
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
    case Qt::Key_ParenLeft:
        btnBracketLeft->click();
        break;
    case Qt::Key_ParenRight:
        btnBracketRight->click();
        break;
    case Qt::Key_AsciiCircum:
        btnYPowerX->click();
        break;
    case Qt::Key_Exclam:
        btnFac->click();
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
    // return QWidget::keyPressEvent(event);
}
