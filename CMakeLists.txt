cmake_minimum_required(VERSION 3.0.0)
cmake_policy(SET CMP0135 NEW)
project(TRANFILER VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE "Debug")

find_program( MEMORYCHECK_COMMAND valgrind )
set( VALGRIND_COMMAND_OPTIONS "--leak-check=full --show-leak-kinds=all --trace-children=yes" )
set( VALGRIND_COMMAND "--leak-check=full --show-leak-kinds=all --trace-children=yes" )
include(CTest)
enable_testing()

set(CORE "core")
file(GLOB_RECURSE CORE_H "${CORE}/*.h")
file(GLOB_RECURSE CORE_CPP "${CORE}/*.cc")

set(SRC "src")
file(GLOB_RECURSE SRC_H "${SRC}/*.h")
file(GLOB_RECURSE SRC_CPP "${SRC}/*.cc")


message(STATUS "CORE_H=${CORE_H}")
message(STATUS "CORE_CPP=${CORE_CPP}")

message(STATUS "SRC_H=${SRC_H}")
message(STATUS "SRC_CPP=${SRC_CPP}")

include_directories(${PROJECT_SOURCE_DIR}/core ${PROJECT_SOURCE_DIR}/src)
add_executable(TRANFILER_CLIENT client.cc ${CORE_H} ${CORE_CPP} ${SRC_H} ${SRC_CPP})
add_executable(TRANFILER_SERVER server.cc ${CORE_H} ${CORE_CPP} ${SRC_H} ${SRC_CPP})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
set(CMAKE_CXX_STANDARD_REQUIRED ON)   

find_package(RapidJSON CONFIG REQUIRED)

target_link_libraries(TRANFILER_CLIENT PRIVATE rapidjson)
target_link_libraries(TRANFILER_SERVER PRIVATE rapidjson)

add_subdirectory(${PROJECT_SOURCE_DIR}/test)