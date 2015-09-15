#include <thrift/concurrency/PosixThreadFactory.h>
#include <thrift/concurrency/ThreadManager.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TThreadPoolServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

#include <iostream>
#include <sstream>
#include <stdexcept>

#include "thrifttutorial/Calculator.h"

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;
using namespace ::apache::thrift::concurrency;

//using boost::shared_ptr;

using namespace std;
using namespace ::tutorial;
using namespace shared;

class CalculatorHandler: virtual public CalculatorIf {
public:
    CalculatorHandler() {
        // Your initialization goes here
    }

    void ping() {
        // Your implementation goes here
        cout << "ping()" << endl;
        sleep(2);
    }

    int32_t add(const int32_t num1, const int32_t num2) {
        // Your implementation goes here
        cout << "add(" << num1 << ", " << num2 << ")" << endl;
        return num1 + num2;
    }

    int32_t calculate(const int32_t logid, const Work& w) {
        cout << "calculate(" << logid << ", " << w.op << ")" << endl;
        int32_t val;

        switch (w.op) {
        case Operation::ADD:
            val = w.num1 + w.num2;
            break;
        case Operation::SUBTRACT:
            val = w.num1 - w.num2;
            break;
        case Operation::MULTIPLY:
            val = w.num1 * w.num2;
            break;
        case Operation::DIVIDE:
            if (w.num2 == 0) {
                InvalidOperation io;
                io.whatOp = w.op;
                io.why = "Cannot divide by 0";
                throw io;
            }
            val = w.num1 / w.num2;
            break;
        default:
            InvalidOperation io;
            io.whatOp = w.op;
            io.why = "Invalid Operation";
            throw io;
        }

        SharedStruct ss;
        ss.key = logid;
        ss.value = to_string(val);

        log[logid] = ss;

        return val;
    }

    void zip() {
        // Your implementation goes here
        cout << "zip" << endl;
    }

    void getStruct(SharedStruct& ret, const int32_t logid) {
        cout << "getStruct(" << logid << ")" << endl;
        ret = log[logid];
    }
protected:
    map<int32_t, SharedStruct> log;

};

int main(int argc, char **argv) {
    int port = 9090;
    boost::shared_ptr<CalculatorHandler> handler(new CalculatorHandler());
    boost::shared_ptr<TProcessor> processor(new CalculatorProcessor(handler));
    boost::shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
    boost::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
    boost::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

    boost::shared_ptr<ThreadManager> threadManager = ThreadManager::newSimpleThreadManager(3);
    boost::shared_ptr<PosixThreadFactory> threadFactory = boost::shared_ptr<PosixThreadFactory>(new PosixThreadFactory());
    threadManager->threadFactory(threadFactory);
    threadManager->start();

    TThreadPoolServer server(processor, serverTransport, transportFactory, protocolFactory, threadManager);
    server.serve();
    return 0;
}

