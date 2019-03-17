# Find the CppUnit includes and library

FIND_PATH(CPPUNIT_INCLUDE_DIR cppunit/TestCase.h
        /usr/local/include
        /usr/include
        ${PROJECT_SOURCE_DIR}/../third-lib/cppunit/include
        )

FIND_LIBRARY(CPPUNIT_LIBRARY cppunit
        ${CPPUNIT_INCLUDE_DIR}/../lib
        /usr/local/lib
        /usr/lib)

IF (CPPUNIT_INCLUDE_DIR AND CPPUNIT_LIBRARY)
    SET(CPPUNIT_FOUND TRUE)
ENDIF (CPPUNIT_INCLUDE_DIR AND CPPUNIT_LIBRARY)

IF (CPPUNIT_FOUND)
    MESSAGE(STATUS "Found CPPUNIT INCLUDE: ${CPPUNIT_INCLUDE_DIR}")
    MESSAGE(STATUS "Found CPPUNIT LIBRARY: ${CPPUNIT_LIBRARY}")
    INCLUDE_DIRECTORIES(${CPPUNIT_INCLUDE_DIR})
    SET(CPPUNIT_LIBRARIES ${CPPUNIT_LIBRARY})
ELSE (CPPUNIT_FOUND)
    IF (CPPUNIT_FIND_REQUIRED)
        MESSAGE(FATAL_ERROR "CPPUNIT not found")
    ELSE (CPPUNIT_FIND_REQUIRED)
        MESSAGE(STATUS "CPPUNIT not found")
    ENDIF (CPPUNIT_FIND_REQUIRED)
ENDIF (CPPUNIT_FOUND)
