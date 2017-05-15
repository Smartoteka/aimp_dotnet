/*
 * AIMP DotNet SDK
 * 
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 * https://github.com/martin211/aimp_dotnet
 * 
 */
#pragma once

#include "SDK\BaseManager.h"
#include "ICallBackHeader.h"
#include "AimpMenuItem.h"


namespace AIMP
{
    namespace SDK
    {
        using namespace AIMP::SDK::MenuManager;

        public ref class AimpMenuManager : public AimpBaseManager<IAIMPServiceMenuManager>, public IAimpServiceMenuManager
        {
        public:
            explicit AimpMenuManager(ManagedAimpCore^ core);

            virtual AimpActionResult CreateMenuItem(IAimpMenuItem ^%item);

            ~AimpMenuManager();

            virtual AimpActionResult Add(IAimpMenuItem ^item);

            virtual AimpActionResult Add(ParentMenuType parentMenuType, IAimpMenuItem ^item);

            virtual AimpActionResult Delete(IAimpMenuItem ^item);

            virtual AimpActionResult Delete(String ^id);

            virtual AimpActionResult GetById(String ^id, IAimpMenuItem ^%item);

            virtual AimpActionResult GetBuiltIn(ParentMenuType parentMenuType, IAimpMenuItem ^%item);

        private:
            HRESULT UnregisterMenu(IAIMPMenuItem* menuItem);
        };
    }
}
