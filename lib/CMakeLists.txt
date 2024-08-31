project(mylib)

add_library(${PROJECT_NAME} STATIC src/error_functions.c src/get_num.c
        ../chapter48/share_data/binary_sems.c
        ../chapter48/share_data/semun.h
        ../chapter48/share_data/svshm_xfr.h
        ../chapter48/share_data/svshm_xfr_writer.c
        ../chapter49/file_map/file_map.c
        ../chapter57/server_client/us_xfs_sv.h)

target_include_directories(${PROJECT_NAME} PRIVATE ./include)