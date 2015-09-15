# apps
ADD_EXECUTABLE(libconfigread app/libconfigread.cpp)
TARGET_LINK_LIBRARIES(libconfigread ${LIBCONFIG_LIBRARIES})

ADD_EXECUTABLE(libconfigupdate app/libconfigupdate.cpp)
TARGET_LINK_LIBRARIES(libconfigupdate ${LIBCONFIG_LIBRARIES})


ADD_EXECUTABLE(libconfigwrite app/libconfigwrite.cpp)
TARGET_LINK_LIBRARIES(libconfigwrite ${LIBCONFIG_LIBRARIES})

ADD_EXECUTABLE(libconfiginvalid app/libconfiginvalid.cpp)
TARGET_LINK_LIBRARIES(libconfiginvalid ${LIBCONFIG_LIBRARIES})
