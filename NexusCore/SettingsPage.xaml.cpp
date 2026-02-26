#include "pch.h"
#include "SettingsPage.xaml.h"
#include "ThemeHelper.h"
#if __has_include("SettingsPage.g.cpp")
#include "SettingsPage.g.cpp"
#endif

#include <winrt/Windows.UI.Xaml.Interop.h>

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;
// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::NexusCore::implementation
{
    // 构造函数
    SettingsPage::SettingsPage()
    {
        InitializeComponent();

        // 注册 Loaded 事件，在页面加载时恢复主题状态
        Loaded({ this, &SettingsPage::OnSettingsPageLoaded });
    }

    void winrt::NexusCore::implementation::SettingsPage::ThemeComboBox_SelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e)
    {
        // 获取 ComboBox 控件
        auto comboBox = sender.try_as<winrt::Microsoft::UI::Xaml::Controls::ComboBox>();
        if (!comboBox) return;

        // 获取选中的项
        auto selectedItem = comboBox.SelectedItem().as<winrt::Microsoft::UI::Xaml::Controls::ComboBoxItem>();
        if (!selectedItem) return;

        // 获取 Tag 属性（主题名称）
        auto tag = selectedItem.Tag();
        if (!tag) return;

        // 将 Tag 转换为字符串
        winrt::hstring themeTag = winrt::unbox_value<winrt::hstring>(tag);

        // 根据 Tag 设置主题
        ElementTheme desired = ElementTheme::Default;
        if (themeTag == L"Light")
        {
            desired = ElementTheme::Light;
        }
        else if (themeTag == L"Dark")
        {
            desired = ElementTheme::Dark;
        }
        else
        {
            desired = ElementTheme::Default;
        }

        // 使用 ThemeHelper 设置主题（会持久化到存储）
        ::NexusCore::Helpers::ThemeHelper::RootTheme(desired);

        // 应用到当前窗口
        auto window = Window::Current();
        if (window)
        {
            ::NexusCore::Helpers::ThemeHelper::UpdateThemeForWindow(window);
        }
    }

    void SettingsPage::OnSettingsPageLoaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        // 从 ThemeHelper 加载当前主题
        ElementTheme currentTheme = ::NexusCore::Helpers::ThemeHelper::RootTheme();

        // 根据保存的主题设置 ComboBox 选择
        if (auto combo = ThemeComboBox())
        {
            switch (currentTheme)
            {
            case ElementTheme::Light:
                combo.SelectedIndex(1);
                break;
            case ElementTheme::Dark:
                combo.SelectedIndex(2);
                break;
            default:
                combo.SelectedIndex(0); // Default/Auto
                break;
            }
        }
    }

}

