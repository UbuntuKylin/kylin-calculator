#ifndef TOOLMODEL_H
#define TOOLMODEL_H

#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFont>
#include <QLabel>
#include <QWidget>
#include <QListWidget>
#include <QKeyEvent>

// 换算器输入输出界面
class ToolModelOutput : public QWidget
{
    Q_OBJECT

public:
    explicit ToolModelOutput(QWidget *parent = 0);
    ~ToolModelOutput() {}

    // 汇率更新
    QLabel *toolLabUpdate;
    QLabel *toolIconUpdate;
    QLabel *toolLabRate;
    double  toolDouRate;

    QVBoxLayout *toolUpdateLayout;
    QWidget *toolUpdateWid;

    // 单位标识
    QLabel *toolLabUnitBef;
    QLabel *toolLabIconBef;

    QLabel *toolLabUnitAft;
    QLabel *toolLabIconAft;

    QHBoxLayout *toolUnitBefLayout;
    QHBoxLayout *toolUnitAftLayout;

    QWidget *toolUnitBefWid;
    QWidget *toolUnitAftWid;

    // 换算历史
    QLabel *toolLabHis;
    // 换算前
    QLabel *toolLabBef;
    // 换算后
    QLabel *toolLabAft;

    // 换算前的单位列表
    QListWidget *unitListBef;
    // 换算后的单位列表
    QListWidget *unitListAft;

    // 初始化单位列表
    void initUnitList(QString listStr);

    // 单位换算函数
    void unitConversion();
};

// 换算器按钮界面
class ToolModelButton : public QWidget
{
    Q_OBJECT

public:
    explicit ToolModelButton(QWidget *parent = 0);

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

public slots:
    // 键盘响应事件
    void keyPressEvent(QKeyEvent *event);
};

// 换算器单位列表界面
class UnitListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UnitListWidget(QWidget *parent = 0);

};

#endif // TOOLMODEL_H
