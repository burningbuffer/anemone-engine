project(anemone VERSION 0.0.1)

file(GLOB HEADERS 
"anemone/*.hpp"
"anemone/components/*.hpp"
"anemone/resourcehandler/*.hpp"
"anemone/core/*.hpp"
"anemone/eventhandler/*.hpp"
"anemone/events/*.hpp"
"anemone/graphics/*.hpp"
"anemone/logger/*.hpp"
"anemone/physics/*.hpp"
"anemone/systems/*.hpp"
"anemone/utils/*.hpp"
"anemone/window/*.hpp"
)

file(GLOB SOURCES 
"anemone/*.cpp"
"anemone/resourcehandler/*.cpp"
"anemone/components/*.cpp"
"anemone/core/*.cpp"
"anemone/eventhandler/*.cpp"
"anemone/events/*.cpp"
"anemone/graphics/*.cpp"
"anemone/logger/*.cpp"
"anemone/physics/*.cpp"
"anemone/systems/*.cpp"
"anemone/utils/*.cpp"
"anemone/window/*.cpp"
)

add_library(${PROJECT_NAME} ${SOURCES} ${HEADERS})

if(WIN32)
target_link_libraries(${PROJECT_NAME} PUBLIC box2d SDL2 SDL2main SDL2_image SDL2_mixer SDL2_ttf glfw3 glew32s glew32 opengl32)
    target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/deps/includes ${CMAKE_SOURCE_DIR}/deps/includes/glm/glm)
    target_include_directories(${PROJECT_NAME} PUBLIC deps/includes/glew deps/includes/glfw)
    #target_include_directories(${PROJECT_NAME} PUBLIC deps/includes/glew/include)
    target_link_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/deps/libs)
endif(WIN32)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/anemone)
