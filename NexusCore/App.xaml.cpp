#include "pch.h"
#include "App.xaml.h"
#include "MainWindow.xaml.h"
#include "ThemeHelper.h"
#include "WindowHelper.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::NexusCore::implementation
{
    /// <summary>
    /// Initializes the singleton application object.  This is the first line of authored code
    /// executed, and as such is the logical equivalent of main() or WinMain().
    /// </summary>
    App::App()
    {
        // Xaml objects should not call InitializeComponent during construction.
        // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent

#if defined _DEBUG && !defined DISABLE_XAML_GENERATED_BREAK_ON_UNHANDLED_EXCEPTION
        UnhandledException([](IInspectable const&, UnhandledExceptionEventArgs const& e)
        {
            if (IsDebuggerPresent())
            {
                auto errorMessage = e.Message();
                __debugbreak();
            }
        });
#endif
    }

    /// <summary>
    /// Invoked when the application is launched.
    /// </summary>
    /// <param name="e">Details about the launch request and process.</param>
    void App::OnLaunched([[maybe_unused]] LaunchActivatedEventArgs const& e)
    {
        
        // 创建并激活窗口
        window = make<MainWindow>();
        // TrackWindow ：将创建的窗口添加到 WindowHelper 的活动窗口列表中，
        // 这样后续可以通过 ActiveWindows() 方法获取所有活动窗口，
        // 或通过 GetWindowForElement() 等方法根据 UI 元素查找所属窗口。
        ::NexusCore::Helpers::WinUIWindowHelper::WindowHelper::TrackWindow(window);

        // 设置窗口最小尺寸；无法使用
        //::NexusCore::Helpers::WinUIWindowHelper::WindowHelper::SetWindowMinSize(window, 800, 600 );
        // 应用主题到窗口
        ::NexusCore::Helpers::ThemeHelper::UpdateThemeForWindow(window);

        window.Activate();
        
    }
}