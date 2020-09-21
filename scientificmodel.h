#ifndef SCIENTIFICMODEL_H
#define SCIENTIFICMODEL_H

#include <QLabel>
#include <QWidget>
#include <QListWidget>
#include <QKeyEvent>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFont>
#include <QColor>
#include <QDebug>

class ScientificOutput : public QWidget
{
    Q_OBJECT

public:
    explicit ScientificOutput(QWidget *parent = 0);
    ~ScientificOutput() {}

    // 显示输出组件
    QLabel *sciLabLastL;
    QLabel *sciLabLastR;
    QLabel *sciLabPre;
    QLabel *sciLabNow;

    // 输出界面布局
    QHBoxLayout *sciOutputLayout;

};


class ScientificModel : public QWidget
{
    Q_OBJECT

public:
    explicit ScientificModel(QWidget *parent = 0);

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

    QPushButton *btnInd;
    QPushButton *btnUndo;
    QPushButton *btnBracketLeft;
    QPushButton *btnBracketRight;

    QPushButton *btnReci;
    QPushButton *btnXPower2;
    QPushButton *btnXPower3;
    QPushButton *btnYPowerX;

    QPushButton *btnFac;
    QPushButton *btnXSquare2;
    QPushButton *btnXSquare3;
    QPushButton *btnYSquareX;

    QPushButton *btnSin;
    QPushButton *btnCos;
    QPushButton *btnTan;
    QPushButton *btnLog;

    QPushButton *btnRad;
    QPushButton *btnPi;
    QPushButton *btnExp;
    QPushButton *btnLn;

//    QPushButton *XPower2Button;
//    QPushButton *PowerButton;
//    QPushButton *SinButton;
//    QPushButton *CosButton;
//    QPushButton *TanButton;
//    QPushButton *SinhButton;
//    QPushButton *CoshButton;
//    QPushButton *TanhButton;
//    QPushButton *XPower3Button;
//    QPushButton *YSquareRootButton;
//    QPushButton *InvsinButton;
//    QPushButton *InvcosButton;
//    QPushButton *InvtanButton;
//    QPushButton *InvsinhButton;
//    QPushButton *InvcoshButton;
//    QPushButton *InvtanhButton;
//    QPushButton *SquareRootButton;
//    QPushButton *PowerOf10Button;
//    QPushButton *LogBase10Button;
//    QPushButton *ExpButton;
//    QPushButton *ModButton;

//    QPushButton *InvertButton;
//    QPushButton *PowerOfEButton;
//    QPushButton *LogBaseEButton;

//    QPushButton *PiButton;

public slots:
    // 键盘响应事件
    void keyPressEvent(QKeyEvent *event);
};

#endif // SCIENTIFICMODEL_H
