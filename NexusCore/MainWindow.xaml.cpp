#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

#include <winrt/Windows.UI.Xaml.Interop.h>
#include <winrt/Microsoft.UI.Windowing.h>

#include <microsoft.ui.xaml.window.h> 
using namespace winrt;
using namespace Microsoft::UI::Xaml;


// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::NexusCore::implementation
{
    MainWindow::MainWindow()
    {
        // 必须调用 XAML 初始化
        InitializeComponent();

        // 导航到默认页面MainPage
        NavigationViewControl().SelectedItem(
            NavigationViewControl().MenuItems().GetAt(0).as<Controls::NavigationViewItem>()
        );
        ContentFrame().Navigate(xaml_typename<NexusCore::MainPage>());

        // 自定义窗口标题栏
        auto appWindow = this->AppWindow();
        if (appWindow) // 空值检查；确保成功获取 AppWindow 对象
        {
            auto titleBar = appWindow.TitleBar();
            // 设置窗口标题栏为自定义
            appWindow.TitleBar().ExtendsContentIntoTitleBar(true);
            // 可选：让系统按钮背景透明
            appWindow.TitleBar().ButtonBackgroundColor(Windows::UI::Colors::Transparent());
        }
    }
    void winrt::NexusCore::implementation::MainWindow::TitleBar_BackRequested(winrt::Microsoft::UI::Xaml::Controls::TitleBar const& sender, winrt::Windows::Foundation::IInspectable const& args)
    {
        if (ContentFrame().CanGoBack())
        {
            ContentFrame().GoBack();
        }

    }


    void winrt::NexusCore::implementation::MainWindow::NavigationViewControl_ItemInvoked(winrt::Microsoft::UI::Xaml::Controls::NavigationView const& , winrt::Microsoft::UI::Xaml::Controls::NavigationViewItemInvokedEventArgs const& args)
    {
        if (args.IsSettingsInvoked())
        {
            ContentFrame().Navigate(xaml_typename<NexusCore::SettingsPage>());
            return;
        }
        // 获取被点击的项
        auto invokedItem = args.InvokedItemContainer().try_as<Controls::NavigationViewItem>();
        // 空值检查
        if (!invokedItem)
            return;
        // 获取 Tag 字符串
        auto tag = unbox_value_or<hstring>(invokedItem.Tag(), L"");
        NavigateToPage(tag);  // 3. 使用私有辅助函数；根据 Tag 字符串执行相应的跳转
        
    }
    void winrt::NexusCore::implementation::MainWindow::NavigateToPage(winrt::hstring const& pageName)
    {
        if (pageName == L"MainPage")
        {
            ContentFrame().Navigate(xaml_typename<NexusCore::MainPage>());
        }
        else if (pageName == L"KeyPage")
        {
            ContentFrame().Navigate(xaml_typename<NexusCore::KeyPage>());
        }
        else if (pageName == L"PlatformPage")
        {
            ContentFrame().Navigate(xaml_typename<NexusCore::PlatformPage>());
        }
    }

}
