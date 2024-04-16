cmake_minimum_required(VERSION 3.26)
project(Trees VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)

add_library(Trees INTERFACE)
target_include_directories(Trees INTERFACE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)

set_target_properties(Trees PROPERTIES PUBLIC_HEADER "include/AVL.h")
set_target_properties(Trees PROPERTIES PUBLIC_HEADER "include/RB.h")
set_target_properties(Trees PROPERTIES PUBLIC_HEADER "include/Treap.h")

install(TARGETS Trees
        EXPORT TreesExport
        PUBLIC_HEADER DESTINATION include
        INCLUDES DESTINATION include)

include(CMakePackageConfigHelpers)

configure_package_config_file(
        "${PROJECT_SOURCE_DIR}/data/TreesConfig.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/TreesConfig.cmake"
        INSTALL_DESTINATION cmake)

write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/TreesConfigVersion.cmake
        COMPATIBILITY AnyNewerVersion)

install(EXPORT TreesExport
        DESTINATION cmake)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/TreesConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/TreesConfigVersion.cmake"
        DESTINATION cmake)

install(FILES "${PROJECT_SOURCE_DIR}/data/config.sh"
        DESTINATION ${CMAKE_INSTALL_PREFIX})
