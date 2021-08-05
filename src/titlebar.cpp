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
#include <QStringList>
#include "titlebar.h"
#include "mainwindow.h"
#include "funclist.h"
#include "xatom-helper.h"
#include "InputSymbols.h"
#include "data_warehouse.h"
#include <QColor>
#include <QDesktopWidget>

TitleBar::TitleBar(QWidget *parent) : QWidget(parent)
{
    /* handle intel ui */
    if (DataWarehouse::getInstance()->platform == QString("intel")) {
        createInterUi();
        //createInterStyle();
    } else {
        // 初始化组件
        setWidgetUi();
        // 设置组件样式
        setWidgetStyle();
    }
}

TitleBar::~TitleBar()
{

}

/* intel title ui */
void TitleBar::createInterUi()
{
    this->setFixedHeight(38);
    this->setWindowFlags(Qt::FramelessWindowHint);

    this->STANDARD_LABEL = tr("standard");
    this->SCIENTIFIC_LABEL = tr("scientific");

    this->m_Icon = new QLabel(this);
    this->m_Icon->setFixedSize(QSize(25 , 25));
    this->m_Icon->setPixmap(QIcon::fromTheme("kylin-calculator").pixmap(QSize(24 , 24)));

    this->m_mode = new QPushButton(this);
    QPixmap icon(":/image/intelStandLight/ic-open.svg");
    icon.scaled(24 , 24);
    m_mode->setIcon(QIcon(icon));
    m_mode->setLayoutDirection(Qt::RightToLeft);
    this->m_mode->setText(tr("standard"));
    this->m_mode->setFlat(false);
    this->m_menu = new QMenu();
    this->m_menu->installEventFilter(this);

    standardMode = new QAction(this->m_menu);
    standardMode->setText(tr("standard"));
    standardMode->setCheckable(true);
    standardMode->setChecked(true);
    scientificMode = new QAction(this->m_menu);
    scientificMode->setText(tr("scientific"));
    scientificMode->setCheckable(true);

    this->m_menu->addAction(standardMode);
    this->m_menu->addAction(scientificMode);
    this->m_mode->setMenu(this->m_menu);

    this->m_min = new QPushButton();
    this->m_min->setFixedSize(QSize(30 , 30));
    this->m_min->setIcon(QIcon::fromTheme("window-minimize-symbolic"));
    this->m_min->setIconSize(QSize(16 , 16));
    this->m_min->setProperty("isWindowButton", 0x1);
    this->m_min->setProperty("useIconHighlightEffect", 0x2);
    this->m_min->setFlat(true);

    this->m_max = new QPushButton();
    this->m_max->setFixedSize(QSize(30 , 30));
    this->m_max->setIcon(QIcon::fromTheme("window-maximize-symbolic"));
    this->m_max->setIconSize(QSize(16 , 16));
    this->m_max->setProperty("isWindowButton", 0x1);
    this->m_max->setProperty("useIconHighlightEffect", 0x2);
    this->m_max->setFlat(true);

    this->m_close = new QPushButton();
    this->m_close->setFixedSize(QSize(30 , 30));
    this->m_close->setIcon(QIcon::fromTheme("window-close-symbolic"));
    this->m_close->setIconSize(QSize(16 , 16));
    this->m_close->setProperty("isWindowButton", 0x2);
    this->m_close->setProperty("useIconHighlightEffect", 0x8);
    this->m_close->setFlat(true);

    this->hlayout = new QHBoxLayout();
    this->hlayout->setMargin(0);

    this->hlayout->addSpacing(16);
    this->hlayout->addWidget(this->m_Icon);
    this->hlayout->addSpacing(4);

    this->hlayout->addWidget(this->m_mode);
    this->hlayout->addStretch(0);

    this->hlayout->addWidget(this->m_min);
    this->hlayout->addSpacing(4);

    this->hlayout->addWidget(this->m_max);
    this->hlayout->addSpacing(4);

    this->hlayout->addWidget(this->m_close);
    this->hlayout->addSpacing(4);

    connect(this->m_min , &QPushButton::clicked , this , &TitleBar::onClicked);
    connect(this->m_max , &QPushButton::clicked , this ,&TitleBar::onClicked);
    connect(this->m_close , &QPushButton::clicked , this , &TitleBar::onClicked);
    connect(this->m_menu , &QMenu::triggered , this , &TitleBar::slotModeChange);

    this->setLayout(this->hlayout);

    return;
}

#if 0
void TitleBar::createInterStyle(void)
{
    if (WidgetStyle::themeColor == 0) {
        QPalette pal(this->palette());

        /* 设置背景色 */
        pal.setColor(QPalette::Background, Qt::black);
        this->setAutoFillBackground(true);
        this->setPalette(pal);
    } else if (WidgetStyle::themeColor == 1) {

    }
    return;
}
#endif

void TitleBar::paintEvent(QPaintEvent *event)
{
    if (DataWarehouse::getInstance()->platform == QString("intel")) {
        Q_UNUSED(event);

        QColor color("#EDEDED");
        QPainter p(this);
        p.setPen(Qt::NoPen);
        p.setBrush(QBrush(color));
        p.drawRect(rect());
    }
    return;
}

bool TitleBar::eventFilter(QObject * obj, QEvent *event)
{
    if (DataWarehouse::getInstance()->platform == QString("intel")) {
        if(obj == this->m_menu)
        {
            QPixmap icon;
            if(event->type() == QEvent::Hide)
            {
                icon.load(":/image/intelStandLight/ic-open.svg");
                icon.scaled(24 , 24);
                m_mode->setIcon(QIcon(icon));
            }
            if (event->type() == QEvent::Show) {
                QPoint globalPos = this->m_mode->mapToGlobal(QPoint(0 , 0));
                this->m_menu->move(globalPos.x() , globalPos.y() + this->m_mode->height());
                icon.load(":/image/intelStandLight/ic-close.svg");
                icon.scaled(24 , 24);
                m_mode->setIcon(QIcon(icon));
                return true;
            }

        }

    } else {
        return QObject::eventFilter(obj, event);
    }
        return QObject::eventFilter(obj, event);
}

void TitleBar::slotModeChange(QAction *action)
{
    QString mode = action->text();
    if (mode == tr("standard")) {
        qDebug() << "Info : change mode to standard";
        this->m_mode->setText(tr("standard"));
        this->standardMode->setChecked(true);
        this->scientificMode->setChecked(false);
        emit sigModeChange(QString("standard"));
    } else if (mode == tr("scientific")) {
        qDebug() << "Info : change mode to scientific";
        this->m_mode->setText(tr("scientific"));
        this->standardMode->setChecked(false);
        this->scientificMode->setChecked(true);
        emit sigModeChange(QString("scientific"));
    }

}

void TitleBar::setFuncLabel(QString label)
{
    this->m_pFuncLabel->setText(label);
}

// 初始化组件
void TitleBar::setWidgetUi()
{
    // 窗体透明
    // this->setAttribute(Qt::WA_TranslucentBackground, true);
    this->setFixedHeight(38);

    // 初始化模式或功能名称
    STANDARD_LABEL = tr("Standard");
    SCIENTIFIC_LABEL = tr("Scientific");
    EXCHANGE_RATE_LABEL = tr("Exchange Rate");

    // 按钮初始化
    // funcListButton = new QPushButton(this);
    m_pIconBtn   = new QPushButton(this);
    m_pFuncLabel = new QLabel(this);
    m_pTopButton = new QPushButton(this);
    m_pMinimizeButton = new QPushButton(this);
    m_pMaximizeButton = new QPushButton(this);
    m_pCloseButton = new QPushButton(this);

    // 设置空间大小
    // funcListButton->setFixedSize(30, 30);
    m_pFuncLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_pTopButton->setFixedSize(30, 30);
    m_pMinimizeButton->setFixedSize(30, 30);
    m_pMaximizeButton->setFixedSize(30, 30);
    m_pCloseButton->setFixedSize(30, 30);
    
    // 设置对象名
    m_pFuncLabel->setObjectName("whiteLabel");
    m_pTopButton->setObjectName("topButton");
    m_pMinimizeButton->setObjectName("minimizeButton");
    m_pMaximizeButton->setObjectName("maximizeButton");
    m_pCloseButton->setObjectName("closeButton");

    // 设置悬浮提示
    // funcListButton->setToolTip(tr("FuncList"));
    m_pTopButton->setToolTip(tr("StayTop"));
    m_pMinimizeButton->setToolTip(tr("Minimize"));
    m_pMaximizeButton->setToolTip(tr("Maximize"));
    m_pCloseButton->setToolTip(tr("Close"));

    // 设置图片
    m_pIconBtn->setIconSize(QSize(24, 24));
    m_pIconBtn->setIcon(QIcon::fromTheme("kylin-calculator"));

    // funcListButton->setIcon(QIcon::fromTheme("open-menu-symbolic"));
    // funcListButton->setIconSize(QSize(16, 16));
    // funcListButton->setProperty("isWindowButton", 0x1);
    // funcListButton->setProperty("useIconHighlightEffect", 0x2);
    // funcListButton->setFlat(true);

    m_pTopButton->setIcon(QIcon::fromTheme("ukui-unfixed"));
    m_pTopButton->setIconSize(QSize(16, 16));
    m_pTopButton->setProperty("isWindowButton", 0x1);
    m_pTopButton->setProperty("useIconHighlightEffect", 0x2);
    m_pTopButton->setFlat(true);

    m_pMinimizeButton->setIcon(QIcon::fromTheme("window-minimize-symbolic"));
    m_pMinimizeButton->setIconSize(QSize(16, 16));
    m_pMinimizeButton->setProperty("isWindowButton", 0x1);
    m_pMinimizeButton->setProperty("useIconHighlightEffect", 0x2);
    m_pMinimizeButton->setFlat(true);

    m_pMaximizeButton->setIcon(QIcon::fromTheme("window-maximize-symbolic"));
    m_pMaximizeButton->setIconSize(QSize(16, 16));
    m_pMaximizeButton->setProperty("isWindowButton", 0x1);
    m_pMaximizeButton->setProperty("useIconHighlightEffect", 0x2);
    m_pMaximizeButton->setFlat(true);


    m_pCloseButton->setIcon(QIcon::fromTheme("window-close-symbolic"));
    m_pCloseButton->setIconSize (QSize(16, 16));
    m_pCloseButton->setProperty("isWindowButton", 0x2);
    m_pCloseButton->setProperty("useIconHighlightEffect", 0x8);
    m_pCloseButton->setFlat(true);

    menuBar = new menuModule(this);
    
    // m_pMenuButton = new QToolButton(this);
    // m_pMenuButton->setIcon(QIcon::fromTheme("open-menu-symbolic"));
    // m_pMenuButton->setFixedSize(30, 30);
    // m_pMenuButton->setIconSize(QSize(16, 16));
    // m_pMenuButton->setProperty("isWindowButton", 0x1);
    // m_pMenuButton->setProperty("useIconHighlightEffect", 0x2);
    // m_pMenuButton->setAutoRaise(true);

    // QVBoxLayout *menuLayout = new QVBoxLayout(m_pMenuButton);
    // menuLayout->addWidget(menuBar->menuButton);
    // menuLayout->setMargin(0);
    // menuLayout->setSpacing(0);

    // 设置按钮布局
    QHBoxLayout *pLayout = new QHBoxLayout(this);
    pLayout->setContentsMargins(4, 4, 4, 4);
    pLayout->setSpacing(0);
    // 这里是有问题的 应该是pLayout->addSpacing(4);但是还不知道是哪里的问题
    pLayout->addSpacing(2);
    pLayout->addWidget(m_pIconBtn);
    pLayout->addSpacing(8);
    pLayout->addWidget(m_pFuncLabel);
    pLayout->addStretch();
    pLayout->addWidget(m_pTopButton);
    pLayout->addSpacing(4);
    pLayout->addWidget(menuBar->menuButton);
    pLayout->addSpacing(4);
    pLayout->addWidget(m_pMinimizeButton);
    pLayout->addSpacing(4);
    pLayout->addWidget(m_pMaximizeButton);
    pLayout->addSpacing(4);
    pLayout->addWidget(m_pCloseButton);
    

    this->setLayout(pLayout);

    // 设置信号和槽函数
    // connect(m_pTopButton,      SIGNAL(clicked(bool)), this, SLOT(onClicked()));
    connect(m_pMinimizeButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
    connect(m_pMaximizeButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
    connect(m_pCloseButton,    SIGNAL(clicked(bool)), this, SLOT(onClicked()));
    // connect(funcListButton,    SIGNAL(clicked(bool)), this, SLOT(onClicked()));

    // connect(m_pMenuButton,    SIGNAL(clicked(bool)), this, SLOT(menuClicked()));

    // m_pTopButton->hide();
    // funcListButton->hide();
    // m_pMenuButton->hide();
    // menuBar->menuButton->hide();
}

// 设置组件样式
void TitleBar::setWidgetStyle()
{
    // 设置按钮样式
    // 设置图片
    // m_pIconBtn->setIcon(QIcon::fromTheme("calc"));
    // funcListButton->setIcon(QIcon::fromTheme("open-menu-symbolic"));
    // m_pTopButton->setIcon(QIcon::fromTheme("ukui-unfixed-symbolic"));
    // m_pMinimizeButton->setIcon(QIcon::fromTheme("window-minimize-symbolic"));
    // m_pCloseButton->setIcon(QIcon::fromTheme("window-close-symbolic"));

    if (WidgetStyle::themeColor == 0) {
        m_pFuncLabel->setStyleSheet("color:#000000;font-size:14px;");
        QString btnStyle = "QPushButton{border:0px;border-radius:4px;background:transparent;}"
                           "QPushButton:Hover{border:0px;border-radius:4px;background:transparent;}"
                           "QPushButton:Pressed{border:0px;border-radius:4px;background:transparent;}";
        m_pIconBtn->setStyleSheet(btnStyle);
    }
    else if (WidgetStyle::themeColor == 1) {
        m_pFuncLabel->setStyleSheet("color:#A6A6A6;font-size:14px;");
        QString btnStyle = "QPushButton{border:0px;border-radius:4px;background:transparent;}"
                           "QPushButton:Hover{border:0px;border-radius:4px;background:transparent;}"
                           "QPushButton:Pressed{border:0px;border-radius:4px;background:transparent;}";
        m_pIconBtn->setStyleSheet(btnStyle);
        // funcListButton->setStyleSheet(btnStyle);
        // m_pTopButton->setStyleSheet(btnStyle);
        // m_pMinimizeButton->setStyleSheet(btnStyle);
        // m_pCloseButton->setStyleSheet(btnStyle);
        // m_pCloseButton->setStyleSheet("QPushButton{border:0px;border-radius:4px;background:transparent;}"
        //                               "QPushButton:Hover{border:0px;border-radius:4px;background:transparent;background-color:#F86457;}"
        //                               "QPushButton:Pressed{border:0px;border-radius:4px;background:transparent;background-color:#E44C50;}");

        // m_pTopButton->setProperty("setIconHighlightEffectDefaultColor", QColor(Qt::white));

    }
}

// 菜单按钮点击事件
// void TitleBar::menuClicked()
// {
//     menuBar->menuButton->click();
// }

// 双击标题栏进行界面的最大化/还原
//void TitleBar::mouseDoubleClickEvent(QMouseEvent *event)
//{
//    Q_UNUSED(event);

//    emit m_pMaximizeButton->clicked();
//}

#ifdef __V10__
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
#endif

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
        // else if (pButton == m_pTopButton)
        // {
//            pWindow->parentWidget()->parentWidget()->parentWidget()->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
//            pWindow->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
        // }

        else if (pButton == m_pCloseButton)
        {
            // this->menuBar->aboutWindow->close();
            pWindow->close();
        }
//         else if (pButton == funcListButton)
//         {
// //            qDebug() << "funcListButton";
//             emit iconButtonSignal();
//         }
        else if (pButton == this->m_min) {
            pWindow->showMinimized();
            m_min->update();
            m_close->update();
        }
        else if(pButton == this->m_max)
        {
            if (DataWarehouse::getInstance()->winFlag == QString("min")) {
                DataWarehouse::getInstance()->winFlag = QString("max");
            } else if (DataWarehouse::getInstance()->winFlag == QString("max")) {
                DataWarehouse::getInstance()->winFlag = QString("min");
            }

            if(DataWarehouse::getInstance()->winFlag == QString("min")){
                pWindow->showNormal();
                pWindow->resize(1200,625);
                pWindow->move(m_start.x(),m_start.y());
                this->m_max->setIcon(QIcon::fromTheme("window-maximize-symbolic"));
//                if(m_mode->text() == STANDARD_LABEL)
//                {
//                    //animation->setEndValue(QRect(m_start.x(), m_start.y(), 432, 628));
//                  //animation->start();
//                    pWindow->resize(400,510);
//                    pWindow->move(m_start.x(),m_start.y());

//                }
//                else if(m_mode->text() == SCIENTIFIC_LABEL)
//                {
//                    //animation->setEndValue(QRect(m_start.x(), m_start.y(), 864, 628));
//                    //animation->start();
//                    pWindow->resize(1200,625);
//                    qDebug() << DataWarehouse::getInstance()->winFlag;
//                    qDebug() << "w: " << pWindow->width();
//                    pWindow->move(m_start.x(),m_start.y());

//                }
//                else if(m_mode->text() == EXCHANGE_RATE_LABEL)
//                {
//                    //animation->setEndValue(QRect(m_start.x(), m_start.y(), 432, 628));
//                    //animation->start();
//                    pWindow->resize(432,628);
//                    pWindow->move(m_start.x(),m_start.y());
//                }
            }
            else
            {
                m_start =  pWindow->pos();
                pWindow->showMaximized();
                this->m_max->setIcon(QIcon::fromTheme("window-restore-symbolic"));

//                QRect screenRect = QApplication::desktop()->availableGeometry();
//                animation->setEndValue(QRect(0, 0, screenRect.width(), screenRect.height()));
//                animation->start();

            }
            emit sigFontUpdate();
        }

        else if(pButton == m_pMaximizeButton) {

//            QPropertyAnimation *animation = new QPropertyAnimation(pWindow, "geometry");
//            //animation->setEasingCurve(QEasingCurve :: OutBounce);
//            animation->setDuration(10000);



            if (DataWarehouse::getInstance()->winFlag == QString("min")) {
                DataWarehouse::getInstance()->winFlag = QString("max");
            } else if (DataWarehouse::getInstance()->winFlag == QString("max")) {
                DataWarehouse::getInstance()->winFlag = QString("min");
            }

            if(DataWarehouse::getInstance()->winFlag == QString("min")){
                pWindow->showNormal();
                if(m_pFuncLabel->text() == STANDARD_LABEL)
                {
//                    animation->setEndValue(QRect(m_start.x(), m_start.y(), 432, 628));
//                    animation->start();
                    pWindow->resize(432,628);
                    pWindow->move(m_start.x(),m_start.y());

                }
                else if(m_pFuncLabel->text() == SCIENTIFIC_LABEL)
                {
//                    animation->setEndValue(QRect(m_start.x(), m_start.y(), 864, 628));
//                    animation->start();
                    pWindow->resize(864,628);
                    pWindow->move(m_start.x(),m_start.y());

                }
                else if(m_pFuncLabel->text() == EXCHANGE_RATE_LABEL)
                {
//                    animation->setEndValue(QRect(m_start.x(), m_start.y(), 432, 628));
//                    animation->start();
                    pWindow->resize(432,628);
                    pWindow->move(m_start.x(),m_start.y());
                }
            }
            else
            {
                m_start =  pWindow->pos();
                pWindow->showMaximized();

//                QRect screenRect = QApplication::desktop()->availableGeometry();
//                animation->setEndValue(QRect(0, 0, screenRect.width(), screenRect.height()));
//                animation->start();

            }
            emit sigFontUpdate();

        }

        else if (pButton == this->m_close) {
            pWindow->close();
        }
    }
}

// void TitleBar::stayTop()
// {
//    this->parentWidget()->parentWidget()->parentWidget()->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
// }

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
