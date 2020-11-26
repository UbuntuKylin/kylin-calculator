#ifndef __INPUT_SYMBOLS_H__
#define __INPUT_SYMBOLS_H__

#include <QString>
#include <QStringList>

class InputSymbols
{
private:
    /*
     *  先这样定义 以后从其他位置获取
     *  T_BRACKET  = "(,)";
     *  T_NUMBER   = "0,00,1,2,3,4,5,6,7,8,9";
     *  T_OPERATOR = "+,-,*,/,=,%,.";
     *  T_FUNCTION = "sin,cos,tan,asin,acos,atan,log,ln";
     *  T_TRANS    = "x^(-1),x^(2),x^(3),x^(y,x^(1/2),x^(1/3),x^(1/y,x!";  //))
     *  T_SCI_NUM  = "PI,E,ANS";
     */
    static const QString T_BRACKET;
    static const QString T_NUMBER;
    static const QString T_OPERATOR;
    static const QString T_FUNCTION;
    static const QString T_TRANS;
    static const QString T_SCI_NUM;

public:
    static const QStringList BRACKET_LIST;
    static const QStringList NUMBER_LIST;
    static const QStringList OPERATOR_LIST;
    static const QStringList ZERO_TO_NINE;
    static const QStringList ARITHMETIC_OPERATOR_LIST;
    static const QStringList FUNCTION_LIST;
    static const QStringList TRANS_LIST;
    static const QStringList SCI_NUM_LIST;

    static const QString BRACKET_QSTR;
    static const QString NUMBER_QSTR;
    static const QString OPERATOR_QSTR;
    static const QString ARITHMETIC_OPERATOR_QSTR;
    static const QString FUNCTION_QSTR;
    static const QString TRANS_QSTR;
    static const QString SCI_NUM_QSTR;


    static const QString SPACE;
    static const QString END;
    static const QString ANS_END;
    static const QString SCI_NUM_END;
    static const QString SCIENTIFIC_NOTATION;
    static const QString POWER_SYMBOL;
    static const QString FACTORIAL_SYMBOL;
    
    static const QString EMPTY;
    static const QString INF_SYMBOL;
    static const QString NAN_SYMBOL;
    static const QString DEG_SYMBOL;
    static const QString RAD_SYMBOL;

    static const QString ROOT;

    static const QString STANDARD;
    static const QString SCIENTIFIC;

    static const QString CLEAN;
    static const QString BACKSPACE;

    static const QString ERROR;
    static const QString ERROR_INF;
    static const QString ERROR_NAN;

    static const QString FUNCTION;
    static const QString TRANS;
    static const QString SCI_NUM;

    static const QString BRACKET_L;
    static const QString BRACKET_R;

    static const QString ZERO;
    static const QString ONE;
    static const QString TWO;
    static const QString THREE;
    static const QString FOUR;
    static const QString FIVE;
    static const QString SIX;
    static const QString SEVEN;
    static const QString EIGHT;
    static const QString NINE;
    static const QString POINT;
    static const QString PERCENT;
    static const QString DOUBLE_ZERO;

    static const QString ADD;
    static const QString SUB;
    static const QString MUL;
    static const QString DIV;
    static const QString EQUAL;

    static const QString SIN;
    static const QString COS;
    static const QString TAN;
    static const QString ARCSIN;
    static const QString ARCCOS;
    static const QString ARCTAN;
    static const QString LOG;
    static const QString LN;

    static const QString RECIPROCAL;
    static const QString SQUARE;
    static const QString CUBE;
    static const QString POWER;
    static const QString SQUARE_ROOT;
    static const QString CUBE_ROOT;
    static const QString POWER_ROOT;
    static const QString FACTORIAL;

    static const QString PI;
    static const QString E;
    static const QString ANS;

    static const QStringList ALL_INPUT_SYMBOL;
};

#endif