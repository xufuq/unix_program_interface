project(aysnc_io)

add_executable(aysnc_io aysnc_io.c)

target_include_directories(aysnc_io PRIVATE ${CMAKE_SOURCE_DIR}/lib/include .)

target_link_libraries(aysnc_io PRIVATE mylib pthread)