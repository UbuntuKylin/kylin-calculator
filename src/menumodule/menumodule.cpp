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

#include <QTime>

#include "menumodule.h"
#include "xatom-helper.h"

menuModule::menuModule(QWidget *parent = nullptr) : QWidget(parent)
{
    init();
}

void menuModule::init()
{
    initAction();
    setStyle();
}

void menuModule::initAction()
{
    // aboutWindow = new QWidget();
    titleText = new QLabel();
    bodyAppName = new QLabel();
    bodyAppVersion = new QLabel();
    bodySupport = new QLabel();

    iconSize = QSize(30,30);
    menuButton = new QToolButton(this);
    menuButton->setToolTip(tr("Menu"));
    menuButton->setProperty("isWindowButton", 0x1);
    menuButton->setProperty("useIconHighlightEffect", 0x2);
    menuButton->setPopupMode(QToolButton::InstantPopup);
    menuButton->setFixedSize(30,30);
    menuButton->setIconSize(QSize(16, 16));
    menuButton->setAutoRaise(true);
    menuButton->setIcon(QIcon::fromTheme("open-menu-symbolic"));

    m_menu = new QMenu();
    QList<QAction *> actions ;
    QAction *actionStandard = new QAction(m_menu);
    actionStandard->setText(tr("standard"));
    QAction *actionScientific = new QAction(m_menu);
    actionScientific->setText(tr("scientific"));
    QAction *actionExchangeRate = new QAction(m_menu);
    actionExchangeRate->setText(tr("exchange rate"));

    QAction *separator = new QAction(m_menu);
    separator->setSeparator(true);

    QAction *actionTheme = new QAction(m_menu);
    actionTheme->setText(tr("Theme"));
    QAction *actionHelp = new QAction(m_menu);
    actionHelp->setText(tr("Help"));
    QAction *actionAbout = new QAction(m_menu);
    actionAbout->setText(tr("About"));
    QAction *actionQuit = new QAction(m_menu);
    actionQuit->setText(tr("Quit"));
    actions << actionStandard
            << actionScientific
            << actionExchangeRate
            << separator
            // << actionTheme
            << actionHelp
            << actionAbout
            << actionQuit;

    m_menu->addActions(actions);

//    互斥按钮组
    QMenu *themeMenu = new QMenu;
    QActionGroup *themeMenuGroup = new QActionGroup(this);
    QAction *autoTheme = new QAction(tr("Auto"),this);
    themeMenuGroup->addAction(autoTheme);
    themeMenu->addAction(autoTheme);
    autoTheme->setCheckable(true);
    QAction *lightTheme = new QAction(tr("Light"),this);
    themeMenuGroup->addAction(lightTheme);
    themeMenu->addAction(lightTheme);
    lightTheme->setCheckable(true);
    QAction *darkTheme = new QAction(tr("Dark"),this);
    themeMenuGroup->addAction(darkTheme);
    themeMenu->addAction(darkTheme);
    darkTheme->setCheckable(true);
    QList<QAction* > themeActions;
    themeActions<<autoTheme<<lightTheme<<darkTheme;
//    autoTheme->setChecked(true);
    actionTheme->setMenu(themeMenu);
    menuButton->setMenu(m_menu);
    connect(m_menu,&QMenu::triggered,this,&menuModule::triggerMenu);
    initGsetting();
    setThemeFromLocalThemeSetting(themeActions);
    themeUpdate();
    connect(themeMenu,&QMenu::triggered,this,&menuModule::triggerThemeMenu);
}

void menuModule::setThemeFromLocalThemeSetting(QList<QAction* > themeActions)
{
    m_pGsettingThemeStatus = new QGSettings(confPath.toLocal8Bit());
    QString appConf = m_pGsettingThemeStatus->get("thememode").toString();
    if("lightonly" == appConf){
        themeStatus = themeLightOnly;
        themeActions[1]->setChecked(true);   //程序gsetting中为浅色only的时候就给浅色按钮设置checked
    }else if("darkonly" == appConf){
        themeStatus = themeBlackOnly;
        themeActions[2]->setChecked(true);
    }else{
        themeStatus = themeAuto;
        themeActions[0]->setChecked(true);
    }
}

void menuModule::themeUpdate(){
    if(themeStatus == themeLightOnly)
    {
        setThemeLight();
    }
    else if(themeStatus == themeBlackOnly){
        setThemeDark();
    }
    else{
        setStyleByThemeGsetting();
    }
}

void menuModule::setStyleByThemeGsetting(){
    QString nowThemeStyle = m_pGsettingThemeData->get("styleName").toString();
    if("ukui-dark" == nowThemeStyle || "ukui-black" == nowThemeStyle) {
        setThemeDark();
    }
    else {
        setThemeLight();
    }
}

void menuModule::triggerMenu(QAction *act)
{
    QString str = act->text();
    if(tr("Quit") == str){
        emit menuModuleClose();
    }
    else if(tr("About") == str){
        aboutAction();
    }
    else if(tr("Help") == str){
        helpAction();
    }
    else if(tr("standard") == str){
        emit menuModuleChanged(QString("standard"));
    }
    else if(tr("scientific") == str){
        emit menuModuleChanged(QString("scientific"));
    }
    else if(tr("exchange rate") == str){
        emit menuModuleChanged(QString("exchange rate"));
    }
}

void menuModule::triggerThemeMenu(QAction *act)
{
    if(!m_pGsettingThemeStatus)
    {
        m_pGsettingThemeStatus = new QGSettings(confPath.toLocal8Bit());  //m_pGsettingThemeStatus指针重复使用避免占用栈空间
    }
    QString str = act->text();
    if("Light" == str){
        themeStatus = themeLightOnly;
        disconnect(m_pGsettingThemeData,&QGSettings::changed,this,&menuModule::dealSystemGsettingChange);
        m_pGsettingThemeStatus->set("thememode","lightonly");
//        disconnect()
        setThemeLight();
    }else if("Dark" == str){
        themeStatus = themeBlackOnly;
        disconnect(m_pGsettingThemeData,&QGSettings::changed,this,&menuModule::dealSystemGsettingChange);
        m_pGsettingThemeStatus->set("thememode","darkonly");
        setThemeDark();
    }else{
        themeStatus = themeAuto;
        m_pGsettingThemeStatus->set("thememode","auto");
        initGsetting();
//        updateTheme();
        themeUpdate();
    }
}

void menuModule::aboutAction()
{
//    关于点击事件处理
    // if (aboutWindow != nullptr) {
    //     aboutWindow->hide();
        
    //     QTime dieTime = QTime::currentTime().addMSecs(50);
    //     while( QTime::currentTime() < dieTime )
    //         QCoreApplication::processEvents(QEventLoop::AllEvents, 100);


    //     aboutWindow->show();
    //     // aboutWindow->activateWindow();
    //     return ;
    // }
    initAbout();
}

void menuModule::helpAction()
{
//    帮助点击事件处理

    DaemonIpcDbus *ipcDbus = new DaemonIpcDbus();
    if(!ipcDbus->daemonIsNotRunning()){
        // qDebug() << "hahahahahaha" << appName;
        ipcDbus->showGuide(appName);
    }
}
#include <QDialog>
void menuModule::initAbout()
{
    aboutWindow = new QWidget();
    aboutWindow->setWindowFlag(Qt::Tool);
    aboutWindow->setWindowIcon(QIcon::fromTheme("calc"));
    aboutWindow->setWindowModality(Qt::WindowModal);
    aboutWindow->setWindowModality(Qt::ApplicationModal);
    // aboutWindow->setModal(true);
    // aboutWindow->setWindowFlags(Qt::FramelessWindowHint);
    MotifWmHints hints;
    // aboutWindow->setWindowFlags(Qt::WindowStaysOnTopHint);
    hints.flags = MWM_HINTS_FUNCTIONS|MWM_HINTS_DECORATIONS;
    hints.functions = MWM_FUNC_ALL;
    hints.decorations = MWM_DECOR_BORDER;
    XAtomHelper::getInstance()->setWindowMotifHint(aboutWindow->winId(), hints);
    aboutWindow->setFixedSize(420,324);
    aboutWindow->setMinimumHeight(324);
    QVBoxLayout *mainlyt = new QVBoxLayout();
    QHBoxLayout *titleLyt = initTitleBar();
    QVBoxLayout *bodylyt = initBody();
    mainlyt->setContentsMargins(0,0,0,0);
    mainlyt->setSpacing(0);
    mainlyt->addLayout(titleLyt);
    mainlyt->addLayout(bodylyt);
    mainlyt->addStretch();
    aboutWindow->setLayout(mainlyt);
    //TODO:在屏幕中央显示
    QRect availableGeometry = qApp->primaryScreen()->availableGeometry();
    aboutWindow->move((availableGeometry.width()-aboutWindow->width())/2,(availableGeometry.height()- aboutWindow->height())/2);
    // aboutWindow->setStyleSheet("background-color:rgba(255,255,255,1);");
    dealSystemGsettingChange("styleName");
    aboutWindow->show();
}

QHBoxLayout* menuModule::initTitleBar()
{
    QLabel* titleIcon = new QLabel();
    titleIcon->setPixmap(QIcon::fromTheme("calc").pixmap(titleIcon->size()));
    titleIcon->setFixedSize(QSize(24,24));
    titleIcon->setScaledContents(true);

    QPushButton *titleBtnClose = new QPushButton;
    titleBtnClose->setFixedSize(30,30);
    titleBtnClose->setIcon(QIcon::fromTheme("window-close-symbolic"));
    titleBtnClose->setProperty("isWindowButton",0x2);
    titleBtnClose->setProperty("useIconHighlightEffect",0x8);
    titleBtnClose->setFlat(true);
    connect(titleBtnClose,&QPushButton::clicked,[=](){aboutWindow->close();});
    
    titleText->setText(tr(appShowingName.toLocal8Bit()));
    titleText->setStyleSheet("font-size:14px;");
    
    QHBoxLayout *hlyt = new QHBoxLayout;
    hlyt->setSpacing(0);
    hlyt->setContentsMargins(4,4,4,4);
    hlyt->addSpacing(4);
    hlyt->addWidget(titleIcon); //居下显示
    hlyt->addSpacing(8);
    hlyt->addWidget(titleText);
    hlyt->addStretch();
    hlyt->addWidget(titleBtnClose);

    return hlyt;
}

QVBoxLayout* menuModule::initBody()
{

    QLabel* bodyIcon = new QLabel();
    bodyIcon->setFixedSize(96,96);
    bodyIcon->setPixmap(QIcon::fromTheme("accessories-calculator").pixmap(bodyIcon->size()));
    // bodyIcon->setStyleSheet("font-size:14px;");
    // bodyIcon->setScaledContents(true);

    bodyAppName->setFixedHeight(28);
    bodyAppName->setText(tr(appShowingName.toLocal8Bit()));
    bodyAppName->setStyleSheet("font-size:18px;");

    bodyAppVersion->setFixedHeight(24);
    bodyAppVersion->setText(tr("Version: ") + appVersion);
    bodyAppVersion->setAlignment(Qt::AlignLeft);
    bodyAppVersion->setStyleSheet("font-size:14px;");

    connect(bodySupport,&QLabel::linkActivated,this,[=](const QString url){
        QDesktopServices::openUrl(QUrl(url));
    });
    bodySupport->setContextMenuPolicy(Qt::NoContextMenu);
    bodySupport->setFixedHeight(24);
    bodySupport->setStyleSheet("font-size:14px;");
    QVBoxLayout *vlyt = new QVBoxLayout;
    vlyt->setMargin(0);
    vlyt->setSpacing(0);
    vlyt->addSpacing(20);
    vlyt->addWidget(bodyIcon,0,Qt::AlignHCenter);
    vlyt->addSpacing(16);
    vlyt->addWidget(bodyAppName,0,Qt::AlignHCenter);
    vlyt->addSpacing(12);
    vlyt->addWidget(bodyAppVersion,0,Qt::AlignHCenter);
    vlyt->addSpacing(12);
    vlyt->addWidget(bodySupport,0,Qt::AlignHCenter);
    vlyt->addStretch();
    return vlyt;
}

void menuModule::setStyle()
{
    // menuButton->setObjectName("menuButton");
    // // qDebug() << "menuButton->styleSheet" << menuButton->styleSheet();
    // menuButton->setStyleSheet("QPushButton::menu-indicator{image:None;}");
}

void menuModule::initGsetting(){
    if(QGSettings::isSchemaInstalled(UKUI_THEME_GSETTING_PATH)){
        m_pGsettingThemeData = new QGSettings(UKUI_THEME_GSETTING_PATH);
        connect(m_pGsettingThemeData,&QGSettings::changed,this,&menuModule::dealSystemGsettingChange);
    }

}

void menuModule::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_F1){
        emit pullupHelp();
    }else{
        QWidget::keyPressEvent(event);
    }
}

void menuModule::dealSystemGsettingChange(const QString key)
{
    if(key == "styleName"){
        refreshThemeBySystemConf();
    }
}

void menuModule::refreshThemeBySystemConf()
{
    QString themeNow = m_pGsettingThemeData->get("styleName").toString();
    if("ukui-dark" == themeNow || "ukui-black" == themeNow){
        setThemeDark();
    }else{
        setThemeLight();
    }
}

void menuModule::setThemeDark()
{
    qDebug()<<"set theme dark";
    if(aboutWindow)
    {
        QPalette palette(this->palette());
        palette.setColor(QPalette::Background, QColor::fromRgb(13,13,14));
        aboutWindow->setPalette(palette);
        // aboutWindow->setStyleSheet("background-color:rgba(13,13,14,1);");
    }
    emit menuModuleSetThemeStyle("dark-theme");
    bodySupport->setText(tr("Service & Support: ") +
                         "<a href=\"mailto://support@kylinos.cn\""
                         "style=\"color:rgba(225,225,225,1)\">"
                         "support@kylinos.cn</a>");
    // menuButton->setProperty("setIconHighlightEffectDefaultColor", QColor(Qt::white));
}

void menuModule::setThemeLight()
{
//    qDebug()<<"set theme light";
    if(aboutWindow)
    {
        QPalette palette(this->palette());
        palette.setColor(QPalette::Background, QColor::fromRgb(255,255,255));
        aboutWindow->setPalette(palette);
        // aboutWindow->setStyleSheet("background-color:rgba(255,255,255,1);");
    }
    emit menuModuleSetThemeStyle("light-theme");
    bodySupport->setText(tr("Service & Support: ") +
                         "<a href=\"mailto://support@kylinos.cn\""
                         "style=\"color:rgba(0,0,0,1)\">"
                         "support@kylinos.cn</a>");
}
