#ifndef TITLE_BAR
#define TITLE_BAR

#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>

#include "funclist.h"

class QLabel;
class QPushButton;

class TitleBar : public QWidget
{
    Q_OBJECT

public:
    explicit TitleBar(QWidget *parent = 0);
    ~TitleBar();

    FuncList *funcList;
    QLabel *m_pFuncLabel;           // 界面标识
    QPushButton *m_pTopButton;      // 界面置顶按钮

    // 模式和功能列表按钮
    QPushButton *funcListButton;

    // 设置模式或功能名称
    void setFuncLabel(QString label);

protected:

    // 进行鼠标界面的拖动
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

signals:
    void iconButtonSignal();

private slots:

    // 进行置顶、最小化、关闭操作
    void onClicked();

    // 窗口置顶操作
    void stayTop();

private:

    // 最大化/还原
//    void updateMaximize();

private:

    QPushButton *m_pMinimizeButton; // 最小化按钮
    QPushButton *m_pCloseButton;    // 关闭按钮

    QPoint m_start;                 // 起始点
    QPoint m_end;                   // 结束点
    bool m_leftButtonPressed;       // 鼠标左键按下标记
};

#endif // TITLE_BAR
