#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFont>
#include <QLabel>
#include <QWidget>
#include <QListWidget>
#include <QStackedWidget>
#include <QRegExp>

#include "titlebar.h"
#include "widgetstyle.h"
#include "funclist.h"
#include "standardmodel.h"
#include "scientificmodel.h"
#include "toolmodel.h"

//class TitleBar;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // 公有组件，即标题栏和功能列表
    void setCommonUi();

    // 计算器输出窗口组件
    void setOutputUi();

    // 标准计算界面布局
    void setStandardUi();

    // 科学计算界面布局
    void setScientificUi();

    // 换算器界面布局
    void setToolUi();

    // 计算器界面切换布局
    void changeCalculatorUi();

    // 换算器界面切换布局
    void changeToolUi();

    void set_ui();

    // 显示输出
    void lab_output(QString s,QLabel *l);

    // 添加千分位
    QString addComma(QString s);

    // 换算器输入响应事件
    void unitCalc();

public slots:
    // 键盘响应事件
    void keyPressEvent(QKeyEvent *event);

    // 处理按钮点击事件
    void btn_handler(bool);

    // del按钮点击事件
    void delete_btn_handle(bool);

    // 功能列表按钮点击事件
    void funcListHandle(bool);

    // 功能列表项点击事件
    void funcListItemClicked(QListWidgetItem*);

    // 窗口置顶按钮点击事件
    void stayTop();

private:

    Qt::WindowFlags winFlags;

    QLabel *lab_last;
    QLabel *lab_now;
    QLabel *lab_prepare;

    QStackedWidget *stackedModelWid;
    QStackedWidget *stackedToolWod;

    QPushButton *btnNum[10];
    QPushButton *btnClear;
    QPushButton *btnDiv;
    QPushButton *btnMulti;
    QPushButton *btnDelete;
    QPushButton *btnSub;
    QPushButton *btnAdd;
    QPushButton *btnEqual;
    QPushButton *btnPer;
    QPushButton *btnPoint;

    // 整体界面布局
    QVBoxLayout *mainLayout;

    QWidget *mainWid;
    QWidget *titleBarWid;
    QWidget *outputWid;
    QWidget *buttonWid;
    QWidget *funcListWid;

    TitleBar *pTitleBar;
    FuncList *funcList;

    StandardOutput *standardOutput;
    StandardModel  *standardModel;

    ScientificOutput *scientificOutput;
    ScientificModel  *scientificModel;

    ToolModelOutput *toolModelOutput;
    ToolModelButton *toolModelButton;

//    QListWidget *funcListWid;

    QString dis_data;
    QString result;
    QString num_now;

    //异常状态标志位,输入有误时置0 按'C'取消
    int flag = 1;

    // 记录键入历史记录
    QString pushHistory;

    // 记录计算历史记录,输入'='时触发
    QVector<QString> disHistory;

    // 重绘窗口
    void paintEvent(QPaintEvent *event);
};

#endif // MAINWINDOW_H
