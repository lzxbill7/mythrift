# apps or test

ADD_EXECUTABLE(server Serv_server.skeleton.cpp)
TARGET_LINK_LIBRARIES(server ${THRIFTSAMPLE_NEEDED_LIBS})
