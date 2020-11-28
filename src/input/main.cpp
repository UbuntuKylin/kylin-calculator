#include <cstdio>
#include <iostream>
#include <string>

#include <QDebug>
#include <QString>
#include <QStringList>
#include <QPair>

#include "InputProcess.h"
#include "BigFloat.h"
#include "InputTools.h"
#include "InputSymbols.h"
#include "QStringCalculator.h"
#include "InputJudgmentGraph.h"

using namespace std;

void init()
{
    printf("/***********input***************/\n");
    printf("/**********start!**************/\n");
    printf("/******************************/\n");
    // qDebug() << (BigFloat(1) + BigFloat(2)).toQString();
    QStringCalculator::cal("(cos(0))!");
    // string a;
    // while(cin >> a)
    //     qDebug() << InputProcess::inputFromButton(QString::fromStdString(a));
}


int main(int argc, char *argv[])
{
    // cout << 123123 << endl;
    init();
    return 0;
}