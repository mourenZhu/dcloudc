# Note that headers are optional, and do not affect add_library, but they will not
# show up in IDEs unless they are listed in add_library.

include_directories(${PROJECT_SOURCE_DIR}/include)

# Optionally glob, but only for CMake 3.12 or later:
file(GLOB COMMON_HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/common/*.h")
# set(HEADER_LIST "${PROJECT_SOURCE_DIR}/include/device_cloud_client/conf.h")

# Make an automatic library - will be static or dynamic based on user setting
add_library(common_library conf.c log.c futil.c ${COMMON_HEADER_LIST})

# We need this directory, and users of our library will need it too
target_include_directories(common_library PUBLIC ${PROJECT_SOURCE_DIR}/include)

# IDEs should put the headers in a nice place
source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Common Header Files"
  FILES ${COMMON_HEADER_LIST})

