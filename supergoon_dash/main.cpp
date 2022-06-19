#include <iostream>
#include <supergoon_engine/test.h>


int main(int, char**) {
    std::cout << "Hello, world!\n";
    auto vec2 = Vector2();
    auto num = vec2.Help();
    std::cout << num << std::endl;
	bool sound_playing = false;
	std::cout << "About to start the musif if you have it enabled, which is : " << sound_playing << std::endl;
	while(sound_playing)
	{
		Sound::Setup();
		SDL_Delay(10);
		Sound::Update();
	}

}


