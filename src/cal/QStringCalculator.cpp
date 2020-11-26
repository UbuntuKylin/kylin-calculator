#include "QStringCalculator.h"

QString QStringCalculator::angelSymbol = DEG_SYMBOL;

//获得符号的优先性
int  QStringCalculator::getOperatotPriority(const QString qstr)
{
    if (qstr == ADD || qstr == SUB)
        return 0;

    if (qstr == MUL || qstr == DIV)
        return 1;

    if (isBracket(qstr))
        return -1;  //注意，这里将括号设为最低优先级，因此括号不会被弹出，除非遇到右括号

}

//判断符号的优先性
void QStringCalculator::postfixCheck(const QString    &qstr,
                                     QStack<QString>  &operatorList,
                                     QStringList      &postfixExpressions)
{
    if (operatorList.empty()) {
        operatorList.push(qstr);
        return;
    }

    if (isBracket(qstr)) {
        if (qstr == BRACKET_L)
            operatorList.push(qstr);
        else
        {
            //弹出所有元素直到遇到左括号
            while (operatorList.top() != BRACKET_L)
            {
                QString t_qstr = operatorList.top();
                postfixExpressions.append(t_qstr);
                operatorList.pop();
            }

            //当遇到左括号时，弹出但不加入coll3(后缀表达式中)
            operatorList.pop();
        }
    }
    else {	//如果不是括号
        //取出栈顶元素，与当前符号进行优先性比较
        QString sym = operatorList.top();

        //比较两符号的优先性
        if (getOperatotPriority(qstr) <= getOperatotPriority(qstr)) {
            //如果c的优先性比栈顶符号小或等于，弹出栈顶元素
            operatorList.pop();
            //并将其压入coll3（后缀表达式）中
            postfixExpressions.push_back(sym);
            //递归调用check,比较当前符号c与下一个栈顶符号的优先性
            postfixCheck(qstr, operatorList, postfixExpressions);
        }
        else {
            //如果c比栈顶符号优先级大，那将c压入coll2(操作符栈)中
            operatorList.push(qstr);
        }
    }

    return ;
}

//从coll中取出元素，分配元素到coll2和coll3中
void QStringCalculator::infixToPostfix(QStringList &infixExpression,
                                       QStringList &postfixExpressions)
{
    QStack<QString> operatorList;
    while (!infixExpression.empty()) {
        QString qstr = infixExpression.at(0);
        infixExpression.removeAt(0);

        if (isNumber(qstr)) {
            postfixExpressions.append(qstr);
        }
        else {
            //调用check函数，针对不同情况作出不同操作
            postfixCheck(qstr, operatorList, postfixExpressions);
        }

    }

    //如果输入结束，将coll2的元素全部弹出，加入后缀表达式中
    while (!operatorList.empty()) {
        QString c = operatorList.top();
        postfixExpressions.push_back(c);
        operatorList.pop();
    }
}

//计算后缀表达式
void QStringCalculator::calPostfix(QStringList      &postfixExpressions,
                                   QStack<BigFloat> &calAns)
{
    while (!postfixExpressions.empty()) {
        QString qstr = postfixExpressions.at(0);
        postfixExpressions.removeAt(0);

        //如果是操作数，压入栈中
        if (ZERO_TO_NINE.contains( qstr.right(1))) {
            BigFloat op(qstr);
            calAns.push(op);
        }
        else {	 //如果是操作符，从栈中弹出元素进行计算
            BigFloat op1 = calAns.top();
            calAns.pop();
            BigFloat op2 = calAns.top();
            calAns.pop();

            if      (qstr == ADD) calAns.push(op2 + op1);
            else if (qstr == SUB) calAns.push(op2 - op1);
            else if (qstr == MUL) calAns.push(op2 * op1);
            else if (qstr == DIV) calAns.push(op2 / op1);

        }
    }
}

QString QStringCalculator::transCalculator(const QStringList &expression,
                                           const int idx)
{
    BigFloat ans_l;
    BigFloat ans_r;

    ans_l = BigFloat(idx == 1 ? expression[0] : qstrListCalculator(expression.mid(1, idx - 2)));
    ans_r = BigFloat(idx == expression.size() - 2 ? expression[expression.size() - 1]
        : qstrListCalculator(expression.mid(idx + 2, expression.size() - 3 - idx)));

    qDebug() << ans_l.toQString();
    qDebug() << ans_r.toQString();
    if (ans_l == BigFloat(0)) {
        if (ans_r == BigFloat(0)) {
            return ONE;
        }
        else if (ans_r > BigFloat(0)) {
            return ZERO;
        } else if (ans_r < BigFloat(0)) {
            return NAN_SYMBOL;
        }
    }
    return (ans_l ^ ans_r).toQString();
}

QString QStringCalculator::functionCalculator(const QStringList &expression)
{
    QString  func;
    BigFloat ans;

    ans = BigFloat(qstrListCalculator(expression.mid(2, expression.size() - 3)));
    func = expression[0];

    if      (func == SIN)    ans = BigFloat::Sin  (ans, angelSymbol);
    else if (func == COS)    ans = BigFloat::Cos  (ans, angelSymbol);
    else if (func == TAN)    ans = BigFloat::Tan  (ans, angelSymbol);
    else if (func == ARCSIN) ans = BigFloat::ASin (ans, angelSymbol);
    else if (func == ARCCOS) ans = BigFloat::ACos (ans, angelSymbol);
    else if (func == ARCTAN) ans = BigFloat::ATan (ans, angelSymbol);
    else if (func == LOG)    ans = BigFloat::Lg   (ans);
    else if (func == LN)     ans = BigFloat::Ln   (ans);
    // qDebug() << expression<<"'           '"<< ans.toQString();
    return ans.toQString();
}

void QStringCalculator::formulaToInfixExpression(QStringList &infixExpression)
{
    for (int i = 0; i < infixExpression.size(); i++) {
        QString qstr = infixExpression.at(i);
        if (isNumber(qstr)) {
            if (qstr.right(1) == PERCENT) {
                infixExpression[i]
                    = (   BigFloat(qstr.left(qstr.size() - 1))
                         / BigFloat(100)
                      ).toQString();
            }
        }

        // function
        else if (isFunction(qstr)) {
            int idx = findBracketPair(infixExpression, i + 1);
            QString temp_qstr = functionCalculator(infixExpression.mid(i, idx - i + 1));

            for (int j = i + 1 ; j <= idx; j++)
                infixExpression.removeAt(i + 1);

            infixExpression.replace(i, temp_qstr);

            i--;
        }

        else if (qstr == POWER_SYMBOL) {
            int idx_l;
            int idx_r;
            if (infixExpression.at(i - 1) == BRACKET_R) {
                idx_l = findBracketPair(infixExpression, i - 1);
            }
            else {
                idx_l = i - 1;
            }
            if (infixExpression.at(i + 1) == BRACKET_L) {
                idx_r = findBracketPair(infixExpression, i + 1);
            }
            else {
                idx_r = i + 1;
            }


            QString temp_qstr;
            temp_qstr = transCalculator(infixExpression.mid(idx_l, idx_r - idx_l + 1), i - idx_l);

            for (int j = idx_l + 1; j <= idx_r; j++)
                infixExpression.removeAt(idx_l + 1);

            infixExpression.replace(idx_l, temp_qstr);

            i = idx_l - 1;
        }

        else if (qstr == FACTORIAL_SYMBOL) {

            if (infixExpression[i-1] == BRACKET_R) {
                int idx = findBracketPair(infixExpression, i - 1);
                infixExpression[idx] = BigFloat::Fact(BigFloat(
                    qstrListCalculator(infixExpression.mid(idx + 1, i - 2 - idx))
                )).toQString();
                for (int j = idx + 1; j <= i ; j++) {
                    infixExpression.removeAt(idx + 1);
                }
                i = idx;
            }
            else {
                infixExpression[i-1] = BigFloat::Fact(BigFloat(infixExpression[i-1])).toQString();
                infixExpression.removeAt(i);
                i--;
            }
        }
    }
    return ;
}

QString QStringCalculator::qstrListCalculator(const QStringList &formulaList)
{
    QStringList      infixExpression;    //盛放中缀表达式
    QStringList      postfixExpressions; //盛放后缀表达式
    QStack<BigFloat> calAns;	         //计算后缀表达式的辅助容器

    infixExpression = formulaList;
    if (infixExpression[0] == SUB) infixExpression.insert(0,ZERO);
    formulaToInfixExpression(infixExpression);
    qDebug () << infixExpression;

    foreach (QString ch, infixExpression) {
        if (ch.contains(INF_SYMBOL) || ch.contains(NAN_SYMBOL)) {
            return ch;
        }
    }
    infixToPostfix(infixExpression, postfixExpressions);

    //计算后缀表达式
    calPostfix(postfixExpressions, calAns);

    QString ans = calAns.top().toQString();

    qDebug() << "ans is" << ans;
    return ans;

}

QString QStringCalculator::cal(const QString &qstr)
{
    qDebug() << "im in cal!";
    qDebug() << qstr;
    QString formula = qstr;
    // deg rad
    if (formula == InputSymbols::DEG_SYMBOL || formula == InputSymbols::RAD_SYMBOL) {
        angelSymbol = formula;
        return formula;
    }

    // 为空
    if(formula.size() == 0)
        return EMPTY;

    // 去掉ANS_END
    formula = clearANS_END_and_SCI_NUM_END(formula);

    // 去掉末尾符号
    while (isArithmeticOperator(formula.right(1)))
        formula.chop(1);

    while (formula.right(1) == EQUAL)
        formula.chop(1);
    if (!allBracketMatchCorrectly(formula))
        formula = bracketCompletion(formula);
    qDebug () << "123123" << formula;
    formula = isCorrectFormula(formula).second;
    qDebug () << "123123" << formula;
    QStringList formulaList = formulaSplit(formula);
    QString ans = qstrListCalculator(formulaList);

    //去掉末尾0

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
        if ((ans.size() - ans.indexOf(".") > PRECISION) || (ans.indexOf(".") > PRECISION)) {
            ans = QString::number(ans.toDouble(), 'g', PRECISION);
        }
    }
    else {
        if (ans.size() > PRECISION) {
            ans = QString::number(ans.toDouble(), 'g', PRECISION);
        }
    }

    qDebug() <<"ansend"<<ans;
    return ans;
}
