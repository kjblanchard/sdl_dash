# Needed for windows defining declspecs automatically
include(GenerateExportHeader)
# Used for linux to find the packages installed.
include(FindPkgConfig)
# Use a modern CMAKE version.
cmake_minimum_required(VERSION 3.2)
message(STATUS "Starting Supergoon Engine Cmake")
#Add all of our source files to this library for building
file(GLOB FILES ./src/supergoon_engine/**/*.cpp)
# We use the build dir for projects we will build in subdirectories
set(EXTERNAL_BUILD_DIR ./external/build)
add_subdirectory(${EXTERNAL_BUILD_DIR}/lua)
add_subdirectory(${EXTERNAL_BUILD_DIR}/jsoncpp-1.8.0)
# Add the SDL folders as we are building it as source
add_subdirectory(${EXTERNAL_BUILD_DIR}/SDL2-2.0.22)
add_subdirectory(${EXTERNAL_BUILD_DIR}/SDL_image)
# We are creating a shared lib (or dll on windows) and add all the files that we globbed above to it for compiling
add_library(supergoon_engine SHARED ${FILES})
# Use newest cpp standard for this target
set_property(TARGET supergoon_engine PROPERTY CXX_STANDARD 20)
# Generate our EXPORT and NO_EXPORT macros in sgengine_exported.h, this is for automatically generating windows declspecs
generate_export_header(supergoon_engine EXPORT_FILE_NAME ${CMAKE_BINARY_DIR}/exports/supergoon_engine_export.h)
# Sets the module path, this is so that we can use the find sdl package below with the FindSDL2.cmake file in the location
# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/)
# Add external libraries, these don't use cmake at all so we have a longer process and need to define them
add_library(fmod SHARED IMPORTED)
add_library(fmodstudio SHARED IMPORTED)
# Define where our compiled FMOD binary files are to be copied from.
set(EXTERNAL_BIN_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/external/bin)
set(EXTERNAL_LIBRARY_OUTPUT_DIR ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
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
    set(COPY_LIBS fmod.dll fmodstudio.dll libjpeg-9.dll libpng16-16.dll zlib1.dll)
elseif(APPLE)
    message(STATUS "Setting Up Fmod for Mac")
    set_target_properties(fmod PROPERTIES IMPORTED_LOCATION ${EXTERNAL_BIN_FOLDER}/libfmod.dylib)
    set_target_properties(fmodstudio PROPERTIES IMPORTED_LOCATION ${EXTERNAL_BIN_FOLDER}/libfmodstudio.dylib)
    set(COPY_LIBS libfmod.dylib libfmodstudio.dylib)
elseif(UNIX)
    message(STATUS "Setting Up Linux, these are installed via apt with the bootstrap.sh, and is found automatically due to issues building from source.")
    # pkg_check_modules(SDL2_image REQUIRED SDL2_image) Used this when not building from source
    set_target_properties(fmod PROPERTIES IMPORTED_LOCATION ${EXTERNAL_BIN_FOLDER}/libfmod.so)
    set_target_properties(fmodstudio PROPERTIES IMPORTED_LOCATION ${EXTERNAL_BIN_FOLDER}/libfmodstudio.so)
    set(COPY_LIBS libfmod.so libfmodstudio.so libfmodstudio.so.13 libfmodstudio.so.13.7)
endif()


message(STATUS "Setting Compiler Options. We want to see as many errors as possible.")
if(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    # target_compile_options(supergoon_engine PRIVATE -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-newline-eof -Wno-padded -Wno-exit-time-destructors -Wno-global-constructors -Wno-constant-conversion)
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "AppleClang")
    # target_compile_options(supergoon_engine PRIVATE -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-newline-eof -Wno-padded -Wno-exit-time-destructors -Wno-global-constructors -Wno-constant-conversion)
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
    # target_compile_options(supergoon_engine PRIVATE /EHsc /W2 /c)
endif()

message(STATUS "Adding include Directories from build submodules, and from header only includes to the project.")
target_include_directories(supergoon_engine
        SYSTEM
        PUBLIC
        ${EXTERNAL_BUILD_DIR}/SDL2-2.0.22/include/
        ${EXTERNAL_BUILD_DIR}/SDL_image/
        ${EXTERNAL_BUILD_DIR}/lua/lua-5.4.4/include/
        ${EXTERNAL_BUILD_DIR}/jsoncpp-1.8.0/include/
        ./external/include/
        )
target_include_directories(supergoon_engine
        PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/src/"
        # This is needed for the declspec exports file.
        "${CMAKE_BINARY_DIR}/exports/"
        )

message(STATUS "Linking to the external libraries.")
target_link_libraries(supergoon_engine
                        PUBLIC
                        PRIVATE SDL2 SDL2main fmod fmodstudio SDL2_image lua_shared jsoncpp_lib
                        INTERFACE )

message(STATUS "Copying the Libraries to the output folder.  We do this for FMOD since we aren't building from source.")
foreach( file_i ${COPY_LIBS})
    add_custom_command(
    TARGET supergoon_engine
    POST_BUILD
    COMMAND ${CMAKE_COMMAND}
    ARGS -E copy ${CMAKE_CURRENT_SOURCE_DIR}/external/bin/${file_i} ${EXTERNAL_LIBRARY_OUTPUT_DIR}/${file_i}
    )
endforeach( file_i )