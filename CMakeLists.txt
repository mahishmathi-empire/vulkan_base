cmake_minimum_required(VERSION 3.15)
project(daagudumoothalu VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# cmake flags
if(CMAKE_BUILD_TYPE MATCHES Debug)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DNDEBUG")
endif()

set(CMAKE_INSTALL_DIR share/${PROJECT_NAME}/cmake)

find_package(Vulkan REQUIRED)
find_package(glfw3 3.3 REQUIRED)

include_directories(
  ${Vulkan_INCLUDE_DIRS}
  ${CMAKE_SOURCE_DIR}/include
)

# add libraries
add_library(glf_vulkan
  src/glfwindow.cpp
  src/vulkan.cpp
)

target_link_libraries(glf_vulkan
  ${Vulkan_LIBRARIES}
  glfw
)

add_library(math
  src/math.cpp
)
target_link_libraries(math

)

# Additional configurations (e.g., for shaders)
set(SHADER_SOURCE_DIR ${CMAKE_SOURCE_DIR}/shaders)
file(GLOB_RECURSE GLSL_SOURCE_FILES
  "${SHADER_SOURCE_DIR}/*.frag"
  "${SHADER_SOURCE_DIR}/*.vert"
)

# Function to compile shaders
function(compile_shader SHADER)
  get_filename_component(FILE_NAME ${SHADER} NAME)
  set(SPIRV "${CMAKE_BINARY_DIR}/shaders/${FILE_NAME}.spv")
  add_custom_command(
    OUTPUT ${SPIRV}
    COMMAND ${Vulkan_GLSLANG_VALIDATOR_EXECUTABLE} -V ${SHADER} -o ${SPIRV}
    DEPENDS ${SHADER}
    COMMENT "Compiling shader ${SHADER}"
  )
  list(APPEND SPIRV_BINARY_FILES ${SPIRV})
endfunction()

# Compile shaders
foreach(GLSL ${GLSL_SOURCE_FILES})
  compile_shader(${GLSL})
endforeach()

add_custom_target(
    Shaders ALL
    DEPENDS ${SPIRV_BINARY_FILES}
)

add_dependencies(glf_vulkan Shaders)

# install
install(
  TARGETS glf_vulkan math
  EXPORT ${PROJECT_NAME}-targets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
)

# Generate the CMake config file
include(CMakePackageConfigHelpers)
# Generate the version file accompanying the project's config file
configure_package_config_file(${PROJECT_NAME}-config.cmake.in
                              ${PROJECT_NAME}-config.cmake
                              INSTALL_DESTINATION ${CMAKE_INSTALL_DIR})

write_basic_package_version_file(${PROJECT_NAME}-config-version.cmake
                                 VERSION ${PROJECT_VERSION}
                                 COMPATIBILITY AnyNewerVersion)

# Install the config and configversion
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake
        DESTINATION ${CMAKE_INSTALL_DIR})

# Make the targets accessible from this packages's build tree
export(
  EXPORT ${PROJECT_NAME}-targets
  NAMESPACE ${PROJECT_NAME}::
  FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-targets.cmake"
)

# Make the targets accessible from this packages's install tree
install(
  EXPORT ${PROJECT_NAME}-targets
  FILE ${PROJECT_NAME}-targets.cmake
  NAMESPACE ${PROJECT_NAME}::
  DESTINATION ${CMAKE_INSTALL_DIR})

# Install all public header files
install(DIRECTORY include/
  DESTINATION include
  FILES_MATCHING PATTERN "*.hpp"
)

# Install shaders
if(EXISTS shaders/)
  install(DIRECTORY shaders/ 
    DESTINATION shaders
  )
endif()

install(DIRECTORY assets/ 
  DESTINATION assets
)

# tests
option(ENABLE_TESTS "Enable tests" ON)
if(${ENABLE_TESTS})
  add_subdirectory(test)
endif()