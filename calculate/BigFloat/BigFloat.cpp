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
 
#include "BigFloat.h"

const BigFloat BigFloat::ZERO   = BigFloat();
const BigFloat BigFloat::ONE    = BigFloat(1);
const BigFloat BigFloat::TEN    = BigFloat(10);
const BigFloat BigFloat::E      = BigFloat(M_E);
const BigFloat BigFloat::PI     = BigFloat(M_PI);
const BigFloat BigFloat::PI_DEG = BigFloat(180);

// 构造函数
BigFloat::BigFloat()
{
    
    this->error         = false;

    this->symbol        = InputSymbols::EMPTY;
    this->integer       = InputSymbols::ZERO;
    this->point         = InputSymbols::EMPTY;
    this->decimal       = InputSymbols::EMPTY;
    this->sciE          = InputSymbols::EMPTY;
    this->sciSymbol     = InputSymbols::EMPTY;
    this->sciNum        = InputSymbols::EMPTY;
    
    this->decimalPlaces = 0;
}

BigFloat::BigFloat(const int &value)
{
    QString qstr = QString::number(value);
    while(qstr.indexOf('-') != -1) {
        qstr[qstr.indexOf('-')] = InputSymbols::SUB[0];
    }
    *this = BigFloat(qstr);
}

BigFloat::BigFloat(const double &value)
{
    QString qstr = QString::number(value, 'f', CAL_PRECISION);
    while(qstr.indexOf('-') != -1) {
        qstr[qstr.indexOf('-')] = InputSymbols::SUB[0];
    }
    *this = BigFloat(qstr);
}

BigFloat::BigFloat(const char *value)
{
    *this = BigFloat(QString(value));
}

BigFloat::BigFloat(const QString &value)
{
    int pointIdx;
    int pointIdxBack;
    int sciIdx;

    this->error = false;
    if ( value.contains(InputSymbols::INF_SYMBOL) || value.contains(InputSymbols::NAN_SYMBOL) )
        error = true;

    this->symbol = value[0];
    if (this->symbol != InputSymbols::SUB)
        this->symbol = InputSymbols::EMPTY;

    pointIdx = value.indexOf(InputSymbols::POINT);
    pointIdxBack = pointIdx == -1 ? 0 : value.size() - pointIdx -1;

    this->integer = value.left(pointIdx);
    if (this->symbol == InputSymbols::SUB)
        this->integer.remove(0, 1);
    
    this->point = ( pointIdx == -1 || pointIdx == value.size()-1 ) ? InputSymbols::EMPTY : InputSymbols::POINT;

    this->decimal = value.right(pointIdxBack);
    
    this->decimalPlaces = pointIdxBack;

    sciIdx = value.indexOf(InputSymbols::SCIENTIFIC_NOTATION);
    if (sciIdx != -1) {
        this->sciE      = InputSymbols::SCIENTIFIC_NOTATION;
        this->sciSymbol = value[sciIdx + 1];
        this->sciNum    = value.right(value.size()-sciIdx-2);
        if(this->point == 0) {
            int intSciIdx = this->integer.indexOf(InputSymbols::SCIENTIFIC_NOTATION);

            this->integer = this->integer.left(intSciIdx);
            this->decimalPlaces = 0;
        }
        else if(this->point != 0) {
            int decSciIdx   = this->decimal.indexOf(InputSymbols::SCIENTIFIC_NOTATION);
            
            this->decimal   = this->decimal.left(decSciIdx);
            this->decimalPlaces -= decSciIdx - 1;
        }
    } else {
        this->sciE      = InputSymbols::EMPTY;
        this->sciSymbol = InputSymbols::EMPTY;
        this->sciNum    = InputSymbols::EMPTY;
    }
    if (this->integer.size() > MAX_LIMIT || this->decimal.size() > MAX_LIMIT)
        *this = BigFloat(this->convertToScientificCounting());

    if (this->isInteger()) {
        this->point         = InputSymbols::EMPTY;
        this->decimal       = InputSymbols::EMPTY;
        this->decimalPlaces = 0;
    }
    if (this->isZero())
        *this = ZERO;
}

BigFloat::BigFloat(const BigFloat &value)
{
    this->error         = value.error;
    this->symbol        = value.symbol;
    this->integer       = value.integer;
    this->point         = value.point;
    this->decimal       = value.decimal;
    this->decimalPlaces = value.decimalPlaces;
    this->sciE          = value.sciE;
    this->sciSymbol     = value.sciSymbol;
    this->sciNum        = value.sciNum;
}

int BigFloat::size() const
{
    return this->toQString().size();
}

bool BigFloat::isZero() const
{
    if (this->toQString().contains(InputSymbols::SCIENTIFIC_NOTATION))
        return false;

    if (this->toQString() == InputSymbols::ZERO)
        return true;
    
    if (fabs(this->toDouble()) < EPS)
        return true;

    return false;
}

bool BigFloat::isInteger() const
{
    BigFloat t(*this);
    t.integer   = InputSymbols::ZERO;
    t.sciE      = InputSymbols::EMPTY;
    t.sciSymbol = InputSymbols::EMPTY;
    t.sciNum    = InputSymbols::ZERO;
    return t.isZero();
}

// 成员函数
void BigFloat::print() const
{
    qDebug() << "+--------print-start------------+";
    qDebug() << "error         is " << this->error;
    qDebug() << "symbol        is " << qPrintable(this->symbol   );
    qDebug() << "integer       is " << qPrintable(this->integer  );
    qDebug() << "point         is " << qPrintable(this->point    );
    qDebug() << "decimal       is " << qPrintable(this->decimal  );
    qDebug() << "sciE          is " << qPrintable(this->sciE     );
    qDebug() << "sciSymbol     is " << qPrintable(this->sciSymbol);
    qDebug() << "sciNum        is " << qPrintable(this->sciNum   );
    qDebug() << "decimalPlaces is " << this->decimalPlaces;
    qDebug() << "+--------print--end-------------+";
}

QString BigFloat::toQString() const
{ 
    return    (this->symbol    == InputSymbols::EMPTY ? InputSymbols::EMPTY : this->symbol   )
            +  this->integer 
            + (this->point     == InputSymbols::EMPTY ? InputSymbols::EMPTY : this->point    )
            +  this->decimal
            + (this->sciE      == InputSymbols::EMPTY ? InputSymbols::EMPTY : this->sciE     )
            + (this->sciSymbol == InputSymbols::EMPTY ? InputSymbols::EMPTY : this->sciSymbol)
            +  this->sciNum;
}

double BigFloat::toDouble() const
{
    QString temp = this->toQString();
    while (temp.indexOf(InputSymbols::SUB) != -1)
        temp[temp.indexOf(InputSymbols::SUB)] = '-';
    return temp.toDouble();
}

QString BigFloat::convertToScientificCounting() const
{
    QString qstr = QString::number(this->toDouble(), 'g', CAL_PRECISION);
    while(qstr.indexOf('-') != -1) {
        qstr[qstr.indexOf('-')] = InputSymbols::SUB[0];
    }
    return qstr;
}

void BigFloat::swap(BigFloat &value1, BigFloat &value2) {
    BigFloat t; 
    t      = value1;
    value1 = value2;
    value2 = t;
}
int  BigFloat::compare(const BigFloat &value1, const BigFloat &value2)
{
    double a = value1.toDouble();
    double b = value2.toDouble();

    if (value1.isZero() && value2.isZero())
        return 0;

    if (value1.isZero()) {
        if (value2.sciE != InputSymbols::SCIENTIFIC_NOTATION) {
            if (fabs(a-b)<EPS)
                return 0;
            return a > b ? 1: -1;
        }
        else {
            if(value2.sciSymbol == InputSymbols::ADD)
                return -1;
            else
                return 1;
        }
    }

    if (value2.isZero()) {
        if (value1.sciE != InputSymbols::SCIENTIFIC_NOTATION) {
            if (fabs(a-b)<EPS)
                return 0;
            return a > b ? 1: -1;
        }
        else {
            if(value1.sciSymbol == InputSymbols::ADD)
                return 1;
            else
                return -1;
        }
    }

    if (value1.toQString().contains(InputSymbols::SCIENTIFIC_NOTATION) 
     || value2.toQString().contains(InputSymbols::SCIENTIFIC_NOTATION)) {
    
        return (a, b, EPS);
    }

    return gsl_fcmp(a, b, EPS);
}

BigFloat& BigFloat::operator = (const int &value)
{
    *this = BigFloat(value);
    return *this;
}

BigFloat& BigFloat::operator = (const double &value)
{
    *this = BigFloat(value);
    return *this;
}

BigFloat& BigFloat::operator = (const char *value)
{
    *this = BigFloat(value);
    return *this;
}

BigFloat& BigFloat::operator = (const QString &value)
{
    *this = BigFloat(value);
    return *this;
}

BigFloat& BigFloat::operator = (const BigFloat &value)
{
    this->error         = value.error;
    this->symbol        = value.symbol;
    this->integer       = value.integer;
    this->point         = value.point;
    this->decimal       = value.decimal;
    this->decimalPlaces = value.decimalPlaces;
    this->sciE          = value.sciE;
    this->sciSymbol     = value.sciSymbol;
    this->sciNum        = value.sciNum;
    return *this;
}

BigFloat& BigFloat::operator += (const BigFloat& value)
{
    *this = BigFloat(this->toDouble() + value.toDouble());
    return *this;
}

BigFloat& BigFloat::operator -= (const BigFloat& value)
{
    *this = BigFloat(this->toDouble() - value.toDouble());
    return *this;
}

BigFloat& BigFloat::operator *= (const BigFloat& value)
{
    *this = BigFloat(this->toDouble() * value.toDouble());
    return *this;
}

BigFloat& BigFloat::operator /= (const BigFloat& value)
{
    *this = BigFloat(this->toDouble() / value.toDouble());
    return *this;
}

BigFloat& BigFloat::operator ^= (const BigFloat& value)
{
    *this = BigFloat( pow(this->toDouble(), value.toDouble()));
    return *this;
}

BigFloat operator + (const BigFloat& value)
{
    return value;
}

BigFloat operator - (const BigFloat& value)
{
    BigFloat t(value);
    if (t.symbol == InputSymbols::EMPTY) {
        t.symbol = InputSymbols::SUB;
    }
    else if (t.symbol == InputSymbols::SUB){
        t.symbol = InputSymbols::EMPTY;
    }
    return t;
}

BigFloat operator + (const BigFloat& value1, const BigFloat& value2)
{
    BigFloat t(value1);
    t += value2;
    return t;
}

BigFloat operator - (const BigFloat& value1, const BigFloat& value2)
{
    BigFloat t(value1);
    t -= value2;
    return t;
}

BigFloat operator * (const BigFloat& value1, const BigFloat& value2)
{
    BigFloat t(value1);
    t *= value2;
    return t;
}

BigFloat operator / (const BigFloat& value1, const BigFloat& value2)
{
    BigFloat t(value1);
    t /= value2;
    return t;
}

BigFloat operator ^ (const BigFloat& value1, const BigFloat& value2)
{
    BigFloat t(value1);
    t ^= value2;
    return t;
}

bool operator == (const BigFloat& value1, const BigFloat& value2)
{
    if (BigFloat::compare(value1, value2) == 0)
        return true;
    return false;
}

bool operator != (const BigFloat& value1, const BigFloat& value2)
{
    if (BigFloat::compare(value1, value2) != 0)
        return true;
    return false;
}

bool operator < (const BigFloat& value1, const BigFloat& value2)
{
    if (BigFloat::compare(value1, value2) < 0)
        return true;
    return false;
}

bool operator <= (const BigFloat& value1, const BigFloat& value2)
{
    if (BigFloat::compare(value1, value2) <= 0)
        return true;
    return false;
}

bool operator > (const BigFloat& value1, const BigFloat& value2)
{
    if (BigFloat::compare(value1, value2) > 0)
        return true;
    return false;
}

bool operator >= (const BigFloat& value1, const BigFloat& value2)
{
    if (BigFloat::compare(value1, value2) >= 0)
        return true;
    return false;
}

BigFloat BigFloat::DEGtoRAD() const
{
    return (*this) *  PI / PI_DEG;
}

BigFloat BigFloat::RADtoDEG() const
{
    return (*this) *  PI_DEG / PI;
}


BigFloat BigFloat::Sin(const BigFloat &value)
{
    return BigFloat(sin(value.DEGtoRAD().toDouble()));
}

BigFloat BigFloat::Sin(const BigFloat &value, const QString angel)
{
    if (angel == InputSymbols::DEG_SYMBOL)
        return Sin(value);
    else
        return BigFloat(sin(value.toDouble()));
}

BigFloat BigFloat::Cos(const BigFloat &value)
{
    return BigFloat(cos(value.DEGtoRAD().toDouble()));
}

BigFloat BigFloat::Cos(const BigFloat &value, const QString angel)
{
    if (angel == InputSymbols::DEG_SYMBOL)
        return Cos(value);
    else
        return BigFloat(cos(value.toDouble()));
}

int BigFloat::TanCheck(const BigFloat &value, const QString angel)
{
    BigFloat t(value);

    if (angel == InputSymbols::RAD_SYMBOL) {
        t = value.RADtoDEG();
    }

    if (((t - BigFloat(90)) / BigFloat::PI_DEG ).isInteger()) {
        
        return 1;
    }
    return 0;
}

BigFloat BigFloat::Tan(const BigFloat &value)
{
    if (value.TanCheck(value, InputSymbols::DEG_SYMBOL) == 1) {
        
        return BigFloat(InputSymbols::NAN_SYMBOL);
    }
    
    return BigFloat(tan(value.DEGtoRAD().toDouble()));
}

BigFloat BigFloat::Tan(const BigFloat &value, const QString angel)
{
    if (angel == InputSymbols::DEG_SYMBOL)
        return Tan(value);
    if (value.TanCheck(value, InputSymbols::RAD_SYMBOL) == 1)
        return BigFloat(InputSymbols::INF_SYMBOL);
    if (value.TanCheck(value, InputSymbols::RAD_SYMBOL) == -1)
        return BigFloat(InputSymbols::SUB + InputSymbols::INF_SYMBOL);
    return BigFloat(tan(value.toDouble()));
    
}

BigFloat BigFloat::ASin(const BigFloat &value)
{
    return BigFloat(asin(value.toDouble())).RADtoDEG();
}

BigFloat BigFloat::ASin(const BigFloat &value, const QString angel)
{
    if (angel == InputSymbols::DEG_SYMBOL)
        return ASin(value);
    else
        return BigFloat(asin(value.toDouble()));
}

BigFloat BigFloat::ACos(const BigFloat &value)
{
    return BigFloat(acos(value.toDouble())).RADtoDEG();
}

BigFloat BigFloat::ACos(const BigFloat &value, const QString angel)
{
    if (angel == InputSymbols::DEG_SYMBOL)
        return ACos(value);
    else
        return BigFloat(acos(value.toDouble()));
}

BigFloat BigFloat::ATan(const BigFloat &value)
{
    return BigFloat(atan(value.toDouble())).RADtoDEG();
}

BigFloat BigFloat::ATan(const BigFloat &value, const QString angel)
{
    if (angel == InputSymbols::DEG_SYMBOL)
        return ATan(value);
    else
        return BigFloat(atan(value.toDouble()));
}

BigFloat BigFloat::Ln(const BigFloat &value)
{
    return BigFloat(log(value.toDouble()));
}

BigFloat BigFloat::Lg(const BigFloat &value)
{
    return BigFloat(log10(value.toDouble()));
}

BigFloat BigFloat::Abs(const BigFloat &value)
{
    if(value.symbol == InputSymbols::EMPTY)
        return value;
    else
        return -value;
}

BigFloat BigFloat::Fact(const BigFloat &value)
{
    // cancel default gsl error handler
    gsl_set_error_handler_off();
    return BigFloat(gsl_sf_gamma((value + ONE).toDouble()));
}

// std::ostream & operator << (std::ostream &stream, const BigFloat &value)
// {
//     stream << value.toQString().toStdString();
//     return stream;
// }

// std::istream & operator >> (std::istream &stream, BigFloat &value)
// {
//     std::string str;
//     stream >> str;
//     QString qstr = QString::fromStdString(str);
//     value = BigFloat(qstr);
//     return stream;
// }
