#Add all of our source files and headers to this library.
file(GLOB FILES supergoon_dash/**/*.?pp)
file(GLOB MAIN ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
add_executable(supergoon_dash ${FILES} ${MAIN})
set_property(TARGET supergoon_dash PROPERTY CXX_STANDARD 20)
target_include_directories(supergoon_dash
        PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/"
        "./supergoon_engine"
        "${CMAKE_BINARY_DIR}/exports/"
        )
target_link_libraries(supergoon_dash PUBLIC supergoon_engine)

# Put win32 assets indo the Debug place, cause MSVC sucks
if(WIN32)
    set(ASSET_OUTPUT_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/assets)
else()
    set(ASSET_OUTPUT_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets)
endif()
# Copy assets into the built folder.
add_custom_command(
        TARGET supergoon_dash POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_CURRENT_SOURCE_DIR}/assets
                ${ASSET_OUTPUT_DIR}
        )

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    message(STATUS "Setting G++ flags")
    target_compile_options(supergoon_dash PRIVATE -Wall -Wextra)
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
    message(STATUS "Setting MSVC flags")
    target_compile_options(supergoon_dash PRIVATE /EHsc /W2 /c)
    # Set the DLLEXPORT variable to export symbols
    # target_compile_definitions(supergoon_dash PRIVATE WIN_EXPORT)
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    message(STATUS "Setting Clang flags")
    # Activate all clang warnings except those that don't really affect much
    target_compile_options(supergoon_dash PRIVATE -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-newline-eof -Wno-padded -Wno-exit-time-destructors -Wno-global-constructors -Wno-constant-conversion)
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "AppleClang")
    message(STATUS "Setting Apple Clang Flags")
    target_compile_options(supergoon_dash PRIVATE -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-newline-eof -Wno-padded -Wno-exit-time-destructors -Wno-global-constructors -Wno-constant-conversion)
else()
    message(STATUS ${CMAKE_CXX_COMPILER_ID})
    target_compile_options(supergoon_dash PRIVATE /EHsc /W2 /c)

endif()