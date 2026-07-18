#include "SpriteRenderer.hpp"

#include <DTEngine/GameObject.hpp>
#include <DTEngine/Utils.hpp>
#include <DTEngine/Shader.hpp>
#include <DTEngine/Sprite.hpp>
#include <DTEngine/Window.hpp>
#include "system/RenderingSystem.hpp"
#include "system/SystemRegistry.hpp"
#include <DTEngine/Animator.hpp>

#include "glad/glad.h"

using namespace DTEngine;

SpriteRenderer::~SpriteRenderer()
{
    SystemRegistry::GetSystem<RenderingSystem>()->RemoveRenderSource(this);

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

SpriteRenderer::SpriteRenderer(GameObject& _gameObject) :
    Component(_gameObject), animationSpriteId(-1)
{
    SystemRegistry::GetSystem<RenderingSystem>()->AddRenderSource(this);
    
    // Default values
    color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
    renderOrder = 0;

    // Basic vertices
    float vertices[] = {
        // positions        // texture coords
        0.5f,  0.5f,        1.0f, 1.0f, // top right
        0.5f, -0.5f,        1.0f, 0.0f, // bottom right
       -0.5f, -0.5f,        0.0f, 0.0f, // bottom left
       -0.5f,  0.5f,        0.0f, 1.0f  // top left
    };
    
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };  

    // Create and link VAO and VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 
}

void SpriteRenderer::Start()
{
    //
}

void SpriteRenderer::Update()
{
    //
}

void SpriteRenderer::RenderCall(Shader* overrideShader)
{
    RenderingSystem* rend = SystemRegistry::GetSystem<RenderingSystem>();
    Window* window = Window::GetInstance();
    int spriteId = animationSpriteId != -1 ? animationSpriteId : usedSpriteId;
    Sprite& sprt = rend->GetSprite(spriteId);
    Shader& shad = overrideShader ? *overrideShader : rend->GetShader(usedShaderId);

    // Cool variables :)
    Vector2 winSize = window->GetSize();
    float aspect = winSize.x / winSize.y;
    float fov = window->fov;
    Vector2 worldPosition = gameObject.transform->GetPosition();
    Vector2 worldScale = gameObject.transform->GetScale();
    float worldRotation = gameObject.transform->GetRotation();
    Vector2 spriteInternalSize = sprt.GetSize();
    Matrix3 projMat(1.0f), modelMat(1.0f);

    // Transform the matrices
    projMat = Matrix3::Ortho(-aspect * fov, aspect * fov, -1.0f * fov, 1.0f * fov);
    modelMat = Matrix3::Translate(modelMat, worldPosition);
    // Rotation
    if (worldRotation != 0.0f)
        modelMat = Matrix3::Rotate(modelMat, Radians(worldRotation));
    // Sprite size
    Vector2 spriteSize = spriteInternalSize / sprt.pixelsPerUnit;
    modelMat = Matrix3::Scale(modelMat, spriteSize);
    // GameObject scale
    modelMat = Matrix3::Scale(modelMat, worldScale);

    // Update shader
    shad.Bind();
    shad.SetMat3("projection", projMat);
    shad.SetMat3("model", modelMat);
    shad.SetVec4("color", color);

    // Draw texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, sprt.texId);

    // Draw vertices
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // Unbind
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
    shad.Unbind();
}

void SpriteRenderer::SetShader(int shaderIndex)
{
    usedShaderId = shaderIndex;
}

void SpriteRenderer::SetSprite(int spriteIndex)
{
    usedSpriteId = spriteIndex;
}

void SpriteRenderer::SetAnimationSprite(int spriteIndex)
{
    animationSpriteId = spriteIndex;
}