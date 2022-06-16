#include <iostream>
#include <primitives/Vector2.h>

int main(int, char**) {
    std::cout << "Hello, world!\n";
    auto key = Vector2();
    key.x = 10;
    key.y = 0;

    std::cout << key.x << std::endl;
}


