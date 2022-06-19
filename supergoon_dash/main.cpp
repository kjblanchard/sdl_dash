#include <iostream>
#include <supergoon_engine/engine/world.hpp>


int main(int, char**) {
    std::cout << "Hello, world!\n";
	auto world = World();
	world.Run();

}


