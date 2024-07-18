file(GLOB DEVICE_HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/device/*.h")

add_library(device_library device.c ${DEVICE_HEADER_LIST})
target_include_directories(device_library PUBLIC ${PROJECT_SOURCE_DIR}/include)
source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Device Header Files"
  FILES ${DEVICE_HEADER_LIST})
