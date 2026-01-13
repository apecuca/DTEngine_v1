#ifndef INCLUDED_GAME_H
#define INCLUDED_GAME_H
#pragma once

namespace DTEngine {class Engine;}

class Game
{
public:
    Game(DTEngine::Engine& _eng);
    ~Game() = default;

private:
    DTEngine::Engine& engine;
};

#endif