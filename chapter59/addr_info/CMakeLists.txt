project(addr_info)

add_executable(info addrinfo.c)

target_include_directories(info PRIVATE ${CMAKE_SOURCE_DIR}/lib/include .)

target_link_libraries(info PRIVATE mylib pthread)