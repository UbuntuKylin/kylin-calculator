#ifndef FUNCBUTTON_H
#define FUNCBUTTON_H

#include <QLabel>
#include <QWidget>
#include <QListWidget>
#include <QKeyEvent>
#include <QVBoxLayout>
#include <QPushButton>

class BasicButton : public QPushButton
{
    Q_OBJECT
public:
    explicit BasicButton(QWidget *parent = 0);
    ~BasicButton() {}

    // 按钮所代表的意义
    QString btnText;

    // 设置按钮内容
    void setText(const QString &text);

    // 获取按钮内容
    QString getText();

    // 获取按钮内容
    QString text();

};

#endif // FUNCBUTTON_H
