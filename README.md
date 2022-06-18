License:

Pixel art: https://pixelfrog-assets.itch.io/pixel-adventure-1


Commented out a section in
SDL_audiocvt.c
That was causing build errors inside of windows, did not reach out currently.

When adding fmod:
if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    if (${CMAKE_SIZEOF_VOID_P} MATCHES "8")
        target_link_libraries(Test lib1_linux64)
    else()
        target_link_libraries(Test lib1_linux32)
    endif()
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    if (${CMAKE_SIZEOF_VOID_P} MATCHES "8")
        target_link_libraries(Test lib1_win64)
    else()
        target_link_libraries(Test lib1_win32)
    endif()
# ETC
endif()
