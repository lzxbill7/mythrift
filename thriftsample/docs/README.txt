# To use the thrift docs, please generate cpp files first.
# Use thrift tool as following. Be careful of the cwd.
thrift -r --gen cpp -out ../include/thriftsample/ student.thrift
