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
    printf("/***********input**************/\n");
    printf("/**********start!**************/\n");
    printf("/******************************/\n");
    qDebug() << QStringCalculator::cal("0.00000000005÷1000000");
    BigFloat a("0.00000000005");
    BigFloat b("1000000");
    a/=b;
    qDebug() << a.toQString();
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