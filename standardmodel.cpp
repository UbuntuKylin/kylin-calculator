#include "standardmodel.h"

StandardOutput::StandardOutput(QWidget *parent)
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
    this->staLabLast->setStyleSheet("color:#8C8C8C;font-size:20px;margin:0 7px 0 7px;");
    this->staLabLast->show();

    QFont staLabPreFont("SourceHanSansCN-Light", 40, 15);
    this->staLabPre->setAlignment(Qt::AlignRight | Qt::AlignTop);
    this->staLabPre->setFont(staLabPreFont);
    this->staLabPre->setText("");
    this->staLabPre->setFixedHeight(35);
    this->staLabPre->setStyleSheet("color:#FB9119;font-size:20px;margin:0 7px 0 7px;");
    this->staLabPre->show();

    QFont staLabNowFont("SourceHanSansCN-Normal", 50, 15);
    this->staLabNow->setAlignment(Qt::AlignRight);
    this->staLabNow->setFont(staLabNowFont);
    this->staLabNow->setText("0");
    this->staLabNow->setFixedHeight(65);
    this->staLabNow->setStyleSheet("color:#FFFFFF;font-size:47px;font-weight:15px;line-height:50px;margin:0 0 5px 7px;");
    this->staLabNow->show();

    this->staLabNow->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->staLabPre->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->staLabNow->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *staOutputLayout = new QVBoxLayout();
    staOutputLayout->addWidget(this->staLabLast);
    staOutputLayout->addWidget(this->staLabPre);
    staOutputLayout->addWidget(this->staLabNow);
    staOutputLayout->setStretchFactor(this->staLabLast, 14);
    staOutputLayout->setStretchFactor(this->staLabPre, 1);
    staOutputLayout->setStretchFactor(this->staLabNow, 1);
    staOutputLayout->setSpacing(0);

    this->setLayout(staOutputLayout);
    this->setFixedHeight(270);
    //    this->setContentsMargins(1, 0, 1, 0);
}

StandardModel::StandardModel(QWidget *parent)
    : QWidget(parent)
{
    // 计算器按钮
    QString str_list = "C,÷,×,,7,8,9,—,4,5,6,+,1,2,3,,%,0,.,=";
    QStringList btn_name_list= str_list.split(",");

    //布局按钮
    QFont btnFont("HelveticaNeueLTPro-UltLt", 30, 10);

    QString btnStyle = "QPushButton{"
                       "width:106px;height:62px;opacity:0.95;"
                       "background-color:#1C1C1E;border-radius:4px;"
                       "font-size:42px;font-family:HelveticaNeueLTPro-UltLt;color:#FFFFFF;"
                       "}"
                       "QPushButton:hover{background-color:rgb(180,180,180);}";

    for (int i = 0; i < 10; i++) {
        btnNum[i] = new QPushButton(this);
        btnNum[i]->setText(QString::number(i));
        btnNum[i]->setStyleSheet(btnStyle);
        btnNum[i]->setFont(btnFont);
        btnNum[i]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    }

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
                          "background-color:#1C1C1E;border-radius:4px;"
                          "font-size:31px;font-family:HelveticaNeueLTPro-UltLt;color:#FFFFFF;"
                          "}"
                          "QPushButton:hover{background-color:rgb(180,180,180);}";

    btnClear = new QPushButton(this);
    btnDiv = new QPushButton(this);
    btnMulti = new QPushButton(this);
    btnDelete = new QPushButton(this);
    btnSub = new QPushButton(this);
    btnAdd = new QPushButton(this);
    btnEqual = new QPushButton(this);
    btnPer = new QPushButton(this);
    btnPoint = new QPushButton(this);

    // 设置按钮的显示文本
    QString btnList = "C,÷,×,,—,+,=,%,.";
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

    // 设置按钮样式standardModel
    btnClear->setStyleSheet(btnOpStyle);
    btnDiv->setStyleSheet(btnOpStyle);
    btnMulti->setStyleSheet(btnOpStyle);
    btnDelete->setStyleSheet(btnOpStyle);
    btnSub->setStyleSheet(btnOpStyle);
    btnAdd->setStyleSheet(btnAddStyle);
    btnEqual->setStyleSheet(btnEqualStyle);
    btnPer->setStyleSheet(btnPerStyle);
    btnPoint->setStyleSheet(btnPerStyle);

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

    // 删除按钮
    btnDelete->setIcon(QIcon(":/image/delete.png"));
    btnDelete->setIconSize(QSize(60, 40));

    // 将按钮进行网格布局
    QGridLayout *btnLayout = new QGridLayout();
    btnLayout->addWidget(btnClear, 0, 0, 1, 1);
    btnLayout->addWidget(btnDiv, 0, 1, 1, 1);
    btnLayout->addWidget(btnMulti, 0, 2, 1, 1);
    btnLayout->addWidget(btnDelete, 0, 3, 1, 1);
    btnLayout->addWidget(btnSub, 1, 3, 1, 1);
    btnLayout->addWidget(btnAdd, 2, 3, 1, 1);
    btnLayout->addWidget(btnEqual, 3, 3, 2, 1);
    btnLayout->addWidget(btnPer, 4, 0, 1, 1);
    btnLayout->addWidget(btnPoint, 4, 2, 1, 1);

    // 数字按钮布局
    btnLayout->addWidget(btnNum[0], 4, 1, 1, 1);
    for (int i = 1; i < 10; i++) {
        btnLayout->addWidget(btnNum[i], 3 - (i - 1)/3, (i - 1) % 3, 1, 1);
    }

    // 设置间距和背景样式
    btnLayout->setSpacing(2);
    btnLayout->setMargin(1);
    this->setFixedHeight(320);
    this->setLayout(btnLayout);
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
}

