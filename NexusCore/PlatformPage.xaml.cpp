#include "pch.h"
#include "PlatformPage.xaml.h"
#if __has_include("PlatformPage.g.cpp")
#include "PlatformPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::NexusCore::implementation
{
    int32_t PlatformPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void PlatformPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }
}
