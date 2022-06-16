cmake_minimum_required(VERSION 3.2)
project(sdl_dash VERSION 0.0.1)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
add_subdirectory(supergoon_engine)
add_subdirectory(supergoon_dash)

# include_directories(
# "/Library/Frameworks/SDL2.framework/Headers"
# "/Library/Frameworks/SDL2_image.framework/Headers"
# )

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
