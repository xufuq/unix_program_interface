project(addr_test)

add_executable(addr_server server.c)

target_include_directories(addr_server PRIVATE ${CMAKE_SOURCE_DIR}/lib/include .)

target_link_libraries(addr_server PRIVATE mylib pthread)

add_executable(addr_client client.c)

target_include_directories(addr_client PRIVATE ${CMAKE_SOURCE_DIR}/lib/include .)

target_link_libraries(addr_client PRIVATE mylib pthread)