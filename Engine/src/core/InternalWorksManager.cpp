#include "InternalWorksManager.hpp"

#include <iostream>
#include <rendering/Rendering.hpp>

using namespace DTEngine;

InternalWorksManager* InternalWorksManager::instance;

InternalWorksManager::~InternalWorksManager()
{
    if (instance == this)
        instance = nullptr;
}

InternalWorksManager::InternalWorksManager()
{
    if (instance != nullptr)
        throw std::string("InternalWorksManager instance duplicate found");

    instance = this;
}

InternalWorksManager* InternalWorksManager::GetInstance()
{
    return instance;
}

bool InternalWorksManager::IsFullyWorking() const
{
    if (rendering == nullptr) return false;
    return true;
}

bool InternalWorksManager::InitWorks()
{
    rendering = std::make_unique<Rendering>();
    if (!rendering->Init()) return false;

    return true;
}

Rendering* InternalWorksManager::GetRendering()
{
    return rendering.get();
}