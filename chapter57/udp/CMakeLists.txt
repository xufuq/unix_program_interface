project(udp)

add_executable(udp_server server.c)

target_include_directories(udp_server PRIVATE ${CMAKE_SOURCE_DIR}/lib/include .)

target_link_libraries(udp_server PRIVATE mylib pthread)

add_executable(udp_client client.c)

target_include_directories(udp_client PRIVATE ${CMAKE_SOURCE_DIR}/lib/include .)

target_link_libraries(udp_client PRIVATE mylib pthread)