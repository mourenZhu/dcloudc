cmake_minimum_required(VERSION 3.22)
project(dcloudc VERSION 1.0
        DESCRIPTION "Very nice project"
        LANGUAGES C)


set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

aux_source_directory(${PROJECT_SOURCE_DIR}/src src_dirs) # 指定源码目录

link_directories(${PROJECT_SOURCE_DIR}/lib) # 指定库搜索路径

find_library(LIBEVENT2_CORE event_core)
find_library(cJSON cjson)

# The compiled library code is here
add_subdirectory(src)

# The executable code is here
add_subdirectory(apps)


