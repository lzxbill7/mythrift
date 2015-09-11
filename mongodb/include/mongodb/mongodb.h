/**
 * @file       mongodb.h
 * @brief      /mythrift/mongodb/include/mongodb/mongodb.h
 *
 * @date       Sep 10, 2015
 * @author     lzx_bupt@126.com
 * @note       create
 */

#ifndef MONGODB_MONGODB_H_
#define MONGODB_MONGODB_H_

#include "mongodb/mongobase.h"

namespace mongodb
{
class MongoDb : public MongoBase
{
public:
    static MongoDb *getInstance();
    static void destroyInstance();

protected:
    MongoDb();
    MongoDb(const MongoDb&) = delete;
    MongoDb& operator=(const MongoDb&) = delete;

private:
    static MongoDb* s_instance;
    static void destroyInstanceAtExit() __attribute__((destructor));

};
} // namespace mongodb

#endif /* MONGODB_INCLUDE_MONGODB_MONGODB_H_ */
