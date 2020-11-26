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

#include "funclist.h"
#include <QDebug>

FuncList::FuncList(QWidget *parent)
    : QWidget(parent)
{
    // 初始化列表项组件
    setWidgetUi();

    // 设置组件样式
    setWidgetStyle();

}

FuncList::~FuncList()
{

}

// 初始化列表项组件
void FuncList::setWidgetUi()
{
    // 计算器
    funcModelLabel = new QLabel(this);
    funcModelLabel->setText(tr("Calculator"));
//    funcModelLabel->setText(tr("计算器"));

    funcModelWid = new QListWidget(this);
    QListWidgetItem *model[2];
     QString modelListStr = tr("standard") + "," + tr("scientific");
//    QString modelListStr = "标准,科学";
    QStringList modelList = modelListStr.split(",");

    // 计算器功能列表初始化
    for (int i = 0; i < modelList.size(); i++) {
        model[i] = new QListWidgetItem("    "+modelList[i], funcModelWid);
        funcModelWid->insertItem(i, model[i]);
    }

    // 列表中标准模式获得焦点
    funcModelWid->item(0)->setSelected(true);


    // 换算器
    funcToolLabel = new QLabel(this);
    funcToolLabel->setText(tr("Unit converter"));
//    funcToolLabel->setText(tr("换算器"));

    funcToolWid = new QListWidget(this);
    QListWidgetItem *tool[9];
    // QString toolListStr = "汇率,长度,重量,容量,面积,速度,能量,温度,功率";
    QString toolListStr = tr("exchange rate");
//    QString toolListStr = tr("exchange rate");
    QStringList toolList = toolListStr.split(",");

    // 换算器功能列表初始化
    for (int i = 0; i < toolList.size(); i++) {
        tool[i] = new QListWidgetItem("    "+toolList[i], funcToolWid);
        funcToolWid->insertItem(i, tool[i]);
    }

    // 将计算器列表和换算器列表加入布局
    QVBoxLayout *funcLayout = new QVBoxLayout(this);

    funcLayout->addWidget(funcModelLabel);
    funcLayout->addWidget(funcModelWid);
    funcLayout->addWidget(funcToolLabel);
    funcLayout->addWidget(funcToolWid);

    this->setLayout(funcLayout);
    this->setContentsMargins(0, 0, 0, 0);
    this->setFixedHeight(430);
    this->setFixedWidth(170);
    this->setGeometry(QRect(0, 30, 430, 170));
}

// 设置组件样式
void FuncList::setWidgetStyle()
{
    // 计算器模式样式
    funcModelWid->setSpacing(2);
    funcModelWid->setFixedHeight(65);
    funcModelWid->setStyleSheet("QListWidget::item{border-radius:4px;}"
                                "QListWidget::item:selected{background-color:#FF800F;}"
                                "QListWidget::item:hover{background-color:#666666;}");

    // 换算器模式样式
    funcToolWid->setSpacing(2);
    funcToolWid->setStyleSheet("QListWidget::item{border-radius:4px;}"
                               "QListWidget::item:selected{background-color:#FF800F;}"
                               "QListWidget::item:hover{background-color:#666666;}");

    // 设置列表样式
    QString funcLabelStyle = "font-family:SourceHanSansCN-Regular;font-size:14px;color:#666666;";

    funcModelLabel->setStyleSheet(funcLabelStyle);
    funcToolLabel->setStyleSheet(funcLabelStyle);
    this->setStyleSheet("background-color:#36363A;color:#FFFFFF;font-size:18px;border:none;border-radius:4px;");
}
