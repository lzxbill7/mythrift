/**
 * @file       mongobase.cpp
 * @brief      /mythrift/mongodb/src/mongobase.cpp
 *
 * @date       Sep 11, 2015
 * @author     lzx_bupt@126.com
 * @note       create
 */

#include "mongo/client/dbclient.h"

#include "mongodb/mongobase.h"

namespace mongodb
{

MongoBase::MongoBase(void) :
        m_dbconn(NULL), m_lastErrorBuff(NULL)
{
    initializeDriver();
}

MongoBase::~MongoBase(void)
{
    close();
}

void MongoBase::initializeDriver(void)
{
    // TODO: check the status, log and exit if needed!
    mongo::client::initialize();
}

void MongoBase::open(const char* endpoint)
{
    if (m_dbconn == NULL)
    {
        m_dbconn = new mongo::DBClientConnection();
        m_dbconn->connect(endpoint);

        m_lastErrorBuff = (char*) malloc(MAX_ERROR_BUFFER);
        m_lastErrorBuff[0] = '\0';
    }
}

void MongoBase::close(void)
{
    if (m_dbconn != NULL)
    {
        delete m_dbconn;
        m_dbconn = NULL;

        delete m_lastErrorBuff;
        m_lastErrorBuff = NULL;
    }
}

}

