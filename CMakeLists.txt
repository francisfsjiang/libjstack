cmake_minimum_required (VERSION 3.8)

project ("libjstack")

message("Building in ${CMAKE_CXX_COMPILER_ID}.")

IF (CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE "Debug")
ENDIF()

IF (CMAKE_BUILD_TYPE MATCHES Debug)
    message("Building in debug mode.")

    IF (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /DLIBJSTACK_DEBUG")
#        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Wall")
    ELSE()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D LIBJSTACK_DEBUG")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-parameter")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-variable")
    endif()


ELSEIF (CMAKE_BUILD_TYPE MATCHES Release)
    message("Building in release mode.")

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

ENDIF ()

if (LIBJSTACK_TRACE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D LIBJSTACK_TRACE")
endif()

set(LIBRARY_OUTPUT_PATH    ${PROJECT_SOURCE_DIR}/lib)

enable_testing()

set(CMAKE_CXX_STANDARD 17)

set (Boost_USE_STATIC_LIBS OFF)
find_package (Boost COMPONENTS system filesystem unit_test_framework REQUIRED)

find_package(OpenSSL REQUIRED)

find_package(CURL REQUIRED)

find_package(PostgreSQL REQUIRED)

set(INCLUDE_DIRS
        ${PROJECT_SOURCE_DIR}/include
        ${BOOST_INCLUDE_DIRS}
        ${OPENSSL_INCLUDE_DIR}
        ${CURL_INCLUDE_DIRS}
        ${PostgreSQL_INCLUDE_DIRS}
        )

set(LIB_DIRS        ${LIB_DIRS}
        ${Boost_LIBRARY_DIRS}
        ${PostgreSQL_LIBRARY_DIRS}
        )

set(LIBS        ${LIBS}
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
        ${CURL_LIBRARIES}
        ${PostgreSQL_LIBRARIES}
        ${OPENSSL_LIBRARIES}
        )


if (WIN32)

    set(INCLUDE_DIRS    ${INCLUDE_DIRS}

            )
    set(LIB_DIRS        ${LIB_DIRS}
            )

    set(LIBS ${LIBS}
            )

elseif (UNIX)

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DBOOST_LOG_DYN_LINK")

    set(INCLUDE_DIRS    ${INCLUDE_DIRS}

            )
    set(LIB_DIRS        ${LIB_DIRS}
            )

    set(LIBS ${LIBS}
            )

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")

endif()

message("Include dirs ${INCLUDE_DIRS}")
message("Lib dirs ${LIB_DIRS}")
message("Libs ${LIBS}")
#link_directories(${Boost_LIBRARY_DIRS})
#link_directories(${CURL_LIBRARIES})

include_directories(${INCLUDE_DIRS})

IF (CODE_COVERAGE STREQUAL "On")
    MESSAGE("Building with code coverage report.")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-instr-generate")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcoverage-mapping")
ENDIF()

# Include sub-projects.
add_subdirectory ("src")
add_subdirectory ("test")
