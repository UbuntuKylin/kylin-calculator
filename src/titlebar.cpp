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

#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QEvent>
#include <QMouseEvent>
#include <QApplication>
#include "titlebar.h"
#include "mainwindow.h"
#include "funclist.h"

TitleBar::TitleBar(QWidget *parent)
    : QWidget(parent)
{
    // 初始化组件
    setWidgetUi();

    // 设置组件样式
    setWidgetStyle();
}

TitleBar::~TitleBar()
{

}

void TitleBar::setFuncLabel(QString label)
{
    this->m_pFuncLabel->setText(label);
}

// 初始化组件
void TitleBar::setWidgetUi()
{
    this->setFixedHeight(38);

    // 按钮初始化
    funcListButton = new QPushButton(this);
    m_pIconLabel = new QLabel(this);
    m_pFuncLabel = new QLabel(this);
    m_pTopButton = new QPushButton(this);
    m_pMinimizeButton = new QPushButton(this);
    m_pCloseButton = new QPushButton(this);

    // 设置空间大小
    funcListButton->setFixedSize(30, 30);
    m_pFuncLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_pTopButton->setFixedSize(30, 30);
    m_pMinimizeButton->setFixedSize(30, 30);
    m_pCloseButton->setFixedSize(30, 30);

    // 设置对象名
    m_pFuncLabel->setObjectName("whiteLabel");
    m_pTopButton->setObjectName("topButton");
    m_pMinimizeButton->setObjectName("minimizeButton");
    m_pCloseButton->setObjectName("closeButton");

    // 设置悬浮提示
    //    m_pMinimizeButton->setToolTip("Minimize");
    //    m_pMaximizeButton->setToolTip("Maximize");
    //    m_pCloseButton->setToolTip("Close");

    // 设置图片
    m_pIconLabel->setStyleSheet("width:30px;height:30px;border-image:url(/usr/share/icons/ukui-icon-theme-default/32x32/apps/calc.png)");
//    funcListButton->setIcon(QIcon(":/image/funclist.png"));
//    m_pTopButton->setIcon(QIcon(":/image/top.png"));
//    m_pMinimizeButton->setIcon(QIcon(":/image/min.png"));
//    m_pCloseButton->setIcon(QIcon(":/image/close.png"));
    m_pIconLabel->setFixedSize(30, 30);
//    m_pMinimizeButton->setIconSize(QSize(25, 25));
//    m_pTopButton->setIconSize(QSize(18, 18));

    funcListButton->setIcon(QIcon::fromTheme("application-menu"));
    funcListButton->setProperty("useIconHighlightEffect", true);
    funcListButton->setProperty("iconHighlightEffectMode", 1);
    funcListButton->setProperty("isWindowButton", 0x1);
    funcListButton->setProperty("useIconHighlightEffect", 0x2);
    funcListButton->setFlat(true);
    funcListButton->update();

    m_pTopButton->setIcon(QIcon::fromTheme("color-select-symbolic"));
    m_pTopButton->setProperty("useIconHighlightEffect", true);
    m_pTopButton->setProperty("iconHighlightEffectMode", 1);
    m_pTopButton->setProperty("isWindowButton", 0x1);
    m_pTopButton->setProperty("useIconHighlightEffect", 0x2);
    m_pTopButton->setFlat(true);
    m_pTopButton->update();

    m_pMinimizeButton->setIcon(QIcon::fromTheme("window-minimize-symbolic"));
    m_pMinimizeButton->setProperty("useIconHighlightEffect", true);
    m_pMinimizeButton->setProperty("iconHighlightEffectMode", 1);
    m_pMinimizeButton->setProperty("isWindowButton", 0x1);
    m_pMinimizeButton->setProperty("useIconHighlightEffect", 0x2);
    m_pMinimizeButton->setFlat(true);
    m_pMinimizeButton->update();

    m_pCloseButton->setIcon(QIcon::fromTheme("window-close-symbolic"));
    m_pCloseButton->setProperty("useIconHighlightEffect", true);
    m_pCloseButton->setProperty("iconHighlightEffectMode", 1);
    m_pCloseButton->setProperty("isWindowButton", 0x2);
    m_pCloseButton->setProperty("useIconHighlightEffect", 0x8);
    m_pCloseButton->setFlat(true);
    m_pCloseButton->update();

    // 设置按钮布局
    QHBoxLayout *pLayout = new QHBoxLayout(this);
    pLayout->addWidget(m_pIconLabel);
    pLayout->addWidget(funcListButton);
    pLayout->addSpacing(5);
    pLayout->addWidget(m_pFuncLabel);
    pLayout->addWidget(m_pTopButton);
    pLayout->addWidget(m_pMinimizeButton);
    pLayout->addWidget(m_pCloseButton);
    pLayout->setSpacing(0);
    pLayout->setContentsMargins(5, 0, 5, 0);

    this->setLayout(pLayout);

    // 设置信号和槽函数
    connect(m_pTopButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
    connect(m_pMinimizeButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
    connect(m_pCloseButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
    connect(funcListButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));

//    m_pTopButton->hide();
//    funcListButton->hide();
}

// 设置组件样式
void TitleBar::setWidgetStyle()
{
    // 设置按钮样式
    m_pFuncLabel->setStyleSheet("color:#A6A6A6;font-size:14px;font-family:SourceHanSansCN-Regular;");
    QString btnStyle = "QPushButton{border-radius:4px;}"
                       "QPushButton:hover{background-color:rgb(180,180,180);}"
                       "QPushButton:pressed{background-color:rgb(180,180,180);}";
//    funcListButton->setStyleSheet(btnStyle);
//    m_pTopButton->setStyleSheet(btnStyle);
//    m_pMinimizeButton->setStyleSheet(btnStyle);
//    m_pCloseButton->setStyleSheet(btnStyle);
//    m_pCloseButton->setStyleSheet("QPushButton{border-radius:4px;}QPushButton:hover{background-color:red;}");

}

// 双击标题栏进行界面的最大化/还原
//void TitleBar::mouseDoubleClickEvent(QMouseEvent *event)
//{
//    Q_UNUSED(event);

//    emit m_pMaximizeButton->clicked();
//}

// 拖动鼠标拖动界面
void TitleBar::mousePressEvent(QMouseEvent *event)
{
    // 鼠标左键按下事件
    if (event->button() == Qt::LeftButton) {
        // 记录鼠标左键状态
        m_leftButtonPressed = true;
        //记录鼠标在屏幕中的位置
        m_start = event->globalPos();
    }
}


void TitleBar::mouseMoveEvent(QMouseEvent *event)
{
    // 持续按住才做对应事件
    if(m_leftButtonPressed) {
        //将父窗体移动到父窗体原来的位置加上鼠标移动的位置：event->globalPos()-m_start
        parentWidget()->parentWidget()->parentWidget()->
                move(parentWidget()->parentWidget()->parentWidget()->
                     geometry().topLeft() + event->globalPos() - m_start);
        //将鼠标在屏幕中的位置替换为新的位置
        m_start = event->globalPos();
    }
}

void TitleBar::mouseReleaseEvent(QMouseEvent *event)
{
    // 鼠标左键释放
    if (event->button() == Qt::LeftButton) {
        // 记录鼠标状态
        m_leftButtonPressed = false;
    }
}

void TitleBar::onClicked()
{
    QPushButton *pButton = qobject_cast<QPushButton *>(sender());
    QWidget *pWindow = this->window();
    if (pWindow->isTopLevel())
    {
        if (pButton == m_pMinimizeButton)
        {
            pWindow->showMinimized();
            m_pMinimizeButton->update();
            m_pCloseButton->update();
        }
        else if (pButton == m_pTopButton)
        {
//            pWindow->parentWidget()->parentWidget()->parentWidget()->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
//            pWindow->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
        }

        else if (pButton == m_pCloseButton)
        {
            pWindow->close();
        }
        else if (pButton == funcListButton)
        {
//            qDebug() << "funcListButton";
            emit iconButtonSignal();
        }
    }
}

void TitleBar::stayTop()
{
//    this->parentWidget()->parentWidget()->parentWidget()->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
}

//void TitleBar::updateMaximize()
//{
//    QWidget *pWindow = this->window();
//    if (pWindow->isTopLevel())
//    {
//        bool bMaximize = pWindow->isMaximized();
//        if (bMaximize)
//        {
////            m_pMaximizeButton->setToolTip(tr("Restore"));
//            m_pMaximizeButton->setProperty("maximizeProperty", "restore");
//        }
//        else
//        {
//            m_pMaximizeButton->setProperty("maximizeProperty", "maximize");
////            m_pMaximizeButton->setToolTip(tr("Maximize"));
//        }

//        m_pMaximizeButton->setStyle(QApplication::style());
//    }
//}
