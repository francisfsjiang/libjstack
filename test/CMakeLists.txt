SET(TEST_SRC
        main.test.cpp
        crypto/crypto.test.cpp
        net/http/client/curl_easy.test.cpp
        data/database/postgresql.test.cpp)

add_executable(libjstack.tests ${TEST_SRC})

target_include_directories(libjstack.tests PRIVATE ${BOOST_INCLUDE_DIRS})

link_directories(${PROJECT_SOURCE_DIR}/lib)

target_link_libraries(libjstack.tests
        libjstack
        ${LIBS}
        )

add_test("libjstack.tests" libjstack.tests)