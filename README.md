# Supergoon Dash

A C++ cross platform application that is "runner" game, where you can control your speed and jump height.  Goal is to learn more about cross compiling in C++, lean CMake a bit better, and get a little better with C++ (only using vscode and cmake for everything)

**[Trello Board](https://trello.com/b/mirFjXRE/geometry-dash-board)**

Currently Compiling on Windows(32bit), Mac (apple silicon/arm64), and Ubuntu linux(64bit)



## Components

- **SDL** - Used for low level handling of windows, timers, events, and input.
- **SDL_Image** - Used for loading png/jpeg
- **SDL_TTF** - Used for loading true type fonts.
- **CMake** - Build system
- **FMOD** - Low level handling of sound
- **Tiled** - Used for creating the maps and outputting data for it
- **[jsoncpp](https://github.com/open-source-parsers/jsoncpp)** - Used for low level handling of json, so that we can load it into lua
- **[Lua](https://www.lua.org/license.html)** - Data tables currently.
- **[sol2](https://github.com/ThePhD/sol2)** - Wrapper around the lua C api
## License

All of the licenses that I'm using will be listed here.

- [jsoncpp](https://github.com/open-source-parsers/jsoncpp) - MIT
- [sol2](https://github.com/ThePhD/sol2) - MIT
- [Lua](https://www.lua.org/license.html) - MIT
- [Pixel art](https://pixelfrog-assets.itch.io/pixel-adventure-1) - Creative Commons License
- FMOD - Indie License

- [Trampoline Sound](https://freesound.org/people/Breviceps/sounds/493161/) - Creative Commons License
- [Jump Sound](https://freesound.org/people/se2001/sounds/528568/) - Creative Commons License
- [Footsteps](https://freesound.org/people/EVRetro/sounds/501102/) - Creative Commons License

## Authors

- [@Kevin Blanchard](https://www.github.com/kjblanchard)


