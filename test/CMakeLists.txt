# Add source to this project's executable.

SET(TEST_SRC
        main.test.cpp
        crypto/crypto.test.cpp
        net/http/client/curl_easy.test.cpp
        )

add_executable(libjstack.tests ${TEST_SRC})
#add_executable(test_executable2 test_file2.cpp)
# indicates the include paths
target_include_directories(libjstack.tests PRIVATE ${BOOST_INCLUDE_DIRS})

link_directories(${PROJECT_SOURCE_DIR}/lib)

message(${CURL_LIBRARIES})

target_link_libraries(libjstack.tests
        libjstack
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
        ${CURL_LIBRARIES}
        )

# declares a test with our executable
add_test("libjstack.tests" libjstack.tests)
#add_test(NAME testname.suit2.test2 COMMAND test_executable2)
# TODO: Add tests and install targets if needed.