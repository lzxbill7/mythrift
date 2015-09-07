/*
 * log.cpp
 *
 *  Created on: Jul 11, 2015
 *      Author: zxliu
 */

#include <stdarg.h>
#include <stdio.h>

#include "utils/log.h"

using std::cout;
using std::cerr;
using std::ostream;
using std::ofstream;

LogLevel Log::level = LOG_DEBUG; // default level
const size_t Log::LOG_MSG_MAX_LEN = 4 * 1024; // 4KiB

ofstream Log::devnull;

void Log::debug(const char* format, ...)
{
    if (level > LOG_DEBUG)
        return;

    va_list args;
    va_start(args, format);
    log(cout, format, args);
    va_end(args);
}

void Log::info(const char* format, ...)
{
    if (level > LOG_INFO)
        return;

    va_list args;
    va_start(args, format);
    log(cout, format, args);
    va_end(args);
}

void Log::warn(const char* format, ...)
{
    if (level > LOG_WARN)
        return;

    va_list args;
    va_start(args, format);
    log(cout, format, args);
    va_end(args);
}

void Log::error(const char* format, ...)
{
    if (level > LOG_ERROR)
        return;

    va_list args;
    va_start(args, format);
    log(cerr, format, args);
    va_end(args);
}

void Log::fatal(const char* format, ...)
{
    if (level > LOG_FATAL)
        return;

    va_list args;
    va_start(args, format);
    log(cerr, format, args);
    va_end(args);
}

void Log::fatalExit(const char* format, ...)
{
    if (level > LOG_FATAL)
        return;

    va_list args;
    va_start(args, format);
    log(cerr, format, args);
    va_end(args);

    exit(EXIT_FAILURE);
}

ofstream& Log::devNull(void)
{
    if (not devnull.good())
    {
        devnull.open("/dev/null");
    }

    return devnull;
}

ostream& Log::debug(void)
{
    if (level > LOG_DEBUG)
    {
        return devNull();
    }

    return cout;
}

ostream& Log::info(void)
{
    if (level > LOG_INFO)
    {
        return devNull();
    }

    return cout;
}

ostream& Log::warn(void)
{
    if (level > LOG_WARN)
    {
        return devNull();
    }

    return cout;
}

ostream& Log::error(void)
{
    if (level > LOG_ERROR)
    {
        return devNull();
    }

    return cerr;
}

ostream& Log::fatal(void)
{
    if (level > LOG_FATAL)
    {
        return devNull();
    }

    return cerr;
}

ostream& Log::endl(ostream& os)
{
    return os << std::endl;
}

void Log::log(ostream& os, const char* format, va_list args)
{
    char buff[LOG_MSG_MAX_LEN];
    vsnprintf(buff, LOG_MSG_MAX_LEN, format, args);
    os << buff << "\n";
    os.flush();
}


