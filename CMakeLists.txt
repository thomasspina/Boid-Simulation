cmake_minimum_required(VERSION 3.31)
project(Boid-Simulation LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON
    SYSTEM)
FetchContent_Declare(imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG master
    GIT_SHALLOW ON
    SYSTEM)

FetchContent_MakeAvailable(SFML imgui)
set(IMGUI_DIR ${imgui_SOURCE_DIR})
set(IMGUI_SFML_FIND_SFML OFF)

FetchContent_Declare(ImGui-SFML
    GIT_REPOSITORY https://github.com/SFML/imgui-sfml.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON
    SYSTEM)
FetchContent_MakeAvailable(ImGui-SFML)

file(GLOB HEADERS include/*.hpp)
file(GLOB SOURCES src/*.cpp)
add_executable(Boid-Simulation ${HEADERS} ${SOURCES})

target_link_libraries(Boid-Simulation PRIVATE ImGui-SFML::ImGui-SFML)
target_include_directories(Boid-Simulation 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_features(Boid-Simulation PRIVATE cxx_std_23)

if(WIN32)
    add_custom_command(
        TARGET Boid-Simulation
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:Boid-Simulation>
        VERBATIM)
endif()
