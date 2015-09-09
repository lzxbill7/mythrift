PROJECT(mythrift)

# Uncomment next line to "debug" the make files
#SET(CMAKE_VERBOSE_MAKEFILE TRUE)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6.0)

# http://www.cmake.org/pipermail/cmake/2010-July/037965.html
EXECUTE_PROCESS(
    COMMAND "${mythrift_SOURCE_DIR}/script/get_version.sh"
    WORKING_DIRECTORY ${mythrift_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_VERSION
    RESULT_VARIABLE GIT_EXIT_CODE
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_STRIP_TRAILING_WHITESPACE)
SET(GIT_VERSION \"${GIT_VERSION}\")
MESSAGE("GIT_VERSION=${GIT_VERSION}")
# MESSAGE("GIT_EXIT_CODE=${GIT_EXIT_CODE}")
ADD_DEFINITIONS(-DGIT_VERSION=${GIT_VERSION})

EXECUTE_PROCESS(
    COMMAND "${mythrift_SOURCE_DIR}/script/get_version_major.sh"
    WORKING_DIRECTORY ${mythrift_SOURCE_DIR}
    OUTPUT_VARIABLE _VERSION_MAJOR
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_STRIP_TRAILING_WHITESPACE)
MESSAGE("_VERSION_MAJOR=${_VERSION_MAJOR}")
ADD_DEFINITIONS(-D_VERSION_MAJOR=${_VERSION_MAJOR})
EXECUTE_PROCESS(
    COMMAND "${mythrift_SOURCE_DIR}/script/get_version_minor.sh"
    WORKING_DIRECTORY ${mythrift_SOURCE_DIR}
    OUTPUT_VARIABLE _VERSION_MINOR
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_STRIP_TRAILING_WHITESPACE)
MESSAGE("_VERSION_MINOR=${_VERSION_MINOR}")
ADD_DEFINITIONS(-D_VERSION_MINOR=${_VERSION_MINOR})
EXECUTE_PROCESS(
    COMMAND "${mythrift_SOURCE_DIR}/script/get_version_patch.sh"
    WORKING_DIRECTORY ${mythrift_SOURCE_DIR}
    OUTPUT_VARIABLE _VERSION_PATCH
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_STRIP_TRAILING_WHITESPACE)
MESSAGE("_VERSION_PATCH=${_VERSION_PATCH}")
ADD_DEFINITIONS(-D_VERSION_PATCH=${_VERSION_PATCH})

MESSAGE("Project Version is ${_VERSION_MAJOR}.${_VERSION_MINOR}.${_VERSION_PATCH}")

SET(${PROJECT_NAME}_MAJOR_VERSION ${_VERSION_MAJOR})
SET(${PROJECT_NAME}_MINOR_VERSION ${_VERSION_MINOR})
SET(${PROJECT_NAME}_PATCH_LEVEL ${_VERSION_PATCH})

# Allows ENDIF() instead of ENDIF(...)
SET(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS TRUE)

SET(${PROJECT_NAME}_SOVERSION "${${PROJECT_NAME}_MAJOR_VERSION}.${${PROJECT_NAME}_MINOR_VERSION}")

SET(${PROJECT_NAME}_VERSION "${${PROJECT_NAME}_MAJOR_VERSION}.${${PROJECT_NAME}_MINOR_VERSION}.${${PROJECT_NAME}_PATCH_LEVEL}")

# Build shared library by default
IF (NOT BUILD_SHARED_LIBS)
    OPTION(BUILD_SHARED_LIBS "Create shared libraries" ON)
ENDIF (NOT BUILD_SHARED_LIBS)


# Add link path(s) to RPATH in shared libraries and executables. Saves setting LD_LIBRARY_PATH each time...
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH 1)

# Library directory - lib or lib64?
IF (NOT LIB_SUFFIX)
    IF (CMAKE_SIZEOF_VOID_P EQUAL 4)
        SET(LIB_SUFFIX "")
    ELSE (CMAKE_SIZEOF_VOID_P EQUAL 4)
        SET(LIB_SUFFIX 64)
    ENDIF (CMAKE_SIZEOF_VOID_P EQUAL 4)
ENDIF (NOT LIB_SUFFIX)


# Custom cmake modules
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

IF (NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE Debug CACHE STRING
        "Choose the type of build, options are: None Debug Release Strict RelWithDebInfo." FORCE)
ENDIF (NOT CMAKE_BUILD_TYPE)

# Compiler/linker flags
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    # using Clang
    # -Weverything -Wweak-vtables -Wsign-conversion -Wconversion
    SET(XTRA "-Wno-gnu-array-member-paren-init -Wno-error=unused-command-line-argument -Wno-padded -Wno-macro-redefined")
    #SET(XTRA "${XTRA} -Wno-packed -Wno-documentation -Wno-c++98-compat -Wno-gnu-anonymous-struct")
    #SET(XTRA "${XTRA} -Wno-exit-time-destructors -Wno-global-constructors")
    #SET(XTRA "${XTRA} -Wshorten-64-to-32 -Wold-style-cast -Wdeprecated -Wfloat-conversion")
    SET(XTRA "${XTRA} -Wformat-nonliteral -Wmissing-noreturn -Wmissing-prototypes -Wshadow")
    SET(XTRA "${XTRA} -Wunreachable-code -Wunreachable-code-return -Wunused-macros")
    SET(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${XTRA}")
    ADD_DEFINITIONS("-D__GNUC__=4")
    ADD_DEFINITIONS("-D__GNUC_MINOR__=4")
    ADD_DEFINITIONS("-D__GXX_EXPERIMENTAL_CXX0X__")
#elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
#    # using GCC
#elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
#    # using Intel C++
#elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
#    # using Visual Studio C++
endif()

IF (("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU") OR ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang"))

    # https://gcc.gnu.org/onlinedocs/gcc/Template-Instantiation.html#Template-Instantiation
    #  -frepo
    #  -fvisibility-inlines-hidden
    #  -Wold-style-cast
    #  -Wnarrowing -Woverloaded-virtual -Wsign-promo

    SET(_DEF_FLAGS "-fmessage-length=0 -pthread -Wall -Wextra -Waddress -Wchar-subscripts -Wcomment -Wempty-body")
    SET(_DEF_FLAGS "-Wmissing-braces -Wreturn-type -Wtrigraphs -Wtype-limits -Wunused-value")
    SET(_DEF_FLAGS "${_DEF_FLAGS} -Werror")
    SET(CMAKE_C_FLAGS             "${CMAKE_C_FLAGS}   ${_DEF_FLAGS}")
    SET(CMAKE_CXX_FLAGS           "${CMAKE_CXX_FLAGS} ${_DEF_FLAGS} -std=c++0x -Wnon-virtual-dtor -Wctor-dtor-privacy")

    # http://wiki.gentoo.org/wiki/Project:Quality_Assurance/As-needed
    # http://www.bnikolic.co.uk/blog/gnu-ld-as-needed.html ,--no-undefined,--no-allow-shlib-undefined
    SET(CMAKE_SHARED_LINKER_FLAGS "-Wl,--no-as-needed")
    SET(CMAKE_MODULE_LINKER_FLAGS "-Wl,--no-as-needed")

    SET(_DEBUG_FLAGS "-g -ggdb3 -O0 -DDEBUG -fno-inline -fstack-protector-all -Wstack-protector")
    SET(CMAKE_C_FLAGS_DEBUG             "${CMAKE_C_FLAGS}   ${_DEBUG_FLAGS}")
    SET(CMAKE_CXX_FLAGS_DEBUG           "${CMAKE_CXX_FLAGS} ${_DEBUG_FLAGS}")
    SET(CMAKE_SHARED_LINKER_FLAGS_DEBUG "${CMAKE_SHARED_LINKER_FLAGS}")
    SET(CMAKE_MODULE_LINKER_FLAGS_DEBUG "${CMAKE_MODULE_LINKER_FLAGS}")

    SET(_RELWITHDEBINFO_FLAGS "-O3 -ggdb3 -D_FORTIFY_SOURCE=2 -fstack-protector-all -Wstack-protector -mmmx -msse -msse2 -mno-sse3 -mno-3dnow")
    SET(CMAKE_C_FLAGS_RELWITHDEBINFO   "${CMAKE_C_FLAGS}   ${_RELWITHDEBINFO_FLAGS}")
    SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS} ${_RELWITHDEBINFO_FLAGS}")
    SET(CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO "${CMAKE_SHARED_LINKER_FLAGS}")
    SET(CMAKE_MODULE_LINKER_FLAGS_RELWITHDEBINFO "${CMAKE_MODULE_LINKER_FLAGS}")

    SET(_REL_FLAGS "${_RELWITHDEBINFO_FLAGS} -D_FORTIFY_SOURCE=2 -fstack-protector-all -DNDEBUG")
    SET(CMAKE_C_FLAGS_RELEASE   "${CMAKE_C_FLAGS}   ${_REL_FLAGS}")
    SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${_REL_FLAGS}")
    SET(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS}")
    SET(CMAKE_MODULE_LINKER_FLAGS_RELEASE "${CMAKE_MODULE_LINKER_FLAGS}")

    SET(_MINSIZEREL_FLAGS "-Os -DNDEBUG -D_FORTIFY_SOURCE=2 -fstack-protector-all -mmmx -msse -msse2 -mno-sse3 -mno-3dnow")
    SET(CMAKE_C_FLAGS_MINSIZEREL   "${CMAKE_C_FLAGS}   ${_MINSIZEREL_FLAGS}")
    SET(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS} ${_MINSIZEREL_FLAGS}")
    SET(CMAKE_SHARED_LINKER_FLAGS_MINSIZEREL "${CMAKE_SHARED_LINKER_FLAGS}")
    SET(CMAKE_MODULE_LINKER_FLAGS_MINSIZEREL "${CMAKE_MODULE_LINKER_FLAGS}")

ELSE (("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU") OR ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang"))

    message(FATAL_ERROR "Unsupported compiler '${CMAKE_CXX_COMPILER_ID}'!")

ENDIF (("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU") OR ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang"))

# Find all third party packages
FIND_PACKAGE(Boost REQUIRED)
FIND_PACKAGE(CppUnit) # REQUIRED) # Can compile without unit tests, right?
FIND_PACKAGE(Mongo REQUIRED)
FIND_PACKAGE(Thrift REQUIRED)

# Enable testing
ENABLE_TESTING()
INCLUDE(CTest)
IF (UNIX)
    # FIND_PROGRAM(CTEST_GIT_COMMAND NAMES git)
    FIND_PROGRAM(CTEST_COVERAGE_COMMAND NAMES gcov)
    FIND_PROGRAM(CTEST_MEMORYCHECK_COMMAND NAMES valgrind)
ENDIF()

# Needed libraries - topologically sorted
SET(UTILS_NEEDED_LIBS utilslib)
SET(MONGODB_NEEDED_LIBS ${MONGO_LIBRARIES} ${BOOST_LIBRARIES})
SET(THRIFTGEN_NEEDED_LIBS thriftgenlib ${THRIFT_LIBRARIES})
SET(THRIFTSAMPLE_NEEDED_LIBS thriftsamplelib ${THRIFT_LIBRARIES})

# Includes, please keep sorted
INCLUDE_DIRECTORIES(hello/include)
INCLUDE_DIRECTORIES(thriftgen/include)
INCLUDE_DIRECTORIES(thriftsample/include)
INCLUDE_DIRECTORIES(utils/include)
# Includes, please keep sorted

# Applications, please keep sorted
ADD_SUBDIRECTORY(hello)
ADD_SUBDIRECTORY(mongodb)
ADD_SUBDIRECTORY(thriftgen)
ADD_SUBDIRECTORY(thriftsample)
ADD_SUBDIRECTORY(utils)
# Applications, please keep sorted

