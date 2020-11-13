#include "basicbutton.h"

// 设置按钮初始样式
BasicButton::BasicButton(QWidget *parent)
    : QPushButton(parent)
{

}

// 设置按钮内容
void BasicButton::setText(const QString &text)
{
    this->btnText = text;
}

// 获取按钮内容
QString BasicButton::getText()
{
    return this->btnText;
}

// 获取按钮内容
QString BasicButton::text()
{
    return this->btnText;
}
