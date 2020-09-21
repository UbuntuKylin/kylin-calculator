#include "funclist.h"
#include <QDebug>

FuncList::FuncList(QWidget *parent)
    : QWidget(parent)
{
    // 计算器
    QLabel *funcModelLabel = new QLabel(this);
    funcModelLabel->setText(tr("计算器"));

    funcModelWid = new QListWidget(this);
    QListWidgetItem *model[2];
    QString modelListStr = "标准,科学";
    QStringList modelList = modelListStr.split(",");

    // 计算器功能列表初始化
    for (int i = 0; i < modelList.size(); i++) {
        model[i] = new QListWidgetItem("    "+modelList[i], funcModelWid);
        funcModelWid->insertItem(i, model[i]); 
    }

    funcModelWid->setSpacing(2);
    funcModelWid->setFixedHeight(65);
    funcModelWid->setStyleSheet("QListWidget::item{border-radius:4px;}"
                                "QListWidget::item:selected{background-color:#FF800F;}"
                                "QListWidget::item:hover{background-color:#666666;}");

    // 列表中标准模式获得焦点
    funcModelWid->item(0)->setSelected(true);

    // 换算器
    QLabel *funcToolLabel = new QLabel(this);
    funcToolLabel->setText(tr("换算器"));

    funcToolWid = new QListWidget(this);
    QListWidgetItem *tool[9];
    QString toolListStr = "汇率,长度,重量,容量,面积,速度,能量,温度,功率";
    QStringList toolList = toolListStr.split(",");

    // 换算器功能列表初始化
    for (int i = 0; i < toolList.size(); i++) {
        tool[i] = new QListWidgetItem("    "+toolList[i], funcToolWid);
        funcToolWid->insertItem(i, tool[i]);
    }

    funcToolWid->setSpacing(2);
    funcToolWid->setStyleSheet("QListWidget::item{border-radius:4px;}"
                               "QListWidget::item:selected{background-color:#FF800F;}"
                               "QListWidget::item:hover{background-color:#666666;}");


    // 将计算器列表和换算器列表加入布局
    QVBoxLayout *funcLayout = new QVBoxLayout(this);

    funcLayout->addWidget(funcModelLabel);
    funcLayout->addWidget(funcModelWid);
    funcLayout->addWidget(funcToolLabel);
    funcLayout->addWidget(funcToolWid);

//    QVBoxLayout *funcListLayout = new QVBoxLayout(this);
//    funcListLayout->addLayout(funcLayout);
//    funcListLayout->addStretch();
//    funcListLayout->setSpacing(0);
//    funcListLayout->setMargin(0);

    this->setLayout(funcLayout);
    this->setContentsMargins(0, 0, 0, 0);
    this->setFixedHeight(430);
    this->setFixedWidth(170);
    this->setGeometry(QRect(0, 30, 430, 170));

    // 设置列表样式
    QString funcLabelStyle = "font-family:SourceHanSansCN-Regular;font-size:14px;color:#666666;";

    funcModelLabel->setStyleSheet(funcLabelStyle);
    funcToolLabel->setStyleSheet(funcLabelStyle);
    this->setStyleSheet("background-color:#36363A;color:#FFFFFF;font-size:18px;border:none;border-radius:4px;");


}


FuncList::~FuncList()
{

}
