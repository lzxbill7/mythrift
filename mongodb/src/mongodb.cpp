/**
 * @file       mongodb.cpp
 * @brief      /mythrift/mongodb/src/mongodb.cpp
 *
 * @date       Sep 10, 2015
 * @author     lzx_bupt@126.com
 * @note       create
 */

#include <stdlib.h>

#include "mongodb/mongodb.h"

namespace mongodb
{

MongoDb* MongoDb::s_instance(NULL);

MongoDb::MongoDb(void)
{
}

MongoDb* MongoDb::getInstance()
{
    if (s_instance == NULL)
    {
        s_instance = new MongoDb();
        s_instance->open("localhost");
    }

    return s_instance;
}

void MongoDb::destroyInstance()
{
    if (NULL != s_instance)
    {
        s_instance->close();

        delete s_instance;
        s_instance = NULL;
    }
}

void MongoDb::destroyInstanceAtExit()
{
    MongoDb::destroyInstance();
}

}
