// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#include "Stdafx.h"
#include "AimpMemoryManager.h"

AimpMemoryManager* AimpMemoryManager::instance = 0;

AimpMemoryManager::AimpMemoryManager() {}

AimpMemoryManager& AimpMemoryManager::getInstance()
{
    if (!instance)
    {
        instance = new AimpMemoryManager();
    }
    return *instance;
}

void AimpMemoryManager::AddObject(int key, void* obj)
{
    const auto info = new ObjectInfo();
    info->object = obj;
    info->disposed = false;
    instance->objects[key] = info;
}

void AimpMemoryManager::Release(int key)
{
    const auto obj = instance->objects[key];

    try
    {
        if (obj != nullptr && !obj->disposed) {
            static_cast<IUnknown*>(obj->object)->Release();
            obj->disposed = true;
        }
        else
        {
            System::Diagnostics::Debug::WriteLine("KEY not found");
        }
    }
    catch (...)
    {
    }
 }

void AimpMemoryManager::ReleaseAll()
{
    for (auto obj = instance->objects.begin(); obj != instance->objects.end(); ++obj)
    {
        if (!obj->second->disposed)
        {
            static_cast<IUnknown*>(obj->second->object)->Release();
            obj->second->disposed = true;
        }
    }
}

