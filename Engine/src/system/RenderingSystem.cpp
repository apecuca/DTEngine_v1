#include "system/RenderingSystem.hpp"

#include <DTEngine/Window.hpp>
#include <DTEngine/SpriteRenderer.hpp>
#include <DTEngine/Sprite.hpp>
#include <DTEngine/Shader.hpp>
#include <DTEngine/Utils.hpp>
#include <DTEngine/GameObject.hpp>
#include "system/SystemRegistry.hpp"
#include "system/PathSystem.hpp"

#include <glad/glad.h>
#include "GLFW/glfw3.h"

#include <algorithm>
#include <stdexcept>

using namespace DTEngine;

RenderingSystem::~RenderingSystem()
{
    //
}

RenderingSystem::RenderingSystem()
{
    //
}

bool RenderingSystem::Init()
{
    if (!glfwInit())
        throw std::runtime_error("Failed to initialize GLFW");

    bool win = InitAndConfigWindow();
    bool postProc = ConfigPostProcessing();

    if (!win || !postProc)
        return false;

    // Load default stuff
    LoadInternalShader("shaders/defaultSprite.vert", "shaders/defaultSprite.frag");
    LoadInternalSprite("images/square.png", 32.0f);
    LoadInternalSprite("images/grid.png", 128.0f);

    return true;
}

bool RenderingSystem::InitAndConfigWindow()
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    glfwWindowHint(GLFW_ALPHA_BITS, 8);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);

    // Placeholder
    glfwWindowHint(GLFW_MOUSE_PASSTHROUGH, GLFW_TRUE);

    // Initialize main window
    window = std::make_unique<DTEngine::Window>(400, 600, "DTEngine test");
    if (!window->winPtr)
        return false;

    glfwMakeContextCurrent(window->winPtr);

    // Load GLAD pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw std::string ("Failed to initialize GLAD");
    }
        
    // Enable vsync
    glfwSwapInterval(1); 

    // Blend function (alpha channel support)
    glEnable(GL_BLEND);
    glBlendFuncSeparate(
        GL_SRC_ALPHA,
        GL_ONE_MINUS_SRC_ALPHA,
        GL_ONE,
        GL_ONE_MINUS_SRC_ALPHA
    );

    window->ConfigWindow();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    return true;
}

bool RenderingSystem::ConfigPostProcessing()
{
    Vector2 screenSize = window->GetSize();

    // Init screen shader
    LoadInternalShader("shaders/framebuffer.vert", "shaders/framebuffer.frag", screenShader);
    
    // Update screen shader
    screenShader->Bind();
    screenShader->SetInt("screenTexture", 0);

    // Frame buffer object
	glGenFramebuffers(1, &worldFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, worldFBO);

	// Generate and setup FBT (Frame buffer texture)
	glGenTextures(1, &worldFBT);
	glBindTexture(GL_TEXTURE_2D, worldFBT);

    // Parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	// Generate texture
	glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA8,
        screenSize.x,
        screenSize.y,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        NULL
    );
    // Attach binded texture to framebuffer
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, worldFBT, 0);

    auto fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (fboStatus != GL_FRAMEBUFFER_COMPLETE)
        return false;

    // Solid FBO (clickable objects only, alpha-only, used by IsPositionSolid)
    glGenFramebuffers(1, &solidFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, solidFBO);

    glGenTextures(1, &solidFBT);
    glBindTexture(GL_TEXTURE_2D, solidFBT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, screenSize.x, screenSize.y, 0, GL_RED, GL_UNSIGNED_BYTE, NULL);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, solidFBT, 0);

    auto solidFboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (solidFboStatus != GL_FRAMEBUFFER_COMPLETE)
        return false;

    // Shader for solid pass — outputs alpha into the red channel
    LoadInternalShader("shaders/defaultSprite.vert", "shaders/solidPass.frag", solidPassShader);

    //
    // Texture and quad
    //

    float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
        // positions   // texCoords
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };

    // Generate VAO and VBO from quad
    glGenVertexArrays(1, &screenquadVAO);
    glGenBuffers(1, &screenquadVBO);
    glBindVertexArray(screenquadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, screenquadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    // Unbind all
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return true;
}

bool RenderingSystem::IsWindowRunning() const
{
    if (window == nullptr) return false;

    return window->IsRunning();
}

void RenderingSystem::RenderCycle()
{
    // Sort by renderOrder
    std::sort(renderers.begin(), renderers.end(),
        [](const SpriteRenderer* a, const SpriteRenderer* b) -> bool {
            return (a->renderOrder < b->renderOrder);
        });

    // SCENE PASS
    RenderPass(worldFBO, RenderPassType::WORLD);

    // SOLID PASS (clickable objects only — used by IsPositionSolid)
    RenderPass(solidFBO, RenderPassType::SOLID);

    // FINAL PASS
    window->Clear();

    screenShader->Bind();

    glBindVertexArray(screenquadVAO);
    glBindTexture(GL_TEXTURE_2D, worldFBT);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    window->SwapBuffers();
}

void RenderingSystem::RenderPass(unsigned int& frameBufferObject, const RenderPassType renderType)
{
    glBindFramebuffer(GL_FRAMEBUFFER, frameBufferObject);

    window->Clear();

    for (auto& spr : renderers)
    {
        if (renderType == RenderPassType::SOLID) {
            if (!spr->gameObject.clickable) continue;
            spr->RenderCall(solidPassShader.get());
        } else {
            spr->RenderCall();
        }
    }

    // Unbind everything
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void RenderingSystem::AddRenderSource(SpriteRenderer* spr)
{
    renderers.push_back(spr);
}

void RenderingSystem::RemoveRenderSource(SpriteRenderer* spr)
{
    std::erase_if(renderers, [&](const SpriteRenderer* it){
        return it == spr;
    });
}

int RenderingSystem::LoadShader(const std::string& vertexFile, const std::string& fragmentFile)
{
    PathSystem* pathSystem = SystemRegistry::GetSystem<PathSystem>();
    std::string assetsPath = pathSystem->GetAssetsPath();

    // retrieve the vertex/fragment source code from path
    std::string vertexCode = pathSystem->GetFileContents(assetsPath + vertexFile);
    std::string fragmentCode = pathSystem->GetFileContents(assetsPath + fragmentFile);

    // Create shader
    std::unique_ptr<Shader> newShad = std::make_unique<Shader>(vertexFile, vertexCode.c_str(), fragmentFile, fragmentCode.c_str());
    loadedShaders.push_back(std::move(newShad));

    return (loadedShaders.size() - 1);
}

void RenderingSystem::LoadInternalShader(const std::string& vertexFile, const std::string& fragmentFile, std::unique_ptr<Shader>& out)
{
    PathSystem* pathSystem = SystemRegistry::GetSystem<PathSystem>();
    std::string resourcesPath = pathSystem->GetResourcesPath();

    // retrieve the vertex/fragment source code from path
    std::string vertexCode = pathSystem->GetFileContents(resourcesPath + vertexFile);
    std::string fragmentCode = pathSystem->GetFileContents(resourcesPath + fragmentFile);

    // Create shader
    out = std::make_unique<Shader>(vertexFile, vertexCode.c_str(), fragmentFile, fragmentCode.c_str());
}

void RenderingSystem::LoadInternalShader(const std::string& vertexFile, const std::string& fragmentFile)
{
    std::unique_ptr<Shader> newShad;
    LoadInternalShader(vertexFile, fragmentFile, newShad);
    loadedShaders.push_back(std::move(newShad));
}

Shader& RenderingSystem::GetShader(int shaderIndex)
{
    if (shaderIndex >= loadedShaders.size())
        throw std::runtime_error("Shader index out of bounds");

    return *(loadedShaders[shaderIndex].get());
}

int RenderingSystem::LoadSprite(const std::string& path, float pixelsPerUnit)
{
    PathSystem* pathSystem = SystemRegistry::GetSystem<PathSystem>();
    std::string assetsPath = pathSystem->GetAssetsPath();

    ImageData imageData = pathSystem->GetImageContent(assetsPath + path);

    std::unique_ptr<Sprite> newSprite = std::make_unique<Sprite>(imageData.data, imageData.width, imageData.height, pixelsPerUnit, imageData.channels);

    loadedSprites.push_back(std::move(newSprite));

    return (loadedSprites.size() - 1);
}

void RenderingSystem::LoadInternalSprite(const std::string& path, float pixelsPerUnit)
{
    PathSystem* pathSystem = SystemRegistry::GetSystem<PathSystem>();
    std::string resourcesPath = pathSystem->GetResourcesPath();

    ImageData imageData = pathSystem->GetImageContent(resourcesPath + path);

    std::unique_ptr<Sprite> newSprite = std::make_unique<Sprite>(imageData.data, imageData.width, imageData.height, pixelsPerUnit, imageData.channels);

    loadedSprites.push_back(std::move(newSprite));
}

bool RenderingSystem::IsValidSpriteIndex(int spriteIndex) const
{
    return spriteIndex >= 0 && (size_t)spriteIndex < loadedSprites.size();
}

Sprite& RenderingSystem::GetSprite(int spriteIndex)
{
    if (!IsValidSpriteIndex(spriteIndex))
        throw std::runtime_error("Sprite index out of bounds: " + std::to_string(spriteIndex));

    return *(loadedSprites[spriteIndex].get());
}

void RenderingSystem::SetAnimationFramerate(int framerate)
{
    animationFramerate = framerate;
}

int RenderingSystem::GetAnimationFramerate() const
{
    return animationFramerate;
}

float RenderingSystem::GetFramesInTimeInterval(float time) const
{
    return (time * (float)animationFramerate);
}

bool RenderingSystem::IsPositionSolid(int x, int y, Vector2 size) const
{
    unsigned char pixel = 0;

    glBindFramebuffer(GL_FRAMEBUFFER, solidFBO);
    glReadPixels(x, size.y - y, 1, 1, GL_RED, GL_UNSIGNED_BYTE, &pixel);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    return pixel > 0;
}