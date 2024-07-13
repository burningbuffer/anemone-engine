project(testgame VERSION 0.0.1)

file(GLOB HEADERS 
"source/*.hpp"
)

file(GLOB SOURCES 
"source/*.cpp"
)

# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
# message (STATUS "COMPILER FLAGS: " ${CMAKE_CXX_FLAGS})

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} anemone)

include_directories(${CMAKE_SOURCE_DIR}/source)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/source)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/resources" "${CMAKE_BINARY_DIR}/bin/Debug/resources" COMMENT "Copying resources directory from ${SOURCE_DIR} to ${DESTINATION_DIR}")
# add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#                    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/resources" "${CMAKE_BINARY_DIR}/bin/Release/resources" COMMENT "Copying resources directory from ${SOURCE_DIR} to ${DESTINATION_DIR}")

file(GLOB FILES_TO_COPY "${CMAKE_SOURCE_DIR}/deps/bin/*")

foreach(FILE ${FILES_TO_COPY})
    get_filename_component(FILENAME ${FILE} NAME)

    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy "${FILE}" "${CMAKE_BINARY_DIR}/bin/Debug" 
        COMMENT "Copying ${FILE} from ${SOURCE_DIR} to ${DESTINATION_DIR}"
    )

    # add_custom_command(
    #     TARGET ${PROJECT_NAME} POST_BUILD
    #     COMMAND ${CMAKE_COMMAND} -E copy "${FILE}" "${CMAKE_BINARY_DIR}/bin/Release" 
    #     COMMENT "Copying ${FILE} from ${SOURCE_DIR} to ${DESTINATION_DIR}"
    # )

    list(APPEND COPY_COMMANDS "${DEST_DIR}/${FILENAME}")
endforeach()