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

#ifndef __BIG_FLOAT_H__
#define __BIG_FLOAT_H__

#include <iostream>
#include <vector>
#include <string>
#include <cmath>

#include <QString>
#include <QDebug>

#include <gsl/gsl_math.h>
#include <gsl/gsl_sf_trig.h>
#include <gsl/gsl_sf_gamma.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_fft_complex.h>

#include "InputSymbols.h"

using namespace std;

class BigFloat
{
private:

    static const     int    PRECISION     = 15;
    static const     int    CAL_PRECISION = PRECISION + 5;
    static const     int    MAX_LIMIT     = CAL_PRECISION;
    static constexpr double EPS           = 1e-15;

    bool    error;

    QString symbol;
    QString integer;
    QString point;
    QString decimal;
    QString sciE;
    QString sciSymbol;
    QString sciNum;

    // 小数点后多少位 用于计算乘法
    int decimalPlaces;

public:
    static const BigFloat ZERO;
    static const BigFloat ONE;
    static const BigFloat TEN;
    static const BigFloat E;
    static const BigFloat PI;
    static const BigFloat PI_DEG;

    BigFloat();
    BigFloat(const int      &);
    BigFloat(const double   &);
    BigFloat(const char     *);
    BigFloat(const QString  &);
    BigFloat(const BigFloat &);

    int  size      () const;
    bool isZero    () const;
    bool isInteger () const;
    // 打印调试信息
    void print() const;    
    
    QString toQString () const;
    double  toDouble  () const;
    QString convertToScientificCounting() const;

    static  void swap    (      BigFloat &,       BigFloat &);
    static  int  compare (const BigFloat &, const BigFloat &);
    
    BigFloat& operator = (const int      &);
    BigFloat& operator = (const double   &);
    BigFloat& operator = (const char     *);
    BigFloat& operator = (const QString  &);
    BigFloat& operator = (const BigFloat &);

    BigFloat & operator += (const BigFloat &);
    BigFloat & operator -= (const BigFloat &);
    BigFloat & operator *= (const BigFloat &);
    BigFloat & operator /= (const BigFloat &);
    BigFloat & operator ^= (const BigFloat &);

    friend BigFloat operator + (const BigFloat &);
    friend BigFloat operator - (const BigFloat &);
    friend BigFloat operator + (const BigFloat &, const BigFloat &);
    friend BigFloat operator - (const BigFloat &, const BigFloat &);
    friend BigFloat operator * (const BigFloat &, const BigFloat &);
    friend BigFloat operator / (const BigFloat &, const BigFloat &);
    friend BigFloat operator ^ (const BigFloat &, const BigFloat &);

    friend bool operator == (const BigFloat &, const BigFloat &);
    friend bool operator != (const BigFloat &, const BigFloat &);
    friend bool operator <  (const BigFloat &, const BigFloat &);
    friend bool operator <= (const BigFloat &, const BigFloat &);
    friend bool operator >  (const BigFloat &, const BigFloat &);
    friend bool operator >= (const BigFloat &, const BigFloat &);

    /*
     *  三角函数,默认输入角度,如果输入弧度,请使用重载函数
     *  用法:
     *  输入为角度:
     *  BigFloat::Sin(一个大数类) 等价于 BigFloat::Sin(一个大数类, 'd')
     *  输入为弧度:
     *  BigFloat::Sin(一个大数类, 'r')
     *  
     *  三角函数,默认输出角度,如果输出弧度,请使用重载函数
     *  输出为角度:
     *  BigFloat::ASin(一个大数类) 等价于 BigFloat::ASin(一个大数类, 'd')
     *  输出为弧度:
     *  BigFloat::ASin(一个大数类, 'r')
     *  
     */
    BigFloat DEGtoRAD () const;
    BigFloat RADtoDEG () const;
    
    static BigFloat Sin      (const BigFloat &);
    static BigFloat Sin      (const BigFloat &, const QString);
    static BigFloat Cos      (const BigFloat &);
    static BigFloat Cos      (const BigFloat &, const QString);
private:
    static int      TanCheck (const BigFloat &, const QString);
public:
    static BigFloat Tan      (const BigFloat &);
    static BigFloat Tan      (const BigFloat &, const QString);
    static BigFloat ASin     (const BigFloat &);
    static BigFloat ASin     (const BigFloat &, const QString);
    static BigFloat ACos     (const BigFloat &);
    static BigFloat ACos     (const BigFloat &, const QString);
    static BigFloat ATan     (const BigFloat &);
    static BigFloat ATan     (const BigFloat &, const QString);

    static BigFloat Ln   (const BigFloat &);
    static BigFloat Lg   (const BigFloat &);
    static BigFloat Abs  (const BigFloat &);
    static BigFloat Fact (const BigFloat &);

    // friend std::ostream& operator << (std::ostream &, const BigFloat &);
    // friend std::istream& operator >> (std::istream &,       BigFloat &);
};


#endif
