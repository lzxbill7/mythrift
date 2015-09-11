/**
 * @file       mongodbtest.cpp
 * @brief      /mythrift/mongodb/app/mongodbtest.cpp
 *
 * @date       Sep 11, 2015
 * @author     lzx_bupt@126.com
 * @note       create
 */


#include <iostream>
#include <stdlib.h>

#include "mongodb/mongodb.h"
#include "mongo/client/dbclient.h" // for the driver

using namespace std;
using namespace mongodb;

void insert() {
    mongo::BSONObjBuilder b;
    b.append("name", "Leon");
    b.append("age", 31);
    mongo::BSONObj p = b.obj();

    cout << "person:" << p << endl;
    MongoDb::getInstance()->insert("tutorial.persons", p);
}

int main(int argc, char* argv[])
{
    insert();
    return EXIT_SUCCESS;
}

