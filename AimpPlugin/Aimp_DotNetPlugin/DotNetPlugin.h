#pragma once

#include <gcroot.h>
#include "IUnknownInterfaceImpl.h"
#include "SDK\AimpPlayer.h"

private ref class ManagedFunctionality
{
public:
    ManagedFunctionality(IAIMPCore* core)
    {
        _core = core;
    }

    void PluginLoadEventReaction(AIMP::SDK::PluginInformation^ sender)
    {
        //// Each plugin should has his own managed core instance
        AIMP::SDK::ManagedAimpCore ^managedCore = gcnew AIMP::SDK::ManagedAimpCore(_core);
        AIMP::AimpPlayer^ instance = nullptr;
        if (sender->PluginAppDomainInfo != nullptr)
        {
            AIMP::AIMPControllerInitializer^ controllerInitializer = (AIMP::AIMPControllerInitializer^)sender->PluginAppDomainInfo->CreateInstanceFromAndUnwrap(System::Reflection::Assembly::GetExecutingAssembly()->Location, AIMP::AIMPControllerInitializer::TypeName);
            instance = controllerInitializer->CreateWithStaticAllocator(managedCore, sender->LoadedPlugin->PluginId, sender->PluginAppDomainInfo->Id, true);
        }
        else
            instance = gcnew AIMP::AimpPlayer(managedCore, sender->LoadedPlugin->PluginId, System::AppDomain::CurrentDomain->Id, false);

        sender->Initialize(instance);
    }

    void PluginUnloadEventReaction(AIMP::SDK::PluginInformation^ sender)
    {

    }
private:
    IAIMPCore* _core;
};

/// <summary>
/// 
/// </summary>
class DotNetPlugin : public IUnknownInterfaceImpl<IAIMPPlugin>
{
public:
    DotNetPlugin();

    virtual PWCHAR WINAPI InfoGet(int index);

    virtual DWORD WINAPI InfoGetCategories();

    // Initialization / Finalization
    virtual HRESULT WINAPI Initialize(IAIMPCore* core);

    virtual HRESULT WINAPI Finalize();

    virtual void WINAPI SystemNotification(int NotifyID, IUnknown* Data);

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObj);

    virtual ULONG WINAPI AddRef(void);

    virtual ULONG WINAPI Release(void);

private:
    HRESULT LoadExtensions(IAIMPCore* core);

private:
    bool inSetFormIntited;
    bool _optionsLoaded;
    gcroot<ManagedFunctionality^> _managedExtension;
    gcroot<AIMP::SDK::AimpDotNetPlugin^> _dotNetPlugin;
    IAIMPServiceConfig *_configService;
    IAIMPExtensionPlayerHook *_playerHook;
    typedef IUnknownInterfaceImpl<IAIMPPlugin> Base;
};
