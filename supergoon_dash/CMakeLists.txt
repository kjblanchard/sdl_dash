#Add all of our source files and headers to this library.
file(GLOB FILES "${CMAKE_SOURCE_DIR}/**/*.?pp")
message(STATUS ${FILES})
add_executable(supergoon_dash ${FILES})
set_property(TARGET supergoon_dash PROPERTY CXX_STANDARD 20)
target_include_directories(supergoon_dash
        PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/"
        )
target_link_libraries(supergoon_dash PUBLIC supergoon_engine)

add_custom_command(
        TARGET supergoon_dash POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_CURRENT_SOURCE_DIR}/assets
                ${CMAKE_CURRENT_BINARY_DIR}/assets)

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    message(STATUS "Setting G++ flags")
    # G++
    # target_compile_options(roukavici PRIVATE -Wall -Wextra)
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
    message(STATUS "Setting MSVC flags")
    # MSVC
    target_compile_options(supergoon_dash PRIVATE /EHsc /W2 /c)
    # Set the DLLEXPORT variable to export symbols
    # target_compile_definitions(roukavici PRIVATE WIN_EXPORT)
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    message(STATUS "Setting Clang flags")
    # Activate all clang warnings except those that don't really affect much
    # target_compile_options(roukavici PRIVATE -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-newline-eof -Wno-padded -Wno-exit-time-destructors -Wno-global-constructors -Wno-constant-conversion)
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "AppleClang")
    message(STATUS "Setting Apple Clang Flags")
#For linux/macos - Link to the current folders libs
# set_target_properties(main PROPERTIES LINK_FLAGS "-Wl,-rpath,./libs")
    target_compile_options(supergoon_dash PRIVATE -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-newline-eof -Wno-padded -Wno-exit-time-destructors -Wno-global-constructors -Wno-constant-conversion)
else()
    message(STATUS ${CMAKE_CXX_COMPILER_ID})
    message(STATUS "How did we get here")
    target_compile_options(supergoon_dash PRIVATE /EHsc /W2 /c)

endif()