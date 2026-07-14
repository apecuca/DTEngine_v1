#include "Game.hpp"

#include <DTEngine/World.hpp>
#include <DTEngine/Component.hpp>
#include <DTEngine/SpriteRenderer.hpp>
#include <DTEngine/Window.hpp>
#include <DTEngine/WorldManager.hpp>
#include <DTEngine/RenderingManager.hpp>
#include <DTEngine/PhysicsManager.hpp>

#include "SuperComponent.hpp"

#include <iostream>

using namespace DTEngine;

Game::Game()
{
    RenderingManager::LoadSprite("pose.png", 1920.0f);
    PhysicsManager::SetGravity(Vector2(0.0f, -9.8f * 2));
    PhysicsManager::CreateLayer("Player");
    PhysicsManager::CreateLayer("Enemy");
    PhysicsManager::CreateLayer("Ground");
    //PhysicsManager::SetCollisionRule("Player", "Enemy", false);

    int firstIndex = WorldManager::RegisterWorld("First", []() {
        // Player
        auto player = WorldManager::Instantiate();
        player->SetLayer("Player");
        player->AddComponent<Rigidbody>();
        player->AddComponent<BoxCollider>();
        auto spr = player->AddComponent<SpriteRenderer>();
        spr->color = Vector4(0.6f, 1.0f, 1.0f, 1.0f);
        spr->renderOrder = 1;
        player->AddComponent<SuperComponent>();

        // Enemy
        auto enemy = WorldManager::Instantiate();
        enemy->SetLayer("Enemy");
        enemy->transform->localPosition = Vector2(-2.0f, 2.0f);
        enemy->AddComponent<SpriteRenderer>();
        enemy->AddComponent<BoxCollider>();
        auto eRb = enemy->AddComponent<Rigidbody>();
        eRb->mass *= 10.0f;

        // Ground
        auto ground = WorldManager::Instantiate();
        ground->SetLayer("Ground");
        ground->transform->localPosition.y = -4.0f;
        ground->transform->localScale.x = 10.0f;
        auto s = ground->AddComponent<SpriteRenderer>();
        auto r = ground->AddComponent<Rigidbody>();
        auto b = ground->AddComponent<BoxCollider>();
        s->color = Vector4(0.6f, 1.0f, 0.6f, 1.0f);
        r->isKinematic = true;
        r->gravityScale = 0.0f;
    });

    int secondIndex = WorldManager::RegisterWorld("Second", []() {
        // Player
        auto player = WorldManager::Instantiate();
        player->SetLayer("Player");
        player->AddComponent<Rigidbody>();
        player->AddComponent<BoxCollider>();
        auto spr = player->AddComponent<SpriteRenderer>();
        spr->color = Vector4(1.0f, 0.6f, 1.0f, 1.0f);
        spr->renderOrder = 1;
        player->AddComponent<SuperComponent>();

        // child
        auto child = WorldManager::Instantiate();
        child->transform->localPosition.x = 2.0f;
        child->transform->localPosition.y = 2.0f;
        child->transform->localScale = Vector2::one() * 0.5f;
        child->transform->SetParent(player->transform);
        child->AddComponent<SpriteRenderer>()->color = Vector4(0.8f, 1.0f, 1.0f, 1.0f);

        // Ground
        auto ground = WorldManager::Instantiate();
        ground->SetLayer("Ground");
        ground->transform->localPosition.y = -4.0f;
        ground->transform->localScale.x = 10.0f;
        auto s = ground->AddComponent<SpriteRenderer>();
        auto r = ground->AddComponent<Rigidbody>();
        auto b = ground->AddComponent<BoxCollider>();
        s->color = Vector4(0.6f, 1.0f, 0.6f, 1.0f);
        r->isKinematic = true;
        r->gravityScale = 0.0f;
    });

    WorldManager::LoadWorld(firstIndex);
}