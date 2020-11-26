#ifndef __INPUT_PROCESS_H__
#define __INPUT_PROCESS_H__

#include <QString>
#include <QVector>

#include "BigFloat.h"
#include "InputTools.h"
#include "InputSymbols.h"
#include "QStringCalculator.h"
#include "InputJudgmentGraph.h"

enum {
    DISPLAY_ON_LABEL_NOW     = 0,
    LABEL_NOW_CAL_QSTR       = 1,
    CAL_ANS                  = 2,
    LATEST_HISTORY           = 3,
    DISPLAY_ON_LABEL_PREPARE = 4,
    LABEL_PREPARE_CAL_QSTR   = 5
};

// 私有继承InputTools, 可能不利于后期修改
class InputProcess : private InputTools
{
private:

    static QString qstrNow;
    static QString qstrPrepare;
    static QString lastQstrPrepare;
    static QString labelNow;
    static QString labelPrepare;
    static QString calAns;
    static QString lastAns;
    static QStringList calHistory;

    static InputJudgmentGraph G;
    
    
    static void    init            ();
    // 实现千分位加入
    static QString addComma        (const QString &);
    static bool    qstrAdd         (const QString &text);
    static bool    qstrNowUpdate   (const QString &text);
    static bool    couldBeCal      ();
    static bool    qstrUpdate      (const QString &text);
    static void    labelUpdate     ();
    static void    graphNodeUpdate (const QString &text);

public:
    /** inputFromButton :外部访问唯一入口
     *  输入:键盘录入;
     *  输出:一个QVector<QString>
     *  QVector[DISPLAY_ON_LABEL_NOW    ]:显示在label_now的字符串
     *  QVector[LABEL_NOW_CAL_QSTR      ]:label_now的运算字符串
     *  QVector[CAL_ANS                 ]:计算结果
     *  QVector[LATEST_HISTORY          ]:最新的历史记录
     *  QVector[DISPLAY_ON_LABEL_PREPARE]:显示在label_prepare的字符串
     *  QVector[LABEL_PREPARE_CAL_QSTR  ]:label_prepare的运算字符串
     */
    static QVector<QString> inputFromButton(const QString &);
    static QVector<QString> inputFromButton(const char    *);
};

#endif