project(server_client)

add_executable(server server.c)

target_include_directories(server PRIVATE ${CMAKE_SOURCE_DIR}/lib/include .)

target_link_libraries(server PRIVATE mylib pthread)

add_executable(client client.c)

target_include_directories(client PRIVATE ${CMAKE_SOURCE_DIR}/lib/include .)

target_link_libraries(client PRIVATE mylib pthread)