cmake_minimum_required(VERSION 3.0.0)
project(TRANFILER VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE "Debug")
include(CTest)
enable_testing()

set(CORE "core")
file(GLOB_RECURSE CORE_H "${CORE}/*.h")
file(GLOB_RECURSE CORE_CPP "${CORE}/*.cc")

message(STATUS "CORE_H=${CORE_H}")
message(STATUS "CORE_CPP=${CORE_CPP}")

include_directories(${PROJECT_SOURCE_DIR}/core)
add_executable(TRANFILER main.cpp ${CORE_H} ${CORE_CPP})
add_executable(TESTMENPOOL test/TestMemPool.cc ${CORE_H} ${CORE_CPP})
add_executable(TESTUPDSERVER test/TestUpdServer.cc ${CORE_H} ${CORE_CPP})

add_test(TESTUPDSERVER test_upd_server)
add_test(TESTMENPOOL test_men_pool)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(RapidJSON)