/*
 * Name:
 *  cal.h
 * 2020年 08月 21日 星期五 16:11:14 CST
 *
 * 函数：QString calculator(QString dis_data);
 * 功能：对输入的四则运算字符串进行处理(可输入"0 . 1 2 3 4 5 6 7 8 9 + - * / % ( )")
 * 通过EPS控制精度（保留小数点后EPS位）
 * 结果长度大于EPS将转为科学计数法
 *
 * 扩展功能：已经预留接口，后续可以加入对sin cos tan log 等函数的识别
 *         precalculator中已经写入了sin的处理，可以自行开发
 *
 */

#ifndef CAL_H
#define CAL_H
#include <QDebug>
#include <deque>
#include <stack>
#include <iostream>
#include <cstdio>
#include <QChar>
#include <complex>
// 精度
#define EPS 10
// 圆周率　用于角度和弧度转换
#define PI acos(-1.0)

// 角度弧度标志位,角度DEG 弧度RAD,默认角度
QString degOrRad = "DEG";

using namespace std;

bool isPra(QString c);
int getPri(char c);
void check(QString c, stack<QString>& coll2, deque<QString>& coll3);
void allocate(deque<QString>& coll1, stack<QString>& coll2, deque<QString>& coll3);
void cal(deque<QString>& coll3, stack<double>& coll4);
int findPair(QString s, int l ,int r);
double deg_rad_trans(double _val);
QString precalculator(QString s);
QString calculator(QString s);



bool isPra(QString c)
{
    if(c[0]=='('||c[0]==')')
        return true;
    else
        return false;
}

//获得符号的优先性
int getPri(char c)
{
    switch(c)
    {
    case '+':
    case '-':
        return 0;	//如果是加减，返回0
        break;
    case '*':
    case '/':
        return 1;	//如果是乘除，返回1
        break;
    case '(':
    case ')':
        return -1;  //注意，这里将括号设为最低优先级，因此括号不会被弹出，除非遇到右括号
        break;
    }
}

//判断符号的优先性
void check(QString c, stack<QString> &coll2, deque<QString> &coll3)
{
    if (coll2.empty())
    {
        coll2.push(c);
        return;
    }

    if (isPra(c))
    {
        if (c[0] == '(')
            coll2.push(c);
        else
        {
            //弹出所有元素直到遇到左括号
            while (coll2.top() != "(")
            {
                QString ch = coll2.top();
                coll3.push_back(ch);
                coll2.pop();
            }

            //当遇到左括号时，弹出但不加入coll3(后缀表达式中）
            coll2.pop();
        }
    }
    else	//如果不是括号
    {
        //取出栈顶元素，与当前符号进行优先性比较
        QString sym = coll2.top();

        //比较两符号的优先性
        if (getPri(c.at(0).toLatin1()) <= getPri(sym.at(0).toLatin1()))
        {
            //如果c的优先性比栈顶符号小或等于，弹出栈顶元素
            coll2.pop();
            //并将其压入coll3（后缀表达式）中
            coll3.push_back(sym);
            //递归调用check,比较当前符号c与下一个栈顶符号的优先性
            check(c,coll2,coll3);
        }
        else
        {
            //如果c比栈顶符号优先级大，那将c压入coll2(操作符栈）中
            coll2.push(c);
        }
    }
}

//从coll中取出元素，分配元素到coll2和coll3中
void allocate(deque<QString> &coll1, stack<QString> &coll2, deque<QString> &coll3)
{
    while (!coll1.empty()) {
        QString c = coll1.front();
        coll1.pop_front();

        if (c[0] >= '0' && c[0] <= '9' || c[0] == '-' && c.size() > 1) {
            coll3.push_back(c);
        }
        else {
            //调用check函数，针对不同情况作出不同操作
            check(c,coll2,coll3);
        }

    }

    //如果输入结束，将coll2的元素全部弹出，加入后缀表达式中
    while (!coll2.empty()) {
        QString c = coll2.top();
        coll3.push_back(c);
        coll2.pop();
    }
}

//计算后缀表达式
void cal(deque<QString> &coll3, stack<double> &coll4)
{
    while (!coll3.empty()) {
        QString c = coll3.front();
        coll3.pop_front();

        //如果是操作数，压入栈中
        if (c[0]>='0' && c[0]<='9') {
            double op = c.toDouble();
            coll4.push(op);
        }
        //如果是操作符，从栈中弹出元素进行计算
        else {
            double op1 = coll4.top();
            coll4.pop();
            double op2 = coll4.top();
            coll4.pop();
            switch (c.at(0).toLatin1())
            {
            case '+':
                coll4.push(op2+op1);
                break;
            case '-':
                coll4.push(op2-op1);
                break;
            case '*':
                coll4.push(op2*op1);
                break;
            case '/':
                coll4.push(op2/op1);
                break;
            }
        }
    }
}


void divide(QString &dis_data, deque<QString> &coll1) {
    dis_data += '$';
    int i = 0;
    for (i; i < dis_data.size();) {
        //科学计数识别
        if (i >= 1 && (dis_data[i] == '+' || dis_data[i] == '-')
          && dis_data[i-1] == 'e') {

            i++;
        }
        if (dis_data[i] != '+' && dis_data[i] != '-'
         && dis_data[i] != '*' && dis_data[i] != '/' && dis_data[i] != '$'
         && dis_data[i] != '(' && dis_data[i] != ')') {

            // 百分号转数字
            if (dis_data[i] == '%') {

                QString t = dis_data.mid(0, i);
                t = QString::number(t.toDouble() / 100.0);
                dis_data.remove(0, i + 1);
                dis_data.insert(0, t);
                i = t.size();
            }
            else
                i++;
        }
        else {
            QString t = dis_data.mid(0, i);

            if(t.size() > 0)
                coll1.push_back(t);

            dis_data.remove(0, i);
            t.clear();
            t += dis_data[0];
            coll1.push_back(t);
            dis_data.remove(0, 1);
            i = 0;
        }
    }
    coll1.pop_back();
}

// 找到和ｌ位置匹配的括号
int findPair(QString s, int l, int r) {
    int cnt = 0;
    for (int i = l + 1; i <= r; i++) {
        if (s[i] == '(') {
            cnt++;
        }
        else if (s[i] == ')') {
            if (cnt == 0) {
                return i;
            }
            else {
                cnt--;
            }
        }
    }
}


// 角度弧度转换
double deg_rad_trans(double _val) {
    if (degOrRad == "DEG")
        return _val * PI / 180.0;
    if (degOrRad == "RAD")
        return _val;
}


QString precalculator(QString s) {
    switch (s.at(0).toLatin1())
    {
    case 's':
        if(s.indexOf("sin(") == 0)  {
            int l = 3;
            int r = findPair(s, l, s.size() - 1);
            QString t;
            t = calculator(s.mid(l + 1, r - l - 1));
            t = QString::number(sin(deg_rad_trans(t.toDouble())), 'f', EPS + 5);
            return (t + s.mid(r + 1, s.size() - r - 1));
        }
        break;
    default:
        return s;
        break;
    }

}



QString calculator(QString dis_data)
{
    if (dis_data.size() == 0) return 0;
    if (dis_data.size() >= 3 && dis_data.contains("inf")) return "inf";
    if (dis_data.size() >= 3 && dis_data.contains("nan")) return "nan";

    //去掉末尾运算符号
    for (int j = dis_data.size() - 1; j >= 0; j++) {
        if (dis_data[j] != '+' && dis_data[j] != '-'
         && dis_data[j] != '*' && dis_data[j] != '/') {
            break;
        } else {
            dis_data.chop(1);
        }
    }
    dis_data = precalculator(dis_data);

    deque<QString> coll1;  //盛放中缀表达式
    stack<QString> coll2;  //盛放操作符
    deque<QString> coll3;	//盛放后缀表达式
    stack<double> coll4;	//计算后缀表达式的辅助容器

    if (dis_data[0]  == '-') {
        dis_data.insert(0, '0');
    }
    //将dis_data中的数据转入到coll1中
    divide(dis_data, coll1);

    allocate(coll1, coll2, coll3);

    //计算后缀表达式
    cal(coll3, coll4);

    QString ans = QString::number(coll4.top(), 'f', EPS + 5);

    //去掉末尾０
    if (ans.contains('.')) {
        while (ans[ans.size() - 1] == '0') {
            ans.chop(1);
        }
        if (ans[ans.size() - 1] == '.') {
            ans.chop(1);
        }
    }
    //科学计算显示
    if (ans.contains('.')) {
        if ((ans.size() - ans.indexOf(".") > EPS) || (ans.indexOf(".") > EPS)) {
            ans = QString::number(ans.toDouble(), 'g', EPS);
        }
    }
    else {
        if (ans.size() > EPS) {
            ans = QString::number(ans.toDouble(), 'g', EPS);
        }
    }
    return ans;

}


#endif
