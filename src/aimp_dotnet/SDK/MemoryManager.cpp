// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2019 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

#include "Stdafx.h"
#include "MemoryManager.h"

MemoryManager* MemoryManager::p_instance = 0;

MemoryManager* MemoryManager::getInstance()
{
    //p_instance = new MemoryManager();
    if (!MemoryManager::p_instance) {
        p_instance = new MemoryManager();
    }

    return p_instance;
}

void MemoryManager::Add(IUnknown* obj)
{
    objects[obj] = obj;
}

void MemoryManager::Dispose(IUnknown* obj)
{
    IUnknown* o = objects[obj];
    if (o != nullptr)
    {
        o->Release();
    }

    objects.erase(obj);
}

void MemoryManager::Clear()
{
    for (auto i = objects.begin(); i != objects.end(); ++i)
    {
        i->second->Release();
    }

    objects.clear();
    //delete p_instance;
}
