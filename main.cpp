#include <iostream>

#include "Engine.hpp"
#include "Game/Game.hpp"

int main(int, char**){
    std::cout << "Hello, from DTEngine!\n";

    DTEngine::Engine engine;
    
    try {
        Game game(engine);
        engine.Run();
    } catch (std::string err) {
        std::cout << "Err: " << err << std::endl;
    }
}
