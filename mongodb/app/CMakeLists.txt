ADD_EXECUTABLE(connecttest connecttest.cpp)
TARGET_LINK_LIBRARIES(connecttest ${MONGODB_NEEDED_LIBS})
# INSTALL(TARGETS connecttest DESTINATION bin)