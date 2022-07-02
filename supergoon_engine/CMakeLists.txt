# Needed for windows defining declspecs automatically
include(GenerateExportHeader)
# Used for linux.
include(FindPkgConfig)
# Use the most current version.
cmake_minimum_required(VERSION 3.2)
message(STATUS "Starting Supergoon Engine Cmake")

#Add all of our source files and headers to this library.
file(GLOB FILES supergoon_engine/**/*.?pp)
#Add all of our tinyxml files and headers to this library.
file(GLOB TINYXML external/tinyxml/src/*)

# Add the SDL folders as we are building it as source, had issues building from source in linux currently.
if(APPLE OR WIN32)
    add_subdirectory(./external/SDL2-2.0.22)
    add_subdirectory(./external/SDL_image)
endif()
# We are creating a shared lib (or dll on windows) and add all the files that we globbed above to it for compiling
add_library(supergoon_engine SHARED ${FILES} ${TINYXML})

# Generate our EXPORT and NO_EXPORT macros in sgengine_exported.h, this is for automatically generating windows declspecs
generate_export_header(supergoon_engine EXPORT_FILE_NAME ${CMAKE_BINARY_DIR}/exports/supergoon_engine_export.h)
# Use newest cpp standard for this target
set_property(TARGET supergoon_engine PROPERTY CXX_STANDARD 20)

# Sets the module path, this is so that we can use the find sdl package below with the FindSDL2.cmake file in the location
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/)

# Add external libraries, these don't use cmake at all so we have a longer process.
add_library(fmod SHARED IMPORTED)
add_library(fmodstudio SHARED IMPORTED)

# Define where our files are to be copied from.
set(EXTERNAL_BIN_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/external/bin)
if(WIN32)
    message(STATUS "Setting up windows build information.")
    set_target_properties(fmod PROPERTIES IMPORTED_LOCATION ${EXTERNAL_BIN_FOLDER}/fmod.dll)
    set_target_properties(fmod PROPERTIES IMPORTED_IMPLIB ${EXTERNAL_BIN_FOLDER}/fmod_vc.lib)
    set_target_properties(fmodstudio PROPERTIES IMPORTED_LOCATION ${EXTERNAL_BIN_FOLDER}/fmodstudio.dll)
    set_target_properties(fmodstudio PROPERTIES IMPORTED_IMPLIB ${EXTERNAL_BIN_FOLDER}/fmodstudio_vc.lib)
    # We need to use the exports on windows as dlls are funky business
    target_compile_definitions(supergoon_engine PRIVATE supergoon_engine_EXPORTS)
    # Set the output of external libs to the runtime folder, due to dlls not getting the proper linking flags in other folders.
    set(EXTERNAL_LIBRARY_OUTPUT_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug)
    # Windows libs to copy over, they have different names than others.
    set(COPY_LIBS fmod.dll fmodstudio.dll SDL2_image.dll SDL2_ttf.dll libjpeg-9.dll libpng16-16.dll zlib1.dll)
elseif(APPLE)
    message(STATUS "Setting Up Fmod for Mac")
    # Find the SDL2_ttf package in the frameworks folder since we don't build it from source.
    set_target_properties(fmod PROPERTIES IMPORTED_LOCATION ${EXTERNAL_BIN_FOLDER}/libfmod.dylib)
    set_target_properties(fmodstudio PROPERTIES IMPORTED_LOCATION ${EXTERNAL_BIN_FOLDER}/libfmodstudio.dylib)
    set(EXTERNAL_LIBRARY_OUTPUT_DIR ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
    set(COPY_LIBS libfmod.dylib libfmodstudio.dylib)
elseif(UNIX)
    message(STATUS "Setting Up Linux, these are installed via apt with the bootstrap.sh, and is found automatically due to issues building from source.")
    find_package(SDL2 REQUIRED)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(SDL2_image REQUIRED SDL2_image)
    set_target_properties(fmod PROPERTIES IMPORTED_LOCATION ${EXTERNAL_BIN_FOLDER}/libfmod.so)
    set_target_properties(fmodstudio PROPERTIES IMPORTED_LOCATION ${EXTERNAL_BIN_FOLDER}/libfmodstudio.so)
    set(EXTERNAL_LIBRARY_OUTPUT_DIR ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
    set(COPY_LIBS libfmod.so libfmodstudio.so libfmodstudio.so.13 libfmodstudio.so.13.7)
endif()


message(STATUS "Setting Compiler Options. We want to see as many errors as possible.")
if(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    target_compile_options(supergoon_engine PRIVATE -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-newline-eof -Wno-padded -Wno-exit-time-destructors -Wno-global-constructors -Wno-constant-conversion)
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "AppleClang")
    target_compile_options(supergoon_engine PRIVATE -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-newline-eof -Wno-padded -Wno-exit-time-destructors -Wno-global-constructors -Wno-constant-conversion)
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
    target_compile_options(supergoon_engine PRIVATE /EHsc /W2 /c)
endif()

message(STATUS "Adding include Directories to the project.")
target_include_directories(supergoon_engine
        SYSTEM
        PUBLIC
        # built sdl2 includes
        "./external/SDL2-2.0.22/include/"
        # built sdl_image
        "./external/SDL_image/"
        # This is where our fmod includes live.
        "./external/include/"
        )
target_include_directories(supergoon_engine
        PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/"
        # This is needed for the exports file.
        "${CMAKE_BINARY_DIR}/exports/"
        )

message(STATUS "Linking to the external libraries.")
target_link_libraries(supergoon_engine PUBLIC SDL2 fmod fmodstudio SDL2_image)

message(STATUS "Copying the Libraries to the output folder.  We do this for FMOD since we aren't building from source.")
foreach( file_i ${COPY_LIBS})
    add_custom_command(
    TARGET supergoon_engine
    POST_BUILD
    COMMAND ${CMAKE_COMMAND}
    ARGS -E copy ${CMAKE_CURRENT_SOURCE_DIR}/external/bin/${file_i} ${EXTERNAL_LIBRARY_OUTPUT_DIR}/${file_i}
    )
endforeach( file_i )