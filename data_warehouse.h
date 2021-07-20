#ifndef __DATA_WAREHOUSE_H__
#define __DATA_WAREHOUSE_H__

#include <QString>

class DataWarehouse
{
public:
    static DataWarehouse* getInstance(void);
    ~DataWarehouse();

    /* 运行平台 */
    /* 990 , 9a0 , v100 , v101 , inter */
    QString platform;

protected:

private:
    DataWarehouse();

    void getPlatForm(void);

    void init(void);
};

#endif
