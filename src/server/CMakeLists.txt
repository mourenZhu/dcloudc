file(GLOB SERVER_HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/server/*.h")

add_library(server_library server.c ${DEVICE_HEADER_LIST})
target_include_directories(server_library PUBLIC ${PROJECT_SOURCE_DIR}/include)
source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "SERVER Header Files"
  FILES ${SERVER_HEADER_LIST})
