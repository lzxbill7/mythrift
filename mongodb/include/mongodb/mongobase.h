/**
 * @file       mongobase.h
 * @brief      /mythrift/mongodb/include/mongodb/mongobase.h
 *
 * @date       Sep 11, 2015
 * @author     lzx_bupt@126.com
 * @note       create
 */

#ifndef MONGODB_MONGOBASE_H_
#define MONGODB_MONGOBASE_H_

#include <string>
#include "mongo/client/dbclient.h"

namespace mongodb
{

class MongoBase
{
public:
    static const size_t MAX_ERROR_BUFFER = 1024;

protected:
    MongoBase(void);
    virtual ~MongoBase(void);

    void open(const char* endpoint = "localhost");
    void open(const std::string& endpoint)
    {
        open(endpoint.c_str());
    }

    // TODO: implement these method
    void close(void);
    void isOpen(void);

    const char* getlastError(void)
    {
        return m_lastErrorBuff;
    }

private:
    void initializeDriver(void);

protected:
    mongo::DBClientConnection* m_dbconn;
    char *m_lastErrorBuff;

};

} // namespace mongodb

#endif /* MONGODB_MONGOBASE_H_ */
