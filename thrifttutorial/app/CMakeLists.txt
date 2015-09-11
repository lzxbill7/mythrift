# apps or test

ADD_EXECUTABLE(calculator Calculator_server.skeleton.cpp)
TARGET_LINK_LIBRARIES(calculator ${THRIFTTUTORIAL_NEEDED_LIBS})
# INSTALL(TARGETS calculator DESTINATION bin)

ADD_EXECUTABLE(sharedserver SharedService_server.skeleton.cpp)
TARGET_LINK_LIBRARIES(sharedserver ${THRIFTTUTORIAL_NEEDED_LIBS})
# INSTALL(TARGETS sharedserver DESTINATION bin)

ADD_EXECUTABLE(calculatorclient client.cpp)
TARGET_LINK_LIBRARIES(calculatorclient ${THRIFTTUTORIAL_NEEDED_LIBS})
# INSTALL(TARGETS calculatorclient DESTINATION bin)
