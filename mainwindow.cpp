#include "mainwindow.h"
#include <QKeyEvent>
#include <QDebug>
#include <QList>
#include <QDesktopWidget>
#include <QThread>
#include <cstdio>
#include <iostream>
using namespace std;

QString calculator(QString dis_data);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setFocus();

    mainWid = new QWidget(this);

    setCommonUi();
//    setOutputUi();

    setStandardUi();

    mainLayout = new QVBoxLayout();
    mainLayout->addWidget(titleBarWid);
    mainLayout->addWidget(outputWid);
    mainLayout->addWidget(buttonWid);

    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    this->mainWid->setLayout(mainLayout);
    this->mainWid->setObjectName("mainWid");
    this->mainWid->setStyleSheet("#mainWid{background-color:#666666;border-radius:6px;}");
    this->setCentralWidget(mainWid);
    this->show();
}

MainWindow::~MainWindow()
{

}

// 公有组件，即标题栏和功能列表
void MainWindow::setCommonUi()
{
    // 窗口设置
    // 无边框、界面置顶
    //    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setWindowFlags(Qt::FramelessWindowHint);

    // 窗体透明
    this->setAttribute(Qt::WA_TranslucentBackground, true);

    // 设置图标
    this->setWindowTitle("麒麟计算器");
    this->setWindowIcon(QIcon("/usr/share/icons/ukui-icon-theme-default/64x64/apps/calc.png"));

    titleBarWid = new QWidget(this);
    titleBarWid->setObjectName("titleBarWid");

    // 标题栏
    pTitleBar = new TitleBar(this);
    installEventFilter(pTitleBar);

    pTitleBar->setFuncLabel(tr("标准"));

    QVBoxLayout *pLayout = new QVBoxLayout();
    pLayout->addWidget(pTitleBar);
    pLayout->addStretch();
    pLayout->setSpacing(0);
    pLayout->setMargin(0);
    titleBarWid->setLayout(pLayout);
    titleBarWid->setFixedHeight(TITLEH);
    titleBarWid->setStyleSheet("background:#1C1C1E;opacity:0.95;border-top-left-radius:6px;border-top-right-radius:6px;");

    // 显示和隐藏功能列表
    connect(pTitleBar->funcListButton,SIGNAL(clicked(bool)),this,SLOT(funcListHandle(bool)));
    connect(pTitleBar->m_pTopButton,SIGNAL(clicked(bool)),this,SLOT(stayTop()));

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
    funcListWid->setStyleSheet("background:#36363A;color:#FFFFFF;font-size:18px;border:none;border-radius:4px;");
    funcListWid->raise();
    funcListWid->setFixedHeight(420);
    funcListWid->setFixedWidth(170);
    funcListWid->setGeometry(QRect(0, 40, 20, 170));
    funcListWid->hide();

    funcList->setAttribute(Qt::WA_ShowWithoutActivating, true);

    // 功能列表项响应点击
    connect(funcList->funcModelWid, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(funcListItemClicked(QListWidgetItem*)));
    connect(funcList->funcToolWid,  SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(funcListItemClicked(QListWidgetItem*)));
}

// 计算器输出窗口组件
void MainWindow::setOutputUi()
{
    outputWid = new QWidget(this);
    outputWid->setObjectName("outputWid");

    // 当前表达式
    this->lab_now = new QLabel(this);

    // 历史记录
    this->lab_last = new QLabel(this);

    // 预测输出
    this->lab_prepare = new QLabel(this);

    lab_now->setWordWrap(true);
    lab_last->setWordWrap(true);
    lab_prepare->setWordWrap(true);

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

    QFont lab_now_font("SourceHanSansCN-Normal", 50, 15);
    this->lab_now->setAlignment(Qt::AlignRight);
    this->lab_now->setFont(lab_now_font);
    this->lab_now->setText("0");
    this->lab_now->setFixedHeight(65);
    this->lab_now->setStyleSheet("color:#FFFFFF;font-size:48px;font-weight:15px;line-height:50px;margin:0 0 5px 7px;");
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
    outputWid->setStyleSheet("#outputWid{background-color:#18181A;border-radius:6px;margin-top:1px}");
}

// 标准计算界面布局
void MainWindow::setStandardUi()
{
    // 固定窗口大小
    this->setFixedSize(432, 628);

    outputWid = new QWidget(this);
    outputWid->setObjectName("outputWid");

    buttonWid = new QWidget(this);
    buttonWid->setObjectName("buttonWid");

    // 初始化标准界面布局
    standardOutput = new StandardOutput(this);
    standardModel  = new StandardModel(this);
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

    // 去除末尾换行符
    historyText.chop(1);
    this->lab_last->setText(historyText);

    QVBoxLayout *staOutputLayout = new QVBoxLayout(this);
    QVBoxLayout *standardLayout = new QVBoxLayout(this);

    staOutputLayout->addWidget(standardOutput);
    staOutputLayout->setMargin(0);

    standardLayout->addWidget(standardModel);
    standardLayout->setMargin(0);

    // 添加界面布局
    outputWid->setLayout(staOutputLayout);
    buttonWid->setLayout(standardLayout);

    // 绑定处理函数
    for (int i = 0; i < 10; i++) {
        QObject::connect(standardModel->btnNum[i],SIGNAL(clicked(bool)),this,SLOT(btn_handler(bool)));
    }

    QObject::connect(standardModel->btnClear,  SIGNAL(clicked(bool)),this,SLOT(btn_handler(bool)));
    QObject::connect(standardModel->btnDiv,    SIGNAL(clicked(bool)),this,SLOT(btn_handler(bool)));
    QObject::connect(standardModel->btnMulti,  SIGNAL(clicked(bool)),this,SLOT(btn_handler(bool)));
    QObject::connect(standardModel->btnSub,    SIGNAL(clicked(bool)),this,SLOT(btn_handler(bool)));
    QObject::connect(standardModel->btnAdd,    SIGNAL(clicked(bool)),this,SLOT(btn_handler(bool)));
    QObject::connect(standardModel->btnEqual,  SIGNAL(clicked(bool)),this,SLOT(btn_handler(bool)));
    QObject::connect(standardModel->btnPer,    SIGNAL(clicked(bool)),this,SLOT(btn_handler(bool)));
    QObject::connect(standardModel->btnPoint,  SIGNAL(clicked(bool)),this,SLOT(btn_handler(bool)));
    QObject::connect(standardModel->btnDelete, SIGNAL(clicked(bool)),this,SLOT(delete_btn_handle(bool)));

    // 设置间距和背景样式
    outputWid->setFixedHeight(270);
    outputWid->setStyleSheet("#outputWid{background-color:#18181A;border-radius:6px;margin-top:1px}");

    buttonWid->setStyleSheet("#buttonWid{background-color:#666666;border-radius:3px;}");
    buttonWid->setFixedHeight(320);
}

// 科学计算界面布局
void MainWindow::setScientificUi()
{
    // 固定窗口大小
    this->setFixedSize(864, 628);

    outputWid = new QWidget(this);
    outputWid->setObjectName("outputWid");

    buttonWid = new QWidget(this);
    buttonWid->setObjectName("buttonWid");

    // 初始化界面布局
    scientificOutput = new ScientificOutput(this);
    scientificModel  = new ScientificModel(this);
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

    // 去除末尾换行符
    historyText.chop(1);
    this->lab_last->setText(historyText);

    QVBoxLayout *sciOutputLayout = new QVBoxLayout(this);
    QVBoxLayout *scientificLayout = new QVBoxLayout(this);

    sciOutputLayout->addWidget(scientificOutput);
    sciOutputLayout->setMargin(0);

    scientificLayout->addWidget(scientificModel);
    scientificLayout->setMargin(0);

    // 添加界面布局
    outputWid->setLayout(sciOutputLayout);
    buttonWid->setLayout(scientificLayout);

    // 绑定处理函数
    for (int i = 0; i < 10; i++) {
        QObject::connect(scientificModel->btnNum[i],SIGNAL(clicked(bool)),this,SLOT(btn_handler(bool)));
    }

    QObject::connect(scientificModel->btnClear,  SIGNAL(clicked(bool)),this,SLOT(btn_handler(bool)));
    QObject::connect(scientificModel->btnDiv,    SIGNAL(clicked(bool)),this,SLOT(btn_handler(bool)));
    QObject::connect(scientificModel->btnMulti,  SIGNAL(clicked(bool)),this,SLOT(btn_handler(bool)));
    QObject::connect(scientificModel->btnSub,    SIGNAL(clicked(bool)),this,SLOT(btn_handler(bool)));
    QObject::connect(scientificModel->btnAdd,    SIGNAL(clicked(bool)),this,SLOT(btn_handler(bool)));
    QObject::connect(scientificModel->btnEqual,  SIGNAL(clicked(bool)),this,SLOT(btn_handler(bool)));
    QObject::connect(scientificModel->btnPer,    SIGNAL(clicked(bool)),this,SLOT(btn_handler(bool)));
    QObject::connect(scientificModel->btnPoint,  SIGNAL(clicked(bool)),this,SLOT(btn_handler(bool)));
    QObject::connect(scientificModel->btnDelete, SIGNAL(clicked(bool)),this,SLOT(delete_btn_handle(bool)));

    // 设置间距和背景样式
    outputWid->setFixedHeight(270);
    outputWid->setStyleSheet("#outputWid{background-color:#18181A;border-radius:6px;margin-top:1px;}");

    buttonWid->setStyleSheet("#buttonWid{background-color:#666666;border-radius:3px;}");
    buttonWid->setFixedHeight(320);
}

// 换算器界面布局
void MainWindow::setToolUi()
{
    // 固定窗口大小
    this->setFixedSize(432, 628);

    outputWid = new QWidget(this);
    buttonWid = new QWidget(this);

    outputWid->setObjectName("outputWid");
    buttonWid->setObjectName("buttonWid");;

    // 初始化数据输出界面
    toolModelOutput = new ToolModelOutput(this);
    toolModelButton = new ToolModelButton(this);
    installEventFilter(toolModelButton);

    // 绑定输出组件
    this->lab_last    = toolModelOutput->toolLabHis;
    this->lab_prepare = toolModelOutput->toolLabAft;
    this->lab_now     = toolModelOutput->toolLabBef;

    this->lab_now->setText("0");
    this->lab_prepare->setText("");
    this->lab_last->setText("");

    QVBoxLayout *toolOutputLayout = new QVBoxLayout(this);
    QVBoxLayout *toolButtonLayout = new QVBoxLayout(this);

    toolOutputLayout->addWidget(toolModelOutput);
    toolOutputLayout->setMargin(0);

    toolButtonLayout->addWidget(toolModelButton);
    toolButtonLayout->setMargin(0);

    outputWid->setLayout(toolOutputLayout);
    buttonWid->setLayout(toolButtonLayout);

    // 绑定处理函数
    for (int i = 0; i < 10; i++) {
        QObject::connect(toolModelButton->btnNum[i],SIGNAL(clicked(bool)),this,SLOT(btn_handler(bool)));
    }

    QObject::connect(toolModelButton->btnClear,  SIGNAL(clicked(bool)),this,SLOT(btn_handler(bool)));
    QObject::connect(toolModelButton->btnDiv,    SIGNAL(clicked(bool)),this,SLOT(btn_handler(bool)));
    QObject::connect(toolModelButton->btnMulti,  SIGNAL(clicked(bool)),this,SLOT(btn_handler(bool)));
    QObject::connect(toolModelButton->btnSub,    SIGNAL(clicked(bool)),this,SLOT(btn_handler(bool)));
    QObject::connect(toolModelButton->btnAdd,    SIGNAL(clicked(bool)),this,SLOT(btn_handler(bool)));
    QObject::connect(toolModelButton->btnEqual,  SIGNAL(clicked(bool)),this,SLOT(btn_handler(bool)));
    QObject::connect(toolModelButton->btnPer,    SIGNAL(clicked(bool)),this,SLOT(btn_handler(bool)));
    QObject::connect(toolModelButton->btnPoint,  SIGNAL(clicked(bool)),this,SLOT(btn_handler(bool)));
    QObject::connect(toolModelButton->btnDelete, SIGNAL(clicked(bool)),this,SLOT(delete_btn_handle(bool)));

    // 设置间距和背景样式
    outputWid->setFixedHeight(270);
    outputWid->setStyleSheet("#outputWid{background-color:#666666;border-radius:6px;margin-top:1px}");

    buttonWid->setStyleSheet("#buttonWid{background-color:#666666;border-radius:3px;}");
    buttonWid->setFixedHeight(320);
}

// 计算器界面切换布局
void MainWindow::changeCalculatorUi()
{
    mainLayout->addWidget(outputWid);
    mainLayout->addWidget(buttonWid);

    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    this->mainWid->setLayout(mainLayout);
    this->mainWid->setObjectName("mainWid");
    this->mainWid->setStyleSheet("#mainWid{background-color:#666666;border-radius:6px;}");
    this->setCentralWidget(mainWid);
    this->show();
}

// 换算器界面切换布局
void MainWindow::changeToolUi()
{
    mainLayout->addWidget(outputWid);
    mainLayout->addWidget(buttonWid);

    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    this->mainWid->setLayout(mainLayout);
    this->mainWid->setObjectName("mainWid");
    this->mainWid->setStyleSheet("#mainWid{background-color:#666666;border-radius:6px;}");
    this->setCentralWidget(mainWid);
    this->show();
}


void MainWindow::set_ui()
{

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
    if (this->pTitleBar->m_pFuncLabel->text() == "标准") {
        standardModel->keyPressEvent(event);
    }
    else if (this->pTitleBar->m_pFuncLabel->text() == "科学") {
        scientificModel->keyPressEvent(event);
    }
    else if (this->pTitleBar->m_pFuncLabel->text() == "汇率") {
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

    this->lab_prepare->setText(addComma(QString::number(moneyAft)));
}


// 输出到label
void MainWindow::lab_output(QString s, QLabel *l) {
    if (l == lab_last) {
        if (s.size()) {
            for (int i = s.size()-1; i>=0; i--) {

                if (s[i] != '+' && s[i] != '-' && s[i] != '.'
                        && s[i] != '*' && s[i] != '/' ) {
                    i = -1;
                    break;
                }
                else {
                    s.chop(1);
                }
            }
        }
    }

    if(s.contains("inf") || s.contains("nan")) return ;

    //处理“，”
    s.push_back("$");
    QString ans = "";

    for (int i = 0; i < s.size();) {
        if ( s[i] != '+' && s[i] != '-' && s[i] != '=' && s[i] != '%'
             && s[i] != '*' && s[i] != '/' && s[i] != '$') {
            i++;
        }
        else {
            QString t = s.mid(0, i);
            s.remove(0, i);
            ans += addComma(t);
            ans += s[0];
            s.remove(0, 1);
            i = 0;
        }
    }
    ans.chop(1);

    //还原“*” “/”
    for (int j = 0; j < ans.size(); j++) {
        if(ans[j] == '/') {
            ans.replace(j, 1, "÷");
        }
        else if (ans[j] == '*') {
            ans.replace(j, 1, "×");
        }
    }



    //putput lab_last or lab_now
    if( (num_now != dis_data && l == lab_last) || l == lab_now || l == lab_prepare)
        l->setText(ans);
}

// 对输入信号处理
void MainWindow::btn_handler(bool)
{
    // 获取当前输入
    QPushButton *btn = dynamic_cast<QPushButton *>(sender());
    QString text = btn->text();

    // 异常判定
    if(text != "C" && flag == 0) return ;

    // 转换为ASCII码
    if (text == "—") {
        text = "-";
    }
    else if (text == "÷") {
        text = "/";
    }
    else if (text == "×") {
        text = "*";
    }

    // 等号之后只能输入"+-*/",否则dis_data清空
    if ( pushHistory.size()>1 && pushHistory[pushHistory.size()-1]=='=') {
        if ( (text != "/") && (text != "*") && (text != "C")
             && (text != "-") && (text != "+") ) {

            dis_data.clear();
            this->lab_prepare->setText(dis_data);
        }
    }

    // 录入历史记录
    if ( text[0] != '=' || ( (text[0] == '=' && pushHistory.size()>0)
                             && pushHistory[pushHistory.size()-1]!='=') ) {

        pushHistory.push_back(text);
    }

    // 0判断
    if (text[0] == '0') {

        // 无输入
        if (dis_data.size() == 0) {
            return ;
        }

        // 前一个输入是运算符号
        else if ( (*(dis_data.end()-1) == '/') || (*(dis_data.end()-1) == '*')
                  || (*(dis_data.end()-1) == '-') || (*(dis_data.end()-1) == '+') ) {
            dis_data.push_back(text[0]);
            num_now.push_back(text[0]);
            lab_output(dis_data, lab_now);
            lab_output(calculator(dis_data), lab_prepare);
        }
        else {

            // %判断
            if (num_now.size() != 0 && num_now.contains('%'))
                return ;
            if (num_now.size() == 1 && num_now.contains('0'))
                return ;

            dis_data.push_back(text[0]);
            num_now.push_back(text[0]);
            lab_output(dis_data, lab_now);
            lab_output(calculator(dis_data), lab_prepare);
        }
    }

    // 输入数字
    else if (text[0] > '0' && text[0] <= '9') {

        // 若首位为0，则将其去掉
        if (dis_data.size() == 1 && dis_data.contains('0')) {
            num_now.chop(1);
            dis_data.chop(1);
        }

        // %判断
        if (num_now.size() != 0 && num_now.contains('%')) {
            return ;
        }
        if (num_now.size() == 1 && num_now.contains('0')) {
            num_now.chop(1);
            dis_data.chop(1);
        }

        dis_data.push_back(text[0]);
        num_now.push_back(text[0]);
        lab_output(dis_data, lab_now);
        lab_output(calculator(dis_data), lab_prepare);
    }
    else if (text[0] == '.') {

        if (pushHistory.size() >= 2 && pushHistory[pushHistory.size()-2] == '=') {
            pushHistory.chop(1);
            return ;
        }

        // 自动补0
        if ( dis_data.size() == 0 ) {
            dis_data += "0.";
            num_now += "0.";
            lab_output(dis_data, lab_now);
        }
        else if(num_now.size() == 0) {
            dis_data += "0.";// 异常判定
            if(text != "C" && flag == 0) return ;

            // 转换为ASCII码
            if (text == "—") {
                text = "-";
            }
            else if (text == "÷") {
                text = "/";
            }
            else if (text == "×") {
                text = "*";
            }
            num_now += "0.";
            lab_output(dis_data, lab_now);
        }

        // .%判断
        else if (num_now.contains('.') || num_now.contains('%')) {
            return ;
        }

        // 正常输入0.
        else if(num_now[0] == '0'){
            dis_data += ".";
            num_now += ".";
            lab_output(dis_data, lab_now);
        }
        else {
            dis_data.push_back('.');
            num_now.push_back('.');
            lab_output(dis_data, lab_now);
        }
    }
    else if ( (text == "/") || (text == "*")
              || (text == "-") || (text == "+") ) {

        if(dis_data.size()==0) {
            dis_data += "0";
            dis_data += text;
            lab_output(dis_data, lab_now);
            lab_output(dis_data, lab_prepare);
            return;
        }

        //前一个是运算符号
        int i = dis_data.size() - 1;

        if ( dis_data[i] == '+' || dis_data[i] == '-'
             || dis_data[i] == '*' || dis_data[i] == '/' ) {

            dis_data.chop(1);
        }

        //科学计算
        if(dis_data[i] == 'e') {
            dis_data += text;
            num_now += text;
            lab_output(dis_data, lab_now);
            lab_output(dis_data, lab_prepare);
        }

        dis_data += text;
        num_now.clear();
        lab_output(dis_data, lab_now);
    }
    else if (text[0] == 'C') {
        this->lab_now->setText("0");
        this->lab_last->setText("");
        this->lab_prepare->setText("");

        flag = 1;
        dis_data.clear();
        num_now.clear();
        disHistory.clear();
    }
    else if (text[0] == '%') {
        if (pushHistory.size()>=2 && pushHistory[pushHistory.size()-2]=='=') {
            pushHistory.chop(1);
            return;
        }

        if (dis_data.isEmpty()) {
            dis_data += "0%";
            num_now += "0%";
        }
        else if (num_now.isEmpty() ) {
            dis_data += "0%";
            num_now += "0%";
        }
        else if (num_now.contains("%")) {
            return ;
        }

        //前一个输入是.
        else if (num_now[num_now.size() - 1] == '.' ) {
            dis_data.replace(dis_data.size()-1,1, '%');
                num_now.replace(num_now.size()-1,1, '%');
        }
        else {
            dis_data += '%';
            num_now += '%';
        }
        lab_output(dis_data, lab_now);
        lab_output(calculator(dis_data), lab_prepare);
    }

    else if (text[0] == '=') {

        if(!dis_data.size()) return ;

        // 前一个是运算符号或.
        int i = dis_data.size() - 1;
        if (dis_data[i] == '+' || dis_data[i] == '-'
                || dis_data[i] == '*' || dis_data[i] == '/') {
            pushHistory.chop(1);
            return;
        }

        if (dis_data[i] == '.') {
            dis_data.chop(1);
        }

        if (num_now.size() >= 0 && num_now.contains(".") && num_now.contains("0")) {
            int i = num_now.size() - 1;
            int j = dis_data.size() - 1;
            while (i >= 0 && j >= 0) {
                if (num_now[i] == '0') {
                    num_now.chop(1);
                    dis_data.chop(1);
                    i--;
                    j--;
                }
                else {
                    break;
                }
            }
            if (i >= 0 && j >= 0 && num_now[i] == '.') {
                num_now.chop(1);
                dis_data.chop(1);
            }
        }

        // 判断 nan 和 inf
        if (calculator(dis_data).contains("nan") || calculator(dis_data).contains("inf")) {
            this->lab_last->setText("");
            this->lab_prepare->setText("");
            this->lab_now->setText("Error!");

            flag = 0;
            num_now.clear();
            dis_data.clear();
            return ;
        }

        // 1=1不输出
        if(dis_data == calculator(dis_data)) {
            pushHistory.chop(1);
            return ;
        }

        lab_output(calculator(dis_data), lab_now);
        lab_output(dis_data + '=' + calculator(dis_data), lab_last);
        lab_output("", lab_prepare);

        disHistory.push_back(dis_data + '=' + calculator(dis_data) + '\n');

        //输出测试到history.txt
        cout << disHistory[disHistory.size() - 1].toStdString() << endl;

        dis_data = calculator(dis_data);
        num_now.clear();

        // 获取历史记录
        int size = disHistory.size();
        QString historyText = "";
        int hisIndex = (size - 5 >= 0) ? (size - 5) : 0;
        for (int i = hisIndex; i < size; i++) {
            historyText = historyText + disHistory.at(i);
        }

        // 去除末尾换行符
        historyText.chop(1);
        this->lab_last->setText(historyText);

        qDebug() << "historyText" << historyText;

        /*
         *	输出历史记录:
         * 	lab_output(disHistory[要输出的历史记录,
         *  如果是最后一条就是disHistory.size()-1],
         *  要输出的QLabel);
         *
         * 	访问十条历史记录:
         * 	for (int i = disHistory.size()-1, j = 1; i >= 0 || j == 10; i--,j++) {
         * 		disHistory[i];
         * 	}
         */
    }

    QString label = this->pTitleBar->m_pFuncLabel->text();
    if (label != "标准" && label != "科学") {
        unitCalc();
    }
}

void MainWindow::delete_btn_handle(bool)
{
    if(flag == 0) {
        this->lab_now->setText("0");
        this->lab_last->setText("");
        flag = 1;
        dis_data.clear();
        num_now.clear();
        return;
    }

    //结果禁用退格
    if (pushHistory.size() > 0 && pushHistory[pushHistory.size() - 1] == '=') {
        return ;
    }

    //退到头啦
    if (dis_data.isEmpty()) {
        this->lab_now->setText("0");
        this->lab_last->setText("");
        this->lab_prepare->setText("");
        return;
    }
    else if (!dis_data.isEmpty() && num_now.isEmpty()) {
        if (dis_data.size() == 1) {
            this->lab_now->setText("0");
            this->lab_last->setText("");
            this->lab_prepare->setText("");
            dis_data.clear();
            num_now.clear();
            return ;
        }

        dis_data.chop(1);
        if (num_now.size()) {
            num_now.chop(1);
        }
        if (num_now.size()) {
            lab_output(calculator(dis_data),lab_prepare);
        }
        else {
            this->lab_prepare->setText("");
        }
        lab_output(dis_data, lab_now);
    }
    else {
        if (dis_data.size() == 1) {
            this->lab_now->setText("0");
            this->lab_last->setText("");
            this->lab_prepare->setText("");
            dis_data.clear();
            num_now.clear();
            return ;
        }

        num_now.remove(num_now.size() - 1, 1);
        dis_data.remove(dis_data.size() - 1, 1);

        if (num_now.size()) {
            lab_output(calculator(dis_data), lab_prepare);
        }
        else {
            this->lab_prepare->setText("");
        }
        lab_output(dis_data, lab_now);
    }
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

void MainWindow::funcListItemClicked(QListWidgetItem* item)
{
    QString label = item->text().trimmed();
    this->funcListWid->hide();

    if (label != this->pTitleBar->m_pFuncLabel->text()) {
        this->pTitleBar->setFuncLabel(label);

        if (label == "标准" || label == "科学") {

            mainLayout->removeWidget(outputWid);
            mainLayout->removeWidget(buttonWid);

            this->outputWid->close();
            this->buttonWid->close();

            // 换算器选项失去焦点
            for (int i = 0; i < funcList->funcToolWid->count(); i++) {
                funcList->funcToolWid->item(i)->setSelected(false);
            }

            if (label == "标准") {
                setStandardUi();
            }
            else if (label == "科学") {
                setScientificUi();
            }

            changeCalculatorUi();
        }
        else {

            // 计算器选项失去焦点
            for (int i = 0; i < funcList->funcModelWid->count(); i++) {
                funcList->funcModelWid->item(i)->setSelected(false);
            }

            if (label == "汇率") {
                mainLayout->removeWidget(outputWid);
                mainLayout->removeWidget(buttonWid);

                this->outputWid->close();
                this->buttonWid->close();

                setToolUi();
            }

            changeToolUi();
        }
    }
}

void MainWindow::stayTop()
{
    if (winFlags == NULL) {
        winFlags = windowFlags();
        setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
//        this->setWindowFlags(Qt::FramelessWindowHint | Qt::X11BypassWindowManagerHint);
        show();
    }
    else {
        winFlags = NULL;
        this->raise();
        setWindowFlags(Qt::FramelessWindowHint);
        show();
    }
}







