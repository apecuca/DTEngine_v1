#ifndef DTENGINE_SPRITERENDERER_H
#define DTENGINE_SPRITERENDERER_H

#include "Component.hpp"

namespace DTEngine 
{

class SpriteRenderer : public Component
{
public:
    virtual ~SpriteRenderer();
    SpriteRenderer(GameObject& _gameObject);

private:
    void Start() override;

    void Update() override;
};

}

#endif