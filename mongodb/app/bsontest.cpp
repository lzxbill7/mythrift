/**
 * @file       bsontest.cpp
 * @brief      /mythrift/mongodb/app/bsontest.cpp
 *
 * @date       Sep 10, 2015
 * @author     lzx_bupt@126.com
 * @note       create
 */

#include <cstdlib>
#include <iostream>
#include "mongo/client/dbclient.h" // for the driver

using namespace std;

using mongo::BSONObj;
// a BSON object
using mongo::BSONElement;
//a single element in a BSON object. This is a key and a value.
using mongo::BSONObjBuilder;
//used to make BSON objects
using mongo::BSONObjIterator;
//used to enumerate BSON objects

void run() {
    BSONObjBuilder b;
    b.append("name", "Joe");
    b.append("age", 33);
    BSONObj p = b.obj();

    cout << "person:" << p << endl;
    mongo::DBClientConnection c;
    c.connect("localhost");
    c.insert("tutorial.persons", p);
}

int main() {
    mongo::client::initialize();
    try {
        run();
        std::cout << "connected ok" << std::endl;
    } catch (const mongo::DBException &e) {
        std::cout << "caught " << e.what() << std::endl;
    }
    return EXIT_SUCCESS;
}

