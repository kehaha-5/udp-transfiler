include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(${PROJECT_SOURCE_DIR}/core ${PROJECT_SOURCE_DIR}/src)

include(GoogleTest)

function(addTest testName filename)
  add_executable(${testName} ${PROJECT_SOURCE_DIR}/test/${filename}.cc ${CORE_H} ${CORE_CPP} ${SRC_H} ${SRC_CPP} )
  target_link_libraries(${testName} GTest::gtest_main GTest::gtest protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite  )
  gtest_discover_tests(${testName})
endfunction()

addTest(TESTTIMER TestTimer)
addTest(TESTACK TestAck)
addTest(TESTDIR TestDir)
addTest(TESTSERVERFILE TestServerFile)
addTest(TESTCLIENTFILE TestClientFile)
addTest(TESTMSG TestMsg)
addTest(TESTCONFIG TestConfig)



