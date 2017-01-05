cmake_minimum_required(VERSION 2.8)
project(zpub)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

if(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    set(PROTOBUF_PROTOC_EXECUTABLE /usr/local/bin/protoc)
    set(GRPC_CPP_PLUGIN_EXECUTABLE  /usr/local/bin/grpc_cpp_plugin)
    set(GRPC_LIBRARIES libgrpc++.a libgrpc.a libprotobuf.a)
elseif(WIN32)
    # TODO
endif(UNIX)

link_libraries(-lzmq pthread -lprofiler -lm ${GRPC_LIBRARIES})

find_package(Protobuf REQUIRED)
set(ZPUB_PROTO
        ${zpub_SOURCE_DIR}/src/zpbs/helloworld.proto
        )
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${ZPUB_PROTO})
# grpc generate cpp
foreach(FIL ${ZPUB_PROTO})
    get_filename_component(ABS_FIL ${FIL} ABSOLUTE)
    get_filename_component(FIL_WE ${FIL} NAME_WE)

    list(APPEND PROTO_SRCS "${CMAKE_CURRENT_BINARY_DIR}/${FIL_WE}.grpc.pb.cc")
    list(APPEND PROTO_HDRS "${CMAKE_CURRENT_BINARY_DIR}/${FIL_WE}.grpc.pb.h")

    add_custom_command(
            OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${FIL_WE}.grpc.pb.cc"
            OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${FIL_WE}.grpc.pb.h"
            COMMAND ${PROTOBUF_PROTOC_EXECUTABLE}
            ARGS -I ${zpub_SOURCE_DIR}/src/zpbs
            --grpc_out=${CMAKE_CURRENT_BINARY_DIR}
            --plugin=protoc-gen-grpc=${GRPC_CPP_PLUGIN_EXECUTABLE}
            ${ABS_FIL}
            DEPENDS ${ABS_FIL} ${PROTOBUF_PROTOC_EXECUTABLE} ${GRPC_CPP_PLUGIN_EXECUTABLE}
            COMMENT "Running C++ protocol buffer compiler with grpc plugin on ${FIL}"
            VERBATIM)
endforeach()
set_source_files_properties(${PROTO_SRCS} ${PROTO_HDRS} PROPERTIES GENERATED TRUE)


INCLUDE_DIRECTORIES(${zpub_SOURCE_DIR}/include
                    ${zpub_SOURCE_DIR}
                    ${CMAKE_CURRENT_BINARY_DIR})

set(SOURCE_FILES
        include/nsky/utils/status.h
        include/nsky/utils/status_code_enum.h
        include/nsky/pub/physical_pub_client.h
        include/nsky/sub/logical_sub_service.h
        include/nsky/sub/physical_sub_service.h
        include/nsky/utils/serialization.h
        include/nsky/pub/pub_impl.h
        include/nsky/pub/publish_interface.h
        src/common/zeromq_help.h
        src/pub/physical_pub_client.cpp
        src/sub/physical_sub_service.cpp
        src/pub/default_client_config.h
        src/pub/stub/zmq_pub_impl.h
        src/pub/stub/zmq_pub_impl.cpp
        src/pub/pub_stub_factory.h
        src/pub/pub_impl.cpp
        )

add_library(zpub ${SOURCE_FILES})

set (PUB_FILES
        ${PROTO_SRCS}
        ${PROTO_HDRS}
        example/cpp/pub_example.cpp)

add_executable(pub ${PUB_FILES})
target_link_libraries(pub zpub)
