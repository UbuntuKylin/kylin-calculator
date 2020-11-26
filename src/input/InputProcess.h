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
    CORRECT_QSTR_ADD,
    CANNOT_ADD_BRACKET_L,
    CANNOT_ADD_BRACKET_R,
    CANNOT_ADD_EQUAL,
    CANNOT_ADD_DOUBLE_ZERO,
    CANNOT_ADD_FUNCTION,
    CANNOT_ADD_TRANS,
    CANNOT_ADD_SCI_NUM,
    INPUT_ERROR
};

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

    static QVector<QString> res;

    static QString qstrNow;
    static QString qstrPrepare;
    static QString labelNow;
    static QString labelPrepare;
    static QString calAns;
    static QString lastAns;
    static QStringList calHistory;

    static InputJudgmentGraph G;
    
    static bool b_couldBeCalFlag;
    static bool b_qstrAddFlag;
    static bool b_qstrNowUpdateFlag;
    static bool b_qstrUpdateFlag;


    static void    init            ();

    /** addComma
     *  实现千分位加入
     *  1000-->1,000
     */
    static QString addComma        (const QString &);
    
    /** couldBeCal函数：
     *  判断qstr能否被计算
     */
    static bool    couldBeCal      (const QString &qstr);
    
    /** qstrAdd: 将text中的按键加入到qstrNow中；
     *  参见字符串处理.txt
     */
    static int    qstrAdd         (const QString &text);

    /** qstrNowUpdate: 更新qstrNow；
     *  参见字符串处理.txt
     */
    static bool    qstrNowUpdate   (const QString &text);
    
    /** qstrUpdate 处理计算后的qstrNow 和 qstrPrepare
     *  
     */
    static bool    qstrUpdate      (const QString &text);
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