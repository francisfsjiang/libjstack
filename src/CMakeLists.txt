IF (CODE_COVERAGE STREQUAL "On")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-instr-generate")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcoverage-mapping")
ENDIF()

set(SRC_FILES
        types.cpp
        crypto/md5.cpp
        crypto/sha.cpp
        net/http/client/curl_easy.cpp
        net/http/client/sync_client.cpp
        )

add_library(libjstack STATIC ${SRC_FILES} )
add_library(libjstack.dynamic SHARED ${SRC_FILES})

target_link_libraries(libjstack ${LIBS})

set_target_properties(libjstack.dynamic PROPERTIES OUTPUT_NAME libjstack)
target_link_libraries(libjstack.dynamic ${LIBS})
