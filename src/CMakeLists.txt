set(SRC_FILES
        types.cpp
        crypto/md5.cpp
        crypto/sha.cpp
        net/http/client/curl_easy.cpp
        net/http/client/sync_client.cpp
        )
# Add source to this project's executable.
add_library(libjstack STATIC ${SRC_FILES} )
add_library(libjstack_dynamic SHARED ${SRC_FILES})

set_target_properties(libjstack_dynamic PROPERTIES OUTPUT_NAME libjstack)
target_link_libraries(libjstack_dynamic ${LIBS})

target_link_libraries(libjstack ${LIBS})

