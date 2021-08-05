#include "data_warehouse.h"

#include <QDebug>

DataWarehouse::DataWarehouse()
{
    init();
}

DataWarehouse::~DataWarehouse()
{

}

DataWarehouse *DataWarehouse::getInstance(void)
{
    static DataWarehouse *instance = NULL;
    if (instance == NULL) {
        instance = new DataWarehouse();
        return instance;
    }

    return instance;
}

void DataWarehouse::init(void)
{
    this->platform.clear();
    getPlatForm();

    this->winFlag = QString("min");
    this->maxInputNum = 35;

    return;
}

void DataWarehouse::getPlatForm(void)
{
    this->platform = QString("intel");
    //qDebug() << "Info : check platform is inter";
    return;
}
