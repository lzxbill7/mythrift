/**
 * @file       libconfigupdate.cpp
 * @brief      /mythrift/hellolibconfig/app/libconfigupdate.cpp
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

// This example reads the configuration file 'example.cfg', adds a new
// movie record to the movies list, and writes the updated configuration to
// 'updated.cfg'.

int main(int argc, char **argv)
{
    static const char *output_file = "updated.cfg";
    Config cfg;

    // Read the file. If there is an error, report it and exit.
    try
    {
        cfg.readFile("../../hellolibconfig/data/example.cfg");
    } catch (const FileIOException &fioex)
    {
        std::cerr << "I/O error while reading file." << std::endl;
        return (EXIT_FAILURE);
    } catch (const ParseException &pex)
    {
        std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine() << " - " << pex.getError() << std::endl;
        return (EXIT_FAILURE);
    }

    // Find the 'movies' setting. Add intermediate settings if they don't yet
    // exist.
    Setting &root = cfg.getRoot();
    if (!root.exists("inventory"))
        root.add("inventory", Setting::TypeGroup);
    Setting &inventory = root["inventory"];
    if (!inventory.exists("movies"))
        inventory.add("movies", Setting::TypeList);
    Setting &movies = inventory["movies"];

    // Create the new movie entry.
    Setting &movie = movies.add(Setting::TypeGroup);
    movie.add("title", Setting::TypeString) = "Buckaroo Banzai";
    movie.add("media", Setting::TypeString) = "DVD";
    movie.add("price", Setting::TypeFloat) = 12.99;
    movie.add("qty", Setting::TypeInt) = 20;

    // Write out the updated configuration.
    try
    {
        cfg.writeFile(output_file);
        cerr << "Updated configuration successfully written to: " << output_file << endl;
    } catch (const FileIOException &fioex)
    {
        cerr << "I/O error while writing file: " << output_file << endl;
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}
