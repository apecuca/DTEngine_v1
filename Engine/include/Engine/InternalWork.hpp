#ifndef DTENGINE_INTERNALWORK_H
#define DTENGINE_INTERNALWORK_H

namespace DTEngine 
{

class InternalWork
{
friend class InternalWorksManager;

protected:
    ~InternalWork() = default;
    InternalWork() = default;

    virtual bool Init() = 0;
};

}

#endif