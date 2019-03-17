# Find the Mongo includes and library

FIND_PATH(MONGO_INCLUDE_DIR mongo/client/dbclient.h
        ${PROJECT_SOURCE_DIR}/../third-lib/mongoclient/include
        /usr/local/include
        /usr/include
        )

FIND_LIBRARY(MONGO_LIBRARY mongoclient
        ${MONGO_INCLUDE_DIR}/../lib
        /usr/local/lib
        /usr/lib
        )

IF (MONGO_INCLUDE_DIR AND MONGO_LIBRARY)
    SET(MONGO_FOUND TRUE)
ENDIF (MONGO_INCLUDE_DIR AND MONGO_LIBRARY)

IF (MONGO_FOUND)
    MESSAGE(STATUS "Found MONGO INCLUDE: ${MONGO_INCLUDE_DIR}")
    MESSAGE(STATUS "Found MONGO LIBRARY: ${MONGO_LIBRARY}")
    INCLUDE_DIRECTORIES(${MONGO_INCLUDE_DIR})
    SET(MONGO_LIBRARIES ${MONGO_LIBRARY})
ELSE (MONGO_FOUND)
    IF (MONGO_FIND_REQUIRED)
        MESSAGE(FATAL_ERROR "MONGO not found")
    ELSE (MONGO_FIND_REQUIRED)
        MESSAGE(STATUS "MONGO not found")
    ENDIF (MONGO_FIND_REQUIRED)
ENDIF (MONGO_FOUND)
