ADD_EXECUTABLE(mongodb_test mongodb_test.cpp)
TARGET_LINK_LIBRARIES(mongodb_test ${MONGODB_NEEDED_LIBS} ${CPPUNIT_LIBRARIES})
ADD_TEST(mongodb_test ${EXECUTABLE_OUTPUT_PATH}/mongodb_test)
