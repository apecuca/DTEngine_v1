#ifndef DTENGINE_INTERNALWORKS_H
#define DTENGINE_INTERNALWORKS_H

#include <memory>

namespace DTEngine
{

class Rendering;

class InternalWorksManager
{
friend class Engine;

public:
    ~InternalWorksManager();
    InternalWorksManager();

public:
    static InternalWorksManager* GetInstance();

    Rendering* GetRendering();

private:
    bool InitWorks();
    bool IsFullyWorking() const;

private:
    static InternalWorksManager* instance;

    std::unique_ptr<Rendering> rendering;
};

}

#endif