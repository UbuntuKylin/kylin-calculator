#ifndef __DATA_WAREHOUSE_H__
#define __DATA_WAREHOUSE_H__

#include <QString>
#include <ukuisdk/kylin-com4c.h>
#include <ukuisdk/kylin-com4cxx.h>

class DataWarehouse
{
public:
    static DataWarehouse* getInstance(void);
    ~DataWarehouse();

    /* 运行平台 */
    /* 990 , 9a0 , v100 , v101 , inter */
    QString platform;

    /* 第一次启动是否为 intel 小插件方式 , 该变量标识第一次启动计算器的方式 , 后续模式切换 该变量不在维护 */
    bool intelPlug;

    /* 标识大窗口和小窗口 */
    /* max , min */
    QString winFlag;

    /* 输入最大限度 */
    int maxInputNum;

protected:

private:
    DataWarehouse();

    void getPlatForm(void);
    void init(void);
};

#endif
