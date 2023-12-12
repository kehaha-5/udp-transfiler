cmake_minimum_required(VERSION 3.0.0)
project(TRANFILER VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE "Debug")
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
add_executable(TESTUPDSERVER test/TestUpdServer.cc ${CORE_H} ${CORE_CPP} ${SRC_H} ${SRC_CPP})
add_executable(TESTTIMER test/TestTimer.cc ${CORE_H} ${CORE_CPP} ${SRC_H} ${SRC_CPP})
add_executable(TESTFILE test/TestFile.cc ${CORE_H} ${CORE_CPP} ${SRC_H} ${SRC_CPP})

add_test(TESTUPDSERVER test_upd_server)
add_test(TESTTIMER test_timer)
add_test(TESTFILE test_file)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(RapidJSON)