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

#include <QDebug>
#include <QTimer>

#include "toolmodel.h"
#include "cal.h"

using namespace std;

// 换算器输入输出界面
ToolModelOutput::ToolModelOutput(QWidget *parent)
    : QWidget(parent)
{
    // 初始化组件
    this->setWidgetUi();

    // 设置组件样式
    this->setWidgetStyle();
}


// 初始化组件
void ToolModelOutput::setWidgetUi()
{
    // 汇率刷新
    toolLabUpdate  = new QLabel(this);
    toolIconUpdate = new QToolButton(this);
    toolLabTime    = new QLabel(this);
    toolLabRate    = new QLabel(this);

    toolUpdateLayout = new QVBoxLayout(this);
    timeRateLayout   = new QVBoxLayout(this);

    timeRateLayout->addWidget(toolLabTime, 0, Qt::AlignCenter);
    timeRateLayout->addWidget(toolLabRate, 0, Qt::AlignCenter);
    timeRateLayout->setSpacing(0);
    timeRateLayout->setMargin(0);

    toolUpdateLayout->addSpacing(15);
    toolUpdateLayout->addWidget(toolLabUpdate,  0, Qt::AlignCenter);
    toolUpdateLayout->addWidget(toolIconUpdate, 0, Qt::AlignCenter);
    toolUpdateLayout->addLayout(timeRateLayout, 0);
    toolUpdateLayout->addSpacing(15);
    toolUpdateLayout->setMargin(0);

    toolUpdateWid = new QWidget(this);
    toolUpdateWid->setLayout(toolUpdateLayout);

    // 换算前单位标识
    toolLabUnitBef = new QLabel(this);
    toolLabIconBef = new QLabel(this);

    toolUnitBefLayout = new QHBoxLayout(this);
    toolUnitBefLayout->addWidget(toolLabUnitBef);
    toolUnitBefLayout->addWidget(toolLabIconBef);
    toolUnitBefLayout->setMargin(0);
    toolUnitBefLayout->setContentsMargins(10, 0, 0, 0);

    toolUnitBefWid = new QPushButton(this);
    toolUnitBefWid->setLayout(toolUnitBefLayout);

    // 换算后单位标识
    toolLabUnitAft = new QLabel(this);
    toolLabIconAft = new QLabel(this);

    toolUnitAftLayout = new QHBoxLayout(this);
    toolUnitAftLayout->addWidget(toolLabUnitAft);
    toolUnitAftLayout->addWidget(toolLabIconAft);
    toolUnitAftLayout->setMargin(0);
    toolUnitAftLayout->setContentsMargins(10, 0, 0, 0);

    toolUnitAftWid = new QPushButton(this);
    toolUnitAftWid->setLayout(toolUnitAftLayout);
    toolUnitAftWid->setFixedSize(106, 66);

    // 汇率刷新
    toolLabUpdate->setText(tr("Rate update"));
    // toolLabUpdate->setText("汇率更新");

    toolIconUpdate->setIcon(QIcon::fromTheme("transform-rotate", QIcon(":/image/update.png")));
    toolIconUpdate->setIconSize(QSize(16, 16));
    toolIconUpdate->setProperty("isWindowButton", 0x1);    
    toolIconUpdate->setProperty("useIconHighlightEffect", 0x2);     
    toolIconUpdate->setAutoRaise(true); 

    // 默认汇率
    toolDouRate = 0.15;

    toolLabTime->setText("2020.09.03 09:30");
    toolLabRate->setText("1 CNY = 0.15 USD");

    toolUpdateWid->setFixedSize(106, 133);

    connect(toolIconUpdate, &QToolButton::clicked, this, &ToolModelOutput::updateRate);

    // 换算前单位标识
    toolRateNameBef = tr("Chinese Yuan");
    // toolRateNameBef = "人民币";
    toolRateSymbBef = "CNY";
    toolLabUnitBef->setText(toolRateNameBef + "\n" + toolRateSymbBef);

    toolLabIconBef->setFixedSize(10, 10);

    toolUnitBefWid->setFixedSize(106, 66);

    // 换算后单位标识
    toolRateNameAft = tr("US Dollar");
    // toolRateNameAft = "美元";
    toolRateSymbAft = "USD";
    toolLabUnitAft->setText(toolRateNameAft + "\n" + toolRateSymbAft);

    toolLabIconAft->setFixedSize(10, 10);

    connect(toolUnitBefWid, SIGNAL(clicked()), this, SLOT(unitListBefShow()));
    connect(toolUnitAftWid, SIGNAL(clicked()), this, SLOT(unitListAftShow()));

    // 数据输出界面
    this->toolLabHis = new QLabel(this);
    this->toolLabBef = new QLabel(this);
    this->toolLabAft = new QLabel(this);

    // toolLabHis->setWordWrap(true);
    // toolLabBef->setWordWrap(true);
    // toolLabAft->setWordWrap(true);

    QFont toolLabHisFont("SourceHanSansCN-Light", 40, 15);
    this->toolLabHis->setAlignment(Qt::AlignRight | Qt::AlignTop);
    this->toolLabHis->setFont(toolLabHisFont);
    this->toolLabHis->setText("");
    this->toolLabHis->setFixedHeight(133);
    this->toolLabHis->setContentsMargins(0, 0, 20, 0);
    this->toolLabHis->show();

    QFont toolLabBefFont("SourceHanSansCN-Normal;", 48, 15);
    this->toolLabBef->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    this->toolLabBef->setFont(toolLabBefFont);
    this->toolLabBef->setText("0");
    this->toolLabBef->setFixedHeight(66);
    this->toolLabBef->setContentsMargins(0, 0, 20, 0);
    this->toolLabBef->show();

    QFont toolLabAftFont("SourceHanSansCN-Normal", 48, 15);
    this->toolLabAft->setAlignment(Qt::AlignRight | Qt::AlignBottom);
    this->toolLabAft->setFont(toolLabAftFont);
    this->toolLabAft->setText("0");
    this->toolLabAft->setFixedHeight(66);
    this->toolLabAft->setContentsMargins(0, 0, 20, 0);
    this->toolLabAft->show();

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

    // 数据单位列表
    this->unitListBef  = new UnitListWidget(this->parentWidget(), this->toolUnitBefWid);
    this->unitListAft  = new UnitListWidget(this->parentWidget(), this->toolUnitAftWid);
    unitListBef->setGeometry(QRect(80, 60, 280, 410));
    unitListAft->setGeometry(QRect(80, 130, 280, 410));

    // QString strUnitList = "人民币,美元,欧元,英镑,日元,韩元,澳大利亚元";
    // initUnitList(strUnitList);

    connect(unitListBef->unitList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(unitListSelect(QListWidgetItem*)));
    connect(unitListAft->unitList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(unitListSelect(QListWidgetItem*)));

    connect(unitListBef->btnCancel, SIGNAL(clicked()), this, SLOT(unitListBefShow()));
    connect(unitListAft->btnCancel, SIGNAL(clicked()), this, SLOT(unitListAftShow()));

    this->unitListBef->hide();
    this->unitListAft->hide();

    rateMap = {
        {"Algerian dinar",      "DZD"},
        {"Australian dollar",   "AUD"},
        {"Bahrain Dinar",       "BHD"},
        {"Bolivar Fuerte",      "VEF"},
        {"Botswana pula",       "BWP"},
        {"Brazilian real",      "BRL"},
        {"Brunei dollar",       "BND"},
        {"Canadian dollar",     "CAD"},
        {"Chilean peso",        "CLP"},
        {"Chinese yuan",        "CNY"},
        {"Colombian peso",      "COP"},
        {"Czech koruna",        "CZK"},
        {"Danish krone",        "DKK"},
        {"Euro",                "EUR"},
        {"Hungarian Forint",    "HUF"},
        {"Icelandic Krona",     "ISK"},
        {"Indian rupee",        "INR"},
        {"Indonesian Rupiah",   "IDR"},
        {"Iranian Rial",        "IRR"},
        {"Israeli New Shekel",  "ILS"},
        {"Japanese yen",        "JPY"},
        {"Kazakhstani Tenge",   "KZT"},
        {"Korean won",          "KRW"},
        {"Kuwaiti dinar",       "KWD"},
        {"Libyan Dinar",        "LYD"},
        {"Malaysian ringgit",   "MYR"},
        {"Mauritian rupee",     "MUR"},
        {"Mexican peso",        "MXN"},
        {"Nepalese Rupee",      "NPR"},
        {"New Zealand dollar",  "NZD"},
        {"Norwegian krone",     "NOK"},
        {"Nuevo Sol",           "PEN"},
        {"Omani rial",          "OMR"},
        {"Pakistani Rupee",     "PKR"},
        {"Peruvian sol",        "PEN"},
        {"Philippine peso",     "PHP"},
        {"Polish zloty",        "PLN"},
        {"Qatari riyal",        "QAR"},
        {"Rial Omani",          "OMR"},
        {"Russian ruble",       "RUB"},
        {"Saudi Arabian riyal", "SAR"},
        {"Singapore dollar",    "SGD"},
        {"South African rand",  "ZAR"},
        {"Sri Lanka Rupee",     "LKR"},
        {"Swedish krona",       "SEK"},
        {"Swiss franc",         "CHF"},
        {"Thai baht",           "THB"},
        {"Trinidadian dollar",  "TTD"},
        {"Tunisian Dinar",      "TND"},
        {"U.A.E. dirham",       "AED"},
        {"U.K. pound",          "GBP"},
        {"Uruguayan peso",      "UYU"},
        {"U.S. dollar",         "USD"},
        {NULL, NULL}
    };

    // 没有ARS
    currencyInfoUS = {
        {"AED", "UAE Dirham"},
        {"ARS", "Argentinian peso"},
        {"AUD", "Australian Dollar"},
        {"BGN", "Bulgarian Lev"},
        {"BHD", "Bahraini Dinar"},
        {"BND", "Brunei Dollar"},
        {"BRL", "Brazilian Real"},
        {"BSD", "Bahaman Dollar"},
        {"BWP", "Botswana Pula"},
        {"CAD", "Canadian Dollar"},
        {"CFA", "CFA Franc"},
        {"CHF", "Swiss Franc"},
        {"CLP", "Chilean Peso"},
        {"CNY", "Chinese Yuan"},
        {"COP", "Colombian Peso"},
        {"CZK", "Czech Koruna"},
        {"DKK", "Danish Krone"},
        {"DOP", "Dominican peso"},
        {"DZD", "Algerian Dinar"},
        {"EEK", "Estonian Kroon"},
        {"EGP", "Egyptian pound"},
        {"EUR", "Euro"},
        {"FJD", "Fijian dollar"},
        {"GBP", "Pound Sterling"},
        {"GTQ", "Guatemalan Quetzal"},
        {"HKD", "Hong Kong Dollar"},
        {"HRK", "Croatian Kuna"},
        {"HUF", "Hungarian Forint"},
        {"IDR", "Indonesian Rupiah"},
        {"ILS", "Israeli New Shekel"},
        {"INR", "Indian Rupee"},
        {"IRR", "Iranian Rial"},
        {"ISK", "Icelandic Krona"},
        {"JPY", "Japanese Yen"},
        {"KRW", "South Korean Won"},
        {"KWD", "Kuwaiti Dinar"},
        {"KZT", "Kazakhstani Tenge"},
        {"LKR", "Sri Lankan Rupee"},
        {"LTL", "Lithuanian Litas"},
        {"LVL", "Latvian Lats"},
        {"LYD", "Libyan Dinar"},
        {"MUR", "Mauritian Rupee"},
        {"MVR", "Maldivian Rupee"},
        {"MXN", "Mexican Peso"},
        {"MYR", "Malaysian Ringgit"},
        {"NOK", "Norwegian Krone"},
        {"NPR", "Nepalese Rupee"},
        {"NZD", "New Zealand Dollar"},
        {"OMR", "Omani Rial"},
        {"PAB", "Panamanian balbos"},
        {"PEN", "Peruvian Nuevo Sol"},
        {"PHP", "Philippine Peso"},
        {"PKR", "Pakistani Rupee"},
        {"PLN", "Polish Zloty"},
        {"PYG", "Paraguayan Guaran"},
        {"QAR", "Qatari Riyal"},
        {"RON", "New Romanian Leu"},
        {"RUB", "Russian Rouble"},
        {"SAR", "Saudi Riyal"},
        {"SEK", "Swedish Krona"},
        {"SGD", "Singapore Dollar"},
        {"THB", "Thai Baht"},
        {"TND", "Tunisian Dinar"},
        {"TRY", "New Turkish Lira"},
        {"TTD", "T&T Dollar (TTD)"},
        {"TWD", "Taiwan Dollar"},
        {"UAH", "Ukrainian Hryvnia"},
        {"USD", "US Dollar"},
        {"UYU", "Uruguayan Peso"},
        {"VEF", "Venezuelan Bolívar"},
        {"ZAR", "South African Rand"},
        {NULL, NULL}
    };

    // 新增ARS、BSD、DOP、EGP、FJD、GTQ、MVR、PAB、PYG、TWD、UAH
    currencyInfoCN = {
        {"AED", "阿联酋迪拉姆"},
        {"ARS", "阿根廷比索"},
        {"AUD", "澳大利亚元"},
        {"BGN", "保加利亚列弗"},
        {"BHD", "巴林第纳尔"},
        {"BND", "文莱元"},
        {"BRL", "巴西雷亚尔"},
        {"BSD", "巴哈马元"},
        {"BWP", "博茨瓦纳普拉"},
        {"CAD", "加拿大元"},
        {"CFA", "中非法郎"},
        {"CHF", "瑞士法郎"},
        {"CLP", "智利比索"},
        {"CNY", "人民币"},
        {"COP", "哥伦比亚比索"},
        {"CZK", "捷克克朗"},
        {"DKK", "丹麦克朗"},
        {"DOP", "多米尼加比索"},
        {"DZD", "阿尔及利亚第纳尔"},
        {"EEK", "爱沙尼亚克朗"},
        {"EGP", "埃及镑"},
        {"EUR", "欧元"},
        {"FJD", "斐济元"},
        {"GBP", "英镑"},
        {"GTQ", "危地马拉格查尔"},
        {"HKD", "港币"},
        {"HRK", "克罗地亚库纳"},
        {"HUF", "匈牙利福林"},
        {"IDR", "印度尼西亚卢比"},
        {"ILS", "以色列新谢克尔"},
        {"INR", "印度卢比"},
        {"IRR", "伊朗里亚尔"},
        {"ISK", "冰岛克朗"},
        {"JPY", "日元"},
        {"KRW", "韩元"},
        {"KWD", "科威特第纳尔"},
        {"KZT", "哈萨克斯坦腾格"},
        {"LKR", "斯里兰卡卢比"},
        {"LTL", "立陶宛立特"},
        {"LVL", "拉脱维亚拉特"},
        {"LYD", "利比亚第纳尔"},
        {"MUR", "毛里求斯卢比"},
        {"MVR", "马尔代夫卢比"},
        {"MXN", "墨西哥比索"},
        {"MYR", "马来西亚林吉特"},
        {"NOK", "挪威克朗"},
        {"NPR", "尼泊尔卢比"},
        {"NZD", "新西兰元"},
        {"OMR", "阿曼里亚尔"},
        {"PAB", "巴拿马巴波亚"},
        {"PEN", "秘鲁新索尔"},
        {"PHP", "菲律宾比索"},
        {"PKR", "巴基斯坦卢比"},
        {"PLN", "波兰兹罗提"},
        {"PYG", "巴拉圭瓜拉尼"},
        {"QAR", "卡塔尔里亚尔"},
        {"RON", "新罗马尼亚列伊"},
        {"RUB", "俄罗斯卢布"},
        {"SAR", "沙特里亚尔"},
        {"SEK", "瑞典克朗"},
        {"SGD", "新加坡元"},
        {"THB", "泰铢"},
        {"TND", "突尼斯第纳尔"},
        {"TRY", "新土尔其里拉"},
        {"TTD", "特立尼达和多巴哥元"},
        {"TWD", "台币"},
        {"UAH", "乌克兰格里夫纳"},
        {"USD", "美元"},
        {"UYU", "乌拉圭比索"},
        {"VEF", "委内瑞拉玻利瓦尔"},
        {"ZAR", "南非兰特"},
        {NULL, NULL}
    };
    // 调试汇率更新函数
    timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, &ToolModelOutput::updateRate);

    timer->start(10);
    firstLoad = true;

    // updateRate();

    this->setAutoFillBackground(true);
    this->setBackgroundRole(QPalette::Base);    

    toolUnitBefWid->setProperty("isWindowButton", 0x1);
    toolUnitBefWid->setProperty("useIconHighlightEffect", 0x2);

    toolUnitAftWid->setProperty("isWindowButton", 0x1);
    toolUnitAftWid->setProperty("useIconHighlightEffect", 0x2);
}

// 设置组件样式
void ToolModelOutput::setWidgetStyle(bool resetFontSize)
{
    if (WidgetStyle::themeColor == 0) {
        toolLabUpdate->setStyleSheet("font-size:16px;color:#272A2D;");

        toolLabTime->setStyleSheet("font-size:10px;color:#272A2D;");
        toolLabRate->setStyleSheet("font-size:10px;color:#272A2D;");
        toolUpdateWid->setStyleSheet("background:#F3F3F3;opacity:1;");

        QString unitLabStyle  = "font-family:SourceHanSansCN-ExtraLight;font-size:18px;color:#272A2D;line-height:22px;";
        toolLabUnitBef->setStyleSheet(unitLabStyle);
        toolLabIconBef->setStyleSheet("border-image:url(:/image/downward.png);");
        toolUnitBefWid->setStyleSheet("QPushButton{background:#F3F3F3;color:#272A2D;opacity:1;}"
                                      "QPushButton:hover{background-color:#F3F3F3;}");
        toolLabUnitAft->setStyleSheet(unitLabStyle);
        toolLabIconAft->setStyleSheet("border-image:url(:/image/downward.png);");
        toolUnitAftWid->setStyleSheet("QPushButton{background:#F3F3F3;color:#272A2D;opacity:1;}"
                                      "QPushButton:hover{background-color:#F3F3F3;}");

        // 数据输出界面
        this->toolLabHis->setStyleSheet("color:#8C8C8C;font-size:20px;font-weight:15px;line-height:50px;");
        this->toolLabAft->setStyleSheet("color:#272A2D;font-size:48px;font-weight:15px;line-height:50px;");

        if (resetFontSize) {
            this->toolLabBef->setStyleSheet("color:#272A2D;font-size:48px;font-weight:15px;");
        }
        else {
            QString fontSizeStr = QString::number(toolLabBef->font().pixelSize());
            this->toolLabBef->setStyleSheet("color:#272A2D;font-size:"+ fontSizeStr +"px;font-weight:15px;");
        }

        // this->setStyleSheet("background-color:#8C8C8C;border-radius:4px;");

    }
    else if (WidgetStyle::themeColor == 1) {
        toolLabUpdate->setStyleSheet("font-family:SourceHanSansCN-ExtraLight;font-size:16px;color:#FFFFFF;");

        toolLabTime->setStyleSheet("font-family:NotoSansHans-Light;font-size:10px;color:#A6A6A6;line-height:17px;");
        toolLabRate->setStyleSheet("font-family:NotoSansHans-Light;font-size:10px;color:#A6A6A6;line-height:17px;");
        toolUpdateWid->setStyleSheet("background:#18181A;opacity:0.75;");

        QString unitLabStyle  = "font-family:SourceHanSansCN-ExtraLight;font-size:18px;color:#FFFFFF;line-height:22px;";
        toolLabUnitBef->setStyleSheet(unitLabStyle);
        toolLabIconBef->setStyleSheet("border-image:url(:/image/downward.png);");
        toolUnitBefWid->setStyleSheet("QPushButton{background:#18181A;color:#FFFFFF;opacity:0.75;}"
                                      "QPushButton:hover{background-color:#18181A;}");
        toolLabUnitAft->setStyleSheet(unitLabStyle);
        toolLabIconAft->setStyleSheet("border-image:url(:/image/downward.png);");
        toolUnitAftWid->setStyleSheet("QPushButton{background:#18181A;color:#FFFFFF;opacity:0.75;}"
                                      "QPushButton:hover{background-color:#18181A;}");

        // 数据输出界面
        this->toolLabHis->setStyleSheet("color:#8C8C8C;font-size:20px;font-weight:15px;line-height:50px;");
        this->toolLabAft->setStyleSheet("color:#FFFFFF;font-size:48px;font-weight:15px;line-height:50px;");

        if (resetFontSize) {
            this->toolLabBef->setStyleSheet("color:#FFFFFF;font-size:48px;font-weight:15px;");
        }
        else {
            QString fontSizeStr = QString::number(toolLabBef->font().pixelSize());
            this->toolLabBef->setStyleSheet("color:#FFFFFF;font-size:"+ fontSizeStr +"px;font-weight:15px;");
        }

        // this->setStyleSheet("background-color:#8C8C8C;border-radius:4px;");

    }
}

// 初始化单位列表
void ToolModelOutput::initUnitList(QString listStr)
{
    QStringList unitStrList = listStr.split(",");

    QListWidgetItem *unitBeforeItem[unitStrList.size()];
    QListWidgetItem *unitAfterItem[unitStrList.size()];

//    unitListBef->clear();
//    unitListAft->clear();

    // 单位列表初始化
//    unitListBef->unitTitle->setText(funName);
//    unitListAft->unitTitle->setText(funName);

    for (int i = 0; i < unitStrList.size(); i++) {

        // 获取汇率名称
        QMap<QString, QString>::iterator it;
        QString itemName;

        // 筛选需要显示的货币
        QString locale = QLocale::system().name();
        if (locale == "zh_CN") {
            if (currencyInfoCN.contains(unitStrList[i])) {

                it = currencyInfoCN.find(unitStrList[i]);
                if (it != currencyInfoCN.end()) {
                    itemName = it.value();
                }
                else {
                    continue ;
                }
            } else {
                continue;
            }
        }
        else if (locale == "en_US") {
            if (currencyInfoUS.contains(unitStrList[i])) {

                it = currencyInfoUS.find(unitStrList[i]);
                if (it != currencyInfoUS.end()) {
                    itemName = it.value();
                }
                else {
                    continue ;
                }
            } else {
                continue;
            }
        }

        UnitListItem *listItemBef = new UnitListItem(unitListBef->unitList);
        UnitListItem *listItemAft = new UnitListItem(unitListAft->unitList);
        
        // 设置列表项的单位名称和单位符号
        listItemBef->unitItemName->setText(itemName);
        listItemAft->unitItemName->setText(itemName);

        listItemBef->unitItemSymb->setText(unitStrList[i]);
        listItemAft->unitItemSymb->setText(unitStrList[i]);

        unitBeforeItem[i] = new QListWidgetItem(unitListBef->unitList, i);
        unitAfterItem[i]  = new QListWidgetItem(unitListAft->unitList, i);

        unitListBef->unitList->setItemWidget(unitBeforeItem[i], listItemBef);
        unitListAft->unitList->setItemWidget(unitAfterItem[i],  listItemAft);
    }

    unitListBef->unitList->setSpacing(2);
    unitListAft->unitList->setSpacing(2);

    // 默认汇率选择人民币和美元
    unitListBef->unitList->setCurrentRow(0);
    unitListAft->unitList->setCurrentRow(63);

//    QString unitListStyle = "QListWidget::item:selected{background-color:#36363A;}"
//                            "QListWidget::item:hover{background-color:#666666;}";

//    unitListBef->setStyleSheet(unitListStyle);
//    unitListAft->setStyleSheet(unitListStyle);

}

// 单位换算函数
void ToolModelOutput::unitConversion()
{
    QString strBefore = this->toolLabBef->text().remove(QRegExp(","));
    strBefore.replace("×", "*");
    strBefore.replace("÷", "/");
    strBefore.replace(SUB, "-");
//    QString strAfter  = this->toolLabAft->text();
    // qDebug() << QString::number(toolDouRate) + "*" + strBefore;
    double douResult = calculator(calculator (strBefore) + "*" + QString::number(toolDouRate)  ).toDouble();

//    double douResult  = (strBefore.toDouble() * toolDouRate);

    QString strResult = QString::number(douResult);

    this->toolLabAft->setText(strResult);
}

// 单位换算历史记录转换
QString ToolModelOutput::unitConvHistory(QString hisText)
{
    QString resHisText;

    hisText.replace("×", "*");
    hisText.replace("÷", "/");
    hisText.replace(SUB, "-");
    // qDebug() << hisText;

    // 默认使用人民币/美元汇率
    if (toolDouRate == 0) {
        toolDouRate = 0.15;
    }

    // int i;
    // i =  hisTextList.size() > 4 ?  hisTextList.size() - 4 : 0;

    // for (i; i < hisTextList.size(); i++) {
    //     QStringList singerHisList = (hisTextList[i]).split("=");
    //     QString dataBef = singerHisList[singerHisList.size()-1].remove(QRegExp(","));
    //     double douResult = calculator( calculator (dataBef) + "*" + QString::number(toolDouRate)   ).toDouble();
    //     resHisText += dataBef + " " + toolRateSymbBef + " = " + QString::number(douResult) + " " + toolRateSymbAft + "\n";
    // }

    // 去掉最后的\n
    // resHisText.chop(1);

    QStringList singerHisList = (hisText).split("=");
    QString dataBef = singerHisList[singerHisList.size()-1].remove(QRegExp(",")).remove("\n");
    double douResult = calculator( calculator (dataBef) + "*" + QString::number(toolDouRate)   ).toDouble();
    QString newHisText = dataBef + " " + toolRateSymbBef + " = " + QString::number(douResult) + " " + toolRateSymbAft + "\n";

    toolDisHistory.append(newHisText);

    // 获取历史记录
    int size = toolDisHistory.size();
    int hisIndex = (size - 4 >= 0) ? (size - 4) : 0;
    for (int i = hisIndex; i < size; i++) {
        resHisText = resHisText + toolDisHistory.at(i);
    }

    // 去除末尾换行符
    resHisText.chop(1);

    return resHisText;
}

// 汇率更新函数
void ToolModelOutput::updateRate()
{
    if (firstLoad) {
        timer->stop();
        firstLoad = false;
    
        // 访问汇算换算api
        // QString strUrl = "https://api.exchangerate-api.com/v4/latest/CNY";
        // QNetworkAccessManager manager;
        // QNetworkRequest netRequest;
        // QNetworkReply *netReply;
        // QEventLoop loop;

        // netRequest.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
        // netRequest.setUrl(QUrl(strUrl));
        // netReply = manager.get(netRequest);

        // connect(netReply, SIGNAL(finished()), &loop, SLOT(quit()));
        // loop.exec();

        // if (netReply->error() != QNetworkReply::NoError) {
        //     return ;
        // }

        // QString strRateAll = netReply->readAll();

        // if (strRateAll == "") {
        //     return ;
        // }

        // // 去掉两端的空格
        // strRateAll = strRateAll.simplified();
        // qDebug() << strRateAll;

        QString strRateAll = "{\"base\":\"CNY\",\"date\":\"2021-06-11\",\"time_last_updated\":1623369601,\"rates\":{\"CNY\":1,\"AED\":0.575,\"AFN\":12.34,\"ALL\":15.77,\"AMD\":81.17,\"ANG\":0.28,\"AOA\":101.21,\"ARS\":14.86,\"AUD\":0.202,\"AWG\":0.28,\"AZN\":0.266,\"BAM\":0.251,\"BBD\":0.313,\"BDT\":13.25,\"BGN\":0.251,\"BHD\":0.0588,\"BIF\":308.3,\"BMD\":0.156,\"BND\":0.207,\"BOB\":1.08,\"BRL\":0.791,\"BSD\":0.156,\"BTN\":11.42,\"BWP\":1.66,\"BYN\":0.39,\"BZD\":0.313,\"CAD\":0.189,\"CDF\":312.11,\"CHF\":0.14,\"CLP\":112.58,\"COP\":561.66,\"CRC\":96.53,\"CUC\":0.156,\"CUP\":4.03,\"CVE\":14.17,\"CZK\":3.27,\"DJF\":27.81,\"DKK\":0.959,\"DOP\":8.91,\"DZD\":20.95,\"EGP\":2.45,\"ERN\":2.35,\"ETB\":6.78,\"EUR\":0.129,\"FJD\":0.319,\"FKP\":0.111,\"FOK\":0.959,\"GBP\":0.111,\"GEL\":0.493,\"GGP\":0.111,\"GHS\":0.91,\"GIP\":0.111,\"GMD\":8.11,\"GNF\":1537.96,\"GTQ\":1.21,\"GYD\":32.8,\"HKD\":1.21,\"HNL\":3.76,\"HRK\":0.968,\"HTG\":14.3,\"HUF\":44.62,\"IDR\":2233.07,\"ILS\":0.51,\"IMP\":0.111,\"INR\":11.42,\"IQD\":228.91,\"IRR\":6534.46,\"ISK\":18.91,\"JMD\":23.21,\"JOD\":0.111,\"JPY\":17.14,\"KES\":16.89,\"KGS\":13.2,\"KHR\":640.25,\"KID\":0.202,\"KMF\":63.23,\"KRW\":174.61,\"KWD\":0.0469,\"KYD\":0.13,\"KZT\":66.88,\"LAK\":1474.08,\"LBP\":235.9,\"LKR\":31,\"LRD\":26.8,\"LSL\":2.13,\"LYD\":0.699,\"MAD\":1.38,\"MDL\":2.76,\"MGA\":593,\"MKD\":7.92,\"MMK\":257.31,\"MNT\":448.17,\"MOP\":1.25,\"MRU\":5.67,\"MUR\":6.36,\"MVR\":2.41,\"MWK\":125.78,\"MXN\":3.08,\"MYR\":0.644,\"MZN\":9.9,\"NAD\":2.13,\"NGN\":66.76,\"NIO\":5.46,\"NOK\":1.3,\"NPR\":18.28,\"NZD\":0.218,\"OMR\":0.0602,\"PAB\":0.156,\"PEN\":0.603,\"PGK\":0.549,\"PHP\":7.47,\"PKR\":24.34,\"PLN\":0.576,\"PYG\":1041.92,\"QAR\":0.57,\"RON\":0.633,\"RSD\":15.11,\"RUB\":11.28,\"RWF\":156.52,\"SAR\":0.587,\"SBD\":1.24,\"SCR\":2.57,\"SDG\":67.49,\"SEK\":1.29,\"SGD\":0.207,\"SHP\":0.111,\"SLL\":1606.89,\"SOS\":90.77,\"SRD\":2.21,\"SSP\":27.82,\"STN\":3.15,\"SYP\":197.22,\"SZL\":2.13,\"THB\":4.88,\"TJS\":1.77,\"TMT\":0.547,\"TND\":0.427,\"TOP\":0.346,\"TRY\":1.33,\"TTD\":1.06,\"TVD\":0.202,\"TWD\":4.33,\"TZS\":363.16,\"UAH\":4.23,\"UGX\":550.96,\"USD\":0.156,\"UYU\":6.81,\"UZS\":1656.53,\"VES\":490206.01,\"VND\":3583.66,\"VUV\":16.88,\"WST\":0.393,\"XAF\":84.3,\"XCD\":0.422,\"XDR\":0.108,\"XOF\":84.3,\"XPF\":15.34,\"YER\":39.08,\"ZAR\":2.13,\"ZMW\":3.53}}";
        // QString strRateAll = "{\"base\":\"CNY\",\"date\":\"2021-03-11\",\"time_last_updated\":1615420801,\"rates\":{\"CNY\":1,\"AED\":0.564287,\"AFN\":11.925466,\"ALL\":15.941879,\"AMD\":80.78,\"ANG\":0.275037,\"AOA\":94.433,\"ARS\":13.919785,\"AUD\":0.199032,\"AWG\":0.275037,\"AZN\":0.261136,\"BAM\":0.252484,\"BBD\":0.307304,\"BDT\":13.035473,\"BGN\":0.252519,\"BHD\":0.057773,\"BIF\":298.750223,\"BMD\":0.153652,\"BND\":0.206603,\"BOB\":1.057767,\"BRL\":0.887713,\"BSD\":0.153652,\"BTN\":11.19463,\"BWP\":1.704798,\"BYN\":0.399818,\"BZD\":0.307304,\"CAD\":0.194177,\"CDF\":304.982306,\"CHF\":0.142806,\"CLP\":112.885499,\"COP\":555.469934,\"CRC\":94.017401,\"CUC\":0.153652,\"CUP\":3.841299,\"CVE\":14.234432,\"CZK\":3.393246,\"DJF\":27.307187,\"DKK\":0.963082,\"DOP\":8.861046,\"DZD\":20.526527,\"EGP\":2.416873,\"ERN\":2.30478,\"ETB\":6.1776,\"EUR\":0.129093,\"FJD\":0.313327,\"FKP\":0.110577,\"FOK\":0.963082,\"GBP\":0.110578,\"GEL\":0.509782,\"GGP\":0.110577,\"GHS\":0.882019,\"GIP\":0.110577,\"GMD\":7.995482,\"GNF\":1561.123152,\"GTQ\":1.18371,\"GYD\":32.529019,\"HKD\":1.1922,\"HNL\":3.702097,\"HRK\":0.972651,\"HTG\":11.682777,\"HUF\":47.54087,\"IDR\":2215.406996,\"ILS\":0.51302,\"IMP\":0.110577,\"INR\":11.194706,\"IQD\":224.6263,\"IRR\":6439.93241,\"ISK\":19.628822,\"JMD\":23.223465,\"JOD\":0.108939,\"JPY\":16.685028,\"KES\":16.846384,\"KGS\":13.029032,\"KHR\":624.11991,\"KID\":0.199031,\"KMF\":63.50956,\"KRW\":175.208429,\"KWD\":0.046039,\"KYD\":0.128043,\"KZT\":64.477847,\"LAK\":1439.550141,\"LBP\":231.630393,\"LKR\":30.131831,\"LRD\":26.726988,\"LSL\":2.338488,\"LYD\":0.694688,\"MAD\":1.386167,\"MDL\":2.706152,\"MGA\":579.07157,\"MKD\":7.980492,\"MMK\":216.743685,\"MNT\":439.246974,\"MOP\":1.227965,\"MRU\":5.534758,\"MUR\":6.125689,\"MVR\":2.365572,\"MWK\":120.496095,\"MXN\":3.240556,\"MYR\":0.633023,\"MZN\":11.359949,\"NAD\":2.338488,\"NGN\":60.844418,\"NIO\":5.365002,\"NOK\":1.300663,\"NPR\":17.911408,\"NZD\":0.214198,\"OMR\":0.059079,\"PAB\":0.153652,\"PEN\":0.567949,\"PGK\":0.539275,\"PHP\":7.455241,\"PKR\":24.104537,\"PLN\":0.591266,\"PYG\":1022.940324,\"QAR\":0.559293,\"RON\":0.630959,\"RSD\":15.192878,\"RUB\":11.351487,\"RWF\":152.594981,\"SAR\":0.576195,\"SBD\":1.208201,\"SCR\":3.255675,\"SDG\":58.58076,\"SEK\":1.307156,\"SGD\":0.206605,\"SHP\":0.110577,\"SLL\":1569.404972,\"SOS\":89.066036,\"SRD\":2.179247,\"SSP\":27.33617,\"STN\":3.162777,\"SYP\":78.666827,\"SZL\":2.338488,\"THB\":4.726832,\"TJS\":1.734593,\"TMT\":0.537566,\"TND\":0.4221,\"TOP\":0.348113,\"TRY\":1.16272,\"TTD\":1.043478,\"TVD\":0.199031,\"TWD\":4.350241,\"TZS\":356.183752,\"UAH\":4.25506,\"UGX\":562.660721,\"USD\":0.153652,\"UYU\":6.826117,\"UZS\":1615.6,\"VES\":288158.05,\"VND\":3557.170823,\"VUV\":16.617988,\"WST\":0.387134,\"XAF\":84.679413,\"XCD\":0.41486,\"XDR\":0.107598,\"XOF\":84.679413,\"XPF\":15.404918,\"YER\":38.486595,\"ZAR\":2.338623,\"ZMW\":3.372328}}";
        // QString strRateAll = "{\"base\":\"CNY\",\"date\":\"2021-05-26\",\"time_last_updated\":1621987201,\"rates\":{\"CNY\":1,\"AED\":0.573,\"AFN\":12.11,\"ALL\":15.7,\"AMD\":80.98,\"ANG\":0.279,\"AOA\":101.13,\"ARS\":14.69,\"AUD\":0.201,\"AWG\":0.279,\"AZN\":0.265,\"BAM\":0.249,\"BBD\":0.312,\"BDT\":13.23,\"BGN\":0.249,\"BHD\":0.0587,\"BIF\":307.49,\"BMD\":0.156,\"BND\":0.207,\"BOB\":1.07,\"BRL\":0.829,\"BSD\":0.156,\"BTN\":11.35,\"BWP\":1.67,\"BYN\":0.39,\"BZD\":0.312,\"CAD\":0.188,\"CDF\":309.94,\"CHF\":0.14,\"CLP\":113.77,\"COP\":588.17,\"CRC\":96.15,\"CUC\":0.156,\"CUP\":4.02,\"CVE\":14.05,\"CZK\":3.25,\"DJF\":27.73,\"DKK\":0.95,\"DOP\":8.86,\"DZD\":20.81,\"EGP\":2.44,\"ERN\":2.34,\"ETB\":6.67,\"EUR\":0.127,\"FJD\":0.317,\"FKP\":0.11,\"FOK\":0.95,\"GBP\":0.11,\"GEL\":0.512,\"GGP\":0.11,\"GHS\":0.903,\"GIP\":0.11,\"GMD\":8.04,\"GNF\":1536.52,\"GTQ\":1.2,\"GYD\":33.32,\"HKD\":1.21,\"HNL\":3.74,\"HRK\":0.96,\"HTG\":14.03,\"HUF\":44.54,\"IDR\":2241.36,\"ILS\":0.508,\"IMP\":0.11,\"INR\":11.35,\"IQD\":227.36,\"IRR\":6517.53,\"ISK\":18.95,\"JMD\":23.39,\"JOD\":0.111,\"JPY\":16.98,\"KES\":16.82,\"KGS\":13,\"KHR\":634.87,\"KID\":0.201,\"KMF\":62.67,\"KRW\":175.09,\"KWD\":0.0467,\"KYD\":0.13,\"KZT\":66.6,\"LAK\":1468.49,\"LBP\":235.18,\"LKR\":30.92,\"LRD\":26.77,\"LSL\":2.16,\"LYD\":0.695,\"MAD\":1.37,\"MDL\":2.76,\"MGA\":587.26,\"MKD\":7.87,\"MMK\":246.62,\"MNT\":445.44,\"MOP\":1.25,\"MRU\":5.61,\"MUR\":6.3,\"MVR\":2.4,\"MWK\":124.7,\"MXN\":3.1,\"MYR\":0.646,\"MZN\":9.36,\"NAD\":2.16,\"NGN\":66.65,\"NIO\":5.51,\"NOK\":1.3,\"NPR\":18.16,\"NZD\":0.216,\"OMR\":0.06,\"PAB\":0.156,\"PEN\":0.595,\"PGK\":0.548,\"PHP\":7.51,\"PKR\":24.05,\"PLN\":0.572,\"PYG\":1038.95,\"QAR\":0.568,\"RON\":0.627,\"RSD\":14.97,\"RUB\":11.46,\"RWF\":156.28,\"SAR\":0.585,\"SBD\":1.22,\"SCR\":2.57,\"SDG\":62.12,\"SEK\":1.29,\"SGD\":0.207,\"SHP\":0.11,\"SLL\":1595.94,\"SOS\":90.16,\"SRD\":2.21,\"SSP\":27.8,\"STN\":3.12,\"SYP\":196.77,\"SZL\":2.16,\"THB\":4.9,\"TJS\":1.76,\"TMT\":0.544,\"TND\":0.423,\"TOP\":0.347,\"TRY\":1.31,\"TTD\":1.06,\"TVD\":0.201,\"TWD\":4.35,\"TZS\":361.85,\"UAH\":4.28,\"UGX\":554.8,\"USD\":0.156,\"UYU\":6.86,\"UZS\":1652.65,\"VES\":476692.3,\"VND\":3593.66,\"VUV\":16.82,\"WST\":0.393,\"XAF\":83.56,\"XCD\":0.421,\"XDR\":0.108,\"XOF\":83.56,\"XPF\":15.2,\"YER\":39,\"ZAR\":2.16,\"ZMW\":3.51}}";

        // 格式化处理汇率信息字符串键值对
        strRateList = strRateAll.split(QRegExp("[{} :,\"\n]"));
        strRateList.removeAll("");

        // 获取汇率时间
        QString strData = strRateList.at(3);

        for (int i = 0; i < 7; i++) {
            strRateList.removeAt(0);
        }

        // strRateList = ("CNY", "1", "AED", "0.544676", "ARS", "11.476237", "AUD", "0.207097", "BGN", "0.247315", "BRL", "0.827556",
        //                 "BSD", "0.148334", "CAD", "0.195039", "CHF", "0.135726", "CLP", "118.484436", "COP", "563.428571",
        //                 "CZK", "3.456454", "DKK", "0.940724", "DOP", "8.630197", "EGP", "2.321366", "EUR", "0.126422",
        //                 "FJD", "0.315268", "GBP", "0.114427", "GTQ", "1.152767", "HKD", "1.150917", "HRK", "0.958357",
        //                 "HUF", "45.826534", "IDR", "2221.384053", "ILS", "0.502548", "INR", "10.885823", "ISK", "20.616798",
        //                 "JPY", "15.644062", "KRW", "170.131068", "KZT", "63.612903", "MVR", "2.287933", "MXN", "3.170424",
        //                 "MYR", "0.615439", "NOK", "1.369261", "NZD", "0.22308", "PAB", "0.148334", "PEN", "0.533837",
        //                 "PHP", "7.225576", "PKR", "24.09776", "PLN", "0.568725", "PYG", "1075.636364", "RON", "0.616233",
        //                 "RUB", "11.478878", "SAR", "0.556857", "SEK", "1.309479", "SGD", "0.201673", "THB", "4.632377",
        //                 "TRY", "1.177668", "TWD", "4.264893", "UAH", "4.205166", "USD", "0.148567", "UYU", "6.303676",
        //                 "ZAR", "2.450397");

        // 获取汇率单位标识
        QString strRateKey = strRateList.at(0);
        for (int i = 2; i < strRateList.size(); i++) {
            if (i % 2 == 0) {
                strRateKey.append(",");
                strRateKey.append(strRateList.at(i));
            }
        }

        // 初始化选择列表的汇率选项
        initUnitList(strRateKey);

    }

//    qDebug() << strRateList;
//    qDebug() << strRateKey;
//    manager.deleteLater();
//    netReply->deleteLater();
//    loop.deleteLater();

    // 更新界面的数据 时间 汇率
    QDateTime date = QDateTime::currentDateTime();
    QString strTime = date.toString("yyyy.MM.dd hh:mm");

//    int idxName = strRateList.indexOf(rateNameAft);

//    unitListBef->unitList->item(0)->setSelected(true);
//    unitListAft->unitList->item(idxName)->setSelected(true);

//    QString rateNameBef = unitListBef->unitList->currentItem()->text();
//    QString rateNameAft = unitListAft->unitList->currentItem()->text();
    // QString rateNameBef = "CNY";
    // QString rateNameAft = "USD";

    QString rateNameBef = toolRateSymbBef;
    QString rateNameAft = toolRateSymbAft;

    int idxName = strRateList.indexOf(rateNameAft);

    // toolDouRate = (strRateList[idxName + 1]).toDouble();
//    toolDouRate =  QString::number(toolDouRate,'f',2).toDouble();

    QString labelRate = "1 "+ rateNameBef + " = " +
                        QString::number(toolDouRate,'f',2) + " " + rateNameAft;
    toolLabTime->setText(strTime);
    toolLabRate->setText(labelRate);

    updateRateName();
}

// 控制换算前的单位列表
void ToolModelOutput::unitListBefShow()
{
    if (unitListBef->isHidden()) {
        // unitListAft->hide();
        unitListBef->show();
        unitListBef->raise();
        unitListBef->setFocus();

        toolUnitBefWid->setBackgroundRole(QPalette::Window);
    }
    else {
        unitListBef->hide();
        toolUnitBefWid->setBackgroundRole(QPalette::Base);
    }
}

// 控制换算后的单位列表
void ToolModelOutput::unitListAftShow()
{
    if (unitListAft->isHidden()) {
        // unitListBef->hide();
        unitListAft->show();
        unitListAft->raise();
        unitListAft->setFocus();
    }
    else {
        unitListAft->hide();
    }
}

// 选择换算前的单位列表
void ToolModelOutput::unitListBefSelect(QListWidgetItem *item)
{

    unitListBef->hide();
}

// 选择换算后的单位列表
void ToolModelOutput::unitListAftSelect(QListWidgetItem *item)
{
    // qDebug() << item->text();
    QString rateSymbol = item->text();
    QString rateName   = rateSymbol;

    // 更新汇率比率显示
    QString labelRate = toolLabRate->text();
    labelRate = labelRate.section("=", 0, 0) + "= " + QString::number(toolDouRate) + " " + rateName;
    toolLabRate->setText(labelRate);

    toolLabUnitAft->setText(rateSymbol + "\n" + rateName);

    unitListAft->hide();
}

// 选择货币单位列表
void ToolModelOutput::unitListSelect(QListWidgetItem *item)
{
    if (unitListAft->isHidden()) {
        // 获取QWidget
        QWidget* itemWid = unitListBef->unitList->itemWidget(item);
        // 获取所有的QLabel
        QList<QLabel*> labelList = itemWid->findChildren<QLabel*>();

        toolRateSymbBef = labelList[1]->text();
        updateRateName();
        unitListBef->hide();
    }
    else {
        // 获取QWidget
        QWidget* itemWid = unitListAft->unitList->itemWidget(item);
        // 获取所有的QLabel
        QList<QLabel*> labelList = itemWid->findChildren<QLabel*>();

        toolRateSymbAft = labelList[1]->text();
        updateRateName();
        unitListAft->hide();
    }
}

// 根据符号更新货币名称并显示
void ToolModelOutput::updateRateName()
{
    // 获取汇率索引值
    int idxRateBef = strRateList.indexOf(toolRateSymbBef) + 1;
    int idxRateAft = strRateList.indexOf(toolRateSymbAft) + 1;

    // 获取汇率比率
    toolDouRate = (strRateList[idxRateAft]).toDouble() / (strRateList[idxRateBef]).toDouble();
//    toolDouRate =  QString::number(toolDouRate).toDouble();
    qDebug() << "select rate " << toolDouRate;

    // 获取汇率名称
    QMap<QString, QString>::iterator it;

    QString locale = QLocale::system().name();
    if (locale == "zh_CN") {
        it = currencyInfoCN.find(toolRateSymbBef);
        if (it != currencyInfoCN.end()) {
            toolRateNameBef = it.value();
        }

        it = currencyInfoCN.find(toolRateSymbAft);
        if (it != currencyInfoCN.end()) {
            toolRateNameAft = it.value();
        }
    }
    else if (locale == "en_US") {
        it = currencyInfoUS.find(toolRateSymbBef);
        if (it != currencyInfoUS.end()) {
            toolRateNameBef = it.value();
        }

        it = currencyInfoUS.find(toolRateSymbAft);
        if (it != currencyInfoUS.end()) {
            toolRateNameAft = it.value();
        }
    }

    // 更新汇率比率显示
    QString labelRate = toolLabRate->text();
    labelRate = "1 " + toolRateSymbBef + " = " + QString::number(toolDouRate, 'f', 2) + " " + toolRateSymbAft;
    toolLabRate->setText(labelRate);

    // 更新汇率名称和符号显示
    toolLabUnitBef->setText(toolRateNameBef + "\n" + toolRateSymbBef);
    toolLabUnitAft->setText(toolRateNameAft + "\n" + toolRateSymbAft);

    QFontMetrics fontmts = toolLabUnitBef->fontMetrics();
    int dif = fontmts.width(toolRateNameBef) - toolLabUnitBef->width();
    if (dif > 0) {
        QString str = fontmts.elidedText(toolRateNameBef,Qt::ElideRight,toolLabUnitBef->width());
        toolLabUnitBef->setText(str + "\n" + toolRateSymbBef);
        toolLabUnitBef->setToolTip(toolRateNameBef);
    }

    dif = fontmts.width(toolRateNameAft) - toolLabUnitAft->width();
    if (dif > 0) {
        QString str = fontmts.elidedText(toolRateNameAft,Qt::ElideRight,toolLabUnitAft->width());
        toolLabUnitAft->setText(str + "\n" + toolRateSymbAft);
        toolLabUnitAft->setToolTip(toolRateNameAft);
    }

    // 更新汇率换算结果
    unitConversion();
}

// 换算器按钮界面
ToolModelButton::ToolModelButton(QWidget *parent)
    : QWidget(parent)
{
    // 初始化组件
    this->setWidgetUi();

    // 设置组件样式
    this->setWidgetStyle();
}

// 初始化组件
void ToolModelButton::setWidgetUi()
{
    for (int i = 0; i < 10; i++) {
        btnNum[i] = new BasicButton(this);
        btnNum[i]->setText(QString::number(i));
        btnNum[i]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        btnNum[i]->setIconSize(QSize(106, 62));
    }

    // btnDZero = new BasicButton(this);
    // btnDZero->setText("00");
    // btnDZero->setIconSize(QSize(106, 62));

    btnClear = new BasicButton(this);
    btnPer = new BasicButton(this);
    btnDelete = new BasicButton(this);

    btnDiv = new BasicButton(this);
    btnMulti = new BasicButton(this);
    btnSub = new BasicButton(this);
    btnAdd = new BasicButton(this);
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

    btnClear->setIconSize(QSize(106, 62));
    btnDiv->setIconSize(QSize(106, 62));
    btnMulti->setIconSize(QSize(106, 62));
    btnDelete->setIconSize(QSize(85,  50));
    btnSub->setIconSize(QSize(106, 62));
    btnAdd->setIconSize(QSize(106, 62));
    btnEqual->setIconSize(QSize(106, 62));
    btnPer->setIconSize(QSize(106, 62));
    btnPoint->setIconSize(QSize(106, 62));

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
    // btnLayout->addWidget(btnDZero, 4, 0, 1, 1);
    btnLayout->addWidget(btnNum[0], 4, 0, 1, 2);
    for (int i = 1; i < 10; i++) {
        btnLayout->addWidget(btnNum[i], 3 - (i - 1)/3, (i - 1) % 3, 1, 1);
    }

    // 设置间距和背景样式
    btnLayout->setSpacing(2);
    btnLayout->setMargin(1);

    this->setFixedHeight(320);
    this->setLayout(btnLayout);

}

// 设置组件样式
void ToolModelButton::setWidgetStyle()
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


        btnStyle = "QPushButton{"
                   "width:106px;height:62px;opacity:1;"
                   "background-color:#F3F3F3;border-radius:4px;"
                   "font-size:42px;font-family:HelveticaNeueLTPro-UltLt;color:#FFFFFF;"
                   "}"
                   "QPushButton:hover{background-color:#E8E8E8;}";

        btnOpStyle = "QPushButton{"
                     "width:106px;height:62px;opacity:1;"
                     "background-color:#F5F5F8;border-radius:4px;"
                     "font-size:35px;font-family:HelveticaNeueLTPro-UltLt;color:#FFFFFF;"
                     "}"
                     "QPushButton:hover{background-color:#E8E8E8;}";

        btnEqualStyle = "QPushButton{"
                        "width:106px;height:126px;opacity:1;"
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
                   "width:106px;height:62px;opacity:0.95;"
                   "background-color:#27292C;border-radius:4px;"
                   "font-size:42px;font-family:HelveticaNeueLTPro-UltLt;color:#FFFFFF;"
                   "}"
                   "QPushButton:hover{background-color:#474747;}";

        btnOpStyle = "QPushButton{"
                     "width:106px;height:62px;opacity:1;"
                     "background-color:#222E36;border-radius:4px;"
                     "font-size:35px;font-family:HelveticaNeueLTPro-UltLt;color:#FFFFFF;}"
                     "QPushButton:hover{background-color:#474747;}";

        btnEqualStyle = "QPushButton{"
                        "width:106px;height:126px;opacity:1;"
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

    this->setStyleSheet("border-radius:4px;");
}

// 键盘响应事件
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
    // return QWidget::keyPressEvent(event);
}


// 换算器单位列表界面
UnitListWidget::UnitListWidget(QWidget *parent, QWidget *pWidget)
    : QWidget(parent)
{
    this->pWidget = pWidget;
    // 初始化组件
    this->setWidgetUi();

    // 设置组件样式
    this->setWidgetStyle();
}

// 初始化组件
void UnitListWidget::setWidgetUi()
{
    // 标题和取消
    unitTitle = new QLabel(this);
    btnCancel = new QPushButton(this);

    unitTitle->setText(tr("currency"));
//    unitTitle->setText("货币");
    unitTitle->setAlignment(Qt::AlignCenter);
    unitTitle->setFixedHeight(20);

    btnCancel->setText(tr("cancel"));
//    btnCancel->setText("取消");

    btnCancel->resize(QSize(55, 20));
    btnCancel->move(this->x() + 260 - btnCancel->width(), 15);

    // 搜索框
    searchEdit = new QLineEdit(this);
    searchEdit->setPlaceholderText(tr("search"));
//    searchEdit->setPlaceholderText("搜索");

    // 单位列表
    unitList = new QListWidget(this);
    unitList->setFrameShape(QListWidget::NoFrame);
    unitList->verticalScrollBar()->setProperty("drawScrollBarGroove", false);
    // unitList->setVerticalScrollMode(QListWidget::ScrollPerPixel);

    // 总体布局
    unitListLayout = new QVBoxLayout(this);
    unitListLayout->addWidget(unitTitle, Qt::AlignCenter);
    unitListLayout->addWidget(searchEdit);
    unitListLayout->addWidget(unitList);

    unitWid = new QWidget(this);
    unitWid->setLayout(unitListLayout);
    unitWid->setObjectName("unitWid");

    QVBoxLayout *unitLayout = new QVBoxLayout(this);
    unitLayout->addWidget(unitWid);

    this->setLayout(unitLayout);
    this->setContentsMargins(0, 0, 0, 0);
    this->setFixedHeight(410);
    this->setFixedWidth(280);

    btnCancel->raise();
    searchEdit->hide();

    //绘制阴影
    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect(this);
    static const QColor shadowColor = QColor(70,70,70); // 阴影颜色
    static const int shadowRedius = 10;                 // 阴影模糊度
    effect->setOffset(0, 0);                // (0,0)代表向四周发散
    effect->setColor(shadowColor);          // 设置阴影颜色
    effect->setBlurRadius(shadowRedius);    // 设定阴影的模糊半径，数值越大越模糊
    this->setGraphicsEffect(effect);
}

// 初始化组件样式
void UnitListWidget::setWidgetStyle()
{
    if (WidgetStyle::themeColor == 0) {
        unitTitle->setStyleSheet("width:30px;height:20px;font-size:14px;font-family:Source Han Sans CN;color:#000000;text-align:center;");
        btnCancel->setStyleSheet("width:30px;height:20px;border:0px;font-size:14px;"
                                 "font-family:Source Han Sans CN;color:#3D6BE5;");

        searchEdit->setStyleSheet("width:246px;height:32px;background:rgba(231,231,231,0.5);border-radius:4px;");
        unitList->setStyleSheet("QListWidget{background-color:#F8F8F8;}"
                                "QListWidget::item{border-radius:4px;height:31px;}"
                                "QListWidget::item:selected{background-color:#3D6BE5;color:#FFFFFF;}"
                                "QListWidget::item:hover{background-color:#E9E9E9;}");


        // unitList->verticalScrollBar()->setStyleSheet("width:4px;background:#E9E9E9;border-radius:2px;border:0;");
        unitWid->setStyleSheet("#unitWid{background-color:#F8F8F8;border-radius:4px;}");

    }
    else if (WidgetStyle::themeColor == 1) {
        unitTitle->setStyleSheet("width:30px;height:20px;font-size:14px;font-family:Source Han Sans CN;color:#FFFFFF;text-align:center;");
        btnCancel->setStyleSheet("width:30px;height:20px;border:0px;font-size:14px;"
                                 "font-family:Source Han Sans CN;color:#EE8A18;");

        searchEdit->setStyleSheet("width:246px;height:32px;background:rgba(30,30,32,0.5);border-radius:4px;");
        unitList->setStyleSheet("QListWidget{background-color:#36363A;}"
                                "QListWidget::item{border-radius:4px;height:31px;}"
                                "QListWidget::item:selected{background-color:#FF800F;}"
                                "QListWidget::item:hover{background-color:#666666;}");

        // unitList->verticalScrollBar()->setStyleSheet("width:4px;background:#47474D;border-radius:2px;border:0;");
        unitWid->setStyleSheet("#unitWid{background-color:#36363A;border-radius:4px;}");

    }
}

// 失去焦点窗口隐藏
void UnitListWidget::focusOutEvent(QFocusEvent *e)
{
    if (this->btnCancel->hasFocus() || this->unitList->hasFocus() || this->pWidget->hasFocus()) {
        return ;
    }
    this->hide();
}

// 单位列表列表项
UnitListItem::UnitListItem(QWidget *parent)
    : QWidget(parent)
{
    // 设置列表项背景透明
    this->setAttribute(Qt::WA_TranslucentBackground, true);

    // 初始化列表项组件
    setWidgetUi();

    // 初始化列表项样式
    setWidgetStyle();
}

// 初始化列表项组件
void UnitListItem::setWidgetUi()
{
    // 初始化组件元素
    unitItemName = new QLabel(this);
    unitItemSymb = new QLabel(this);

    unitItemLayout = new QHBoxLayout(this);

    // 文字对齐方式和自适应放缩
    unitItemName->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    unitItemSymb->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

//    unitItemName->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // 将组件加入布局
    unitItemLayout->addWidget(unitItemName);
    unitItemLayout->addWidget(unitItemSymb);

    unitItemLayout->setSpacing(0);
    unitItemLayout->setMargin(0);

    this->setLayout(unitItemLayout);
}

// 初始化列表项样式
void UnitListItem::setWidgetStyle()
{
    // 单位名称组件样式
    QString itemNameStyle  = "font-family:SourceHanSansCN-ExtraLight;font-size:16px;background:transparent;";
    unitItemName->setStyleSheet(itemNameStyle);

    // 单位符号组件样式
    QString itemSymbStyle  = "font-family:SourceHanSansCN-ExtraLight;font-size:16px;width:30px;background:transparent;";
    unitItemSymb->setStyleSheet(itemSymbStyle);

    unitItemSymb->setFixedWidth(50);

    this->setFixedHeight(32);
}
