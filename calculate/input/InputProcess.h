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

#ifndef __INPUT_PROCESS_H__
#define __INPUT_PROCESS_H__

#include <QString>
#include <QVector>

#include "BigFloat.h"
#include "InputTools.h"
#include "InputSymbols.h"
#include "QStringCalculator.h"
#include "InputJudgmentGraph.h"


// 私有继承InputTools, 可能不利于后期修改
class InputProcess : private InputTools
{
private:

    static QVector<QString> res;

    static QString qstrNow;
    static QString qstrPrepare;
    static QString labelNow;
    static QString labelPrepare;
    static QString calAns;
    static QString lastAns;
    static QStringList calHistory;

    static InputJudgmentGraph G;

    static int i_qstrAddFlag;
    static int i_qstrNowUpdateFlag;
    static int i_couldBeCalFlag;
    static int i_qstrUpdateFlag;


    static void    init            ();

    /** qstrAdd: 将text中的按键加入到qstrNow中；
     *  参见字符串处理.md
     */
    static int    qstrAdd         (const QString &text);

    /** qstrNowUpdate: 更新qstrNow；
     *  参见字符串处理.md
     */
    static int    qstrNowUpdate   (const QString &text);

    /** qstrUpdate 处理计算后的qstrNow 和 qstrPrepare
     *
     */
    static int     qstrUpdate      (const QString &text);

    static void    labelUpdate     ();
    static void    graphNodeUpdate (const QString &text);
    static QVector<QString> output (const QString &text);
    static void    init_inputFromButton();
public:
    /** inputFromButton :外部访问唯一入口
     *  输入:键盘录入;
     *  输出:一个QVector<QString>
     *  QVector[0:DISPLAY_ON_LABEL_NOW    ]:显示在label_now的字符串
     *  QVector[1:LABEL_NOW_CAL_QSTR      ]:label_now的运算字符串
     *  QVector[2:CAL_ANS                 ]:计算结果
     *  QVector[3:LATEST_HISTORY          ]:最新的历史记录
     *  QVector[4:DISPLAY_ON_LABEL_PREPARE]:显示在label_prepare的字符串
     *  QVector[5:LABEL_PREPARE_CAL_QSTR  ]:label_prepare的运算字符串
     */
    static QVector<QString> inputFromButton(const QString &);
    static QVector<QString> inputFromButton(const char    *);
};

#endif