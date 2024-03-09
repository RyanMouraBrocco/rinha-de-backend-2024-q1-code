cmake_minimum_required(VERSION 3.0.0)
project(RyansDB VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

find_package(Protobuf REQUIRED)
include_directories(Data/Customer/)
include_directories(Data/Transaction/)
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS
    Data/Customer/customer_data.proto
    Data/Transaction/transaction_data.proto
)

add_executable(RyansDB
    main.cpp
    Connections/connection.cpp
    Socket/socket.cpp
    ${PROTO_SRCS}
)

target_link_libraries(RyansDB
    ${Protobuf_LIBRARIES}
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
