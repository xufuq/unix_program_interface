project(file_map)

add_executable(file_map file_map.c)

target_include_directories(file_map PRIVATE ${CMAKE_SOURCE_DIR}/lib/include)

target_link_libraries(file_map PRIVATE mylib pthread)