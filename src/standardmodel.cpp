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

#include "standardmodel.h"
#include "data_warehouse.h"

StandardOutput::StandardOutput(QWidget *parent)
{
        // 初始化组件
        this->setWidgetUi();
        // 设置组件样式
        this->setWidgetStyle();
}

// 初始化组件
void StandardOutput::setWidgetUi()
{
    // 当前表达式
    this->staLabNow  = new QLabel(this);

    // 历史记录
    this->staLabLast = new QLabel(this);

    // 预测输出
    this->staLabPre = new QLabel(this);

    //    staLabNow->setWordWrap(true);
    //    staLabLast->setWordWrap(true);
    //    staLabPre->setWordWrap(true);

    QFont staLabLastFont("SourceHanSansCN-Light", 40, 15);
    this->staLabLast->setAlignment(Qt::AlignRight | Qt::AlignTop);
    this->staLabLast->setFont(staLabLastFont);
    this->staLabLast->setText("");
    this->staLabLast->show();

    QFont staLabPreFont("SourceHanSansCN-Light", 40, 15);
    this->staLabPre->setAlignment(Qt::AlignRight | Qt::AlignTop);
    this->staLabPre->setFont(staLabPreFont);
    this->staLabPre->setText("");
    //this->staLabPre->setFixedHeight(35);
    this->staLabPre->show();

    if (DataWarehouse::getInstance()->platform == QString("intel")) {
        QFont staLabNowFont("OPPOSans" , 48 , 15);
        staLabNowFont.setBold(true);
        staLabNowFont.setPixelSize(48);
        this->staLabNow->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        this->staLabNow->setFont(staLabNowFont);
        this->staLabNow->setText("0");
        this->staLabNow->show();
    } else {
        QFont staLabNowFont("SourceHanSansCN-Normal", 48, 15);
        this->staLabNow->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        this->staLabNow->setFont(staLabNowFont);
        this->staLabNow->setText("0");
        //this->staLabNow->setFixedHeight(65);
        this->staLabNow->show();
    }

    this->staLabLast->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->staLabPre->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->staLabNow->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *staOutputLayout = new QVBoxLayout();

    /* intel output ui */
    if (DataWarehouse::getInstance()->platform == QString("intel")) {
        this->staLabLast->hide();
        this->staLabPre->hide();

        staOutputLayout->addWidget(this->staLabNow);
        staOutputLayout->setSpacing(0);

        this->setLayout(staOutputLayout);
        //this->setFixedHeight(102);

        return;
    }

    staOutputLayout->addWidget(this->staLabLast);
    staOutputLayout->addWidget(this->staLabPre);
    staOutputLayout->addWidget(this->staLabNow);
    staOutputLayout->setStretchFactor(this->staLabLast, 14);
    staOutputLayout->setStretchFactor(this->staLabPre, 1);
    staOutputLayout->setStretchFactor(this->staLabNow, 1);
    staOutputLayout->setSpacing(0);

    this->setLayout(staOutputLayout);
    //this->setFixedHeight(270);
    //    this->setContentsMargins(1, 0, 1, 0);
}

// 设置组件样式
void StandardOutput::setWidgetStyle(bool resetFontSize)
{
    /* handle intel ui */
    if (DataWarehouse::getInstance()->platform == QString("intel")) {
        return;
    }

    if (WidgetStyle::themeColor == 0) {
        this->staLabLast->setStyleSheet("color:#8C8C8C;font-size:12px;margin:0 7px 0 7px;");
        this->staLabPre->setStyleSheet("color:#FB9119;font-size:20px;margin:0 7px 0 7px;");


        if (resetFontSize) {
            this->staLabNow->setStyleSheet("color:#272A2D;font-size:48px;font-weight:15px;margin:0 0 5px 7px;");
        }
        else {
            QString fontSizeStr = QString::number(staLabNow->font().pixelSize());
            this->staLabNow->setStyleSheet("color:#272A2D;font-size:" + fontSizeStr + "px;font-weight:15px;margin:0 0 5px 7px;");
        }
    }
    else if (WidgetStyle::themeColor == 1) {
        this->staLabLast->setStyleSheet("color:#8C8C8C;font-size:12px;margin:0 7px 0 7px;");
        this->staLabPre->setStyleSheet("color:#FB9119;font-size:20px;margin:0 7px 0 7px;");

        if (resetFontSize) {
            this->staLabNow->setStyleSheet("color:#FFFFFF;font-size:48px;font-weight:15px;margin:0 0 5px 7px;");
        }
        else {
            QString fontSizeStr = QString::number(staLabNow->font().pixelSize());
            this->staLabNow->setStyleSheet("color:#FFFFFF;font-size:" + fontSizeStr + "px;font-weight:15px;margin:0 0 5px 7px;");
        }
    }
}

StandardModel::StandardModel(QWidget *parent)
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

void StandardModel::createIntelModel(void)
{
    qDebug() << "Info : create intel stand mode ui...";

    //this->setFixedSize(400 , 400);

    for (int i = 0 ; i < 10 ; i++) {
        btnNum[i] = new BasicButton(this);
        btnNum[i]->setText(QString::number(i));
        btnNum[i]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        btnNum[i]->setIcon(QIcon(":/image/intelStandLight/"+ QString::number(i) +".png"));
        if (i == 0) {
            btnNum[i]->setIconSize(QSize(200, 80));
        } else {
            btnNum[i]->setIconSize(QSize(100, 80));
        }
    }

    btnClear  = new BasicButton(this);   /* 清除键 */
    btnPer    = new BasicButton(this);   /* 百分号 */
    btnDelete = new BasicButton(this);   /* 删除键 */
    btnDiv   = new BasicButton(this);    /* 除号 */
    btnMulti = new BasicButton(this);    /* 乘号 */
    btnSub   = new BasicButton(this);    /* 减号 */
    btnAdd   = new BasicButton(this);    /* 加号 */
    btnEqual = new BasicButton(this);    /* 等号 */
    btnPoint = new BasicButton(this);    /* 小数点 */

    // 设置按钮的显示文本
    QString btnList = "C,÷,×,B,ｰ,+,=,%,.";
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

    btnClear->setIcon(QIcon(":/image/intelStandLight/ac.png"));
    btnDiv->setIcon(QIcon(":/image/intelStandLight/except.png"));
    btnMulti->setIcon(QIcon(":/image/intelStandLight/ride.png"));
    btnDelete->setIcon(QIcon(":/image/intelStandLight/delete.png"));
    btnSub->setIcon(QIcon(":/image/intelStandLight/reduce.png"));
    btnAdd->setIcon(QIcon(":/image/intelStandLight/add.png"));
    btnEqual->setIcon(QIcon(":/image/intelStandLight/equal.png"));
    btnPer->setIcon(QIcon(":/image/intelStandLight/per.png"));
    btnPoint->setIcon(QIcon(":/image/intelStandLight/spot.png"));

    btnClear ->setIconSize(QSize(100, 80));
    btnDiv   ->setIconSize(QSize(100, 80));
    btnMulti ->setIconSize(QSize(100, 80));
    btnDelete->setIconSize(QSize(100, 80));
    btnSub   ->setIconSize(QSize(100, 80));
    btnAdd   ->setIconSize(QSize(100, 80));
    btnEqual ->setIconSize(QSize(100, 80));
    btnPer   ->setIconSize(QSize(100, 80));
    btnPoint ->setIconSize(QSize(100, 80));

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

        // 将按钮进行网格布局
    QGridLayout *btnLayout = new QGridLayout();
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
    btnLayout->addWidget(btnNum[0], 4, 0, 1, 2);
    for (int i = 1; i < 10; i++) {
        btnLayout->addWidget(btnNum[i], 3 - (i - 1)/3, (i - 1) % 3, 1, 1);
    }

    // 设置间距和背景样式
    btnLayout->setSpacing(2);
    btnLayout->setMargin(1);
    this->setLayout(btnLayout);
}

void StandardModel::createIntelStyle(void)
{
    qDebug() << "change intel stand mode ui style...";

    QString btnStyle;
    QString btnOpStyle;
    QString btnEqualStyle;

    if (WidgetStyle::themeColor == 0) {
        for (int i = 0; i < 10; i++) {
            btnNum[i]->setIcon(QIcon(":/image/intelStandLight/"+ QString::number(i) +".png"));
            //btnNum[i]->setIcon(QIcon(":/image/light/standard/btnNum"+ QString::number(i) +".png"));
        }

        btnClear->setIcon(QIcon(":/image/intelStandLight/ac.png"));
        btnDiv->setIcon(QIcon(":/image/intelStandLight/except.png"));
        btnMulti->setIcon(QIcon(":/image/intelStandLight/ride.png"));
        btnDelete->setIcon(QIcon(":/image/intelStandLight/delete.png"));
        btnSub->setIcon(QIcon(":/image/intelStandLight/reduce.png"));
        btnAdd->setIcon(QIcon(":/image/intelStandLight/add.png"));
        btnEqual->setIcon(QIcon(":/image/intelStandLight/equal.png"));
        btnPer->setIcon(QIcon(":/image/intelStandLight/per.png"));
        btnPoint->setIcon(QIcon(":/image/intelStandLight/spot.png"));

        //btnClear->setIcon(QIcon(":/image/light/standard/btnClear.png"));
        //btnDiv->setIcon(QIcon(":/image/light/standard/btnDiv.png"));
        //btnMulti->setIcon(QIcon(":/image/light/standard/btnMulti.png"));
        //btnDelete->setIcon(QIcon(":/image/light/standard/btnDelete.png"));
        //btnSub->setIcon(QIcon(":/image/light/standard/btnSub.png"));
        //btnAdd->setIcon(QIcon(":/image/light/standard/btnAdd.png"));
        //btnEqual->setIcon(QIcon(":/image/light/standard/btnEqual.png"));
        //btnPer->setIcon(QIcon(":/image/light/standard/btnPer.png"));
        //btnPoint->setIcon(QIcon(":/image/light/standard/btnPoint.png"));

        btnStyle = "QPushButton{"
                   "background-color:#FFFFFF;border-radius:0px;"
                   "font-size:42px;font-family:HelveticaNeueLTPro-UltLt;color:#FFFFFF;"
                   "}"
                   "QPushButton:pressed{background-color:#F6F6F6;}";

        btnOpStyle = "QPushButton{"
                     "background-color:#FFFFFF;border-radius:0px;"
                     "font-size:35px;font-family:HelveticaNeueLTPro-UltLt;color:#FFFFFF;"
                     "}"
                     "QPushButton:pressed{background-color:#F6F6F6;}";

        btnEqualStyle = "QPushButton{"
                        "background-color:#FB7054;border-radius:0px;"
                        "font-size:48px;font-family:HelveticaNeueLTPro-UltLt;color:#FFFFFF;"
                        "}"
                        "QPushButton:pressed{background-color:#EA5E42;}";
    }
    else if (WidgetStyle::themeColor == 1) {
/* 暗色主题的设计稿还未给出 */
#if 0
        for (int i = 0; i < 10; i++) {
            btnNum[i]->setIcon(QIcon(":/image/standard/btnNum"+ QString::number(i) +".png"));
        }

        btnClear->setIcon(QIcon(":/image/standard/btnClear.png"));
        btnDiv->setIcon(QIcon(":/image/standard/btnDiv.png"));
        btnMulti->setIcon(QIcon(":/image/standard/btnMulti.png"));
        btnDelete->setIcon(QIcon(":/image/standard/btnDelete.png"));
        btnSub->setIcon(QIcon(":/image/standard/btnSub.png"));
        btnAdd->setIcon(QIcon(":/image/standard/btnAdd.png"));
        btnEqual->setIcon(QIcon(":/image/standard/btnEqual.png"));
        btnPer->setIcon(QIcon(":/image/standard/btnPer.png"));
        btnPoint->setIcon(QIcon(":/image/standard/btnPoint.png"));

        btnStyle = "QPushButton{"
                   "width:100px;height:80px;opacity:0.95;"
                   "background-color:#27292C;border-radius:4px;"
                   "font-size:42px;font-family:HelveticaNeueLTPro-UltLt;color:#FFFFFF;"
                   "}"
                   "QPushButton:hover{background-color:#474747;}";

        btnOpStyle = "QPushButton{"
                     "width:100px;height:80px;opacity:1;"
                     "background-color:#222E36;border-radius:4px;"
                     "font-size:35px;font-family:HelveticaNeueLTPro-UltLt;color:#FFFFFF;}"
                     "QPushButton:hover{background-color:#474747;}";

        btnEqualStyle = "QPushButton{"
                        "width:200px;height:80px;opacity:1;"
                        "background-color:#E64A19;border-radius:4px;"
                        "font-size:48px;font-family:HelveticaNeueLTPro-UltLt;color:#FFFFFF;"
                        "}"
                        "QPushButton:hover{background-color:#E45E4C;}";
#endif
    }

    /* 设置按钮风格 */
    for (int i = 0 ; i < 10 ; i++) {
        btnNum[i]->setStyleSheet(btnStyle);
    }

    // 设置按钮样式standardModel
    btnClear->setStyleSheet(btnStyle);
    btnPer->setStyleSheet(btnStyle);
    btnDelete->setStyleSheet(btnStyle);
    btnPoint->setStyleSheet(btnStyle);

    btnDiv->setStyleSheet(btnOpStyle);
    btnMulti->setStyleSheet(btnOpStyle);
    btnSub->setStyleSheet(btnOpStyle);
    btnAdd->setStyleSheet(btnOpStyle);

    btnEqual->setStyleSheet(btnEqualStyle);

    return;
}

// 初始化组件
void StandardModel::setWidgetUi()
{
    // qDebug() << "im in StandardModel::setWidgetUi()!";
    // 计算器按钮
    QString str_list = "C,÷,×,B,7,8,9,ｰ,4,5,6,+,1,2,3,,%,0,.,=";
    QStringList btn_name_list= str_list.split(",");

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

    // 设置按钮的显示文本
    QString btnList = "C,÷,×,B,ｰ,+,=,%,.";
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

    btnClear ->setIconSize(QSize(106, 62));
    btnDiv   ->setIconSize(QSize(106, 62));
    btnMulti ->setIconSize(QSize(106, 62));
    btnDelete->setIconSize(QSize(85,  50));
    btnSub   ->setIconSize(QSize(106, 62));
    btnAdd   ->setIconSize(QSize(106, 62));
    btnEqual ->setIconSize(QSize(106, 62));
    btnPer   ->setIconSize(QSize(106, 62));
    btnPoint ->setIconSize(QSize(106, 62));

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

    // 将按钮进行网格布局
    QGridLayout *btnLayout = new QGridLayout();
//    btnLayout->addWidget(btnClear, 0, 0, 1, 1);
//    btnLayout->addWidget(btnDiv, 0, 1, 1, 1);
//    btnLayout->addWidget(btnMulti, 0, 2, 1, 1);
//    btnLayout->addWidget(btnDelete, 0, 3, 1, 1);
//    btnLayout->addWidget(btnSub, 1, 3, 1, 1);
//    btnLayout->addWidget(btnAdd, 2, 3, 1, 1);
//    btnLayout->addWidget(btnEqual, 3, 3, 2, 1);
//    btnLayout->addWidget(btnPer, 4, 0, 1, 1);
//    btnLayout->addWidget(btnPoint, 4, 2, 1, 1);

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
    //this->setFixedHeight(320);
    this->setLayout(btnLayout);
}

// 设置组件样式
void StandardModel::setWidgetStyle()
{
    // qDebug() << "im in StandardModel::setWidgetStyle()!";
    // qDebug() << WidgetStyle::themeColor;
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
    //布局按钮

    for (int i = 0; i < 10; i++) {
        btnNum[i]->setStyleSheet(btnStyle);
    }

    // btnDZero->setStyleSheet(btnStyle);

    // 设置按钮样式standardModel
    btnClear->setStyleSheet(btnStyle);
    btnPer->setStyleSheet(btnStyle);
    btnDelete->setStyleSheet(btnStyle);
    btnPoint->setStyleSheet(btnStyle);

    btnDiv->setStyleSheet(btnOpStyle);
    btnMulti->setStyleSheet(btnOpStyle);
    btnSub->setStyleSheet(btnOpStyle);
    btnAdd->setStyleSheet(btnOpStyle);

    btnEqual->setStyleSheet(btnEqualStyle);
}

// 格式化输入表达式
void StandardModel::StaFormatInput(QString text)
{

}

void StandardModel::keyPressEvent(QKeyEvent *event)
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
    // return QWidget::keyPressEvent(event);
}

