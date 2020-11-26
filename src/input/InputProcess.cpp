#include "InputProcess.h"

QVector<QString> InputProcess::res = QVector<QString>{ZERO, ZERO, EMPTY,EMPTY,EMPTY,EMPTY};

QString InputProcess::qstrNow      = ZERO;
QString InputProcess::qstrPrepare  = EMPTY;
QString InputProcess::labelNow     = ZERO;
QString InputProcess::labelPrepare = EMPTY;
QString InputProcess::calAns       = EMPTY;
QString InputProcess::lastAns      = EMPTY;
QStringList InputProcess::calHistory = QStringList();

InputJudgmentGraph InputProcess::G = InputJudgmentGraph();

bool InputProcess::b_couldBeCalFlag    = false;
bool InputProcess::b_qstrAddFlag       = false;
bool InputProcess::b_qstrNowUpdateFlag = false;
bool InputProcess::b_qstrUpdateFlag    = false;

void InputProcess::init()
{
    qstrNow      = ZERO;
    qstrPrepare  = EMPTY;
    labelNow     = ZERO;
    labelPrepare = EMPTY;
    lastAns      = EMPTY;
    res = QVector<QString>{ZERO, ZERO, EMPTY,EMPTY,EMPTY,EMPTY};
}

QString InputProcess::addComma(const QString &qstr)
{
    QString s = qstr;
    if (s.isEmpty())
        return EMPTY;

    int pointFlag = 0;
    int pointIndex;

    for (int i = 0; i < s.size(); i++) {
        if ( s[i] == POINT[0] 
          || s[i] == SCIENTIFIC_NOTATION[0]
          || s[i] == ANS_END[0] ) {
            
            pointFlag = 1;
            pointIndex = i;
            break;
        }
    }

    if(pointFlag == 1) {
        return addComma(s.mid(0,pointIndex)) + s.mid(pointIndex, s.size()-pointIndex);
    }
    else {
        QString ans;
        for(int i = s.size() - 3; i > 0; i -= 3)
            s.insert(i, ",");
        return s;
    }
    return EMPTY;
}

bool InputProcess::couldBeCal(const QString &qstr)
{
    // 1.
    if (qstr.size() == 0)
        return false;
    QString ch = qstr.right(1);
    // 2.
    if ( isArithmeticOperator(ch)
      || ch == BRACKET_L
      || ch == POINT
      || ch == POWER_SYMBOL
      || FUNCTION_QSTR.contains(ch) ) {

        return false;
    }

    if (isCorrectFormula(qstr).first == 0) {
        return false;
    }

    return true;
}

int InputProcess::qstrAdd(const QString &text)
{
    int formulaOrNum = formulaTypeCheck(qstrNow);

    // 括号判定
    if (BRACKET_LIST.contains(text)) {
        QString ch = qstrNow.right(1);

        // 左括号
        if (text == BRACKET_L) {
            // 空或0直接加
            if ( qstrNow.size() == 0 
              || qstrNow.size() == 1 && qstrNow == ZERO ) {
            
                qstrNow = text;
                return CORRECT_QSTR_ADD;
            }

            // 末尾是 + - * / ^ 左括号才可以加
            if ( isArithmeticOperator(ch)
              || ch == POWER_SYMBOL && ch == BRACKET_L) {

                qstrNow += text;
                return CORRECT_QSTR_ADD;
            }
            return CANNOT_ADD_BRACKET_L;
        }
        
        // 右括号
        if (text == BRACKET_R) {
            if ( ch == BRACKET_R 
              || ZERO_TO_NINE.contains(ch)) {

                qstrNow += BRACKET_R;
                if (findBracketPair(qstrNow, qstrNow.size()-1) == -1) {
                    qstrNow.chop(1);
                    return CANNOT_ADD_BRACKET_R;
                }
                return CORRECT_QSTR_ADD;
            }
            return CANNOT_ADD_BRACKET_R;
        }
        return CANNOT_ADD_BRACKET_R;
    }
    
    // 想想
    if (text == EQUAL) {
        return true;
    }
    
    // + - * / 0 1 2 3 4 5 6 7 8 9 . % 00 C B 直接加
    if ( NUMBER_LIST .contains(text)
      || text == CLEAN
      || text == BACKSPACE
      ||  ARITHMETIC_OPERATOR_LIST.contains(text) ) {

        // 00 判断
        if (text == DOUBLE_ZERO) {
            if ( qstrNow.size() == 0
              || qstrNow.size() == 1 && qstrNow == ZERO ) {
                
                return CANNOT_ADD_DOUBLE_ZERO;
            }

            QString qstrBack = qstrNow.right(1);
            if (isCorrectInt(getAnsNumberFromBack(qstrNow)).first != 0) {
                return CANNOT_ADD_DOUBLE_ZERO;
            }
        }
        qstrNow += text;
        return CORRECT_QSTR_ADD;
    }

    // function
    if (FUNCTION_LIST.contains(text)) {
        if ( (qstrNow.size() == 1 && qstrNow.left(1) == BRACKET_L)) {
            return CANNOT_ADD_FUNCTION;
        }
        if ( formulaOrNum == 0
          || formulaOrNum == 1) {
            
            qstrNow = qstrNow + text + BRACKET_L;
        }
        else if ( formulaOrNum ==  2
               || formulaOrNum == -2
               || formulaOrNum == -1 ) {
            
            qstrNow = text + BRACKET_L + qstrNow + BRACKET_R;
        }
        else {
            return CANNOT_ADD_FUNCTION;
        }
        return CORRECT_QSTR_ADD;
    }

    // trans
    if (TRANS_LIST.contains(text)) {
        if ( (qstrNow.size() == 1 && qstrNow.left(1) == BRACKET_L) ) {
            return CANNOT_ADD_TRANS;
        }
        QStringList temp_trans = QString("x^(—1),x^(2),x^(3),x^(,x^(1÷2),x^(1÷3),x^(1÷,x!").split(",");  //))
        QString temp = text;
        temp = temp_trans.at(TRANS_LIST.indexOf(temp));
        temp.remove(0, 1);
        if (formulaOrNum == 0)
            qstrNow = ZERO + temp;
        else if (formulaOrNum == -1 || formulaOrNum == -2)
            qstrNow = qstrNow + temp;
        else if (formulaOrNum == 2)
            qstrNow = BRACKET_L + qstrNow + BRACKET_R + temp;
        else
            return CANNOT_ADD_TRANS;
        return CORRECT_QSTR_ADD;
    }

    // sci_num
    if (SCI_NUM_LIST.contains(text)) {
        if (qstrNow.size() == 0 || qstrNow.size() == 1 && qstrNow == ZERO) {
            if      (text == PI ) qstrNow = (BigFloat::PI).toQString() + SCI_NUM_END;
            else if (text == E  ) qstrNow = (BigFloat::E ).toQString() + SCI_NUM_END;
            else if (text == ANS) {
                qstrNow = lastAns + SCI_NUM_END;
                return !(lastAns.isEmpty());
            }
        }
        else if ( isArithmeticOperator(qstrNow.right(1)) || qstrNow.right(1) == BRACKET_L
            || qstrNow.right(1) == QString(ANS_END) || qstrNow == ZERO) {

            if      (text == PI ) qstrNow = qstrNow + (BigFloat::PI).toQString() + SCI_NUM_END;
            else if (text == E  ) qstrNow = qstrNow + (BigFloat::E ).toQString() + SCI_NUM_END;
            else if (text == ANS) {
                qstrNow = qstrNow + lastAns + SCI_NUM_END;
                return !(lastAns.isEmpty());
            }
        }
        else
            return CANNOT_ADD_SCI_NUM;
    }

    return INPUT_ERROR;
}

bool InputProcess::qstrNowUpdate(const QString &text)
{
    QString qstrBack;
    QString qstrBack2;

    if (qstrNow.size() >= 1) qstrBack  = QString(qstrNow.at(qstrNow.size()-1));
    if (qstrNow.size() >= 2) qstrBack2 = QString(qstrNow.at(qstrNow.size()-2));

    // 1. C check
    if (qstrBack == CLEAN) {
        init();
        return true;
    }

    // 8.
    if (qstrNow.contains(ANS_END)) {
        if (qstrBack2 == ANS_END) {
            if (ZERO_TO_NINE.contains(qstrBack))
                qstrNow.remove(0, qstrNow.indexOf(ANS_END) + 1);
            else if (qstrBack2 == POINT || qstrBack2 == PERCENT) {
                return false;
            }
        }
    }

    // 1. B check
    if (qstrBack == BACKSPACE) {
        if (qstrNow.size() <= 2) {
            init();
        }
        else {
            // 先去掉"B"
            qstrNow.chop(1);

            // 有末尾标识符的直接去掉整个数字
            if (qstrBack == ANS_END || qstrBack == SCI_NUM_END) {
                qstrNow.chop(getAnsNumberLengthFromBack(qstrNow));
            }
            else {
                qstrNow.chop(1);

                // 2.末尾是function
                if (qstrNow.size() && FUNCTION_QSTR.contains(qstrNow.right(1))) {
                    while (qstrNow.size() && FUNCTION_QSTR.contains(qstrNow.right(1)))
                        qstrNow.chop(1);
                }
            }
        }
        if (qstrNow.size() == 0)
            init();
        return true;
    }

    // 3.
    if ( qstrNow.size() >= 2
     && ( isArithmeticOperator(qstrBack2) || qstrBack2 == POINT )
     && ( isArithmeticOperator(qstrBack ) || qstrBack  == EQUAL ) ) {

        qstrNow.remove(qstrNow.size()-2, 1);
        return true;
    }

    // 4.
    if ( qstrNow.size() >= 2
     && ( isArithmeticOperator(qstrBack2) || isBracket(qstrBack2) )
     && ( qstrBack == POINT || qstrBack == PERCENT ) ) {

        qstrNow.insert(qstrNow.size()-1, ZERO);
        return true;
    }

    // 5.
    if (qstrNow.size() >= 2 && ZERO_TO_NINE.contains(qstrBack)) {

        if (qstrNow.size() == 2) {
            if (qstrBack2 == ZERO) {
                qstrNow.remove(0, 1);
                return qstrBack == ZERO ? true : false;
            }
        }
        QString qstrBack3 = QString(qstrNow[qstrNow.size()-3]);
        if ( isArithmeticOperator(qstrBack3) || qstrBack3 == BRACKET_L) {
            qstrNow.remove(qstrNow.size() - 2, 0);
            return qstrBack == ZERO ? true : false;
        }
        return true;
    }

    // 6.
    if (qstrBack == BRACKET_R) {
        if (findBracketPair(qstrNow, qstrNow.size() - 1) == -1) {
            qstrNow.chop(1);
            return false;
        }
        return true;
    }

    return false;
}

bool InputProcess::qstrUpdate(const QString &text)
{
    if (!calAns.size()) {
        return false;
    }

    if (calAns == qstrNow) {
        labelPrepare.clear();
        qstrPrepare.clear();
        return false;
    }

    if (text == EQUAL) {
        calHistory.append(clearANS_END_and_SCI_NUM_END
                            (isCorrectFormula(qstrNow).second + EQUAL +calAns)
                         );
        qstrPrepare.clear();
        qstrNow = calAns + ANS_END;
        lastAns = calAns;
    }

    return true;
}

void InputProcess::labelUpdate()
{
    // updatelabelNow
    QStringList qstrList;
    qstrList = formulaSplit(qstrNow);

    for (int i = 0; i < qstrList.size(); i++) {
        if (ZERO_TO_NINE.contains(QString(qstrList.at(i).at(0))))
            qstrList[i] = addComma(qstrList[i]);
    }
    labelNow = qstrList.join("");

    // updatelabelPrepare
    qstrList = formulaSplit(qstrPrepare);
    // qDebug () << qstrList;
    for (int i = 0; i < qstrList.size(); i++) {
        if (ZERO_TO_NINE.contains(QString(qstrList.at(i).at(0))))
            qstrList[i] = addComma(qstrList[i]);
    }
    labelPrepare = qstrList.join("");
}

void InputProcess::graphNodeUpdate(const QString &text)
{
    // 1.
    if ( ( G.getStatus(STANDARD) && !G.getStatus(ERROR) )
    ||   ( G.getStatus(SCIENTIFIC) && (!G.getStatus(ERROR_INF)  || !G.getStatus(ERROR_NAN) ) ) ) {

        // 2.
        if (text == CLEAN || text == BACKSPACE) {
            if (G.getStatus(STANDARD))
                G.updateAllSon(STANDARD, true);
            if (G.getStatus(SCIENTIFIC)) {
                G.updateAllSon(SCIENTIFIC, true);
            }
        }
        return ;
    }

    if (text == EQUAL) {
        if (calAns.contains(INF_SYMBOL)) {
            G.update(ERROR_INF, false);
        }
        else if (calAns.contains(NAN_SYMBOL)) {
            G.update(ERROR_NAN, false);
        }

        return ;
    }
    return ;
}

QVector<QString> InputProcess::output(const QString &text)
{
    labelUpdate();

    res[DISPLAY_ON_LABEL_NOW    ]
        = clearANS_END_and_SCI_NUM_END(labelNow);

    res[LABEL_NOW_CAL_QSTR      ]
        = clearANS_END_and_SCI_NUM_END(qstrNow);

    res[CAL_ANS                 ]
        = text == EQUAL ? clearANS_END_and_SCI_NUM_END(calAns) : EMPTY;

    res[LATEST_HISTORY          ]
        = (text == EQUAL && calHistory.size() && b_couldBeCalFlag)
         ? calHistory.at(calHistory.size()-1) : EMPTY;

    res[DISPLAY_ON_LABEL_PREPARE]
        = clearANS_END_and_SCI_NUM_END(labelPrepare);

    res[LABEL_PREPARE_CAL_QSTR  ]
        = clearANS_END_and_SCI_NUM_END(qstrPrepare);

    return res;

}

void InputProcess::init_inputFromButton()
{
    qstrPrepare  = EMPTY;
    labelNow     = EMPTY;
    labelPrepare = EMPTY;
    calAns       = EMPTY;

    b_couldBeCalFlag    = false;
    b_qstrAddFlag       = false;
    b_qstrNowUpdateFlag = false;
    b_qstrUpdateFlag    = false;
}

QVector<QString> InputProcess::inputFromButton(const QString &text)
{
    init_inputFromButton();

    if (!text.size())
        return res;

    // 测试输出
    if (text == "test") {
        res[DISPLAY_ON_LABEL_NOW    ] = "2,000";
        res[LABEL_NOW_CAL_QSTR      ] = "1000+1000=2000";
        res[CAL_ANS                 ] = "2000";
        res[LATEST_HISTORY          ] = "1000+1000=2000";
        res[DISPLAY_ON_LABEL_PREPARE] = "";
        res[LABEL_PREPARE_CAL_QSTR  ] = "";
        return res;
    }

    // 计算标志位处理
    if (text == STANDARD || text == SCIENTIFIC || text == DEG_SYMBOL || text == RAD_SYMBOL) {
        if (text == STANDARD) {
            G.updateAllSon(SCIENTIFIC, 0);
            init();
            G.updateAllSon(STANDARD, 1);
            calHistory.clear();
            return res;
        }
        if (text == SCIENTIFIC) {
            G.updateAllSon(STANDARD, 0);
            init();
            G.updateAllSon(SCIENTIFIC, 1);
            calHistory.clear();
            return res;
        }
        if (text == DEG_SYMBOL || text == RAD_SYMBOL) {
            QStringCalculator::cal(text);
            return res;
        }
    }

    if (!G.find(text))
        return res;

    b_qstrAddFlag = qstrAdd(text);
    qDebug() << "AfterQstrAddFlag:" << qstrNow;
    if (!b_qstrAddFlag) {
        return output(text);
    }
    b_qstrNowUpdateFlag = qstrNowUpdate(text);
    qDebug() << "AfterQstrNowUpdate:" << qstrNow;

    if (!b_qstrNowUpdateFlag) {
        return output(text);
    }

    QString qstrBack;
    QString qstrBack2;
    if (qstrNow.size() >= 1) qstrBack  = QString(qstrNow[qstrNow.size()-1]);
    if (qstrNow.size() >= 2) qstrBack2 = QString(qstrNow[qstrNow.size()-2]);

    b_couldBeCalFlag = couldBeCal(qstrNow);
    if (b_couldBeCalFlag) {
        calAns = QStringCalculator::cal(qstrNow);
        qDebug () << "calAns is" << calAns;
        bool b_qstrUpdateFlag = qstrUpdate(text);
        if (!b_qstrUpdateFlag) {
            return output(text);
        }
    }
    // labelUpdate();
    graphNodeUpdate(text);


    return output(text);
}


QVector<QString> InputProcess::inputFromButton(const char *text)
{
    return inputFromButton(QString(text));
}