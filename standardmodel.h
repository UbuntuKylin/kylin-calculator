#ifndef STANDARDMODEL_H
#define STANDARDMODEL_H

#include <QKeyEvent>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFont>
#include <QLabel>
#include <QWidget>
#include <QListWidget>
#include <QDebug>

class StandardOutput : public QWidget
{
    Q_OBJECT

public:
    explicit StandardOutput(QWidget *parent = 0);
    ~StandardOutput() {}

    // 显示输出组件
    QLabel *staLabLast;
    QLabel *staLabNow;
    QLabel *staLabPre;
};


class StandardModel : public QWidget
{
    Q_OBJECT

public:
    explicit StandardModel(QWidget *parent = 0);

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

#endif // STANDARDMODEL_H
