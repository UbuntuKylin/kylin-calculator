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

#ifndef __QSTRING_CALCULATOR_H__
#define __QSTRING_CALCULATOR_H__

#include <iostream>
#include <cstdio>

#include <QString>
#include <QStack>
#include <QQueue>

#include "InputTools.h"
#include "BigFloat.h"

class QStringCalculator : public InputTools
{
private:

    static const     int    PRECISION     = 15;
    static const     int    CAL_PRECISION = PRECISION + 5;
    static const     int    MAX_LIMIT     = CAL_PRECISION;
    static constexpr double EPS           = 1e-15;

    static QString angelSymbol;

    static int     getOperatotPriority  (const QString qstr);
    
    static void    postfixCheck   (const QString    &qstr,
                                   QStack<QString>  &operatorList,
                                   QStringList      &postfixExpressions);

    static void   infixToPostfix (QStringList &infixExpression,
                                  QStringList &postfixExpressions);

    static void    calPostfix     (QStringList      &postfixExpressions,
                                   QStack<BigFloat> &calAns);

    static QString transCalculator(const QStringList &expression,
                                   const int idx);
    /*
     * 科学计算函数处理
     *  例如：sin(90) return 1;
     *	通过deg_rad_trans进行弧度角度转换
     *  如果觉得递归调用性能不够好
     *  可以自行改写为语法树
     *
     */
    static QString functionCalculator(const QStringList &expression);

    static void formulaToInfixExpression(QStringList &infixExpression);

    static QString qstrListCalculator(const QStringList &formulaList);

public:
    static QString cal(const QString &formula);

};

#endif