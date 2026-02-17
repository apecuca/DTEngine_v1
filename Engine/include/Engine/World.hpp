#ifndef INCLUDED_WORLD_H
#define INCLUDED_WORLD_H

#include <vector>
#include <memory>

namespace DTEngine
{
    class GameObject;

class World final
{
public:
    ~World();
    World();

private:
    std::vector<std::unique_ptr<GameObject>> gameObjects;

};

}

#endif