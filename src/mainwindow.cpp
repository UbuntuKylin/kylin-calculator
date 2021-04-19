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

#include <QKeyEvent>
#include <QDebug>
#include <QList>
#include <QDesktopWidget>
#include <QThread>
#include <KWindowSystem>
#include <iostream>

#include "mainwindow.h"
#include "xatom-helper.h"

MainWindow *MainWindow::getInstance()
{   

    static MainWindow *instance = nullptr;
    if (nullptr == instance) {
        instance = new MainWindow();
    }
    return instance;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
#ifndef __V10__
    // 添加窗管协议
    MotifWmHints hints;
    hints.flags = MWM_HINTS_FUNCTIONS | MWM_HINTS_DECORATIONS;
    hints.functions = MWM_FUNC_ALL;
    hints.decorations = MWM_DECOR_BORDER;
    XAtomHelper::getInstance()->setWindowMotifHint(this->winId(), hints);
#endif

    InputProcess::inputFromButton(STANDARD);

    // 初始化列表项组件
    setWidgetUi();

    // 设置组件样式
    setWidgetStyle();
}

MainWindow::~MainWindow()
{

}

// 初始化列表项组件
void MainWindow::setWidgetUi()
{
    QRect availableGeometry = qApp->primaryScreen()->availableGeometry();
    this->move((availableGeometry.width() - this->width())/2, (availableGeometry.height() - this->height())/2);

    if(QGSettings::isSchemaInstalled(UKUI_THEME_GSETTING_PATH))
    {
        themeData = new QGSettings(UKUI_THEME_GSETTING_PATH);
        if(themeData->get("style-name").toString() == "ukui-dark" || themeData->get("style-name").toString() == "ukui-black"){
            WidgetStyle::themeColor = 1;
        }
        else
        {
            WidgetStyle::themeColor = 0;
            
        }
    }
    setFocus();

    mainWid = new QWidget(this);

    outputWid = new QWidget(this);
    outputWid->setObjectName("outputWid");

    buttonWid = new QWidget(this);
    buttonWid->setObjectName("buttonWid");

    mainOutputLayout = new QVBoxLayout(outputWid);
    mainOutputLayout->setMargin(0);

    mainButtonLayout = new QVBoxLayout(buttonWid);
    mainButtonLayout->setMargin(0);

    // 公有组件，即标题栏和功能列表
    setCommonUi();
    
    // 标准计算界面布局
    setStandardUi();

    mainLayout = new QVBoxLayout(mainWid);
    mainLayout->addWidget(pTitleBar);
    mainLayout->addWidget(outputWid);
    mainLayout->addWidget(buttonWid);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);

    this->mainWid->setLayout(mainLayout);

    if(QGSettings::isSchemaInstalled(UKUI_THEME_GSETTING_PATH))
    {
        themeData = new QGSettings(UKUI_THEME_GSETTING_PATH);
        if(themeData->get("style-name").toString() == "ukui-dark" || themeData->get("style-name").toString() == "ukui-black"){
            WidgetStyle::themeColor = 1;
            // changeDarkTheme();
        }
        else
        {
            WidgetStyle::themeColor = 0;
            // changeLightTheme();
        }

        connect(themeData,&QGSettings::changed,this,[=]()
        {
            qDebug() << "主题颜色" << themeData->get("style-name").toString();
            if(themeData->get("style-name").toString() == "ukui-dark" || themeData->get("style-name").toString() == "ukui-black"){
                WidgetStyle::themeColor = 1;
                changeDarkTheme();
            }
            else
            {
                WidgetStyle::themeColor = 0;
                changeLightTheme();
            }
        });
    }
}

// 设置组件样式
void MainWindow::setWidgetStyle()
{

    this->mainWid->setObjectName("mainWid");

    qDebug() << "WidgetStyle::themeColor " << WidgetStyle::themeColor;

    this->mainWid->setAutoFillBackground(true);
    this->mainWid->setBackgroundRole(QPalette::Base);

    this->pTitleBar->setAutoFillBackground(true);
    this->pTitleBar->setBackgroundRole(QPalette::Base);

    if (WidgetStyle::themeColor == 0) {
        // this->mainWid->setStyleSheet("#mainWid{background-color:#FFFFFF;}");
        // titleBarWid->setStyleSheet("#titleBarWid{background-color:#FFFFFF;}");
        // pTitleBar->setStyleSheet("#titleBarWid{background-color:#FFFFFF;}");
        
        // funcListWid->setStyleSheet("background:#F8F8F8;color:#F8F8F8;font-size:18px;border:none;border-radius:4px;");
        // outputWid->setStyleSheet("#outputWid{background-color:#FFFFFF;border-radius:4px;}");
        // buttonWid->setStyleSheet("#buttonWid{background-color:#FFFFFF;border-radius:4px;}");

    }
    else if (WidgetStyle::themeColor == 1) {
        // this->mainWid->setStyleSheet("#mainWid{background-color:#131314;}");
        // titleBarWid->setStyleSheet("#titleBarWid{background-color:#131314;}");
        // pTitleBar->setStyleSheet("#titleBarWid{background-color:#131314;}");
        // funcListWid->setStyleSheet("background:#36363A;color:#FFFFFF;font-size:18px;border:none;border-radius:4px;");
        // outputWid->setStyleSheet("#outputWid{background-color:#131314;border-radius:4px;}");
        // buttonWid->setStyleSheet("#buttonWid{background-color:#131314;border-radius:4px;}");

    }
    this->setCentralWidget(mainWid);
    qDebug() << "/***********************************************************/";
    // qDebug() << this->styleSheet();
    // this->setStyleSheet("border-radius:6px;");
    // this->show();
}

// 公有组件，即标题栏和功能列表
void MainWindow::setCommonUi()
{
    // 窗口设置
    // 无边框、界面置顶
    //    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
#ifdef __V10__
    this->setWindowFlags(Qt::FramelessWindowHint);
#endif
    // 窗体透明
    // this->setAttribute(Qt::WA_TranslucentBackground, true);

    // 设置图标
    this->setWindowTitle(tr("kylin-calculator"));
    //    this->setWindowTitle("麒麟计算器");
    this->setWindowIcon(QIcon::fromTheme("kylin-calculator"));

    // titleBarWid = new QWidget(this);
    // titleBarWid->setObjectName("titleBarWid");

    // 标题栏
    pTitleBar = new TitleBar(this);
    installEventFilter(pTitleBar);

    // menuBar里面的一些需要被触发的槽
    connect(pTitleBar->menuBar,  SIGNAL(menuModuleClose()),
            pTitleBar->window(), SLOT(close()));
    connect(pTitleBar->menuBar,  SIGNAL(menuModuleChanged(QString)),
            this,                SLOT(changeModel(QString)));

    pTitleBar->setFuncLabel(pTitleBar->STANDARD_LABEL);

    // QVBoxLayout *pLayout = new QVBoxLayout();
    // pLayout->addWidget(pTitleBar);
    // // pLayout->addStretch();
    // pLayout->setSpacing(0);
    // pLayout->setContentsMargins(0,0,0,0);
    // titleBarWid->setLayout(pLayout);
    // titleBarWid->setFixedHeight(TITLEH);

    // 显示和隐藏功能列表
    // connect(pTitleBar->funcListButton,SIGNAL(clicked(bool)),this,SLOT(funcListHandle(bool)));
    connect(pTitleBar->m_pTopButton,SIGNAL(clicked(bool)),this,SLOT(stayTop()));

    // 右键菜单
    labelMenu   = new QMenu(this);
    copyAction  = new QAction(this);
    pasteAction = new QAction(this);

    labelMenu->addAction(copyAction);
    labelMenu->addAction(pasteAction);

    copyAction->setText(tr("Copy"));
    pasteAction->setText(tr("Paste"));

    connect(copyAction,  &QAction::triggered, this, &MainWindow::copyCalResult);
    connect(pasteAction, &QAction::triggered, this, &MainWindow::pasteToLabNow);

    // 模式切换和功能列表
    funcList = new FuncList(this);
    installEventFilter(funcList);

    QVBoxLayout *funcListLayout = new QVBoxLayout();
    funcListLayout->addWidget(funcList);
    funcListLayout->addStretch();
    funcListLayout->setSpacing(0);
    funcListLayout->setMargin(0);

    funcListWid = new QWidget(this);
    funcListWid->setLayout(funcListLayout);
    funcListWid->setContentsMargins(0, 0, 0, 0);
    funcListWid->raise();
    funcListWid->setFixedHeight(170);
    funcListWid->setFixedWidth(170);
    funcListWid->setGeometry(QRect(187, 40, 20, 170));
    funcListWid->hide();

    // funcList->setAttribute(Qt::WA_ShowWithoutActivating, true);

    // 功能列表项响应点击
    connect(funcList->funcModelWid, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(funcListItemClicked(QListWidgetItem*)));
    connect(funcList->funcToolWid,  SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(funcListItemClicked(QListWidgetItem*)));
}

// 计算器输出窗口组件
void MainWindow::setOutputUi()
{
    // 当前表达式
    this->lab_now = new QLabel(this);

    // 历史记录
    this->lab_last = new QLabel(this);

    // 预测输出
    this->lab_prepare = new QLabel(this);

//    lab_now->setWordWrap(true);
//    lab_last->setWordWrap(true);
//    lab_prepare->setWordWrap(true);

    QFont lab_last_font("SourceHanSansCN-Light", 40, 15);
    this->lab_last->setAlignment(Qt::AlignRight | Qt::AlignTop);
    this->lab_last->setFont(lab_last_font);
    this->lab_last->setText("");
    this->lab_last->setStyleSheet("color:#8C8C8C;font-size:20px;margin:0 7px 0 7px;");
    this->lab_last->show();

    QFont lab_prepare_font("SourceHanSansCN-Light", 40, 15);
    this->lab_prepare->setAlignment(Qt::AlignRight | Qt::AlignTop);
    this->lab_prepare->setFont(lab_prepare_font);
    this->lab_prepare->setText("");
    this->lab_prepare->setFixedHeight(35);
    this->lab_prepare->setStyleSheet("color:#FB9119;font-size:20px;margin:0 7px 0 7px;");
    this->lab_prepare->show();

    QFont lab_now_font("SourceHanSansCN-Normal", 48, 15);
    this->lab_now->setAlignment(Qt::AlignRight);
    this->lab_now->setFont(lab_now_font);
    this->lab_now->setText("0");
    this->lab_now->setFixedHeight(65);
    this->lab_now->setStyleSheet("color:#FFFFFF;font-size:48px;font-weight:15px;margin:0 0 5px 7px;");
    this->lab_now->show();

    this->lab_now->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->lab_prepare->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->lab_now->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *outputLayout = new QVBoxLayout();
    outputLayout->addWidget(this->lab_last);
    outputLayout->addWidget(this->lab_prepare);
    outputLayout->addWidget(this->lab_now);
    outputLayout->setStretchFactor(this->lab_last, 14);
    outputLayout->setStretchFactor(this->lab_prepare, 1);
    outputLayout->setStretchFactor(this->lab_now, 1);
    outputLayout->setSpacing(0);
    outputWid->setLayout(outputLayout);
    outputWid->setFixedHeight(270);
    outputWid->setStyleSheet("#outputWid{background-color:#18181A;border-radius:4px;}");

    this->lab_now->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this->lab_now, &MainWindow::customContextMenuRequested, this, &MainWindow::myCustomContextMenuRequested);
}

// 标准计算界面布局
void MainWindow::setStandardUi()
{
    // 固定窗口大小
    this->setFixedSize(432, 628);

    // 设置当前模式
    this->currentModel = STANDARD;

    // 初始化标准界面布局
    if (standardOutput == nullptr) {
        standardOutput = new StandardOutput(this);
        standardModel  = new StandardModel(this);

        // 绑定处理函数
        for (int i = 0; i < 10; i++) {
            QObject::connect(standardModel->btnNum[i],SIGNAL(clicked(bool)),this,SLOT(btn_handler(bool)));
        }

        // QObject::connect(standardModel->btnDZero,  SIGNAL(clicked(bool)),this,SLOT(btn_handler(bool)));

        QObject::connect(standardModel->btnClear,  SIGNAL(clicked(bool)),this,SLOT(btn_handler(bool)));
        QObject::connect(standardModel->btnDiv,    SIGNAL(clicked(bool)),this,SLOT(btn_handler(bool)));
        QObject::connect(standardModel->btnMulti,  SIGNAL(clicked(bool)),this,SLOT(btn_handler(bool)));
        QObject::connect(standardModel->btnSub,    SIGNAL(clicked(bool)),this,SLOT(btn_handler(bool)));
        QObject::connect(standardModel->btnAdd,    SIGNAL(clicked(bool)),this,SLOT(btn_handler(bool)));
        QObject::connect(standardModel->btnEqual,  SIGNAL(clicked(bool)),this,SLOT(btn_handler(bool)));
        QObject::connect(standardModel->btnPer,    SIGNAL(clicked(bool)),this,SLOT(btn_handler(bool)));
        QObject::connect(standardModel->btnPoint,  SIGNAL(clicked(bool)),this,SLOT(btn_handler(bool)));
        QObject::connect(standardModel->btnDelete, SIGNAL(clicked(bool)),this,SLOT(delete_btn_handle(bool)));

        standardOutput->staLabNow->setContextMenuPolicy(Qt::CustomContextMenu);
        connect(standardOutput->staLabNow, &MainWindow::customContextMenuRequested, this, &MainWindow::myCustomContextMenuRequested);
    }

    installEventFilter(standardModel);
    
    // 绑定输出组件
    this->lab_last = standardOutput->staLabLast;
    this->lab_prepare = standardOutput->staLabPre;
    this->lab_now = standardOutput->staLabNow;

    this->lab_now->setText("0");
    this->lab_prepare->setText("");

    // 获取历史记录
    int size = disHistory.size();
    QString historyText = "";
    int hisIndex = (size - 5 >= 0) ? (size - 5) : 0;
    for (int i = hisIndex; i < size; i++) {
        historyText = historyText + disHistory.at(i);
    }

    historyText.replace(SUB, "-");

    // 去除末尾换行符
    historyText.chop(1);
    this->lab_last->setText(historyText);

    // QVBoxLayout *staOutputLayout = new QVBoxLayout(this);
    // QVBoxLayout *standardLayout = new QVBoxLayout(this);

    // staOutputLayout->addWidget(standardOutput);
    // staOutputLayout->setMargin(0);

    // standardLayout->addWidget(standardModel);
    // standardLayout->setMargin(0);

    // 添加界面布局
    // outputWid->setLayout(staOutputLayout);
    // buttonWid->setLayout(standardLayout);

    standardModel->setWidgetStyle();
    standardOutput->setWidgetStyle();

    mainOutputLayout->addWidget(standardOutput);
    mainButtonLayout->addWidget(standardModel);

    standardOutput->show();
    standardModel->show();

    // 设置间距和背景样式
    outputWid->setFixedHeight(270);
//    outputWid->setStyleSheet("#outputWid{background-color:#131314;border-radius:4px;}");

//    buttonWid->setStyleSheet("#buttonWid{background-color:#262628;border-radius:4px;}");
    buttonWid->setFixedHeight(320);

    funcListWid->setGeometry(QRect(187, 40, 20, 170));
}

// 科学计算界面布局
void MainWindow::setScientificUi()
{
    // 固定窗口大小
    this->setFixedSize(864, 628);

    // 设置当前模式
    this->currentModel = SCIENTIFIC;

    // outputWid = new QWidget(this);
    // outputWid->setObjectName("outputWid");

    // buttonWid = new QWidget(this);
    // buttonWid->setObjectName("buttonWid");

    // 初始化界面布局
    if (scientificOutput == nullptr) {
        scientificOutput = new ScientificOutput(this);
        scientificModel  = new ScientificModel(this);

        InputProcess::inputFromButton(RAD_SYMBOL);

        // 绑定处理函数
        for (int i = 0; i < 10; i++) {
            QObject::connect(scientificModel->btnNum[i],SIGNAL(clicked(bool)),this,SLOT(btn_handler(bool)));
        }

        // QObject::connect(scientificModel->btnDZero,  SIGNAL(clicked(bool)),this,SLOT(btn_handler(bool)));

        QObject::connect(scientificModel->btnClear,  SIGNAL(clicked(bool)),this,SLOT(btn_handler(bool)));
        QObject::connect(scientificModel->btnDiv,    SIGNAL(clicked(bool)),this,SLOT(btn_handler(bool)));
        QObject::connect(scientificModel->btnMulti,  SIGNAL(clicked(bool)),this,SLOT(btn_handler(bool)));
        QObject::connect(scientificModel->btnSub,    SIGNAL(clicked(bool)),this,SLOT(btn_handler(bool)));
        QObject::connect(scientificModel->btnAdd,    SIGNAL(clicked(bool)),this,SLOT(btn_handler(bool)));
        QObject::connect(scientificModel->btnEqual,  SIGNAL(clicked(bool)),this,SLOT(btn_handler(bool)));
        QObject::connect(scientificModel->btnPer,    SIGNAL(clicked(bool)),this,SLOT(btn_handler(bool)));
        QObject::connect(scientificModel->btnPoint,  SIGNAL(clicked(bool)),this,SLOT(btn_handler(bool)));
        QObject::connect(scientificModel->btnDelete, SIGNAL(clicked(bool)),this,SLOT(delete_btn_handle(bool)));

        // QObject::connect(scientificModel->btnInd,   SIGNAL(clicked(bool)),this,SLOT(btn_handler(bool)));
        QObject::connect(scientificModel->btnUndo,          SIGNAL(clicked(bool)),this,SLOT(sciBtnHandler(bool)));
        QObject::connect(scientificModel->btnBracketLeft,   SIGNAL(clicked(bool)),this,SLOT(btn_handler(bool)));
        QObject::connect(scientificModel->btnBracketRight,  SIGNAL(clicked(bool)),this,SLOT(btn_handler(bool)));

        QObject::connect(scientificModel->btnReci,      SIGNAL(clicked(bool)),this,SLOT(sciBtnHandler(bool)));
        QObject::connect(scientificModel->btnXPower2,   SIGNAL(clicked(bool)),this,SLOT(sciBtnHandler(bool)));
        QObject::connect(scientificModel->btnXPower3,   SIGNAL(clicked(bool)),this,SLOT(sciBtnHandler(bool)));
        QObject::connect(scientificModel->btnYPowerX,   SIGNAL(clicked(bool)),this,SLOT(sciBtnHandler(bool)));

        QObject::connect(scientificModel->btnFac,       SIGNAL(clicked(bool)),this,SLOT(sciBtnHandler(bool)));
        QObject::connect(scientificModel->btnXSquare2,  SIGNAL(clicked(bool)),this,SLOT(sciBtnHandler(bool)));
        QObject::connect(scientificModel->btnXSquare3,  SIGNAL(clicked(bool)),this,SLOT(sciBtnHandler(bool)));
        QObject::connect(scientificModel->btnYSquareX,  SIGNAL(clicked(bool)),this,SLOT(sciBtnHandler(bool)));

        QObject::connect(scientificModel->btnSin,   SIGNAL(clicked(bool)),this,SLOT(sciBtnHandler(bool)));
        QObject::connect(scientificModel->btnCos,   SIGNAL(clicked(bool)),this,SLOT(sciBtnHandler(bool)));
        QObject::connect(scientificModel->btnTan,   SIGNAL(clicked(bool)),this,SLOT(sciBtnHandler(bool)));
        QObject::connect(scientificModel->btnLog,   SIGNAL(clicked(bool)),this,SLOT(sciBtnHandler(bool)));

        QObject::connect(scientificModel->btnRad,   SIGNAL(clicked(bool)),this,SLOT(sciBtnHandler(bool)));
        QObject::connect(scientificModel->btnPi,    SIGNAL(clicked(bool)),this,SLOT(sciBtnHandler(bool)));
        QObject::connect(scientificModel->btnExp,   SIGNAL(clicked(bool)),this,SLOT(sciBtnHandler(bool)));
        QObject::connect(scientificModel->btnLn,    SIGNAL(clicked(bool)),this,SLOT(sciBtnHandler(bool)));

    }
    
    installEventFilter(scientificModel);

    // 绑定输出组件
    this->lab_last = scientificOutput->sciLabLastR;
    this->lab_prepare = scientificOutput->sciLabPre;
    this->lab_now = scientificOutput->sciLabNow;

    this->lab_now->setText("0");
    this->lab_prepare->setText("");

    // 获取历史记录
    int size = disHistory.size();
    QString historyText = "";
    int hisIndex = (size - 5 >= 0) ? (size - 5) : 0;
    for (int i = hisIndex; i < size; i++) {
        historyText = historyText + disHistory.at(i);
    }

    historyText.replace(SUB, "-");

    // 去除末尾换行符
    historyText.chop(1);
    this->lab_last->setText(historyText);

    // QVBoxLayout *sciOutputLayout = new QVBoxLayout(this);
    // QVBoxLayout *scientificLayout = new QVBoxLayout(this);

    // sciOutputLayout->addWidget(scientificOutput);
    // sciOutputLayout->setMargin(0);

    // scientificLayout->addWidget(scientificModel);
    // scientificLayout->setMargin(0);

    // // 添加界面布局
    // outputWid->setLayout(sciOutputLayout);
    // buttonWid->setLayout(scientificLayout);

    scientificModel->setWidgetStyle();
    scientificModel->updateBtnSinDisplay();
    scientificModel->updateBtnRadDisplay();
    scientificOutput->setWidgetStyle();

    mainOutputLayout->addWidget(scientificOutput);
    mainButtonLayout->addWidget(scientificModel);

    scientificOutput->show();
    scientificModel->show();

    
    // 设置间距和背景样式
    outputWid->setFixedHeight(270);
//    outputWid->setStyleSheet("#outputWid{background-color:#18181A;margin-top:1px;border-radius:4px;}");

//    buttonWid->setStyleSheet("#buttonWid{background-color:#262628;border-radius:4px;}");
    buttonWid->setFixedHeight(320);

    funcListWid->setGeometry(QRect(640, 40, 20, 170));
}

// 换算器界面布局
void MainWindow::setToolUi()
{
    // 固定窗口大小
    this->setFixedSize(432, 628);

    // 设置当前模式
    this->currentModel = EXCHANGE_RATE;

    // outputWid = new QWidget(this);
    // buttonWid = new QWidget(this);

    // outputWid->setObjectName("outputWid");
    // buttonWid->setObjectName("buttonWid");

    // 初始化数据输出界面
    if (toolModelOutput == nullptr) {
        toolModelOutput = new ToolModelOutput(this);
        toolModelButton = new ToolModelButton(this);

        // 绑定处理函数
        for (int i = 0; i < 10; i++) {
            QObject::connect(toolModelButton->btnNum[i],SIGNAL(clicked(bool)),this,SLOT(btn_handler(bool)));
        }

        // QObject::connect(toolModelButton->btnDZero,  SIGNAL(clicked(bool)),this,SLOT(btn_handler(bool)));

        QObject::connect(toolModelButton->btnClear,  SIGNAL(clicked(bool)),this,SLOT(btn_handler(bool)));
        QObject::connect(toolModelButton->btnDiv,    SIGNAL(clicked(bool)),this,SLOT(btn_handler(bool)));
        QObject::connect(toolModelButton->btnMulti,  SIGNAL(clicked(bool)),this,SLOT(btn_handler(bool)));
        QObject::connect(toolModelButton->btnSub,    SIGNAL(clicked(bool)),this,SLOT(btn_handler(bool)));
        QObject::connect(toolModelButton->btnAdd,    SIGNAL(clicked(bool)),this,SLOT(btn_handler(bool)));
        QObject::connect(toolModelButton->btnEqual,  SIGNAL(clicked(bool)),this,SLOT(btn_handler(bool)));
        QObject::connect(toolModelButton->btnPer,    SIGNAL(clicked(bool)),this,SLOT(btn_handler(bool)));
        QObject::connect(toolModelButton->btnPoint,  SIGNAL(clicked(bool)),this,SLOT(btn_handler(bool)));
        QObject::connect(toolModelButton->btnDelete, SIGNAL(clicked(bool)),this,SLOT(delete_btn_handle(bool)));

    }
    
    installEventFilter(toolModelButton);

    // 绑定输出组件
    this->lab_last    = toolModelOutput->toolLabHis;
    this->lab_prepare = toolModelOutput->toolLabAft;
    this->lab_now     = toolModelOutput->toolLabBef;

    this->lab_now->setText("0");
    this->lab_prepare->setText("");

    // // 获取历史记录
    // int size = disHistory.size();
    // QString historyText = "";
    // int hisIndex = (size - 5 >= 0) ? (size - 5) : 0;
    // for (int i = hisIndex; i < size; i++) {
    //     historyText = historyText + disHistory.at(i);
    // }
    // if (historyText != "") {
	//     // 去除末尾换行符
	//     historyText.chop(1);

	//     historyText = toolModelOutput->unitConvHistory(historyText);
	//     historyText.replace(SUB, "-");

	//     qDebug() << "historyText" << historyText << toolModelOutput->toolDouRate;

	//     this->lab_last->setText(historyText);
    // }

    // QVBoxLayout *toolOutputLayout = new QVBoxLayout(this);
    // QVBoxLayout *toolButtonLayout = new QVBoxLayout(this);

    // toolOutputLayout->addWidget(toolModelOutput);
    // toolOutputLayout->setMargin(0);

    // toolButtonLayout->addWidget(toolModelButton);
    // toolButtonLayout->setMargin(0);

    // outputWid->setLayout(toolOutputLayout);
    // buttonWid->setLayout(toolButtonLayout);

    toolModelButton->setWidgetStyle();
    toolModelOutput->setWidgetStyle();
    toolModelOutput->unitListBef->setWidgetStyle();
    toolModelOutput->unitListAft->setWidgetStyle();

    mainOutputLayout->addWidget(toolModelOutput);
    mainButtonLayout->addWidget(toolModelButton);

    toolModelOutput->show();
    toolModelButton->show();

    // 设置间距和背景样式
    outputWid->setFixedHeight(270);
//    outputWid->setStyleSheet("#outputWid{background-color:#666666;border-radius:4px;margin-top:1px;}");

//    buttonWid->setStyleSheet("#buttonWid{background-color:#262628;border-radius:4px;}");
    buttonWid->setFixedHeight(320);

    funcListWid->setGeometry(QRect(187, 40, 20, 170));
}

// 计算器界面切换布局
void MainWindow::changeCalculatorUi()
{
    mainLayout->addWidget(outputWid);
    mainLayout->addWidget(buttonWid);

    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);

    this->mainWid->setLayout(mainLayout);
    this->mainWid->setObjectName("mainWid");
//    this->mainWid->setStyleSheet("#mainWid{background-color:#666666;}");
    this->setCentralWidget(mainWid);
    // this->show();
}

// 换算器界面切换布局
void MainWindow::changeToolUi()
{
    mainLayout->addWidget(outputWid);
    mainLayout->addWidget(buttonWid);

    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);

    this->mainWid->setLayout(mainLayout);
    this->mainWid->setObjectName("mainWid");
//    this->mainWid->setStyleSheet("#mainWid{background-color:#666666;}");
    this->setCentralWidget(mainWid);
    // this->show();
}

// 重绘窗口
void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); // 反锯齿;
    painter.setPen(Qt::transparent);

    QWidget::paintEvent(event);
}


// 实现键盘输入
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_F1) {
        if (!mDaemonIpcDbus->daemonIsNotRunning()){
            //增加标题栏帮助菜单、F1快捷键打开用户手册
            mDaemonIpcDbus->showGuide("tools/kylin-calculator");
        }
    }

    // QString label = this->pTitleBar->m_pFuncLabel->text();
    // label.replace(tr("calculator"), "");
    QString label = this->currentModel;

    if (label == STANDARD) {
        standardModel->keyPressEvent(event);
    }
    else if (label == SCIENTIFIC) {
        scientificModel->keyPressEvent(event);
    }
    else if (label == EXCHANGE_RATE) {
        toolModelButton->keyPressEvent(event);
    }
}

// 实现千分位加入
QString MainWindow::addComma(QString s) {
    if(s.isEmpty()) return "";

    int pointFlag = 0;
    int pointIndex;

    for (int i = 0; i < s.size(); i++) {

        if(s[i] == '.') {
            pointFlag = 1;
            pointIndex = i;
        }
    }

    if(pointFlag == 1) {
        return addComma(s.mid(0,pointIndex)) + s.mid(pointIndex,s.size()-pointIndex);
    }
    else {
        QString ans;
        for(int i =s.size()-3; i > 0; i -= 3)
            s.insert(i,",");
        return s;
    }
}
// 换算器输入响应事件
void MainWindow::unitCalc()
{
    double rate = 0.15;
    QString textAft = this->lab_prepare->text().remove(QRegExp(","));

    qDebug() << "textAft--" << textAft;
    qDebug() << "textAft.toDouble()--" << textAft.toDouble();
    double moneyAft = textAft.toDouble() * rate;

    this->lab_prepare->setText(QString::number(moneyAft));
}

// 将用于显示的表达式格式化为用于运算的表达式
QString MainWindow::formatDisToCal(QString text)
{
    text.replace(SUB, "-");
    text.replace("×", "*");
    text.replace("÷", "/");
    text.replace(",", "" );

    return text;
}

// 切换深色主题
void MainWindow::changeDarkTheme()
{
    WidgetStyle::themeColor = 1;

    // QString label = this->pTitleBar->m_pFuncLabel->text();
    // label.replace(tr("calculator"), "");
    QString label = this->currentModel;

    this->setWidgetStyle();
    pTitleBar->setWidgetStyle();
    funcList->setWidgetStyle();

    if (label.contains(STANDARD)) {
        standardModel->setWidgetStyle();
        standardOutput->setWidgetStyle(false);
    }
    else if (label.contains(SCIENTIFIC)) {
        scientificModel->setWidgetStyle();
        scientificOutput->setWidgetStyle(false);
    }
    else if (label.contains(EXCHANGE_RATE)) {
        toolModelButton->setWidgetStyle();
        toolModelOutput->setWidgetStyle(false);
        toolModelOutput->unitListBef->setWidgetStyle();
        toolModelOutput->unitListAft->setWidgetStyle();
    }
}

// 切换浅色主题
void MainWindow::changeLightTheme()
{
    WidgetStyle::themeColor = 0;

    // QString label = this->pTitleBar->m_pFuncLabel->text();
    // label.replace(tr("calculator"), "");
    QString label = this->currentModel;

    this->setWidgetStyle();
    pTitleBar->setWidgetStyle();
    funcList->setWidgetStyle();

    if (label.contains(STANDARD)) {
        standardModel->setWidgetStyle();
        standardOutput->setWidgetStyle(false);
    }
    else if (label.contains(SCIENTIFIC)) {
        scientificModel->setWidgetStyle();
        scientificOutput->setWidgetStyle(false);
    }
    else if (label.contains(EXCHANGE_RATE)) {
        toolModelButton->setWidgetStyle();
        toolModelOutput->setWidgetStyle(false);
        toolModelOutput->unitListBef->setWidgetStyle();
        toolModelOutput->unitListAft->setWidgetStyle();
    }
}

// 重置输入界面字号
void MainWindow::resetFontSize(QString calModel, QString fontSizeStr)
{
    if (calModel == STANDARD) {
        lab_now->setStyleSheet("font-size:" + fontSizeStr + "px;font-weight:15px;margin:0 0 5px 7px;");
    }
    else if (calModel == SCIENTIFIC) {
        lab_now->setStyleSheet("font-size:" + fontSizeStr + "px;font-weight:15px;margin:0 0 0 7px;");
    }
    else if (calModel == EXCHANGE_RATE) {
        lab_now->setStyleSheet("font-size:" + fontSizeStr + "px;font-weight:15px;");
    }
}

// 更新输出界面
void MainWindow::updateOutput(QVector<QString> outVector)
{
    for (int i = 0; i < outVector.size(); i++) {
        if (outVector[i] == INF_SYMBOL) {
            outVector[i] = tr("Error!");
        }
        if (outVector[i] == NAN_SYMBOL) {
            outVector[i] = tr("Error!");
        }
        if (outVector[i] == "input Error!") {
            outVector[i] = tr("Input error!");
        }
    }

    // 获取数据
    this->disData = outVector[DISPLAY_ON_LABEL_NOW];
    this->calData = outVector[LABEL_NOW_CAL_QSTR];

    // 更新界面显示
    this->lab_now->setText(outVector[DISPLAY_ON_LABEL_NOW]);
    this->lab_prepare->setText(outVector[DISPLAY_ON_LABEL_PREPARE]);

    qDebug() << "DISPLAY_ON_LABEL_NOW"      << outVector[DISPLAY_ON_LABEL_NOW]      << "\n" <<
                "LABEL_NOW_CAL_QSTR"        << outVector[LABEL_NOW_CAL_QSTR]        << "\n" <<
                "CAL_ANS"                   << outVector[CAL_ANS]                   << "\n" <<
                "LATEST_HISTORY"            << outVector[LATEST_HISTORY]            << "\n" <<
                "DISPLAY_ON_LABEL_PREPARE"  << outVector[DISPLAY_ON_LABEL_PREPARE]  << "\n" <<
                "LABEL_PREPARE_CAL_QSTR"    << outVector[LABEL_PREPARE_CAL_QSTR]    << "\n";

    // 输出为"0"时设置为最大字号
    if (lab_now->text().size() == 1) {
        this->resetFontSize(this->currentModel, "48");
    }
    // 数字过长字号缩小
    else if (lab_now->fontInfo().pixelSize() > 16) {
        QFont labFont = lab_now->font();
        QFontMetrics fontMts(labFont);
        int dif = fontMts.width(lab_now->text()) - lab_now->width();
        
        QString fontSizeStr = QString::number(lab_now->fontInfo().pixelSize() - 8);

        // 不同模式下需要判断的距离阈值不一样
        while ((this->currentModel == STANDARD      && dif > -10) ||
               (this->currentModel == SCIENTIFIC    && dif > -12) ||
               (this->currentModel == EXCHANGE_RATE && dif > -20)) {
            this->resetFontSize(this->currentModel, fontSizeStr);
            labFont.setPixelSize(labFont.pixelSize() - 8);
            QFontMetrics fontMts(labFont);
            dif = fontMts.width(lab_now->text()) - lab_now->width();
            fontSizeStr = QString::number(labFont.pixelSize() - 8);
        }
    }

    return ;
}

void MainWindow::btn_merge(const QString &disText)
{
    QFontMetrics fontMts = lab_now->fontMetrics();
    int dif = fontMts.width(lab_now->text()) - lab_now->width();

    this->inputLongSym = false;

    // 数字过长禁止输入
    if (disText != BACKSPACE && disText != CLEAN && disText != EQUAL) {
        
        if (lab_now->fontInfo().pixelSize() <= 16) {
            // 不同模式下需要判断的距离阈值不一样
            if ((this->currentModel == STANDARD      && dif > -15) ||
                (this->currentModel == SCIENTIFIC    && dif > -12) ||
                (this->currentModel == EXCHANGE_RATE && dif > -35)) {
                
                this->lab_prepare->setText(tr("input too long"));
                this->inputLongSym = true;
                return ;
            }
        }
    }
    // 删除时字号放大
    else if (disText == BACKSPACE && lab_now->fontInfo().pixelSize() < 48) {

        QFont labFont = lab_now->font();
        labFont.setPixelSize(lab_now->fontInfo().pixelSize() + 8);
        QFontMetrics fm(labFont);
        int dif = fm.width(lab_now->text()) - (lab_now->width() -10);

        // 放大字号时的距离阈值
        if (dif < 50) {
            QString fontSizeStr = QString::number(lab_now->fontInfo().pixelSize() + 8);

            this->resetFontSize(this->currentModel, fontSizeStr);
        }
    }
    // 清除时设置为最大字号
    else if (disText == CLEAN || disText == EQUAL) {
        this->resetFontSize(this->currentModel, "48");
    }
    
    qDebug() << "disText is " << disText;
    // 格式化为用于运算的表达式
    QString calText = disText;
    calText = formatDisToCal(calText);

    disData.push_back(disText);
    calData.push_back(calText);

    // 获取显示字符串 运算字符串
    QVector<QString> resVector = InputProcess::inputFromButton(disText);
    // qDebug() << disText;

    // 将显示结果和运算结果进行显示
    updateOutput(resVector);

    // 等于号的运算逻辑 更新界面显示
    if (resVector[LATEST_HISTORY].size()) {
        disHistory.push_back(resVector[LATEST_HISTORY] + '\n');

        //输出测试到history.txt
        cout << disHistory[disHistory.size() - 1].toStdString() << endl;

        disData.clear();
        calData.clear();

        // 更新界面显示
        // lab_now->setText(lab_prepare->text());
        // lab_prepare->clear();

        // 获取历史记录
        int size = disHistory.size();
        QString historyText = "";
        int hisIndex = (size - 5 >= 0) ? (size - 5) : 0;
        for (int i = hisIndex; i < size; i++) {
            historyText = historyText + disHistory.at(i);
        }

        // 去除末尾换行符
        historyText.chop(1);

        // qDebug() << "historyText" << historyText;

        // 在汇率模式下，根据历史记录修改为对应的记录
        // QString label = this->pTitleBar->m_pFuncLabel->text();
        // label.replace(tr("calculator"), "");
        QString label = this->currentModel;
        if (label != STANDARD && label != SCIENTIFIC) {
            qDebug() << "disHistory[] " << disHistory[disHistory.size() - 1];
            historyText = toolModelOutput->unitConvHistory(disHistory[disHistory.size() - 1]);
        }

        historyText.replace(SUB, "-");

        this->lab_last->setText(historyText);

        qDebug() << "historyText" << historyText;
    }
}

// 标准模式按钮对输入信号处理
void MainWindow::btn_handler(bool)
{
    // 获取当前输入，默认是用于显示的表达式
    BasicButton *btn = dynamic_cast<BasicButton *>(sender());
    QString disText = btn->text();
    qDebug() << "disTextis:"<<disText;
    btn_merge(disText);

    // QString label = this->pTitleBar->m_pFuncLabel->text();
    // label.replace(tr("calculator"), "");
    QString label = this->currentModel;
    if (label != STANDARD && label != SCIENTIFIC && inputLongSym == false) {
       toolModelOutput->unitConversion();
    }
}


// 科学模式下专属按钮点击事件
void MainWindow::sciBtnHandler(bool)
{
    // 获取当前输入
    BasicButton *btn = dynamic_cast<BasicButton *>(sender());

    // if (btn == scientificModel->btnInd) {

    // }
    // qDebug() << 123;
    QString text = btn->text();
    // qDebug() << 456;
    btn_merge(text);

//     text = scientificModel->sciFormatInput(text);

//     dis_data.push_back(text);
// //    num_now.push_back(text);
//     this->lab_now->setText(dis_data);

    return ;
}

void MainWindow::delete_btn_handle(bool)
{
    // "B" 可能要改
    btn_merge(BACKSPACE);
    // updateOutput(InputProcess::inputFromButton(BACKSPACE));

    QString label = this->currentModel;
    if (label != STANDARD && label != SCIENTIFIC) {
       toolModelOutput->unitConversion();
    }

    return ;
}

void MainWindow::funcListHandle(bool)
{
    if (funcListWid->isHidden()) {
        //        this->setFuncListUi();
        this->funcListWid->show();
    }
    else {
        this->funcListWid->hide();
    }
}

void MainWindow::changeModel(QString label)
{
    qDebug() << label;
    this->funcListWid->hide();

    if (label != this->currentModel) {

        QLayoutItem *outputChild = mainOutputLayout->takeAt(0);
        QLayoutItem *buttonChild = mainButtonLayout->takeAt(0);

        mainOutputLayout->removeItem(outputChild);
        mainButtonLayout->removeItem(buttonChild);

        outputChild->widget()->hide();
        buttonChild->widget()->hide();

        this->lab_now->clear();
        this->dis_data.clear();

        if (label == STANDARD) {
            this->pTitleBar->setFuncLabel(pTitleBar->STANDARD_LABEL);
            calData += STANDARD;
            InputProcess::inputFromButton(STANDARD);

            setStandardUi();
        }
        else if (label == SCIENTIFIC) {
            this->pTitleBar->setFuncLabel(pTitleBar->SCIENTIFIC_LABEL);
            calData += SCIENTIFIC;
            InputProcess::inputFromButton(SCIENTIFIC);
            
            setScientificUi();
        }
        else if (label == EXCHANGE_RATE) {
            this->pTitleBar->setFuncLabel(pTitleBar->EXCHANGE_RATE_LABEL);
            calData += STANDARD;
            InputProcess::inputFromButton(STANDARD);

            setToolUi();
        }
        
    }

}

// 判断字符串是否为纯数字
bool MainWindow::isDigitStr(QString str)
{
    // QString转换为char*
    QByteArray byteArray = str.toLatin1();
    const char *s = byteArray.data();

    // // 判断首字符
    // if (*s && (*s == 'ｰ' || *s == '-')) {
    //     s++;
    // }

    // 判断是否为纯数字
    while (*s && *s >= '0' && *s <= '9') {
        qDebug() << *s;
        s++;
    }
    
    // 不是纯数字
    if (*s) {
        return false;
    }
    // 是纯数字
    else {
        return true;
    }
}

// 响应右键菜单
void MainWindow::myCustomContextMenuRequested(const QPoint& pos)
{
    QString labNowStr = this->lab_now->text().remove(",");
    if (this->isDigitStr(labNowStr) == false) {
        copyAction->setEnabled(false);
    }
    else {
        copyAction->setEnabled(true);
    }

    // QClipboard *clipboard = QApplication::clipboard();
    QString clipText = clipboard->text();
    if (this->isDigitStr(clipText) == false) {
        pasteAction->setEnabled(false);
    }
    else {
        pasteAction->setEnabled(true);
    }

    labelMenu->exec(QCursor::pos());
}

// 复制计算结果到剪切板
void MainWindow::copyCalResult()
{
    clipboard->setText(this->lab_now->text().remove(","));
    qDebug() << "clipboard->setText" << this->lab_now->text().remove(",");
}

// 将剪切板内容粘贴到运算式中
void MainWindow::pasteToLabNow()
{
    // QClipboard *clipboard = QApplication::clipboard();
    QString clipText = clipboard->text();

    for (int i = 0; i < clipText.size(); i++) {
        this->btn_merge(QString(clipText[i]));
    }
}

void MainWindow::funcListItemClicked(QListWidgetItem* item)
{
    QString label = item->text().trimmed();
    this->funcListWid->hide();

    if (label != this->currentModel) {
        this->pTitleBar->setFuncLabel(label + tr("calculator"));

        if (label == tr("standard") || label == tr("scientific")) {

            mainLayout->removeWidget(outputWid);
            mainLayout->removeWidget(buttonWid);

            this->outputWid->close();
            this->buttonWid->close();

            this->lab_now->clear();
            this->dis_data.clear();

            // 换算器选项失去焦点
            for (int i = 0; i < funcList->funcToolWid->count(); i++) {
                funcList->funcToolWid->item(i)->setSelected(false);
            }

            if (label == tr("standard")) {
                calData += STANDARD;
                InputProcess::inputFromButton(STANDARD);
                setStandardUi();
            }
            else if (label == tr("scientific")) {
                calData += SCIENTIFIC;
                InputProcess::inputFromButton(SCIENTIFIC);
                InputProcess::inputFromButton(RAD_SYMBOL);
                setScientificUi();
            }

            // changeCalculatorUi();
        }
        else {

            // 计算器选项失去焦点
            for (int i = 0; i < funcList->funcModelWid->count(); i++) {
                funcList->funcModelWid->item(i)->setSelected(false);
            }

            if (label == tr("exchange rate")) {
                mainLayout->removeWidget(outputWid);
                mainLayout->removeWidget(buttonWid);

                this->outputWid->close();
                this->buttonWid->close();

                setToolUi();
            }

            // changeToolUi();
        }

    }
}

void MainWindow::stayTop()
{
    // 使用KWindowSystem可以更加方便地控制窗口置顶
    if (winFlags == NULL) {
        winFlags = windowFlags();
        KWindowSystem::setState(this->winId(), KWindowSystem::KeepAbove);
        // pTitleBar->m_pTopButton->setStyleSheet("QPushButton{border-radius:4px;background-color:rgb(180,180,180);}");
        pTitleBar->m_pTopButton->setIcon(QIcon::fromTheme("ukui-fixed-symbolic"));

        pTitleBar->m_pTopButton->setAutoFillBackground(true);
        pTitleBar->m_pTopButton->setBackgroundRole(QPalette::Window);
    }
    else {
        winFlags = NULL;
        KWindowSystem::clearState(this->winId(), KWindowSystem::KeepAbove);
        pTitleBar->m_pTopButton->setIcon(QIcon::fromTheme("ukui-unfixed-symbolic"));

        pTitleBar->m_pTopButton->setBackgroundRole(QPalette::Base);
    }
}

// 汇率换算事件
void MainWindow::unitConversion()
{
    toolModelOutput->unitConversion();
    // this->lab_prepare->setText(lab_prepare->text());
    this->lab_prepare->setText(addComma(lab_prepare->text()));
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    mMoveing = true;
    mMovePosition = event->globalPos() - pos();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (mMoveing && (event->buttons() && Qt::LeftButton)
        && (event->globalPos()-mMovePosition).manhattanLength() > QApplication::startDragDistance())
    {
        setCursor( Qt::ClosedHandCursor );
        move(event->globalPos()-mMovePosition);
        mMovePosition = event->globalPos() - pos();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    mMoveing = false;
    setCursor( Qt::ArrowCursor );
}
