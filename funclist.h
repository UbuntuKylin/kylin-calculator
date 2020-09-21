#ifndef FUNLIST_H
#define FUNLIST_H

#include <QLabel>
#include <QWidget>
#include <QListWidget>
#include <QKeyEvent>
#include <QVBoxLayout>
#include <QPushButton>

class FuncList : public QWidget
{
    Q_OBJECT

public:
    explicit FuncList(QWidget *parent = 0);
    ~FuncList();

    QListWidget *funcModelWid;
    QListWidget *funcToolWid;

signals:


private:
};

#endif // FUNLIST_H
