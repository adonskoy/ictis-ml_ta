cmake_minimum_required(VERSION 3.8)
project(algoritms_seminars)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(2sem)
add_subdirectory(utils)



#add_executable(cheese 2sem/cheese.cpp)
add_executable(4laba 2sem/4laba.cpp)
#add_executable(test 2sem/test_struct.cpp)
add_executable(test_struct 2sem/test_struct.cpp)
#add_executable(file_manager utils/file_manager.cpp)