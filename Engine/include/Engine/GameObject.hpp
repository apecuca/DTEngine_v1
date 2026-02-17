#ifndef INCLUDED_GAMEOBJECT_H
#define INCLUDED_GAMEOBJECT_H

#include "Entity.hpp"

namespace DTEngine
{

class GameObject final : public Entity
{
public:
    ~GameObject();
    GameObject();

};

}

#endif