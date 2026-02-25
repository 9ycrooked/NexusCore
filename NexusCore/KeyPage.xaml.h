#pragma once

#include "KeyPage.g.h"

namespace winrt::NexusCore::implementation
{
    struct KeyPage : KeyPageT<KeyPage>
    {
        KeyPage()
        {
            // 构造函数中不调用 InitializeComponent()，以遵循 C++/WinRT 的指导原则。
        }

        void OnLoaded(winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::NexusCore::factory_implementation
{
    struct KeyPage : KeyPageT<KeyPage, implementation::KeyPage>
    {
    };
}
