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

#ifndef TOOLMODEL_H
#define TOOLMODEL_H

#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QFont>
#include <QLabel>
#include <QWidget>
#include <QListWidget>
#include <QScrollBar>
#include <QKeyEvent>
#include <QTime>
#include <QDateTime>
#include <QList>
#include <QStringList>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QSslError>
#include <QEventLoop>
#include <QRegExp>

#include "basicbutton.h"
#include "InputSymbols.h"
//#include "cal.h"

class UnitListWidget;
class UnitListItem;

// 换算器输入输出界面
class ToolModelOutput : public QWidget, public InputSymbols
{
    Q_OBJECT

public:
    explicit ToolModelOutput(QWidget *parent = 0);
    ~ToolModelOutput() {}

    // 当前功能标识
    QString funName;

    // 汇率更新
    QLabel *toolLabUpdate;
    QLabel *toolIconUpdate;
    QLabel *toolLabRate;

    // 单位换算比率
    double  toolDouRate = 0;
    // 获取汇率信息字符串键值对
    QStringList strRateList;
    // 货币及其符号对应
    QMap<QString, QString> rateMap;
    // 符号及其货币的对应关系
    QMap<QString, QString> currencyInfo;
    QMap<QString, QString> currencyInfo1;

    QVBoxLayout *toolUpdateLayout;
    QWidget *toolUpdateWid;

    // 单位标识
    QString toolRateNameBef;
    QString toolRateSymbBef;
    QLabel *toolLabUnitBef;
    QLabel *toolLabIconBef;

    QString toolRateNameAft;
    QString toolRateSymbAft;
    QLabel *toolLabUnitAft;
    QLabel *toolLabIconAft;

    QHBoxLayout *toolUnitBefLayout;
    QHBoxLayout *toolUnitAftLayout;

    QPushButton *toolUnitBefWid;
    QPushButton *toolUnitAftWid;

    // 换算历史
    QLabel *toolLabHis;
    // 换算前
    QLabel *toolLabBef;
    // 换算后
    QLabel *toolLabAft;

    // 换算前的单位列表
    UnitListWidget *unitListBef;
    // 换算后的单位列表
    UnitListWidget *unitListAft;

    // 时间控制
    QTimer *timer;

    // 初始化组件
    void setWidgetUi();

    // 设置组件样式
    void setWidgetStyle();

    // 初始化单位列表
    void initUnitList(QString listStr);

    // 单位换算函数
    void unitConversion();

    // 单位换算历史记录转换
    QString unitConvHistory(QString hisText);

    // 汇率更新函数
    void updateRate();



//signals:
//    void clicked();

public slots:
    // 控制换算前的单位列表
    void unitListBefShow();

    // 控制换算后的单位列表
    void unitListAftShow();

    // 选择换算前的单位列表
    void unitListBefSelect(QListWidgetItem*);

    // 选择换算后的单位列表
    void unitListAftSelect(QListWidgetItem*);

    // 选择货币单位列表
    void unitListSelect(QListWidgetItem*);

private:

    // 根据符号更新货币名称并显示
    void updateRateName();
};

// 换算器按钮界面
class ToolModelButton : public QWidget
{
    Q_OBJECT

public:
    explicit ToolModelButton(QWidget *parent = 0);

    BasicButton *btnNum[10];

    BasicButton *btnClear;
    BasicButton *btnPer;
    BasicButton *btnDelete;

    BasicButton *btnDiv;
    BasicButton *btnMulti;
    BasicButton *btnSub;
    BasicButton *btnAdd;
    BasicButton *btnEqual;

    BasicButton *btnDZero;
    BasicButton *btnPoint;

    // 初始化组件
    void setWidgetUi();

    // 设置组件样式
    void setWidgetStyle();

public slots:
    // 键盘响应事件
    void keyPressEvent(QKeyEvent *event);
};

// 换算器单位列表项
class UnitListItem : public QWidget
{
    Q_OBJECT
public:
    explicit UnitListItem(QWidget *parent = 0);

    // 初始化列表项组件
    void setWidgetUi();

    // 初始化列表项样式
    void setWidgetStyle();

    // 单位名称
    QLabel *unitItemName;
    // 单位标识
    QLabel *unitItemSymb;

    // 列表项水平布局
    QHBoxLayout *unitItemLayout;
};

// 换算器单位列表界面
class UnitListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UnitListWidget(QWidget *parent = 0);

    // 标题和取消
    QLabel *unitTitle;
    QPushButton *btnCancel;

    // 搜索框
    QLineEdit *searchEdit;

    // 单位列表
    QListWidget *unitList;
    QHBoxLayout *unitItemLayout;
    QLabel *unitName;
    QLabel *unitSign;

    // 总体布局
    QVBoxLayout *unitListLayout;

    // 初始化组件
    void setWidgetUi();

    // 初始化组件样式
    void setWidgetStyle();

};

#endif // TOOLMODEL_H
