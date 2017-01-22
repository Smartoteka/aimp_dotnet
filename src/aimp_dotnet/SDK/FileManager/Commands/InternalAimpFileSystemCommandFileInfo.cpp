#include "Stdafx.h"
#include "InternalAimpFileSystemCommandFileInfo.h"

using namespace AIMP::SDK;

InternalAimpFileSystemCommandFileInfo::InternalAimpFileSystemCommandFileInfo(gcroot<AIMP::SDK::FileManager::Commands::IAimpFileSystemCommandFileInfo^> instance)
{
    _instance = instance;
}

HRESULT WINAPI InternalAimpFileSystemCommandFileInfo::GetFileAttrs(IAIMPString* FileName, TAIMPFileAttributes* Attrs)
{
    AIMP::SDK::FileManager::AimpFileAttributes attr;
    AimpActionResult result = _instance->GetFileAttrs(AIMP::SDK::AimpExtension::GetString(FileName), attr);
    Attrs = new TAIMPFileAttributes();
    Attrs->Attributes = (DWORD)attr.Attributes;
    //Attrs->TimeCreation = attr.TimeCreation->ToOADate();
    //Attrs->TimeLastAccess = attr.TimeLastAccess->ToOADate();
    Attrs->TimeLastWrite = attr.TimeLastWrite.ToOADate();

    return (HRESULT)result;
}

HRESULT WINAPI InternalAimpFileSystemCommandFileInfo::GetFileSize(IAIMPString* FileName, INT64* Size)
{
    long long size = 0;
    AimpActionResult result = _instance->GetFileSize(AIMP::SDK::AimpExtension::GetString(FileName), size);
    *Size = size;
    return (HRESULT)result;
}

HRESULT WINAPI InternalAimpFileSystemCommandFileInfo::IsFileExists(IAIMPString* FileName)
{
    return (HRESULT)_instance->IsFileExists(AIMP::SDK::AimpExtension::GetString(FileName));
}

ULONG WINAPI InternalAimpFileSystemCommandFileInfo::AddRef(void)
{
    return Base::AddRef();
}

ULONG WINAPI InternalAimpFileSystemCommandFileInfo::Release(void)
{
    return Base::Release();
}

HRESULT WINAPI InternalAimpFileSystemCommandFileInfo::QueryInterface(REFIID riid, LPVOID* ppvObject)
{
    HRESULT res = Base::QueryInterface(riid, ppvObject);

    if (riid == IID_IAIMPFileSystemCommandFileInfo)
    {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    *ppvObject = NULL;
    return res;
}