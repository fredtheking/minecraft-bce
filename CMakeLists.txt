cmake_minimum_required(VERSION 3.30)
set(PROJECT_NAME "minecraft-bce")
project(${PROJECT_NAME} LANGUAGES C CXX)

set(CMAKE_POLICY_VERSION_MINIMUM 3.5)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_SUPPRESS_REGENERATION ON CACHE INTERNAL "")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc")
set(GAME_NAME "Minecraft-Better-Cpp-Edition")
set(CLEAN_BIN_DIR ${CMAKE_SOURCE_DIR}/build)

include(FetchContent)



# importing ImGui (1.92.1)
FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        GIT_TAG        v1.92.1
        GIT_SHALLOW    TRUE
        GIT_PROGRESS   TRUE
)
FetchContent_MakeAvailable(imgui)
set(imgui_SOURCE_DIR "${CMAKE_BINARY_DIR}/_deps/imgui-src")
file(GLOB IMGUI_SOURCES ${imgui_SOURCE_DIR}/*.cpp)
add_library(imgui STATIC ${IMGUI_SOURCES})
target_include_directories(imgui PUBLIC ${imgui_SOURCE_DIR})


# importing raylib (5.5)
FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG        5.5
        GIT_SHALLOW    TRUE
        GIT_PROGRESS   TRUE
)
FetchContent_MakeAvailable(raylib)
FetchContent_GetProperties(raylib)


# importing rlImGui (HASH: 4d8a61842903978bc42adf3347cd34f4e6524efc)
FetchContent_Declare(
        rlImGui
        GIT_REPOSITORY https://github.com/raylib-extras/rlImGui.git
        GIT_TAG        4d8a61842903978bc42adf3347cd34f4e6524efc
        GIT_SHALLOW    TRUE
        GIT_PROGRESS   TRUE
)
FetchContent_MakeAvailable(rlImGui)
set(rlImGui_SOURCE_DIR "${CMAKE_BINARY_DIR}/_deps/rlimgui-src")
add_library(rlImGui STATIC ${rlImGui_SOURCE_DIR}/rlImGui.cpp ${rlImGui_SOURCE_DIR}/rlImGui.h)
target_include_directories(rlImGui PUBLIC ${rlImGui_SOURCE_DIR})
target_link_libraries(rlImGui PUBLIC raylib imgui)


# importing yaml-cpp (0.8.0)
FetchContent_Declare(
        yaml-cpp
        GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
        GIT_TAG        0.8.0
        GIT_SHALLOW    TRUE
        GIT_PROGRESS   TRUE
)
FetchContent_MakeAvailable(yaml-cpp)


# importing TinyFileDialogs (HASH: cc6b593c029110af8045826ce691f540c85e850c)
FetchContent_Declare(
        tinyfiledialogs
        GIT_REPOSITORY https://github.com/native-toolkit/libtinyfiledialogs.git
        GIT_TAG        cc6b593c029110af8045826ce691f540c85e850c
        GIT_SHALLOW    TRUE
        GIT_PROGRESS   TRUE
)
FetchContent_MakeAvailable(tinyfiledialogs)


# building game
file(GLOB_RECURSE GAME_SOURCES CONFIGURE_DEPENDS src/**)
list(APPEND GAME_SOURCES ${tinyfiledialogs_SOURCE_DIR}/tinyfiledialogs.c)
add_executable(${GAME_NAME} ${GAME_SOURCES})
target_include_directories(${GAME_NAME} PRIVATE ${tinyfiledialogs_SOURCE_DIR})
target_link_libraries(${GAME_NAME} PRIVATE rlImGui imgui raylib yaml-cpp::yaml-cpp)


set_target_properties(${GAME_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CLEAN_BIN_DIR})
add_custom_command(TARGET ${GAME_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets"
        "${CLEAN_BIN_DIR}/assets"
)