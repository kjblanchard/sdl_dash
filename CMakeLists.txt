cmake_minimum_required(VERSION 3.2)
project(sdl_dash
        VERSION 0.1.0
        LANGUAGES CXX)
# This is needed for building sdl_image
enable_language(OBJC)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )
include(CPack)
add_subdirectory(supergoon_engine)
add_subdirectory(supergoon_dash)
# Build OSX universal
set(CMAKE_OSX_ARCHITECTURES arm64 x86_64)