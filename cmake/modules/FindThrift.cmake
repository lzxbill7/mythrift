# Find the Thrift includes and library

FIND_PATH(THRIFT_INCLUDE_DIR thrift/Thrift.h
        ${PROJECT_SOURCE_DIR}/../third-lib/thrift-0.9.3/include
        /usr/local/include
        /usr/include
        )

FIND_LIBRARY(THRIFT_LIBRARY thrift
        ${THRIFT_INCLUDE_DIR}/../lib64
        ${THRIFT_INCLUDE_DIR}/../lib
        /usr/local/lib64
        /usr/lib64)

IF (THRIFT_INCLUDE_DIR AND THRIFT_LIBRARY)
    SET(THRIFT_FOUND TRUE)
ENDIF (THRIFT_INCLUDE_DIR AND THRIFT_LIBRARY)

IF (THRIFT_FOUND)
    MESSAGE(STATUS "Found THRIFT INCLUDE: ${THRIFT_INCLUDE_DIR}")
    MESSAGE(STATUS "Found THRIFT LIBRARY: ${THRIFT_LIBRARY}")
    INCLUDE_DIRECTORIES(${THRIFT_INCLUDE_DIR})
    SET(THRIFT_LIBRARIES ${THRIFT_LIBRARY})
ELSE (THRIFT_FOUND)
    IF (THRIFT_FIND_REQUIRED)
        MESSAGE(FATAL_ERROR "THRIFT not found")
    ELSE (THRIFT_FIND_REQUIRED)
        MESSAGE(STATUS "THRIFT not found")
    ENDIF (THRIFT_FIND_REQUIRED)
ENDIF (THRIFT_FOUND)
