/**
 * @file       libconfiginvalid.cpp
 * @brief      /mythrift/hellolibconfig/app/libconfiginvalid.cpp
 *
 * @date       Sep 15, 2015
 * @author     lzx_bupt@126.com
 * @note       create
 */

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <libconfig.h++>

using namespace std;
using namespace libconfig;

// This example demonstrates the handling of parsing errors in
// 'invalid.cfg'.
int main(int argc, char **argv)
{
    Config cfg;
    try
    {
        cfg.readFile("../../hellolibconfig/data/invalid.cfg");
    } catch (const FileIOException &fioex)
    {
        std::cerr << "File I/O error" << std::endl;
        return (EXIT_FAILURE);
    } catch (const ParseException &pex)
    {
        std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine() << " - " << pex.getError() << std::endl;
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

