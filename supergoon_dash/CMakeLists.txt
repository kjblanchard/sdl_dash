#Add all of our source files and headers to this library.
file(GLOB FILES "${CMAKE_SOURCE_DIR}/**/*.?pp")
message(STATUS ${FILES})
add_executable(main ${FILES})
set_property(TARGET main PROPERTY CXX_STANDARD 20)
target_include_directories(main
        PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/"
        )
target_link_libraries(main PUBLIC supergoon_engine)
#For linux/macos - Link to the current folders libs
set_target_properties(main PROPERTIES LINK_FLAGS "-Wl,-rpath,./libs")
# add_custom_command(
#         TARGET main POST_BUILD
#         COMMAND ${CMAKE_COMMAND} -E copy
#                 ${CMAKE_SOURCE_DIR}/geometrydash/sfx/Master.bank
#                 ${CMAKE_CURRENT_BINARY_DIR}/sfx/Master.bank)
# add_custom_command(
#         TARGET main POST_BUILD
#         COMMAND ${CMAKE_COMMAND} -E copy
#                 ${CMAKE_SOURCE_DIR}/geometrydash/sfx/Master.strings.bank
#                 ${CMAKE_CURRENT_BINARY_DIR}/sfx/Master.strings.bank)