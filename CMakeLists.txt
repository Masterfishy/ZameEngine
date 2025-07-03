cmake_minimum_required(VERSION 3.22)
project(Aiya)

# Enable C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BUILD_TESTS OFF)

# Retreive GLM package
include(FetchContent)

FetchContent_Declare(
	glm
	GIT_REPOSITORY	https://github.com/g-truc/glm.git
	GIT_TAG 	0af55ccecd98d4e5a8d1fad7de25ba429d60e863 #refs/tags/1.0.1
)

FetchContent_MakeAvailable(glm)

# Emscripten specific configuration
set(EMSCRIPTEN_LINK_FLAGS
    "-s WASM=1"
    "-s USE_WEBGL2=1"
    "-s FULL_ES3=1"
    "-s MIN_WEBGL_VERSION=2"
    "-s MAX_WEBGL_VERSION=2"
    "-s ALLOW_MEMORY_GROWTH=1"
    "-s NO_EXIT_RUNTIME=1"
    # "-s EXPORTED_RUNTIME_METHODS=['ccall','cwrap']"
    "--bind"
    "-s USE_GLFW=3"
    # Flags for asset loading
    # "-s FETCH=1"
    # "-s ASYNCIFY=1"
    "--preload-file shaders"
    "--preload-file textures"
    # Flags for audio support
    # "-s USE_SDL=2"
    # "-s USE_SDL_MIXER=2"
)
string(JOIN " " EMSCRIPTEN_LINK_FLAGS_STR ${EMSCRIPTEN_LINK_FLAGS})
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${EMSCRIPTEN_LINK_FLAGS_STR}")

# Set output file extensions
set(CMAKE_EXECUTABLE_SUFFIX ".js")

# Create the executable
add_library(ZameEngine src/engine/entity.cpp
                       src/engine/attack-system/attack_system.cpp
                       src/engine/input-system/input_system.cpp
                       src/engine/render-system/render_system.cpp
                       src/engine/render-system/texture.cpp
                       src/engine/render-system/shader_program.cpp
                       src/engine/render-system/window.cpp
                       src/engine/walk-system/walk_system.cpp
)

add_executable(${PROJECT_NAME} src/aiya/main.cpp
                               src/aiya/game.cpp                    
)

# Link libraries
target_link_libraries(ZameEngine PUBLIC glfw # From Emscripten
                                        glm::glm
)

target_link_libraries(${PROJECT_NAME} PRIVATE ZameEngine)

# Include directories
target_include_directories(ZameEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/engine
                                             ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/components
                                             ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/attack-system
                                             ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/input-system
                                             ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/render-system
                                             ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/walk-system
                                             ${CMAKE_CURRENT_SOURCE_DIR}/external
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/aiya)

# Copy resource files to build
add_custom_target(copy_resources
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/web
                                               ${CMAKE_CURRENT_LIST_DIR}/assets 
                                               ${CMAKE_CURRENT_BINARY_DIR}
)
add_dependencies(${PROJECT_NAME} copy_resources)

# Output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)

#-----------------------------------------------------------------------------#
# Tests                                                                       #
#-----------------------------------------------------------------------------#
if (BUILD_TESTS)
    # Emscripten specific configuration for testing
    set(EMSCRIPTEN_LINK_FLAGS
        "-s USE_WEBGL2=1"
        "-s FULL_ES3=1"
        "-s MIN_WEBGL_VERSION=2"
        "-s MAX_WEBGL_VERSION=2"
        "-s ALLOW_MEMORY_GROWTH=1"
        "-s NO_EXIT_RUNTIME=1"
        "--bind"
        "-s USE_GLFW=3"
        # Flags for asset loading
        # "-s FETCH=1"
        # "-s ASYNCIFY=1"
        "--preload-file shaders"
        "--preload-file textures"
        # Flags for audio support
        # "-s USE_SDL=2"
        # "-s USE_SDL_MIXER=2"
    )
    string(JOIN " " EMSCRIPTEN_LINK_FLAGS_STR ${EMSCRIPTEN_LINK_FLAGS})
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${EMSCRIPTEN_LINK_FLAGS_STR}")

    # Unset output file extensions
    unset(CMAKE_EXECUTABLE_SUFFIX)

    FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    enable_testing()

    add_executable(InputComponentTest tests/input_component_test.cpp)
    add_test(NAME InputComponentTest
            COMMAND InputComponentTest
    )

    target_link_libraries(InputComponentTest PRIVATE ZameEngine
                                                    GTest::gtest_main
    )
endif()
