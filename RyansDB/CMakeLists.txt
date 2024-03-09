cmake_minimum_required(VERSION 3.0.0)
project(RyansDB VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

find_package(Protobuf REQUIRED)
include_directories(Dto/Customer/)
include_directories(Dto/Transaction/)
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS
    Dto/Customer/customer_dto.proto
    Dto/Transaction/transaction_dto.proto
)

add_executable(RyansDB
    main.cpp
    Connections/connection.cpp
    Socket/socket.cpp
    Data/customer_data.cpp
    ${PROTO_SRCS}
)

target_link_libraries(RyansDB
    ${Protobuf_LIBRARIES}
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
