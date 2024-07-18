add_executable(client clientapp.c)

target_link_libraries(client PRIVATE device_library common_library )

add_executable(server serverapp.c)

target_link_libraries(server PRIVATE common_library )

