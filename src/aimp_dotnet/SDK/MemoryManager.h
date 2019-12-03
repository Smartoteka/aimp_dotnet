#pragma once

#include <vector>
#include <map>

public class MemoryManager
{
private:
    std::map<void*, IUnknown*> objects;
    std::vector<IUnknown*> _objects;
    static MemoryManager* p_instance;
public:
    static MemoryManager* getInstance();
    void Add(IUnknown* obj);
    void Dispose(IUnknown* obj);
    void Clear();
};
