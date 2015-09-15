/**
 * @file       libconfigwrite.cpp
 * @brief      /mythrift/hellolibconfig/app/libconfigwrite.cpp
 *
 * @date       Sep 14, 2015
 * @author     lzx_bupt@126.com
 * @note       create
 */

#include <cstdlib>
#include <iostream>
#include <iomanip>

#include <libconfig.h++>

using namespace std;
using namespace libconfig;

// This example constructs a new configuration in memory and writes it to
// 'newconfig.cfg'.
int main(int argc, char **argv)
{
    static const char *output_file = "newconfig.cfg";
    Config cfg;
    Setting &root = cfg.getRoot();

    // Add some settings to the configuration.
    Setting &address = root.add("address", Setting::TypeGroup);
    address.add("street", Setting::TypeString) = "1 Woz Way";
    address.add("city", Setting::TypeString) = "San Jose";
    address.add("state", Setting::TypeString) = "CA";
    address.add("zip", Setting::TypeInt) = 95110;
    Setting &array = root.add("array", Setting::TypeArray);

    for (int i = 0; i < 10; ++i)
        array.add(Setting::TypeInt) = 10 * i;

    // Write out the new configuration.
    try
    {
        cfg.writeFile(output_file);
        cerr << "New configuration successfully written to: " << output_file << endl;
    } catch (const FileIOException &fioex)
    {
        cerr << "I/O error while writing file: " << output_file << endl;
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

