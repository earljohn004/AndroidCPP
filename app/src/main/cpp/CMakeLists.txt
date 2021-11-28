
cmake_minimum_required(VERSION 3.10.2)

project("androidcpp")

add_library( androidcpp
        SHARED
        src/native-lib.cpp )

find_library( log-lib
        log )

target_link_libraries(
        androidcpp
        ${log-lib} )