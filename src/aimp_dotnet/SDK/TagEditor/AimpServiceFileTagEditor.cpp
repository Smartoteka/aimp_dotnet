// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#include "Stdafx.h"
#include "AimpServiceFileTagEditor.h"
#include "AimpFileTagEditor.h"
#include "SDK/FileManager/AimpFileInfo.h"

using namespace AIMP::SDK;

AimpServiceFileTagEditor::
AimpServiceFileTagEditor(ManagedAimpCore^ core) : BaseAimpService<IAIMPServiceFileTagEditor>(core)
{
}

ActionResultType AimpServiceFileTagEditor::EditFile(String^ filePath, IAimpFileTagEditor^% editor)
{
    IAIMPServiceFileTagEditor* service = GetAimpService();
    IAIMPString* str = AimpConverter::ToAimpString(filePath);
    ActionResultType result = ActionResultType::Fail;

    try
    {
        if (service != nullptr)
        {
            IAIMPFileTagEditor* aimpEditor = nullptr;
            result = CheckResult(service->EditFile(str, IID_IAIMPFileTagEditor, reinterpret_cast<void**>(&aimpEditor)));

            if (result == ActionResultType::OK && aimpEditor != nullptr)
            {
                editor = gcnew AimpFileTagEditor(aimpEditor);
            }
        }

        return result;
    }
    finally
    {
        ReleaseObject(service);
        ReleaseObject(str);
    }
}

ActionResultType AimpServiceFileTagEditor::EditFile(IAimpStream^ fileStream, IAimpFileTagEditor^% editor)
{
    IAIMPServiceFileTagEditor* service = GetAimpService();
    IAIMPStream* stream = static_cast<AimpStream^>(fileStream)->InternalAimpObject;
    ActionResultType result = ActionResultType::Fail;

    try
    {
        if (service != nullptr)
        {
            IAIMPFileTagEditor* aimpEditor = nullptr;
            result = CheckResult(service->EditFile(stream, IID_IAIMPFileTagEditor,
                                                   reinterpret_cast<void**>(&aimpEditor)));

            if (result == ActionResultType::OK && aimpEditor != nullptr)
            {
                editor = gcnew AimpFileTagEditor(aimpEditor);
            }
        }
    }
    finally
    {
        ReleaseObject(service);
    }

    return result;
}

ActionResultType AimpServiceFileTagEditor::EditTag(String^ filePath, TagType tag, IAimpFileInfo^% fileInfo)
{
    IAIMPServiceFileTagEditor* service = GetAimpService();
    IAIMPString* str = AimpConverter::ToAimpString(filePath);
    ActionResultType result = ActionResultType::Fail;

    try
    {
        if (service != nullptr)
        {
            IAIMPFileInfo* aimpFileInfo = nullptr;
            result = CheckResult(service->EditTag(str, int(tag), IID_IAIMPFileInfo,
                                                  reinterpret_cast<void**>(&aimpFileInfo)));

            if (result == ActionResultType::OK && aimpFileInfo != nullptr)
            {
                fileInfo = gcnew AimpFileInfo(aimpFileInfo);
            }
        }
    }
    finally
    {
        ReleaseObject(service);
        ReleaseObject(str);
    }

    return result;
}

ActionResultType AimpServiceFileTagEditor::EditTag(IAimpStream^ fileStream, TagType tag, IAimpFileInfo^% fileInfo)
{
    IAIMPServiceFileTagEditor* service = GetAimpService();
    IAIMPStream* stream = static_cast<AimpStream^>(fileStream)->InternalAimpObject;
    ActionResultType result = ActionResultType::Fail;

    try
    {
        if (service != nullptr)
        {
            IAIMPFileInfo* aimpFileInfo = nullptr;
            result = CheckResult(service->EditTag(stream, int(tag), IID_IAIMPFileInfo,
                                                  reinterpret_cast<void**>(&aimpFileInfo)));

            if (result == ActionResultType::OK && aimpFileInfo != nullptr)
            {
                fileInfo = gcnew AimpFileInfo(aimpFileInfo);
            }
        }
    }
    finally
    {
        ReleaseObject(service);
    }

    return result;
}

IAIMPServiceFileTagEditor* AimpServiceFileTagEditor::GetAimpService()
{
    IAIMPServiceFileTagEditor* service = nullptr;
    GetService(IID_IAIMPServiceFileTagEditor, &service);
    return service;
}
