project(cs_test)

add_executable(cs_server server.c)
target_include_directories(cs_server PRIVATE ${CMAKE_SOURCE_DIR}/lib/include .)
target_link_libraries(cs_server PRIVATE mylib pthread)

add_executable(cs_client client.c)
target_include_directories(cs_client PRIVATE ${CMAKE_SOURCE_DIR}/lib/include .)
target_link_libraries(cs_client PRIVATE mylib pthread)