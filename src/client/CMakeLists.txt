file(GLOB CLIENT_HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/client/*.h")

add_library(client_library client.c ${CLIENT_HEADER_LIST})
target_include_directories(client_library PUBLIC ${PROJECT_SOURCE_DIR}/include)
source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Client Header Files"
  FILES ${CLIENT_HEADER_LIST})
