project(recv)

add_executable(${PROJECT_NAME} recv.c)

message(${CMAKE_SOURCE_DIR})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/lib/include)

target_link_libraries(${PROJECT_NAME} PRIVATE mylib pthread)