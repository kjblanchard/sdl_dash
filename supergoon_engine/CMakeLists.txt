# Needed for windows defining declspecs automatically
include(GenerateExportHeader)
# Used for linux.
include(FindPkgConfig)
# Use the most current version.
cmake_minimum_required(VERSION 3.2)
message(STATUS "Starting Supergoon Engine Cmake")

#Add all of our source files and headers to this library.
file(GLOB FILES supergoon_engine/**/*.?pp)
# Add the SDL folder as we are building it as source.
if(APPLE OR WIN32)
    add_subdirectory(./external/SDL2-2.0.22)
endif()
# We are creating a shared lib (or dll on windows) and add all the files that we globbed above to it for compiling
add_library(supergoon_engine SHARED ${FILES})

# Generate our EXPORT and NO_EXPORT macros in sgengine_exported.h, this is for automatically generating windows declspecs
generate_export_header(supergoon_engine EXPORT_FILE_NAME ${CMAKE_BINARY_DIR}/exports/supergoon_engine_export.h)
# Use newest cpp standard for this target
set_property(TARGET supergoon_engine PROPERTY CXX_STANDARD 20)

# Sets the module path, this is so that we can use the find sdl package below with the FindSDL2.cmake file in the location
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/)
# We are building this from source
find_package(SDL2 REQUIRED)

# Add external libraries, these don't use cmake at all so we have a longer process.
add_library(fmod SHARED IMPORTED)
add_library(fmodstudio SHARED IMPORTED)
# Define where our files are to be copied from.
set(EXTERNAL_BIN_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/external/bin)
if(WIN32)
    message(STATUS "Setting up windows build information.")
# Set the filenames for the libs, this is due to the libs being built for different platforms, windows has different names.
    set_target_properties(fmod PROPERTIES IMPORTED_LOCATION ${EXTERNAL_BIN_FOLDER}/fmod.dll)
    set_target_properties(fmod PROPERTIES IMPORTED_IMPLIB ${EXTERNAL_BIN_FOLDER}/fmod_vc.lib)
    set_target_properties(fmodstudio PROPERTIES IMPORTED_LOCATION ${EXTERNAL_BIN_FOLDER}/fmodstudio.dll)
    set_target_properties(fmodstudio PROPERTIES IMPORTED_IMPLIB ${EXTERNAL_BIN_FOLDER}/fmodstudio_vc.lib)
    add_library(SDL2_image::SDL2_image SHARED IMPORTED)
    set_target_properties(SDL2_image::SDL2_image PROPERTIES IMPORTED_LOCATION ${EXTERNAL_BIN_FOLDER}/SDL2_image.dll)
    set_target_properties(SDL2_image::SDL2_image PROPERTIES IMPORTED_IMPLIB ${EXTERNAL_BIN_FOLDER}/SDL2_image.lib)
    add_library(SDL2_ttf::SDL2_ttf SHARED IMPORTED)
    set_target_properties(SDL2_ttf::SDL2_ttf PROPERTIES IMPORTED_LOCATION ${EXTERNAL_BIN_FOLDER}/SDL2_ttf.dll)
    set_target_properties(SDL2_ttf::SDL2_ttf PROPERTIES IMPORTED_IMPLIB ${EXTERNAL_BIN_FOLDER}/SDL2_ttf.lib)
    # We need to use the exports on windows as dlls are funky business
    target_compile_definitions(supergoon_engine PRIVATE supergoon_engine_EXPORTS)
    # Set the output of external libs to the runtime folder, due to dlls not getting the proper linking flags in other folders.
    set(EXTERNAL_LIBRARY_OUTPUT_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug)
    # Windows libs to copy over, they have different names
    set(COPY_LIBS fmod.dll fmodstudio.dll SDL2_image.dll SDL2_ttf.dll libjpeg-9.dll libpng16-16.dll zlib1.dll)
elseif(APPLE)
    message(STATUS "Setting Up Fmod for Mac")
    # Find the SDL2_image package in the frameworks folder.
    find_package(SDL2_image CONFIG REQUIRED)
    find_package(SDL2_ttf CONFIG REQUIRED)
    set_target_properties(fmod PROPERTIES IMPORTED_LOCATION ${EXTERNAL_BIN_FOLDER}/libfmod.dylib)
    set_target_properties(fmodstudio PROPERTIES IMPORTED_LOCATION ${EXTERNAL_BIN_FOLDER}/libfmodstudio.dylib)
    set(EXTERNAL_LIBRARY_OUTPUT_DIR ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
    set(COPY_LIBS libfmod.dylib libfmodstudio.dylib)
elseif(UNIX)
    message(STATUS "Setting Up Linux")
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(SDL2_image REQUIRED SDL2_image)
    pkg_check_modules(SDL2_ttf REQUIRED SDL2_ttf)
    set_target_properties(fmod PROPERTIES IMPORTED_LOCATION ${EXTERNAL_BIN_FOLDER}/libfmod.so)
    set_target_properties(fmodstudio PROPERTIES IMPORTED_LOCATION ${EXTERNAL_BIN_FOLDER}/libfmodstudio.so)
    set(EXTERNAL_LIBRARY_OUTPUT_DIR ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
    set(COPY_LIBS libfmod.so libfmodstudio.so libfmodstudio.so.13 libfmodstudio.so.13.7)
endif()


message(STATUS "Setting Compiler Options.")
if(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    message(STATUS "Setting Clang flags")
    target_compile_options(supergoon_engine PRIVATE -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-newline-eof -Wno-padded -Wno-exit-time-destructors -Wno-global-constructors -Wno-constant-conversion)
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "AppleClang")
    message(STATUS "Setting Apple Clang Flags")
    # target_compile_options(supergoon_engine PRIVATE -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-newline-eof -Wno-padded -Wno-exit-time-destructors -Wno-global-constructors -Wno-constant-conversion)
endif()

message(STATUS "Adding include Directories to the project.")
target_include_directories(supergoon_engine
        PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/"
        "${CMAKE_BINARY_DIR}/exports/"
        "./external/SDL2-2.0.22/include/"
        "./external/include/"
        )

message(STATUS "Linking to the external libraries.")
# We are compiling from source for apple/win32 (due to m1 mac on RC build currently.)
if(APPLE OR WIN32)
    target_link_libraries(supergoon_engine PUBLIC SDL2::SDL2 SDL2::SDL2main fmod fmodstudio SDL2_image::SDL2_image SDL2_ttf::SDL2_ttf )
else()
    target_link_libraries(supergoon_engine PUBLIC SDL2 SDL2main fmod fmodstudio SDL2_image SDL2_ttf )
endif()


message(STATUS "Copying the Libraries to the output folder.")


foreach( file_i ${COPY_LIBS})
    add_custom_command(
    TARGET supergoon_engine
    POST_BUILD
    COMMAND ${CMAKE_COMMAND}
    ARGS -E copy ${CMAKE_CURRENT_SOURCE_DIR}/external/bin/${file_i} ${EXTERNAL_LIBRARY_OUTPUT_DIR}/${file_i}
    )
endforeach( file_i )

# Add relative links for the lib folder, could not be needed.
# set_target_properties(fmod PROPERTIES LINK_FLAGS "-Wl,-rpath,./lib")
# set_target_properties(fmodstudio PROPERTIES LINK_FLAGS "-Wl,-rpath,./lib")