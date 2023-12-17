include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(${PROJECT_SOURCE_DIR}/core ${PROJECT_SOURCE_DIR}/src)

add_executable(TESTTIMER ${PROJECT_SOURCE_DIR}/test/TestTimer.cc ${CORE_H} ${CORE_CPP} ${SRC_H} ${SRC_CPP} )
target_link_libraries(TESTTIMER GTest::gtest_main GTest::gtest )
add_executable(TESTACK ${PROJECT_SOURCE_DIR}/test/TestAck.cc ${CORE_H} ${CORE_CPP} ${SRC_H} ${SRC_CPP} )
target_link_libraries(TESTACK GTest::gtest_main GTest::gtest )

include(GoogleTest)
gtest_discover_tests(TESTTIMER)
gtest_discover_tests(TESTACK)

