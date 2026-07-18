#ifndef INCLUDED_RENDERINGSYSTEM_H
#define INCLUDED_RENDERINGSYSTEM_H

#include "system/InternalSystem.hpp"

#include <DTEngine/Utils.hpp>
#include <iostream>
#include <memory>
#include <vector>

namespace DTEngine {

class Window;
class Shader;
class Sprite;
class SpriteRenderer;

class RenderingSystem : public InternalSystem
{
friend class SystemRegistry;
friend class RenderingManager;
friend class Engine;

public:
    virtual ~RenderingSystem();
    RenderingSystem();
    
    // Returns if the main window is still running
    bool IsWindowRunning() const;

    void AddRenderSource(SpriteRenderer* spr);
    void RemoveRenderSource(SpriteRenderer* spr);

    Shader& GetShader(int shaderIndex);
    int LoadShader(const std::string& vertexFile, const std::string& fragmentFile);
    void LoadInternalShader(const std::string& vertexFile, const std::string& fragmentFile, std::unique_ptr<Shader>& out);
    void LoadInternalShader(const std::string& vertexFile, const std::string& fragmentFile);
    
    Sprite& GetSprite(int spriteIndex);
    bool IsValidSpriteIndex(int spriteIndex) const;
    int LoadSprite(const std::string& file, float pixelsPerUnit);
    void LoadInternalSprite(const std::string& file, float pixelsPerUnit);

    void SetAnimationFramerate(int framerate);
    int GetAnimationFramerate() const;
    float GetFramesInTimeInterval(float time) const;
    
    bool IsPositionSolid(int x, int y, Vector2 size) const;
    
protected:
    bool Init() override;
    
private:
    bool InitAndConfigWindow();
    bool ConfigPostProcessing();
    void RenderCycle();

    enum RenderPassType { WORLD, SOLID };
    void RenderPass(unsigned int& frameBufferObject, const RenderPassType renderType);

private:
    std::unique_ptr<DTEngine::Window> window;

    std::vector<std::unique_ptr<Shader>> loadedShaders;
    std::vector<std::unique_ptr<Sprite>> loadedSprites;

    std::vector<SpriteRenderer*> renderers;

    int animationFramerate = 24;

    // Frame Buffer Object, Frame Buffer Texture, Render Buffer Object
    unsigned int worldFBO, worldFBT;
    unsigned int solidFBO, solidFBT;
    std::unique_ptr<Shader> solidPassShader;
    unsigned int screenquadVAO, screenquadVBO;
    std::unique_ptr<Shader> screenShader;
};
}

#endif