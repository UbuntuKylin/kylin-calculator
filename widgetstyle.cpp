#include "widgetstyle.h"
#include <QPainterPath>

//WidgetStyle::WidgetStyle(QWidget *parent)
//{
//    handleIconClickedSub(); //在屏幕中央显示
//    mystyle();
//}

//void WidgetStyle::handleIconClickedSub()    //在屏幕中央显示
//{
//    QRect availableGeometry = qApp->primaryScreen()->availableGeometry();
//    this->move((availableGeometry.width() - this->width())/2, (availableGeometry.height() - this->height())/2);
//}

//void WidgetStyle::isDiaLog(int w, int h, QString titleText)
//{
//    this->setFixedSize(w + SHADOW*2, h + SHADOW*2);
//    icon->hide();
//    text->setText(titleText);
//    text->setStyleSheet("color:#1B1B1B;font-weight:bold;");
//}

//void WidgetStyle::WidgetStyleClose()
//{
//    this->close();
//}

//void WidgetStyle::mystyle()
//{
//    font.setFamily(QFontDatabase::applicationFontFamilies(QFontDatabase::addApplicationFont(":/data/data/PingFang-Jian-ChangGuiTi-2.ttf")).at(0));//读取字体

//    //窗口设置
//    this->setWindowFlags(Qt::FramelessWindowHint);//无边框
//    this->setFixedSize(WINDOWW + SHADOW*2, WINDOWH + SHADOW*2);
//    this->setAttribute(Qt::WA_TranslucentBackground, true);//窗体透明


    //控件
//    title = new QWidget;    //标题栏
//    title->setMaximumHeight(TITLEH);
//    title->setMinimumHeight(TITLEH);
//    title->setObjectName("title");

//    body = new QWidget; //窗体

//    icon = new QLabel;  //图标
//    icon->setPixmap(QPixmap::fromImage(QImage(":/data/data/icon.png")));

//    text = new QLabel;  //标题
//    text->setText(tr("麒麟U盘启动器"));

//    widgetMin =new QPushButton;//最小化按钮
//    widgetMin->setObjectName("widgetMin");
//    widgetMin->setIconSize(QSize(30,30));
//    widgetMin ->setIcon(QIcon(":/data/data/min_d.png"));
//    widgetMin->setMaximumSize(30,30);
//    widgetMin->setMinimumSize(30,30);
//    connect(widgetMin,&QPushButton::clicked,this,[=]{this->setWindowState(Qt::WindowMinimized);});

//    widgetClose =new QPushButton;//关闭按钮
//    widgetClose->setObjectName("widgetClose");
//    widgetClose->setIconSize(QSize(30,30));
//    widgetClose->setIcon(QIcon(":/data/data/close_d.png"));
//    widgetClose->setMaximumSize(30,30);
//    widgetClose->setMinimumSize(30,30);
//    connect(widgetClose,&QPushButton::clicked,this,&WidgetStyle::WidgetStyleClose);

//    //布局
//    QHBoxLayout *hlt=new QHBoxLayout;//水平布局
//    hlt->setMargin(0);//控件间距
//    hlt->setSpacing(0);//控件间距
//    hlt->addSpacing(WIDGETRADIUS);
//    hlt->addWidget(icon,1);
//    hlt->addSpacing(5);
//    hlt->addWidget(text,1);
//    hlt->addStretch(99);
//    hlt->addWidget(widgetMin,1);
//    hlt->addSpacing(4);
//    hlt->addWidget(widgetClose,1);
//    hlt->addSpacing(4);
//    title->setLayout(hlt);
//    QHBoxLayout *hlt2=new QHBoxLayout;//标题栏
//    hlt2->setMargin(0);
//    hlt2->setSpacing(0);
//    hlt2->addSpacing(SHADOW+1);
//    hlt2->addWidget(title);
//    hlt2->addSpacing(SHADOW+1);
//    QHBoxLayout *hlt3=new QHBoxLayout;//窗体
//    hlt3->setMargin(0);
//    hlt3->setSpacing(0);
//    hlt3->addSpacing(SHADOW+1);
//    hlt3->addWidget(body);
//    hlt3->addSpacing(SHADOW+1);
//    QVBoxLayout *vl=new QVBoxLayout;//垂直布局
//    vl->setMargin(0);
//    vl->setSpacing(0);
//    vl->addSpacing(SHADOW);
//    vl->addLayout(hlt2,1);
//    vl->addLayout(hlt3,99);
//    vl->addSpacing(SHADOW+3);
//    this->setLayout(vl);

    //样式表stylesheet//测试用border:1px solid red;
//    this->setStyleSheet(".QPushButton{background-color:rgba(100,105,241,1);border-radius:"+QString::number(BUTTONRADIUS)+"px;}"
//                        ".QPushButton:hover{background-color:rgba(136,140,255,1);}"
//                        ".QPushButton:pressed{background-color:rgba(82,87,217,1);}");
//    title->setStyleSheet("WidgetStyle #title{background-color:rgba(255,255,255,0.7);border-top-left-radius:"
//                         +QString::number(WIDGETRADIUS)+"px;border-top-right-radius:"+QString::number(WIDGETRADIUS)+"px;}");//圆角
//    icon->setStyleSheet("background-color:rgba(255,255,255,0);");
//    text->setStyleSheet("background-color:rgba(255,255,255,0);color:#303133");
//    body->setStyleSheet("background-color:rgba(255,255,255,1)");
//    widgetMin->setStyleSheet("WidgetStyle #widgetMin{background-color:rgba(255,255,255,0);}"
//                             "WidgetStyle #widgetMin:hover{background-color:rgba(100,105,241,1);}"
//                             "WidgetStyle #widgetMin:pressed{background-color:rgba(82,87,217,1);}");
//    widgetClose->setStyleSheet("WidgetStyle #widgetClose{background-color:rgba(255,255,255,0);}"
//                               "WidgetStyle #widgetClose:hover{background-color:rgba(240,64,52,1);}"
//                               "WidgetStyle #widgetClose:pressed{background-color:rgba(215,51,53,1);}");
//}

void WidgetStyle::paintEvent(QPaintEvent *event)    //重绘窗口
{
    //设置字体字号
    QFont ft = font;
    ft.setPixelSize(14);
    text->setFont(ft);

    //上半部分阴影
    QPainterPath painterPath;
    painterPath.setFillRule(Qt::WindingFill);       //设置填充方式
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillPath(painterPath, QBrush(Qt::white));
    //下半部分阴影
    QPainterPath painterPath2;
    painterPath2.setFillRule(Qt::WindingFill);

    QColor color(0, 0, 0);
    for(int i=0; i<SHADOW; i++)
    {
        int alpha=SHADOWALPHA*255/4;
        color.setAlpha(alpha - (alpha/SHADOW)*(i+1));
        painter.setPen(color);

        QRect rec(SHADOW-i,SHADOW-i,this->width()-(SHADOW-i)*2,TITLEH+WIDGETRADIUS*2 );
        painterPath.addRoundedRect(rec,WIDGETRADIUS,WIDGETRADIUS);
        painter.setClipRegion(QRegion(0,0,this->width(),TITLEH+WIDGETRADIUS)); //裁剪区域（标题栏）
        painter.drawPath(painterPath);

        QRect rec2(rec.left(),rec.top()+TITLEH,this->width()-(SHADOW-i)*2,this->height()-TITLEH-WIDGETRADIUS);
        painterPath2.addRect(rec2);
        painter.setClipRegion(QRegion(0,TITLEH+WIDGETRADIUS,this->width(),this->height())); //裁剪区域（窗体）
        painter.drawPath(painterPath2);
    }

    QWidget::paintEvent(event);
}
