cmake_minimum_required(VERSION 4.0)
project(shader_repo)

find_package(Vulkan REQUIRED)


add_library(Shader_Engine INTERFACE)
target_include_directories(Shader_Engine INTERFACE
        "${CMAKE_CURRENT_SOURCE_DIR}/../engine/include"
)
target_link_libraries(Shader_Engine INTERFACE Vulkan::Headers)


# auto-shader discovery
message(STATUS "[shader_repo] scanning for shaders to compile...")
file(GLOB CHILDREN "${CMAKE_CURRENT_SOURCE_DIR}/*")

foreach (CHILD ${CHILDREN})
    if (IS_DIRECTORY "${CHILD}" AND EXISTS "${CHILD}/CMakeLists.txt")
        get_filename_component(PLUGIN_NAME "${CHILD}" NAME)
        message(STATUS "   + registering shader: ${PLUGIN_NAME}")

        add_subdirectory("${CHILD}")

    endif ()
endforeach ()

message(STATUS "[shader_repo] scan/compile complete.")