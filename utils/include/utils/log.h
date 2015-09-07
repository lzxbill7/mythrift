/*
 * log.h
 *
 *  Created on: Jul 11, 2015
 *      Author: zxliu
 */

#ifndef UTILS_LOG_H_
#define UTILS_LOG_H_

#include <iostream>
#include <fstream>

enum LogLevel
{
    LOG_DEBUG = 0,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR,
    LOG_FATAL,
    LOG_FATALEXIT
};

class Log
{
public:
    static LogLevel level;
    static std::ofstream devnull;

public:
    static void debug(const char* format, ...);
    static void info(const char* format, ...);
    static void warn(const char* format, ...);
    static void error(const char* format, ...);
    static void errorNo(const char* message);
    static void fatal(const char* format, ...);
    static void fatalExit(const char* format,...);

    static std::ostream& debug(void);
    static std::ostream& info(void);
    static std::ostream& warn(void);
    static std::ostream& error(void);
    static std::ostream& fatal(void);
    static std::ostream& endl(std::ostream& os);

private:
    static void log(std::ostream&, const char* format, va_list args);
    static std::ofstream& devNull(void);

private:
    static const size_t LOG_MSG_MAX_LEN;

};

#endif /* UTILS_LOG_H_ */
