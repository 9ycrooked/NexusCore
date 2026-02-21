#pragma once

#include "PlatformPage.g.h"

namespace winrt::NexusCore::implementation
{
    struct PlatformPage : PlatformPageT<PlatformPage>
    {
        PlatformPage()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);
    };
}

namespace winrt::NexusCore::factory_implementation
{
    struct PlatformPage : PlatformPageT<PlatformPage, implementation::PlatformPage>
    {
    };
}
