#ifndef __INPUT_TOOLS_H__
#define __INPUT_TOOLS_H__

#include <QPair>
#include <QString>
#include <QStringList>
#include <QDebug>

#include "InputSymbols.h"
class InputTools : public InputSymbols
{
private:
    static const QPair<int, QString> QP_QSTR_ERROR;
    static const QPair<int, QStringList> QP_QSTR_LIST_ERROR;

public: 
    static bool isSpace              (const QChar);
    static bool isSpace              (const char);
    static bool isBracket            (const QChar);
    static bool isBracket            (const char);
    static bool isBracket            (const QString &);
    static bool isNumber             (const QChar);
    static bool isNumber             (const char);
    static bool isNumber             (const QString &);
    static bool isOperator           (const QChar);
    static bool isOperator           (const char);
    static bool isOperator           (const QString &);
    static bool isArithmeticOperator (const QChar);
    static bool isArithmeticOperator (const char);
    static bool isArithmeticOperator (const QString &);

    static bool isFunction           (const QString &);
    static bool isTrans              (const QString &);
    static bool isSciNum             (const QString &);

    /*8 findBracketPair:
     *  找到和qstr[idx]位置匹配的括号
     *  如果找不到,返回-1
     */
    static int  findBracketPair(const QString     &qstr,     const int idx);
    static int  findBracketPair(const QStringList &qstrList, const int idx);
    static bool allBracketMatchCorrectly(const QString &qstr);
    static QString bracketCompletion(const QString &qstr);
private:
    static QString getFunctionOrSciNumName (const QString &qstr, const int idx);
public:
    static QStringList formulaSplit (const QString &);


    static void qpairUpdate(      QPair<int, QString> &qpair1,
                            const QPair<int, QString> &qpair2);

    static void qpairUpdate(      QPair<int, QStringList> &qpair1,
                            const QPair<int, QStringList> &qpair2);

public:
    /** isCorrect* 函数:
     *  判断内容是否正确
     *  正确 first返回1 second返回原串
     *  修改后正确返回2 second返回修改后的串
     *  无法修改的错误返回0 second 返回ERROR
     */
    static QPair<int, QString> isCorrectInt    (const QString &);
    static QPair<int, QString> isCorrectDouble (const QString &);
    /** isCorrectNumber
     *  返回值是3 可能是其他类型
     */
    static QPair<int, QString>     isCorrectNumber      (const QString &);
private:
    static bool adjacencyJudgment (const QString &, const QString &);
public:
    static QPair<int, QStringList> isCorrectFormulaList (const QStringList &);
    static QPair<int, QString>     isCorrectFormula     (const QString &);

    /** formulaTypeCheck 判断传入QString的类型
     *  数的定义：当前可以操作的只包含-1234567890.%的串(如果有'-',必须在第一位)
	 *  1.运行字符串检测函数
	 *  2.检测空                        返回 0 
	 *  3.检测是数                      返回-1
	 *  4.检测是ANS                     返回-2
	 *  5.检测是式子末尾有 + - * /      返回 1
	 *  6.其他&检测是式子末尾无 + - * / 返回 2
     */
    static int formulaTypeCheck (const QString &);

    static int     getNumberLengthFromBack    (const QString &);
    static int     getAnsNumberLengthFromBack (const QString &);
    static QString getNumberFromBack          (const QString &);
    static QString getAnsNumberFromBack       (const QString &);
    static QString clearANS_END(const QString &);
    static QString clearSCI_NUM_END(const QString &);
    static QString clearANS_END_and_SCI_NUM_END(const QString &);
};

#endif