#include "InputProcess.h"

QString InputProcess::qstrNow      = ZERO;
QString InputProcess::qstrPrepare  = EMPTY;
QString InputProcess::lastQstrPrepare = EMPTY;
QString InputProcess::labelNow     = ZERO;
QString InputProcess::labelPrepare = EMPTY;
QString InputProcess::calAns       = EMPTY;
QString InputProcess::lastAns      = EMPTY;
QStringList InputProcess::calHistory = QStringList();

InputJudgmentGraph InputProcess::G = InputJudgmentGraph();

void InputProcess::init()
{
    qstrNow      = ZERO;
    qstrPrepare  = EMPTY;
    lastQstrPrepare = EMPTY;
    labelNow     = ZERO;
    labelPrepare = EMPTY;
    lastAns      = EMPTY;
}

QString InputProcess::addComma(const QString &qstr)
{
    qDebug () << "im in addComma!" ; 
    qDebug() << qstr;
    QString s = qstr;
    if(s.isEmpty()) return "";

    int pointFlag = 0;
    int pointIndex;

    for (int i = 0; i < s.size(); i++) {

        if(s[i] == '.' || s[i] == 'e' || s[i] == ANS_END[0]) {
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
            s.insert(i,",");
        return s;
    }
    return EMPTY;
}

bool InputProcess::qstrAdd(const QString &text)
{
    int formulaOrNum = formulaTypeCheck(qstrNow);

    QString ch = qstrNow.right(1);
    if (BRACKET_LIST.contains(text)  ) {
        if (text == BRACKET_L) {
            if (qstrNow.size() == 0) {
                qstrNow += text;
                return true;
            }
            else if (qstrNow.size() == 1 && qstrNow.left(1) == ZERO) {
                qstrNow = BRACKET_L;
                return true;
            }
            
            if (isArithmeticOperator(ch) || ch == POWER_SYMBOL && ch == BRACKET_L) {
                return true;
            }
            return false;
        }
        else if (text == BRACKET_R) {
            if (ch == BRACKET_R || ZERO_TO_NINE.contains(ch)) {

                qstrNow += BRACKET_R;
                if (findBracketPair(qstrNow, qstrNow.size()-1) == -1) {
                    qstrNow.chop(1);
                    return false;
                }
                return true;
            }
            return false;
        }
        return false;
    }
    // + - * / = 0 1 2 3 4 5 6 7 8 9 . % 00 C B
    else if (NUMBER_LIST .contains(text) || text == CLEAN || text == BACKSPACE 
         || OPERATOR_LIST.contains(text)) {
        
        // 00 判断
        if (text == DOUBLE_ZERO) {
            if (!qstrNow.size()){
                return false;
            }

            QString qstrBack = qstrNow.right(1);
            if (isCorrectInt(getAnsNumberFromBack(qstrNow)).first != 0) {
                return false;
            }
        }

        qstrNow += text;
    }

    // function
    else if (FUNCTION_LIST.contains(text)) {
        if ( (qstrNow.size() == 1 && qstrNow.left(1) == BRACKET_L)) {
            return false;
        }
        if (formulaOrNum == 0 || formulaOrNum == 1) {

            qstrNow = qstrNow + text + BRACKET_L;
        }
        else if (formulaOrNum == 2 || formulaOrNum == -2 || formulaOrNum == -1)
            qstrNow = text + BRACKET_L + qstrNow + BRACKET_R;
        else
            return false;
    }
    
    // trans
    else if (TRANS_LIST.contains(text)) {
        if ( (qstrNow.size() == 1 && qstrNow.left(1) == BRACKET_L)) {
            return false;
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
            return false;
    }

    else if (SCI_NUM_LIST.contains(text)) {
        if ( isArithmeticOperator(qstrNow.right(1)) || qstrNow.right(1) == BRACKET_L
            || qstrNow.right(1) == QString(ANS_END) || qstrNow == ZERO) {

            if      (text == PI ) qstrNow = qstrNow + (BigFloat::PI).toQString() + ANS_END;
            else if (text == E  ) qstrNow = qstrNow + (BigFloat::E ).toQString() + ANS_END;
            else if (text == ANS) {
                qstrNow = qstrNow + lastAns;
                return !(lastAns.isEmpty());
            }
        }
        else
            return false;
    }
    else {
        return true;
    }

    return true;
}
bool InputProcess::couldBeCal()
{
    if (qstrNow.right(1) == EQUAL) {
        qstrNow.chop(1);
    }
    if (isArithmeticOperator(qstrNow.right(1)) || qstrNow.right(1) == BRACKET_L 
        || qstrNow.right(1) == POINT) {
    
        return false;
    }

    if (isCorrectFormula( qstrNow).first == 0) {
        return false;
    } 
    else {
        qstrNow = isCorrectFormula(qstrNow).second;
    }
    return true;
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

    // 1. B check
    if (qstrBack == BACKSPACE) {
        if (qstrNow.size() <= 2) {
            init();
        }
        else {
            // 先去掉"B"
            qstrNow.chop(1);

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
        qstrPrepare = lastQstrPrepare;
        return false;
    }

    if (text == EQUAL) {
        calHistory.append(clearANS_END_and_SCI_NUM_END(qstrNow + EQUAL +calAns));
        qstrPrepare.clear();
        qstrNow = calAns + ANS_END;
        lastAns = calAns;
    }
    
    else if (calAns != qstrNow) {
        // 123+情况
        QString temp = qstrNow.left(qstrNow.size()-1);
        if (temp == calAns) {
            qstrPrepare.clear();
            calAns.clear();
        }
        else {
            qstrPrepare = calAns;
        }
    }
    else if (calAns == qstrNow) {
        qstrPrepare.clear();
        calAns.clear();
    } 
    else {
        return false;
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
    qDebug () << qstrList;
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

QVector<QString> InputProcess::inputFromButton(const QString &text)
{
    qstrPrepare  = EMPTY;
    labelNow     = EMPTY;
    labelPrepare = EMPTY;
    calAns       = EMPTY;
    
    QVector<QString> res;
    res.resize(6);

    if (text == "test") {
        res[DISPLAY_ON_LABEL_NOW    ] = "2,000";
        res[LABEL_NOW_CAL_QSTR      ] = "1000+1000=2000";
        res[CAL_ANS                 ] = "2000";
        res[LATEST_HISTORY          ] = "1000+1000=2000";
        res[DISPLAY_ON_LABEL_PREPARE] = "";
        res[LABEL_PREPARE_CAL_QSTR  ] = "";
        return res;
    }

    if (!text.size())
        return res;
    
    if (text == STANDARD) {
        G.update(SCIENTIFIC, 0);
        init();
        G.updateAllSon(STANDARD, 1);
        return res;
    }

    if (text == SCIENTIFIC) {
        G.update(STANDARD, 0);
        init();
        G.updateAllSon(SCIENTIFIC, 1);
        return res;
    }

    if (text == DEG_SYMBOL || text == RAD_SYMBOL) {
        QStringCalculator::cal(text);
        return res;
    }
    
    if (!G.find(text))
        return res;

    qstrAdd(text);
    qDebug () << "1."<<qstrNow;
    qstrNowUpdate(text);
    qDebug () << "2."<<qstrNow;

    QString qstrBack;
    QString qstrBack2;
    if (qstrNow.size() >= 1) qstrBack  = QString(qstrNow[qstrNow.size()-1]);
    if (qstrNow.size() >= 2) qstrBack2 = QString(qstrNow[qstrNow.size()-2]);
    // 7.
    if (qstrBack == EQUAL) {
        qstrNow = clearANS_END_and_SCI_NUM_END(qstrNow);
    }
    // 8.
    if (qstrNow.contains(ANS_END)) {
        if (qstrBack2 == ANS_END && ZERO_TO_NINE.contains(qstrBack))
            qstrNow.remove(0, qstrNow.indexOf(ANS_END) + 1);
    }

    // qDebug () << qstrNow;
    if (couldBeCal()) 
        calAns = QStringCalculator::cal(qstrNow);
    // qDebug() << text;
    qDebug () << "calAns is" << calAns;
    if (!qstrUpdate(text)) {
        qstrPrepare = lastQstrPrepare;
    }
    qDebug () << calAns;
    labelUpdate();
    qDebug () << calAns;
    graphNodeUpdate(text);
    qDebug () << calAns;
    res[0] = clearANS_END_and_SCI_NUM_END(labelNow);
    res[1] = clearANS_END_and_SCI_NUM_END(qstrNow);
    res[2] = text == EQUAL ? clearANS_END_and_SCI_NUM_END(calAns) : EMPTY;
    res[3] = (text == EQUAL && calHistory.size()) ? calHistory.at(calHistory.size()-1) : EMPTY;
    res[4] = clearANS_END_and_SCI_NUM_END(labelPrepare);
    res[5] = clearANS_END_and_SCI_NUM_END(qstrPrepare);

    lastQstrPrepare = qstrPrepare;
    return res;
}


QVector<QString> InputProcess::inputFromButton(const char *text)
{
    return inputFromButton(QString(text));
}