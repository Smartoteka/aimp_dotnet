﻿using AIMP.SDK;
using AIMP.SDK.MusicLibrary.DataFilter;
using AIMP.SDK.MusicLibrary.DataStorage;

namespace dotnet_musiclibrary
{
    public class CustomAimpGroupingTreeDataProvider : IAimpGroupingTreeDataProvider
    {
        public AimpActionResult AppendFilter(IAimpDataFilterGroup filter, IAimpGroupingTreeSelection selection)
        {
            return AimpActionResult.NotImplemented;
        }

        public CapabilitiesFlags GetCapabilities()
        {
            return CapabilitiesFlags.None;
        }

        public AimpActionResult GetData(IAimpGroupingTreeSelection selection, out IAimpGroupingTreeDataProviderSelection data)
        {
            data = null;

            string name;
            object value;

            var count = selection.GetCount();

            if (count > 0)
            {
                if (selection.GetValue(0, out name, out value) == AimpActionResult.Ok)
                {
                    return AimpActionResult.Ok;
                }
            }

            data = new CustomAimpGroupingTreeDataProviderSelection();

            return AimpActionResult.Ok;
        }

        public AimpActionResult GetFieldForAlphabeticIndex(out string fieldName)
        {
            fieldName = "Test";
            return AimpActionResult.Ok;
        }
    }
}