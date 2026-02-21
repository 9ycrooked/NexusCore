#include "pch.h"
#include "KeyPage.xaml.h"
#if __has_include("KeyPage.g.cpp")
#include "KeyPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::NexusCore::implementation
{
    int32_t KeyPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void KeyPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }
}
