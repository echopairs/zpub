cmake_minimum_required(VERSION 3.5)
project(zpub)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

INCLUDE_DIRECTORIES(${zpub_SOURCE_DIR}/include)

set(SOURCE_FILES
        main.cpp
        include/nsky/utils/status.h
        include/nsky/utils/status_code_enum.h
        include/nsky/pub/physical_pub_client.h
        include/nsky/pub/logical_pub_client.h
        include/nsky/sub/logical_sub_client.h
        include/nsky/sub/physical_sub_client.h
        include/nsky/utils/serialization.h
        src/common/zeromq_help.h
        src/demos/pub_example.cpp
        src/demos/sub_example.cpp)
add_executable(zpub ${SOURCE_FILES})