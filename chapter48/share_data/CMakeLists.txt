project(share_data)

add_executable(write binary_sems.h binary_sems.c semun.h svshm_xfr.h svshm_xfr_writer.c)

target_include_directories(write PRIVATE ${CMAKE_SOURCE_DIR}/lib/include)

target_link_libraries(write PRIVATE mylib pthread)

add_executable(read binary_sems.h binary_sems.c semun.h svshm_xfr.h svshm_xfr_reader.c)

target_include_directories(read PRIVATE ${CMAKE_SOURCE_DIR}/lib/include)

target_link_libraries(read PRIVATE mylib pthread)