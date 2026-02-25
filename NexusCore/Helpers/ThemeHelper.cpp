#include "pch.h"
#include "ThemeHelper.h"
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.UI.ViewManagement.h>
#include <winrt/Microsoft.UI.h>
#include <winrt/Microsoft.UI.Windowing.h>

using namespace winrt;
using namespace winrt::Microsoft::UI;
using namespace winrt::Microsoft::UI::Xaml;
using namespace winrt::Windows::Storage;
using namespace winrt::Windows::UI::ViewManagement;

namespace NexusCore::Helpers
{
    // Initialize static members
    winrt::Microsoft::UI::Xaml::ElementTheme ThemeHelper::s_rootTheme = winrt::Microsoft::UI::Xaml::ElementTheme::Default;
    winrt::event_token ThemeHelper::s_actualThemeChangedToken{};

    winrt::Microsoft::UI::Xaml::ElementTheme NexusCore::Helpers::ThemeHelper::RootTheme()
    {
        return winrt::Microsoft::UI::Xaml::ElementTheme();
    }

    void NexusCore::Helpers::ThemeHelper::RootTheme(winrt::Microsoft::UI::Xaml::ElementTheme value)
    {
        s_rootTheme = value;
        SaveThemeToSettings();
    }
}



