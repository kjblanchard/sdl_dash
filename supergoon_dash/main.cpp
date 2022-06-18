#include <iostream>
#include <supergoon_engine/test.h>


int main(int, char**) {
    std::cout << "Hello, world!\n";
    auto vec2 = Vector2();
    auto num = vec2.Help();
    std::cout << num << std::endl;
	while(true)
	{
		std::cout << "num" << std::endl;
		SDL_Delay(10);
		Sound::Update();
	}

}


