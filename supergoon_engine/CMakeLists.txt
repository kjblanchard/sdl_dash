# Needed for windows defining declspecs automatically
include(GenerateExportHeader)
# Use the most current version.
cmake_minimum_required(VERSION 3.2)
message(STATUS "Starting Supergoon Engine Cmake")

#Add all of our source files and headers to this library.
file(GLOB FILES supergoon_engine/**/*.?pp)
# Add the SDL folder as we are building it as source.
add_subdirectory(./lib/SDL2-2.0.22)
# We are creating a shared lib (or dll on windows) and add all the files that we globbed above to it for compiling
add_library(supergoon_engine SHARED ${FILES})

# Generate our EXPORT and NO_EXPORT macros in sgengine_exported.h, this is for automatically generating windows declspecs
generate_export_header(supergoon_engine EXPORT_FILE_NAME ${CMAKE_BINARY_DIR}/exports/supergoon_engine_export.h)
# Use newest cpp standard for this target
set_property(TARGET supergoon_engine PROPERTY CXX_STANDARD 20)

# Sets the module path, this is so that we can use the find sdl package below with the FindSDL2.cmake file in the location
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/)
find_package(SDL2 REQUIRED)


# Add external libraries.
add_library(fmod SHARED IMPORTED)
add_library(fmodstudio SHARED IMPORTED)
if(WIN32)
    message(STATUS "Setting up windows build information.")
# Set the filenames for the libs, this is due to the libs being built for different platforms, windows has different names.
    set_target_properties(fmod PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/fmod/lib/fmod.dll)
    set_target_properties(fmod PROPERTIES IMPORTED_IMPLIB ${CMAKE_CURRENT_SOURCE_DIR}/lib/fmod/lib/fmod_vc.lib)
    set_target_properties(fmodstudio PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/fmod/lib/fmodstudio.dll)
    set_target_properties(fmodstudio PROPERTIES IMPORTED_IMPLIB ${CMAKE_CURRENT_SOURCE_DIR}/lib/fmod/lib/fmodstudio_vc.lib)
    # We need to use the exports on windows as dlls are funky business
    target_compile_definitions(supergoon_engine PRIVATE supergoon_engine_EXPORTS)
    # Set the output of external libs to the runtime folder, due to dlls not getting the proper linking flags in other folders.
    set(EXTERNAL_LIBRARY_OUTPUT_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
    # Windows libs to copy over, they have different names
    set(COPY_LIBS fmod.dll fmodstudio.dll)
endif()

if(APPLE)
    message(STATUS "Setting Up Fmod for Mac")
    set_target_properties(fmod PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/fmod/lib/mac/libfmod.dylib)
    set_target_properties(fmodstudio PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/fmod/lib/mac/libfmodstudio.dylib)
    set(EXTERNAL_LIBRARY_OUTPUT_DIR ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
    set(COPY_LIBS libfmod.dylib libfmodstudio.dylib)
endif()


message(STATUS "Setting Compiler Options.")
if(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    message(STATUS "Setting Clang flags")
    target_compile_options(supergoon_engine PRIVATE -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-newline-eof -Wno-padded -Wno-exit-time-destructors -Wno-global-constructors -Wno-constant-conversion)
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "AppleClang")
    message(STATUS "Setting Apple Clang Flags")
    target_compile_options(supergoon_engine PRIVATE -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-newline-eof -Wno-padded -Wno-exit-time-destructors -Wno-global-constructors -Wno-constant-conversion)
endif()

message(STATUS "Adding include Directories to the project.")
target_include_directories(supergoon_engine
        PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/"
        "${CMAKE_BINARY_DIR}/exports/"
        "./lib/SDL2-2.0.22/include/"
        "./lib/fmod/include/"
        )

message(STATUS "Linking to the external libraries.")
target_link_libraries(supergoon_engine PUBLIC SDL2 fmod fmodstudio)


message(STATUS "Copying the Libraries to the output folder.")
foreach( file_i ${COPY_LIBS})
    add_custom_command(
    TARGET supergoon_engine
    POST_BUILD
    COMMAND ${CMAKE_COMMAND}
    ARGS -E copy ${CMAKE_CURRENT_SOURCE_DIR}/lib/fmod/lib/${file_i} ${EXTERNAL_LIBRARY_OUTPUT_DIR}/${file_i}
    )
endforeach( file_i )

# Add relative links for the lib folder, could not be needed.
# set_target_properties(fmod PROPERTIES LINK_FLAGS "-Wl,-rpath,./lib")
# set_target_properties(fmodstudio PROPERTIES LINK_FLAGS "-Wl,-rpath,./lib")