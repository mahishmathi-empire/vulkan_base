cmake_minimum_required(VERSION 3.15.0)
project(daagudumoothalu_test VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

# add path to CMAKE_PREFIX_PATH
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR}/../build/)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR}/../build/)

set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# link directories
link_directories(${CMAKE_INSTALL_PREFIX}/lib/)

# find dependencies
find_package(daagudumoothalu REQUIRED)

list(APPEND local_INCLUDE_DIRS ${CMAKE_INSTALL_PREFIX}/include/)

# include directories
include_directories(
  ${daagudumoothalu_INCLUDE_DIRS}
  ${local_INCLUDE_DIRS}
)

# add all cpp files in the folder
file(GLOB SOURCES "*.cpp")

# make executables
foreach(source ${SOURCES})
  get_filename_component(name ${source} NAME_WE)
  add_executable(${name} ${source})
  target_link_libraries(${name}
    daagudumoothalu::glf_vulkan
    daagudumoothalu::math
  )

  # set runtime path
  set_target_properties(${name} PROPERTIES
   BUILD_WITH_INSTALL_RPATH TRUE
   INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
  install(TARGETS ${name} RUNTIME DESTINATION bin)
endforeach(source ${SOURCES})

