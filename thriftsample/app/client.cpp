#include "thriftsample/Serv.h"  // 替换成你的.h
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TBinaryProtocol.h>

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

using boost::shared_ptr;

int main(int argc, char **argv) {
    boost::shared_ptr<TSocket> socket(new TSocket("localhost", 9090));
    boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));

    transport->open();

    // 我们的代码写在这里
    // 先创建一个Student类型的变量，Student是我们在student.thrift中定义过的

    Student s;
    s.sno = 123;
    s.sname = "xiaoshe";
    s.ssex = 1;
    s.sage = 30;

    // 再定义一个对象client，又是以"Serv"开头的类

    ServClient client(protocol);

    // 最后调用put函数向服务端传输数据, put是student.thrift采用service定义的成员函数。

    // 调用put后，服务端也调用相应的put()
    client.put(s);
    transport->close();
    return 0;
}
