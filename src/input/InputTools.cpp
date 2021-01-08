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
 
#include "InputTools.h"

const QPair<int, QString>     InputTools::QP_QSTR_ERROR      = qMakePair(0, ERROR);
const QPair<int, QStringList> InputTools::QP_QSTR_LIST_ERROR = qMakePair(0, QStringList(ERROR));

bool InputTools::isSpace(const QChar qc)
{
    if (SPACE == qc)
        return true;
    return false;
}

bool InputTools::isSpace(const char c)
{
    if (SPACE == QString(c))
        return true;
    return false;
}

bool InputTools::isBracket(const QChar qc)
{
    if (BRACKET_LIST.contains(qc))
        return true;
    return false;
}

bool InputTools::isBracket(const char c)
{
    return isBracket(QChar(c));
}

bool InputTools::isBracket(const QString &qstr)
{
    if (!qstr.size())
        return false;

    foreach (QChar qc, qstr) {
        if (!isBracket(qc))
            return false;
    }
    return true;
}

bool InputTools::isNumber(const QChar qc)
{
    if (NUMBER_LIST.contains(qc))
        return true;
    return false;
}

bool InputTools::isNumber(const char c)
{
    return isNumber(QChar(c));
}

bool InputTools::isNumber(const QString &qstr)
{

    if (!qstr.size())
        return false;

    if ( (qstr.contains(INF_SYMBOL) || qstr.contains(NAN_SYMBOL)) && qstr.size()<= 4 )
        return true;

    if (qstr.contains(SCIENTIFIC_NOTATION)) {
        int idx = qstr.indexOf(SCIENTIFIC_NOTATION);
        if (isNumber(qstr.mid(0,idx)) && isNumber(qstr.mid(idx + 2, qstr.size()-idx-2)))
            return true;
        return false;
    }

    if ( qstr.size() > 1 && qstr[0] == SUB)
        return isNumber(qstr.right(qstr.size() - 1));

    foreach (QChar qc, qstr) {
        if (!isNumber(qc))
            return false;
    }
    return true;
}

bool InputTools::isOperator(const QChar qc)
{
    if (OPERATOR_LIST.contains(qc))
        return true;
    return false;
}

bool InputTools::isOperator(const char c)
{
    return isOperator(QChar(c));
}

bool InputTools::isOperator(const QString &qstr)
{
    if (!qstr.size())
        return false;

    foreach (QChar qc, qstr) {
        if (!isOperator(qc))
            return false;
    }
    return true;
}

bool InputTools::isArithmeticOperator(const QChar qc)
{
    if (ARITHMETIC_OPERATOR_LIST.contains(qc))
        return true;
    return false;
}

bool InputTools::isArithmeticOperator(const char c)
{
    return isArithmeticOperator(QChar(c));
}

bool InputTools::isArithmeticOperator(const QString &qstr)
{
    if (!qstr.size())
        return false;

    foreach (QChar qc, qstr) {
        if (!isArithmeticOperator(qc))
            return false;
    }
    return true;
}

bool InputTools::isFunction(const QString &qstr)
{
    if (FUNCTION_LIST.contains(qstr))
        return true;
    return false;
}

bool InputTools::isTrans(const QString &qstr)
{
    if (TRANS_LIST.contains(qstr))
        return true;
    return false;
}

bool InputTools::isSciNum(const QString &qstr)
{
    if (SCI_NUM_LIST.contains(qstr))
        return true;
    return false;
}

/*  findBracketPair:
 *  找到和qstr[idx]位置匹配的括号
 *  如果找不到,返回-1
 */
int InputTools::findBracketPair(const QString &qstr, const int idx)
{
    if (qstr.size() <  idx) {
        return -1;
    }

    if (!BRACKET_LIST.contains(qstr[idx]))
        return -1;

    int i_cnt = 0;
    if (qstr[idx] == BRACKET_L) {
        for (int i = idx; i < qstr.size(); i++) {
            if (qstr[i] == BRACKET_L)
                i_cnt++;
            else if (qstr[i] == BRACKET_R)
                i_cnt--;

            if(!i_cnt)
                return i;
        }
    }
    else if (qstr[idx] == BRACKET_R) {
        for (int i = idx; i >=0; i--) {
            if (qstr[i] == BRACKET_L)
                i_cnt++;
            else if (qstr[i] == BRACKET_R)
                i_cnt--;

            if(!i_cnt)
                return i;
        }
    }
    return -1;
}

int InputTools::findBracketPair(const QStringList &qstrList, const int idx)
{
    QString t;
    foreach (QString a, qstrList) {
        t.append(a[0]);
    }
    return findBracketPair(t,idx);
}

bool InputTools::allBracketMatchCorrectly(const QString &qstr)
{
    if (!qstr.size())
        return false;

    for (int i = 0; i < qstr.size(); i++) {
        if (isBracket(qstr[i]))
            if (findBracketPair(qstr, i) == -1)
                return false;
    }
    return true;
}

QString InputTools::bracketCompletion(const QString &qstr)
{
    QString res = qstr;
    int braCnt  = 0;
    for (int i = 0; i < res.size(); i++ ) {
        QString ch = QString(res[i]);
        if (ch == BRACKET_L)
            braCnt++;
        else if (ch == BRACKET_R) {
            braCnt--;
        }
    }

    if (braCnt > 0) {
        while (braCnt--)
            res.insert(int(res.size()), BRACKET_R);
    }
    else if (braCnt < 0) {
        while (braCnt--)
            res.insert(0, BRACKET_L);
    }

    return res;
}

QString InputTools::getFunctionOrSciNumName(const QString &qstr, const int idx)
{
    qDebug () << "im in getFunctionOrSciNumName!";
    if (qstr.size() < idx + 3)
        return "";

    QString ans = qstr.mid(idx,4);
    qDebug () << ans;
    while(ans.contains(BRACKET_L) || ans.contains(BRACKET_R)) {
        ans.chop(1);
    }

    while(!ans.right(1)[0].isLetter())
        ans.chop(1);

    if (FUNCTION_LIST.contains(ans)) {
        return ans;
    }

    if (SCI_NUM_LIST.contains(ans)) {
        return ans;
    }

    return "";
}

QStringList InputTools::formulaSplit(const QString &qstr)
{
    qDebug () << "im in formulaSplit!";
    qDebug () << "Before formulaSplit :" <<qstr;
    QStringList ans;
    QString formula = qstr + END;

    if (!formula.size())
        return ans;

    for (int i = 0; i < formula.size();)
    {
        QString ch = QString(formula[i]);
        // %处理
        if (ch == PERCENT && !i) {
            ans.append(ch);
            formula.remove(0, 1);
            i = 0;
        }

        // + - * / ( ) ^ $ e处理
        else if (isArithmeticOperator(ch) || isBracket(ch)
            || ch == POWER_SYMBOL || ch == END
            || ch == SCIENTIFIC_NOTATION
            || ch == FACTORIAL_SYMBOL) {
            if (i)
                ans.append(formula.mid(0,i));
            ans.append(ch);
            formula.remove(0, i + 1);
            i = 0;
        }

        else if (formula[i].isLetter()) {
            QString t = getFunctionOrSciNumName(formula, i);
            if (t.size()) {
                if (i)
                    ans.append(formula.mid(0,i));
                ans.append(t);
                formula.remove(0, i + t.size());
                i = 0;
            }
            else {
                if (formula[i] == 'i' || formula[i] == 'n') {
                    if (formula.mid(i, 3) == INF_SYMBOL || formula.mid(i, 3) == NAN_SYMBOL) {
                        ans.append(formula.mid(i, 3));
                        formula.remove(0,3);
                        i = 0;
                    }
                }
            }
        }
        else
            i++;
    }

    while (ans.contains(SCIENTIFIC_NOTATION)) {
        int idx = ans.indexOf(SCIENTIFIC_NOTATION);
        ans.replace(idx - 1, ans.mid(idx - 1, 4).join(""));

        for (int i = idx; i <= idx + 2; i++)
            ans.removeAt(idx);
    }
    ans.removeAt(ans.size()-1);
    qDebug () << "After formulaSplit  :" <<ans;
    return ans;
}

void InputTools::qpairUpdate(     QPair<int, QString> &qpair1,
                            const QPair<int, QString> &qpair2)
{
    if (qpair1 == QP_QSTR_ERROR)
        return;

    if (qpair2.first == 0) {
        qpair1 = QP_QSTR_ERROR;
        return ;
    }

    if (qpair2.first == 1) {
        if (qpair1 == QP_QSTR_ERROR || qpair1.first == 2)
            return ;
        qpair1 = qpair2;
        return ;
    }

    if (qpair2.first == 2) {
        if (qpair1 == QP_QSTR_ERROR)
            return ;
        qpair1 = qpair2;
        return ;
    }
    return ;
}

void InputTools::qpairUpdate(     QPair<int, QStringList> &qpair1,
                            const QPair<int, QStringList> &qpair2)
{
    if (qpair1 == QP_QSTR_LIST_ERROR)
        return;

    if (qpair2.first == 0) {
        qpair1 = QP_QSTR_LIST_ERROR;
        return ;
    }

    if (qpair2.first == 1) {
        if (qpair1 == QP_QSTR_LIST_ERROR || qpair1.first == 2)
            return ;
        qpair1 = qpair2;
        return ;
    }

    if (qpair2.first == 2) {
        if (qpair1 == QP_QSTR_LIST_ERROR)
            return ;
        qpair1 = qpair2;
        return ;
    }
    return ;
}

QPair<int, QString> InputTools::isCorrectInt(const QString &qstr)
{
    if (!qstr.size())
        return qMakePair(0,ERROR);

    QPair<int,QString> qp;

    if (qstr[0] == SUB) {
        qp = isCorrectInt(qstr.right(qstr.size()-1));
        qp.second = SUB + qp.second;
        return qp;
    }

    foreach (QChar ch, qstr) {
        if (!isNumber(ch) || ch == POINT || ch == PERCENT)
            return qMakePair(0,ERROR);
    }

    qp = qMakePair(1, qstr);

    if (qstr[0] == ZERO && qstr.size() > 1) {
        qpairUpdate(qp, qMakePair(2, qstr));
        while (qp.second.at(0) == ZERO) {
            qp.second.remove(0,1);
        }
    }

    return qp;
}

QPair<int, QString> InputTools::isCorrectDouble(const QString &qstr)
{
    if (!qstr.size())
        return qMakePair(0,ERROR);

    if (qstr.contains(INF_SYMBOL) || qstr.contains(NAN_SYMBOL)) {
        if (qstr.size() == 3)
            return qMakePair(1,qstr);
        if (qstr.size() == 4 && qstr[0] == SUB) {
            return qMakePair(1,qstr);
        }
        return qMakePair(0,ERROR);
    }

    int idx;
    QPair<int,QString> qp;

    if (qstr.contains(SCIENTIFIC_NOTATION)) {
        idx = qstr.indexOf(SCIENTIFIC_NOTATION);
        if (idx != -1) {
            // 判断e后的'+','-'
            if (qstr[idx + 1] != ADD && qstr[idx + 1] != SUB)
                return qMakePair(0,ERROR);

            // 判断e后的数字
            qp = isCorrectInt(qstr.right(qstr.size() - idx - 2));
            if (!qp.first) {
                return qMakePair(0,ERROR);
            }
            else {
                qp.second = qstr.left(idx) + qp.second;
            }

            // 判断e前的整数
            QPair<int,QString> qp1 = isCorrectInt(qstr.left(idx));
            QPair<int,QString> qp2 = isCorrectDouble(qstr.left(idx));
            if (qp1.first && !qp2.first) {
                qp1.second += qstr.right(qstr.size() - idx);
                qpairUpdate(qp, qp1);
            }
            else if (!qp1.first && qp2.first) {
                qp2.second += qstr.right(qstr.size() - idx);
                qpairUpdate(qp, qp2);
            }
            else {
                return qMakePair(0,ERROR);
            }
        }
        return qp;
    }
    if (qstr.contains(POINT)) {
        idx = qstr.contains(POINT);
        if (idx != -1) {
            qp = isCorrectInt(qstr.left(idx));
            if (!qp.first) {
                return qMakePair(0,ERROR);
            }
            else {
                qp.second += qstr.right(qstr.size() - idx);
            }
            foreach (QChar ch , qstr.right(qstr.size() - 1 - idx) ) {
                if (!isNumber(ch) || ch == POINT || ch == PERCENT)
                    return qMakePair(0,ERROR);
            }
            if (qp.second.right(1) == ZERO) {
                qp.first = 2;
                while (qp.second.right(1) == ZERO)
                    qp.second.chop(1);
                if (qp.second.right(1) == POINT)
                    qp.second.chop(1);
            }
        }
        return qp;
    }
    return qMakePair(0,ERROR);
}

QPair<int, QString> InputTools::isCorrectNumber(const QString &qstr)
{
    if (!qstr.size())
        return QP_QSTR_ERROR;

    QPair<int,QString> qp;

    // %处理
    if (qstr.contains(PERCENT)) {
        qp = isCorrectNumber(qstr.left(qstr.size()-1));
        if (!qp.first)
            return QP_QSTR_ERROR;
        qp.second += PERCENT;
        return qp;
    }

    if (   qstr.contains(POINT) || qstr.contains(SCIENTIFIC_NOTATION)
        || qstr.contains(INF_SYMBOL)   || qstr.contains(NAN_SYMBOL)) {
        qp = isCorrectDouble(qstr);
        if (!qp.first)
            return QP_QSTR_ERROR;
    }
    else {
        qp = isCorrectInt(qstr);
        if (!qp.first)
            return QP_QSTR_ERROR;
    }
    return qp;
}

bool InputTools::adjacencyJudgment(const QString &x, const QString &y)
{
    // )
    if (x == BRACKET_R) {
        if (isArithmeticOperator(y) || y == POWER_SYMBOL || y == FACTORIAL_SYMBOL)
            return true;
        return false;
    }
    // ^
    if (x == POWER_SYMBOL) {
        if (isNumber(y) || y == BRACKET_L || isSciNum(y))
            return true;
        return false;
    }

    // + - * /
    if (isArithmeticOperator(x)) {
        if (isNumber(y) || y == BRACKET_L || isSciNum(y) || isFunction(y))
            return true;
        return false;
    }

    // function
    if (isFunction(x)) {
        if (y == BRACKET_L)
            return true;
        return false;
    }

    // num
    if (isNumber(x) || isSciNum(x)) {
        if (   y == BRACKET_R || y == POWER_SYMBOL
            || isArithmeticOperator(y) || y == FACTORIAL_SYMBOL) {

            return true;
        }
        return false;
    }

    if (x == FACTORIAL_SYMBOL) {
        if ( isArithmeticOperator(y) || y == BRACKET_R) {
            return true;
        }
        return false;
    }
    return true;
}

QPair<int, QStringList> InputTools::isCorrectFormulaList(const QStringList &formulaList)
{
    qDebug () << "im in InputTools::isCorrectFormulaList";
    if (!formulaList.size()) {
        // qDebug() << "in isCorrectFormulaList:";
        // qDebug() << "   " << formulaList;
        // qDebug() << "formulaList is empty!";
        // 可以这样用,会将QPair<int, QString>隐式转换成QPair<int, QStringList>类型
        // return qMakePair(1, QString(""));
        return qMakePair(1, QStringList(""));
    }
    // formulaList[0]不能是     "* /"
    // formulaList.right(1)不能是 "+ - * /"
    if (   ( isArithmeticOperator(formulaList[0]) && formulaList[0] != SUB && formulaList[0] != ADD)
        || ( isArithmeticOperator(formulaList.back())) ) {
        return QP_QSTR_LIST_ERROR;
    }

    QPair<int, QStringList> qp;
    qp = qMakePair(1, formulaList);

    // 首位-判断
    if (qp.second.size() > 1 && qp.second.at(0) == SUB && isNumber(qp.second.at(1)) ){
        qp.second.removeAt(0);
        qp.second.replace(0, SUB + qp.second.at(0));
    }

    // 首位+判断
    if (qp.second.at(0) == ADD){
        qp.second.removeAt(0);
        qp.first = 2;
    }

    // size 为 1 只能是数
    if (qp.second.size() == 1) {
        QPair<int, QString> temp_qp = isCorrectNumber(qp.second.at(0));
        qp.first = temp_qp.first;
        qp.second.replace(0, temp_qp.second);
        return qp;
    }

    for (int i = 0; i < qp.second.size() - 1; i++) {
        QString qstri = qp.second.at(i);
        QString qstrj = qp.second.at(i + 1);

        if (!adjacencyJudgment(qstri, qstrj))
            return QP_QSTR_LIST_ERROR;

        if (qstri == BRACKET_L) {
            int idx = findBracketPair(qp.second, i);
            if (idx == -1) {
                return QP_QSTR_LIST_ERROR;
            }
            else {
                QPair<int, QStringList> temp_qp;
                temp_qp = isCorrectFormulaList(qp.second.mid(i + 1, idx - i - 1));

                if (!qp.first || !temp_qp.first)
                    return QP_QSTR_LIST_ERROR;
                if (qp.first != 2)
                    qp.first = temp_qp.first;

                if (temp_qp.second.size() && !temp_qp.second.contains("")) {
                    qp.second =   qp.second.mid(0, i + 1)
                                + temp_qp.second
                                + qp.second.mid(idx, qp.second.size() - idx);
                    i += temp_qp.second.size();
                }
                else {
                    qp.first  =   2;
                    qp.second =   qp.second.mid(0, i)
                                + qp.second.mid(idx + 1, qp.second.size() - idx - 1);
                    if (i)
                        i -= 2;
                    else
                        return qMakePair(qp.first, QStringList(""));
                }
            }
        }
        else  if (isNumber(qstri)) {
            if (isNumber(qstrj))
                return QP_QSTR_LIST_ERROR;

            QPair<int, QString> temp_qp = isCorrectNumber(qstri);
            if (!temp_qp.first)
                return QP_QSTR_LIST_ERROR;

            if (temp_qp.first) {
                if (qp.first != 2)
                    qp.first = temp_qp.first;
                qp.second.replace(i, temp_qp.second);
            }
        }
    }
    return qp;
}

QPair<int, QString> InputTools::isCorrectFormula(const QString &qstr)
{
    qDebug () << "im in InputTools::isCorrectFormula";
    if (!qstr.size())
        return qMakePair(0,ERROR);

    QPair<int, QString> qp = qMakePair(1, qstr);

    qp.second = clearANS_END_and_SCI_NUM_END(qp.second);
    qDebug() << qp.second;
    if (!allBracketMatchCorrectly(qp.second)) {
        qp.first = 2;
        qp.second = (bracketCompletion(qp.second));
    }

    QStringList formulaList = formulaSplit(qp.second);
    QPair<int, QStringList> qpList = isCorrectFormulaList(formulaList);

    if (!qpList.first)
        return qMakePair(0,ERROR);

    if (qp.first == 2)
        qpList.first = qp.first;
        return qMakePair(qpList.first, qpList.second.join(""));
}

int InputTools::formulaTypeCheck(const QString &formula)
{
    // 空返回0
    if (formula.isEmpty())
        return 0;
    if (   (  isNumber(formula) )
        || ( formula[0] == SUB && formulaTypeCheck(formula.right(formula.size()-1)) == -1) ) {

        return -1;
    }
    if (   ( isNumber(formula.left(formula.size()-1)) && formula.right(1) == ANS_END )
        || ( formula[0] == SUB && formulaTypeCheck(formula.right(formula.size()-1)) == -2 ) ) {

        return -2;
    }
    if (isArithmeticOperator(formula.right(1)))
        return 1;
    return 2;
}

int InputTools::getNumberLengthFromBack(const QString &qstr)
{
    if (!NUMBER_LIST.contains(qstr.right(1)))
        return 0;

    if (formulaTypeCheck(qstr) == -1) {
        return qstr.size();
    }

    QStringList temp = formulaSplit(qstr);
    if (isCorrectNumber(temp.at(temp.size()-1)).first == 3)
        return 0;
    return temp.at(temp.size()-1).size();
}

int InputTools::getAnsNumberLengthFromBack(const QString &qstr)
{
    if (qstr.right(1) != ANS_END)
        return 0;

    if (formulaTypeCheck(qstr) == -2) {
        return qstr.size();
    }
    return getAnsNumberLengthFromBack(qstr.mid(0, qstr.size() - 1)) + 1;
}

QString InputTools::getNumberFromBack(const QString &qstr)
{
    return qstr.right(getNumberLengthFromBack(qstr));
}

QString InputTools::getAnsNumberFromBack(const QString &qstr)
{
    return qstr.right(getAnsNumberLengthFromBack(qstr));
}

QString InputTools::clearANS_END(const QString &qstr)
{
    QString res = qstr;
    while (res.indexOf(ANS_END) != -1)
        res.remove(res.indexOf(ANS_END), 1);
    return res;
}

QString InputTools::clearSCI_NUM_END(const QString &qstr)
{
    QString res = qstr;
    while (res.indexOf(SCI_NUM_END) != -1)
        res.remove(res.indexOf(SCI_NUM_END), 1);
    return res;
}

QString InputTools::clearANS_END_and_SCI_NUM_END(const QString &qstr) {
    QString res = qstr;
    res = clearANS_END(res);
    res = clearSCI_NUM_END(res);
    return res;
}

QString InputTools::addComma(const QString &qstr)
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

int InputTools::couldBeCal(const QString &qstr)
{
    // 1.
    if (qstr.size() == 0)
        return COULD_NOT_BE_CAL;
    QString ch = qstr.right(1);
    // 2.
    if ( isArithmeticOperator(ch)
      || ch == BRACKET_L
      || ch == POINT
      || ch == POWER_SYMBOL
      || FUNCTION_QSTR.contains(ch) ) {

        return COULD_NOT_BE_CAL;
    }
    if (ch == EQUAL) {
        QString tempQstr = qstr;
        tempQstr.chop(1);
        if ( isCorrectFormula( tempQstr ).first == 0 ) {
            return COULD_NOT_BE_CAL;
        }
    }
    // 3.
    if (ch != EQUAL && isCorrectFormula(qstr).first == 0) {
        return COULD_NOT_BE_CAL;
    }

    return COULD_BE_CAL;
}