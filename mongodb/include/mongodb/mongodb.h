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

namespace mongodb
{
class MongoDb
{
public:
    static MongoDb *getInstance();
    static void destroyInstance();

private:
    static MongoDb* s_instance;
    static void destroyInstanceAtExit() __attribute__((destructor));
};
} // namespace mongodb

#endif /* MONGODB_INCLUDE_MONGODB_MONGODB_H_ */
