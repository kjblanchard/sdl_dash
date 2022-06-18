include(GenerateExportHeader)
cmake_minimum_required(VERSION 3.2)
#Random status message
message(STATUS "Starting Engine Cmake..")

#Add all of our source files and headers to this library.
file(GLOB FILES supergoon_engine/**/*.?pp)
add_subdirectory(./lib/SDL2-2.0.22)
add_library(supergoon_engine SHARED ${FILES})

# Generate our EXPORT and NO_EXPORT macros in sgengine_exported.h
generate_export_header(supergoon_engine EXPORT_FILE_NAME ${CMAKE_BINARY_DIR}/exports/supergoon_engine_export.h)


# add_library(fmod SHARED IMPORTED)
# set_target_properties(fmod PROPERTIES IMPORTED_LOCATION ./lib/fmod/lib/libfmod.dylib)
# add_library(fmodstudio SHARED IMPORTED)
# set_target_properties(fmod PROPERTIES IMPORTED_LOCATION ./lib/fmod/lib/libfmodstudio.dylib)
# set(libnames fmod fmodstudio)
# foreach(library ${libnames})
#         add_library(${library} SHARED IMPORTED)
# endforeach()

# foreach(library ${libnames})
#     set_target_properties( ${library}
#                             PROPERTIES IMPORTED_LOCATION
#                             ./lib/${library}.dylib
#                             )


#Add absolute paths to link to for development.
# foreach(library ${libnames})
#         set_target_properties( ${library}
#                                 PROPERTIES IMPORTED_LOCATION
#                                 /usr/local/lib/${library}.dylib
#                                 )
# endforeach()

#Add relative paths to link to for distribution.
# foreach(library ${libnames})
#         set_target_properties(${library} PROPERTIES LINK_FLAGS "-Wl,-rpath,./libs")
# endforeach()

#Set c++20 standard for this.
set_property(TARGET supergoon_engine PROPERTY CXX_STANDARD 20)


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/)
find_package(SDL2 REQUIRED)

# And now, we tell CMake that libdependency should be linked to our library
message(STATUS "Setting Up Fmod for Mac")
add_library(fmod SHARED IMPORTED)
add_library(fmodstudio SHARED IMPORTED)
set_target_properties(fmod PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/fmod/lib/mac/libfmod.dylib)
set_target_properties(fmodstudio PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/fmod/lib/mac/libfmodstudio.dylib)



if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    message(STATUS "Setting G++ flags")
    # G++
    # target_compile_options(roukavici PRIVATE -Wall -Wextra)
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
    message(STATUS "Setting MSVC flags")
    # MSVC
    target_compile_options(supergoon_engine PRIVATE /EHsc /W2 /c)
    # Set the DLLEXPORT variable to export symbols
    # target_compile_definitions(roukavici PRIVATE WIN_EXPORT)
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    message(STATUS "Setting Clang flags")
    # Activate all clang warnings except those that don't really affect much
    # target_compile_options(roukavici PRIVATE -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-newline-eof -Wno-padded -Wno-exit-time-destructors -Wno-global-constructors -Wno-constant-conversion)
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "AppleClang")
    message(STATUS "Setting Apple Clang Flags")
    target_compile_options(supergoon_engine PRIVATE -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-newline-eof -Wno-padded -Wno-exit-time-destructors -Wno-global-constructors -Wno-constant-conversion)
    add_custom_command(
            TARGET supergoon_engine POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_CURRENT_SOURCE_DIR}/lib/fmod/lib/mac/libfmod.dylib
            ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/libfmod.dylib)
    add_custom_command(
            TARGET supergoon_engine POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_CURRENT_SOURCE_DIR}/lib/fmod/lib/mac/libfmodstudio.dylib
            ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/libfmodstudio.dylib)
    # Add relative paths to link to for distribution.
    set_target_properties(fmod PROPERTIES LINK_FLAGS "-Wl,-rpath,./lib")
    set_target_properties(fmodstudio PROPERTIES LINK_FLAGS "-Wl,-rpath,./lib")
else()
    message(STATUS ${CMAKE_CXX_COMPILER_ID})
    message(STATUS "How did we get here")
    target_compile_options(supergoon_engine PRIVATE /EHsc /W2 /c)
    target_compile_definitions(supergoon_engine PRIVATE supergoon_engine_EXPORTS)

endif()
# target_link_libraries(supergoon_engine PUBLIC SDL2 fmod fmodstudio)
#Include directories for the sgengine.
target_include_directories(supergoon_engine
        PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/"
        "${CMAKE_BINARY_DIR}/exports/"
        "./lib/SDL2-2.0.22/include/"
        "./lib/fmod/include/"
        )
target_link_libraries(supergoon_engine PUBLIC SDL2 fmod fmodstudio)