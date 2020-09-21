#include "scientificmodel.h"

ScientificOutput::ScientificOutput(QWidget *parent)
    : QWidget(parent)
{
    this->sciLabLastL = new QLabel(this);
    this->sciLabLastR = new QLabel(this);
    this->sciLabPre = new QLabel(this);
    this->sciLabNow = new QLabel(this);

    sciLabLastL->setWordWrap(true);
    sciLabLastR->setWordWrap(true);
    sciLabPre->setWordWrap(true);
    sciLabNow->setWordWrap(true);

    QFont labLastFont("SourceHanSansCN-Light", 40, 15);
    this->sciLabLastL->setAlignment(Qt::AlignRight | Qt::AlignTop);
    this->sciLabLastL->setFont(labLastFont);
    this->sciLabLastL->setText("left");
    this->sciLabLastL->setStyleSheet("color:#8C8C8C;font-size:20px;margin:0 7px 0 7px;");

    this->sciLabLastL->show();

    this->sciLabLastR->setAlignment(Qt::AlignRight | Qt::AlignTop);
    this->sciLabLastR->setFont(labLastFont);
    this->sciLabLastR->setText("right");
    this->sciLabLastR->setStyleSheet("color:#8C8C8C;font-size:20px;margin:0 7px 0 7px;");
    this->sciLabLastR->show();

    QFont sciLabPreFont("SourceHanSansCN-Light", 40, 15);
    this->sciLabPre->setAlignment(Qt::AlignRight | Qt::AlignTop);
    this->sciLabPre->setFont(sciLabPreFont);
    this->sciLabPre->setText("0");
    this->sciLabPre->setFixedHeight(35);
    this->sciLabPre->setStyleSheet("color:#FB9119;font-size:20px;margin:0 7px 0 7px;");
    //    this->sciLabPre->setContentsMargins(0, 0, 20, 0);
    this->sciLabPre->show();

    QFont sciLabNowFont("SourceHanSansCN-Normal", 50, 15);
    this->sciLabNow->setAlignment(Qt::AlignRight);
    this->sciLabNow->setFont(sciLabNowFont);
    this->sciLabNow->setText("0");
    this->sciLabNow->setFixedHeight(65);
    this->sciLabNow->setStyleSheet("color:white;font-size:48px;font-weight:15px;margin:0 0 0 7px;");
    this->sciLabNow->setContentsMargins(0, 0, 0, 0);
    this->sciLabNow->show();

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
}

ScientificModel::ScientificModel(QWidget *parent)
    : QWidget(parent)
{
    // 计算器按钮
    // 布局按钮
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

    QString btnSciStyle = "QPushButton{"
                          "width:106px;height:62px;opacity:1;"
                          "background-color:#181E23;border-radius:4px;"
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

    btnInd = new QPushButton(this);
    btnUndo = new QPushButton(this);
    btnBracketLeft = new QPushButton(this);
    btnBracketRight = new QPushButton(this);

    btnReci = new QPushButton(this);
    btnXPower2 = new QPushButton(this);
    btnXPower3 = new QPushButton(this);
    btnYPowerX = new QPushButton(this);

    btnFac = new QPushButton(this);
    btnXSquare2 = new QPushButton(this);
    btnXSquare3 = new QPushButton(this);
    btnYSquareX = new QPushButton(this);

    btnSin = new QPushButton(this);
    btnCos = new QPushButton(this);
    btnTan = new QPushButton(this);
    btnLog = new QPushButton(this);

    btnRad = new QPushButton(this);
    btnPi = new QPushButton(this);
    btnExp = new QPushButton(this);
    btnLn = new QPushButton(this);

    //    XPower2Button = new QPushButton(this);
    //    PowerButton = new QPushButton(this);
    //    SinButton = new QPushButton(this);
    //    CosButton = new QPushButton(this);
    //    TanButton = new QPushButton(this);
    //    SinhButton = new QPushButton(this);
    //    CoshButton = new QPushButton(this);
    //    TanhButton = new QPushButton(this);
    //    XPower3Button = new QPushButton(this);
    //    YSquareRootButton = new QPushButton(this);
    //    InvsinButton = new QPushButton(this);
    //    InvcosButton = new QPushButton(this);
    //    InvtanButton = new QPushButton(this);
    //    InvsinhButton = new QPushButton(this);
    //    InvcoshButton = new QPushButton(this);
    //    InvtanhButton = new QPushButton(this);
    //    SquareRootButton = new QPushButton(this);
    //    PowerOf10Button = new QPushButton(this);
    //    LogBase10Button = new QPushButton(this);
    //    ExpButton = new QPushButton(this);
    //    ModButton = new QPushButton(this);

    //    InvertButton = new QPushButton(this);
    //    PowerOfEButton = new QPushButton(this);
    //    LogBaseEButton = new QPushButton(this);

    //    PiButton = new QPushButton(this);

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

    btnList = "2nd,Ans,(,),1/x,x²,x³,y^x,x!,√x,³√x,x√y,sin,cos,tan,log,Rad,π,e,ln";
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
    btnClear->setStyleSheet(btnOpStyle);
    btnDiv->setStyleSheet(btnOpStyle);
    btnMulti->setStyleSheet(btnOpStyle);
    btnDelete->setStyleSheet(btnOpStyle);
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

//    // 绑定处理函数
//    for (int i = 0; i < 10; i++) {
//        QObject::connect(btnNum[i],SIGNAL(clicked(bool)),this,SLOT(btnHandler(bool)));
//    }

//    QObject::connect(btnClear,  SIGNAL(clicked(bool)),this,SLOT(btnHandler(bool)));
//    QObject::connect(btnDiv,    SIGNAL(clicked(bool)),this,SLOT(btnHandler(bool)));
//    QObject::connect(btnMulti,  SIGNAL(clicked(bool)),this,SLOT(btnHandler(bool)));
//    QObject::connect(btnSub,    SIGNAL(clicked(bool)),this,SLOT(btnHandler(bool)));
//    QObject::connect(btnAdd,    SIGNAL(clicked(bool)),this,SLOT(btnHandler(bool)));
//    QObject::connect(btnEqual,  SIGNAL(clicked(bool)),this,SLOT(btnHandler(bool)));
//    QObject::connect(btnPer,    SIGNAL(clicked(bool)),this,SLOT(btnHandler(bool)));
//    QObject::connect(btnPoint,  SIGNAL(clicked(bool)),this,SLOT(btnHandler(bool)));
//    QObject::connect(btnDelete, SIGNAL(clicked(bool)),this,SLOT(btnDelHandle(bool)));


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
