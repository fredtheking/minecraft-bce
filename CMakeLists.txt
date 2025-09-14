cmake_minimum_required(VERSION 3.30)
set(PROJECT_NAME "minecraft-bce")
project(${PROJECT_NAME} LANGUAGES C CXX)

set(ENV{LANG} "en_US.UTF-8")
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_SUPPRESS_REGENERATION ON CACHE INTERNAL "")
set(CLEAN_BIN_DIR ${CMAKE_SOURCE_DIR}/build)

# MSVC stuff
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT /Zi- /DEBUG:NONE")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /INCREMENTAL:NO")

include(FetchContent)



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
set_target_properties(raylib PROPERTIES EXCLUDE_FROM_ALL TRUE)


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
set_target_properties(imgui PROPERTIES EXCLUDE_FROM_ALL TRUE)


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
set_target_properties(rlImGui PROPERTIES EXCLUDE_FROM_ALL TRUE)


# importing FTXUI (6.1.9)
FetchContent_Declare(
        ftxui
        GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
        GIT_TAG v6.1.9
        GIT_SHALLOW    TRUE
        GIT_PROGRESS   TRUE
)
FetchContent_MakeAvailable(ftxui)


# importing yaml-cpp (0.8.0)
FetchContent_Declare(
        yaml-cpp
        GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
        GIT_TAG        0.8.0
        GIT_SHALLOW    TRUE
        GIT_PROGRESS   TRUE
)
FetchContent_MakeAvailable(yaml-cpp)
set_target_properties(yaml-cpp PROPERTIES EXCLUDE_FROM_ALL TRUE)


# importing TinyFileDialogs (HASH: cc6b593c029110af8045826ce691f540c85e850c)
FetchContent_Declare(
        tinyfiledialogs
        GIT_REPOSITORY https://github.com/native-toolkit/libtinyfiledialogs.git
        GIT_TAG        cc6b593c029110af8045826ce691f540c85e850c
        GIT_SHALLOW    TRUE
        GIT_PROGRESS   TRUE
)
FetchContent_MakeAvailable(tinyfiledialogs)



# common things
file(GLOB_RECURSE COMMON_SOURCES CONFIGURE_DEPENDS src/common/**)
set(THIRD_PARTY_DLLS_DIR "${CMAKE_SOURCE_DIR}/third-party/dlls")


# server
file(GLOB_RECURSE SERVER_SOURCES CONFIGURE_DEPENDS src/server/**)
message(STATUS "SERVER_SOURCES = ${SERVER_SOURCES}")
set(SERVER_EXE_NAME minecraft-bce-server)
add_executable(${SERVER_EXE_NAME} ${COMMON_SOURCES} ${SERVER_SOURCES} ${tinyfiledialogs_SOURCE_DIR}/tinyfiledialogs.c)
target_include_directories(${SERVER_EXE_NAME} PRIVATE ${CMAKE_SOURCE_DIR} ${tinyfiledialogs_SOURCE_DIR})
target_link_libraries(${SERVER_EXE_NAME} PRIVATE yaml-cpp::yaml-cpp ftxui::component ftxui::dom ftxui::screen)
set_target_properties(${SERVER_EXE_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CLEAN_BIN_DIR}/server)
add_custom_command(TARGET ${SERVER_EXE_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets/common"
        "${CLEAN_BIN_DIR}/server/assets"
)


# client
file(GLOB_RECURSE CLIENT_SOURCES CONFIGURE_DEPENDS src/client/**)
list(APPEND CLIENT_SOURCES ${SERVER_SOURCES})
list(FILTER CLIENT_SOURCES EXCLUDE REGEX ".*/server/console-app")
message(STATUS "CLIENT_SOURCES = ${CLIENT_SOURCES}")
set(CLIENT_EXE_NAME minecraft-bce-client)
add_executable(${CLIENT_EXE_NAME} ${COMMON_SOURCES} ${CLIENT_SOURCES} ${tinyfiledialogs_SOURCE_DIR}/tinyfiledialogs.c)
target_include_directories(${CLIENT_EXE_NAME} PRIVATE ${CMAKE_SOURCE_DIR} ${tinyfiledialogs_SOURCE_DIR})
target_link_libraries(${CLIENT_EXE_NAME} PRIVATE raylib imgui rlImGui yaml-cpp::yaml-cpp)
set_target_properties(${CLIENT_EXE_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CLEAN_BIN_DIR}/client)
add_custom_command(TARGET ${CLIENT_EXE_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets/client"
        "${CLEAN_BIN_DIR}/client/assets"
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets/common"
        "${CLEAN_BIN_DIR}/client/assets"
)