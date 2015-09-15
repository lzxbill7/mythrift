# apps or test

ADD_EXECUTABLE(calculatorserver calculatorserver.cpp)
TARGET_LINK_LIBRARIES(calculatorserver ${THRIFTTUTORIAL_NEEDED_LIBS})
# INSTALL(TARGETS calculatorserver DESTINATION bin)

ADD_EXECUTABLE(calculatorserver_threadpool calculatorserver_threadpool.cpp)
TARGET_LINK_LIBRARIES(calculatorserver_threadpool ${THRIFTTUTORIAL_NEEDED_LIBS})
# INSTALL(TARGETS calculatorserver_threadpool DESTINATION bin)

ADD_EXECUTABLE(sharedserver sharedserver.cpp)
TARGET_LINK_LIBRARIES(sharedserver ${THRIFTTUTORIAL_NEEDED_LIBS})
# INSTALL(TARGETS sharedserver DESTINATION bin)

ADD_EXECUTABLE(calculatorclient client.cpp)
TARGET_LINK_LIBRARIES(calculatorclient ${THRIFTTUTORIAL_NEEDED_LIBS})
# INSTALL(TARGETS calculatorclient DESTINATION bin)
