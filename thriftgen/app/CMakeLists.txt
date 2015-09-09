# apps or test

ADD_EXECUTABLE(calculator Calculator_server.skeleton.cpp)
TARGET_LINK_LIBRARIES(calculator ${THRIFTGEN_NEEDED_LIBS})
# INSTALL(TARGETS calculator DESTINATION bin)

ADD_EXECUTABLE(sharedserver SharedService_server.skeleton.cpp)
TARGET_LINK_LIBRARIES(sharedserver ${THRIFTGEN_NEEDED_LIBS})
# INSTALL(TARGETS sharedserver DESTINATION bin)

ADD_EXECUTABLE(calculatorclient client.cpp)
TARGET_LINK_LIBRARIES(calculatorclient ${THRIFTGEN_NEEDED_LIBS})
# INSTALL(TARGETS calculatorclient DESTINATION bin)
