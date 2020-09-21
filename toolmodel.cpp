#include "toolmodel.h"

ToolModelOutput::ToolModelOutput(QWidget *parent)
    : QWidget(parent)
{
    // 汇率刷新
    toolLabUpdate  = new QLabel(this);
    toolIconUpdate = new QLabel(this);
    toolLabRate    = new QLabel(this);

    toolLabUpdate->setText("汇率更新");
    toolLabUpdate->setStyleSheet("font-family:SourceHanSansCN-ExtraLight;font-size:16px;color:#FFFFFF;");

    toolIconUpdate->setFixedSize(16, 16);
    toolIconUpdate->setStyleSheet("border-image:url(:/image/update.png);");

    toolLabRate->setText("2020.09.03 09:30\n1 CNY = 0.15 USD");
    toolLabRate->setStyleSheet("font-family:NotoSansHans-Light;font-size:10px;color:#A6A6A6;line-height:17px;");

    toolUpdateLayout = new QVBoxLayout(this);
    toolUpdateLayout->addWidget(toolLabUpdate,  0, Qt::AlignCenter);
    toolUpdateLayout->addWidget(toolIconUpdate, 0, Qt::AlignCenter);
    toolUpdateLayout->addWidget(toolLabRate,    0, Qt::AlignCenter);

    toolUpdateWid = new QWidget(this);
    toolUpdateWid->setLayout(toolUpdateLayout);
    toolUpdateWid->setFixedSize(106, 133);
//    toolUpdateWid->setFixedWidth(107);
    toolUpdateWid->setStyleSheet("background:#18181A;opacity:0.75;");

    // 换算前单位标识
    toolLabUnitBef = new QLabel(this);
    toolLabIconBef = new QLabel(this);

    QString unitLabStyle  = "font-family:SourceHanSansCN-ExtraLight;font-size:18px;color:#FFFFFF;line-height:22px;";

    toolLabUnitBef->setText("人民币\nCNY");
    toolLabUnitBef->setStyleSheet(unitLabStyle);

    toolLabIconBef->setFixedSize(10, 10);
    toolLabIconBef->setStyleSheet("border-image:url(:/image/downward.png);");

    toolUnitBefLayout = new QHBoxLayout(this);
    toolUnitBefLayout->addWidget(toolLabUnitBef);
    toolUnitBefLayout->addWidget(toolLabIconBef);

    toolUnitBefWid = new QWidget(this);
    toolUnitBefWid->setLayout(toolUnitBefLayout);
    toolUnitBefWid->setFixedSize(106, 66);
    toolUnitBefWid->setStyleSheet("background:#18181A;color:#FFFFFF;opacity:0.75;");

    // 换算后单位标识
    toolLabUnitAft = new QLabel(this);
    toolLabIconAft = new QLabel(this);

    toolLabUnitAft->setText("美元\nUSD");
    toolLabUnitAft->setStyleSheet(unitLabStyle);

    toolLabIconAft->setFixedSize(10, 10);
    toolLabIconAft->setStyleSheet("border-image:url(:/image/downward.png);");

    toolUnitAftLayout = new QHBoxLayout(this);
    toolUnitAftLayout->addWidget(toolLabUnitAft);
    toolUnitAftLayout->addWidget(toolLabIconAft);

    toolUnitAftWid = new QWidget(this);
    toolUnitAftWid->setLayout(toolUnitAftLayout);
    toolUnitAftWid->setFixedSize(106, 66);
    toolUnitAftWid->setStyleSheet("background:#18181A;color:#FFFFFF;opacity:0.75;");

    // 数据输出界面
    this->toolLabHis = new QLabel(this);
    this->toolLabBef = new QLabel(this);
    this->toolLabAft = new QLabel(this);

    toolLabHis->setWordWrap(true);
    toolLabBef->setWordWrap(true);
    toolLabAft->setWordWrap(true);

    QFont toolLabHisFont("SourceHanSansCN-Light", 40, 15);
    this->toolLabHis->setAlignment(Qt::AlignRight | Qt::AlignTop);
    this->toolLabHis->setFont(toolLabHisFont);
    this->toolLabHis->setText("");
    this->toolLabHis->setStyleSheet("color:#8C8C8C;font-size:20px;background-color:#18181A;");
    this->toolLabHis->setFixedHeight(133);
    this->toolLabHis->setContentsMargins(0, 0, 20, 0);
    this->toolLabHis->show();

    QFont toolLabBefFont("SourceHanSansCN-Normal;", 50, 15);
    this->toolLabBef->setAlignment(Qt::AlignRight | Qt::AlignBottom);
    this->toolLabBef->setFont(toolLabBefFont);
    this->toolLabBef->setText("0");
    this->toolLabBef->setStyleSheet("color:#FFFFFF;font-size:45px;background-color:#18181A;");
    this->toolLabBef->setFixedHeight(66);
    this->toolLabBef->setContentsMargins(0, 0, 20, 0);
    this->toolLabBef->show();

    QFont toolLabAftFont("SourceHanSansCN-Normal", 50, 15);
    this->toolLabAft->setAlignment(Qt::AlignRight | Qt::AlignBottom);
    this->toolLabAft->setFont(toolLabAftFont);
    this->toolLabAft->setText("0");
    this->toolLabAft->setStyleSheet("color:#FFFFFF;font-size:45px;background-color:#18181A;");
    this->toolLabAft->setFixedHeight(66);
    this->toolLabAft->setContentsMargins(0, 0, 20, 0);
    this->toolLabAft->show();

    // 数据单位列表
    this->unitListBef = new QListWidget(this);
    this->unitListAft  = new QListWidget(this);

    this->unitListBef->hide();
    this->unitListAft->hide();

    // 将数据输出组件和数据单位列表加入布局
    QGridLayout *toolOutputLayout = new QGridLayout(this);

    toolOutputLayout->addWidget(toolUpdateWid, 0, 0, 1, 1);
    toolOutputLayout->addWidget(toolUnitBefWid, 1, 0, 1, 1);
    toolOutputLayout->addWidget(toolUnitAftWid, 2, 0, 1, 1);
    toolOutputLayout->addWidget(toolLabHis, 0, 1, 1, 1);
    toolOutputLayout->addWidget(toolLabBef, 1, 1, 1, 1);
    toolOutputLayout->addWidget(toolLabAft, 2, 1, 1, 1);

    toolOutputLayout->setSpacing(2);
    toolOutputLayout->setContentsMargins(1, 1, 1, 0);

    this->setLayout(toolOutputLayout);
    this->setFixedHeight(270);
    this->setStyleSheet("background-color:#8C8C8C;border-radius:4px;");
}

void ToolModelOutput::initUnitList(QString listStr)
{
    QStringList unitStrList = listStr.split(",");

    QListWidgetItem *unitBeforeItem[unitStrList.size()];
    QListWidgetItem *unitAfterItem[unitStrList.size()];

    unitListBef->clear();
    unitListAft->clear();

    // 单位列表初始化
    for (int i = 0; i < unitStrList.size(); i++) {

        unitBeforeItem[i] = new QListWidgetItem(unitStrList[i], unitListBef);
        unitAfterItem[i]  = new QListWidgetItem(unitStrList[i], unitListAft);

        unitListBef->addItem(unitBeforeItem[i]);
        unitListAft->addItem(unitAfterItem[i]);
    }

    unitListBef->setSpacing(2);
    unitListAft->setSpacing(2);

    QString unitListStyle = "QListWidget::item:selected{background-color:#36363A;}"
                            "QListWidget::item:hover{background-color:#666666;}";

    unitListBef->setStyleSheet(unitListStyle);
    unitListAft->setStyleSheet(unitListStyle);
}

void ToolModelOutput::unitConversion()
{
    QString strBefore = this->toolLabBef->text();
    QString strAfter  = this->toolLabAft->text();
}

ToolModelButton::ToolModelButton(QWidget *parent)
    : QWidget(parent)
{
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
    this->setStyleSheet("border-radius:4px;");
}

void ToolModelButton::keyPressEvent(QKeyEvent *event)
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
