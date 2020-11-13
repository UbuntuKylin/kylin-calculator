#include "InputSymbols.h"
//  "2nd,Ans,(,),1/x,x²,x³,y^x,x!,√x,³√x,x√y,
// QString btnList = "C,÷,×,B,—,+,=,%,.";
const QString InputSymbols::T_BRACKET  = "(,)";
const QString InputSymbols::T_NUMBER   = "0,1,2,3,4,5,6,7,8,9,.,%,00";
const QString InputSymbols::T_OPERATOR = "+,—,×,÷,=";
const QString InputSymbols::T_FUNCTION = "sin,cos,tan,asin,acos,atan,log,ln";
const QString InputSymbols::T_TRANS    = "1/x,x²,x³,y^x,√x,³√x,x√y,x!";  //))
const QString InputSymbols::T_SCI_NUM  = "PI,E,ANS";

const QStringList InputSymbols::BRACKET_LIST             = T_BRACKET    .split(",");
const QStringList InputSymbols::NUMBER_LIST              = T_NUMBER     .split(",");
const QStringList InputSymbols::OPERATOR_LIST            = T_OPERATOR   .split(",");
const QStringList InputSymbols::ZERO_TO_NINE             = NUMBER_LIST  .mid(0, 10);
const QStringList InputSymbols::ARITHMETIC_OPERATOR_LIST = OPERATOR_LIST.mid(0, 4);
const QStringList InputSymbols::FUNCTION_LIST            = T_FUNCTION   .split(",");
const QStringList InputSymbols::TRANS_LIST               = T_TRANS      .split(",");
const QStringList InputSymbols::SCI_NUM_LIST             = T_SCI_NUM    .split(",");

const QString InputSymbols::BRACKET_QSTR             = BRACKET_LIST            .join("");
const QString InputSymbols::NUMBER_QSTR              = NUMBER_LIST             .join("");
const QString InputSymbols::OPERATOR_QSTR            = OPERATOR_LIST           .join("");
const QString InputSymbols::ARITHMETIC_OPERATOR_QSTR = ARITHMETIC_OPERATOR_LIST.join("");
const QString InputSymbols::FUNCTION_QSTR            = FUNCTION_LIST           .join("");
const QString InputSymbols::TRANS_QSTR               = TRANS_LIST              .join("");
const QString InputSymbols::SCI_NUM_QSTR             = SCI_NUM_LIST            .join("");

const QString InputSymbols::SPACE               = " ";
const QString InputSymbols::END                 = "$";
const QString InputSymbols::ANS_END             = "@";
const QString InputSymbols::SCI_NUM_END         = "#"; 
const QString InputSymbols::SCIENTIFIC_NOTATION = "e";
const QString InputSymbols::POWER_SYMBOL        = "^";
const QString InputSymbols::FACTORIAL_SYMBOL    = "!";

const QString InputSymbols::EMPTY      = QString();
const QString InputSymbols::INF_SYMBOL = "inf";
const QString InputSymbols::NAN_SYMBOL = "nan";
const QString InputSymbols::DEG_SYMBOL = "deg";
const QString InputSymbols::RAD_SYMBOL = "rad";

const QString InputSymbols::ROOT        = "root";

const QString InputSymbols::STANDARD    = "standard";
const QString InputSymbols::SCIENTIFIC  = "scientific";

const QString InputSymbols::CLEAN       = "C";
const QString InputSymbols::BACKSPACE   = "B";

const QString InputSymbols::ERROR       = "error";
const QString InputSymbols::ERROR_INF   = "error_inf";
const QString InputSymbols::ERROR_NAN   = "error_nan";

const QString InputSymbols::FUNCTION = "function";
const QString InputSymbols::TRANS    = "trans";
const QString InputSymbols::SCI_NUM   = "sci_num";

const QString InputSymbols::BRACKET_L = BRACKET_LIST[0];
const QString InputSymbols::BRACKET_R = BRACKET_LIST[1];

const QString InputSymbols::ZERO        = NUMBER_LIST[0];
const QString InputSymbols::ONE         = NUMBER_LIST[1];
const QString InputSymbols::TWO         = NUMBER_LIST[2];
const QString InputSymbols::THREE       = NUMBER_LIST[3];
const QString InputSymbols::FOUR        = NUMBER_LIST[4];
const QString InputSymbols::FIVE        = NUMBER_LIST[5];
const QString InputSymbols::SIX         = NUMBER_LIST[6];
const QString InputSymbols::SEVEN       = NUMBER_LIST[7];
const QString InputSymbols::EIGHT       = NUMBER_LIST[8];
const QString InputSymbols::NINE        = NUMBER_LIST[9];
const QString InputSymbols::POINT       = NUMBER_LIST[10];
const QString InputSymbols::PERCENT     = NUMBER_LIST[11];
const QString InputSymbols::DOUBLE_ZERO = NUMBER_LIST[12];


const QString InputSymbols::ADD   = OPERATOR_LIST[0];
const QString InputSymbols::SUB   = OPERATOR_LIST[1];
const QString InputSymbols::MUL   = OPERATOR_LIST[2];
const QString InputSymbols::DIV   = OPERATOR_LIST[3];
const QString InputSymbols::EQUAL = OPERATOR_LIST[4];

const QString InputSymbols::SIN    = FUNCTION_LIST[0];
const QString InputSymbols::COS    = FUNCTION_LIST[1];
const QString InputSymbols::TAN    = FUNCTION_LIST[2];
const QString InputSymbols::ARCSIN = FUNCTION_LIST[3];
const QString InputSymbols::ARCCOS = FUNCTION_LIST[4];
const QString InputSymbols::ARCTAN = FUNCTION_LIST[5];
const QString InputSymbols::LOG    = FUNCTION_LIST[6];
const QString InputSymbols::LN     = FUNCTION_LIST[7];

const QString InputSymbols::RECIPROCAL  = TRANS_LIST[0];
const QString InputSymbols::SQUARE      = TRANS_LIST[1];
const QString InputSymbols::CUBE        = TRANS_LIST[2];
const QString InputSymbols::POWER       = TRANS_LIST[3];
const QString InputSymbols::SQUARE_ROOT = TRANS_LIST[4];
const QString InputSymbols::CUBE_ROOT   = TRANS_LIST[5];
const QString InputSymbols::POWER_ROOT  = TRANS_LIST[6];
const QString InputSymbols::FACTORIAL   = TRANS_LIST[7];

const QString InputSymbols::PI  = SCI_NUM_LIST[0];
const QString InputSymbols::E   = SCI_NUM_LIST[1];
const QString InputSymbols::ANS = SCI_NUM_LIST[2];

const QStringList InputSymbols::ALL_INPUT_SYMBOL
= QStringList(STANDARD  )
+ QStringList(SCIENTIFIC)
+ QStringList(CLEAN     )
+ QStringList(BACKSPACE )
+ QStringList(DEG_SYMBOL)
+ QStringList(RAD_SYMBOL)
+ BRACKET_LIST
+ NUMBER_LIST
+ OPERATOR_LIST
+ FUNCTION_LIST
+ TRANS_LIST
+ SCI_NUM_LIST;