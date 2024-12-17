cmake_minimum_required(VERSION 3.28)
project(Boid-Simulation LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(Boid-Simulation src/main.cpp)
target_link_libraries(Boid-Simulation PRIVATE sfml-graphics)
target_compile_features(Boid-Simulation PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET Boid-Simulation
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:Boid-Simulation>
        VERBATIM)
endif()
