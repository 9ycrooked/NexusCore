#include "pch.h"
#include "SettingsPage.xaml.h"
#include "ThemeHelper.h"
#include "WindowHelper.h"
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

        // // 注册 Loaded 事件，在页面加载时恢复主题状态
        // Loaded({ this, &SettingsPage::OnSettingsPageLoaded });
    }

    void winrt::NexusCore::implementation::SettingsPage::ThemeComboBox_SelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& /*e*/)
    {
        // 从 ComboBoxItem.Tag 读取选定的主题
        hstring tag;
        if (auto combo = sender.try_as<ComboBox>())
        {
            if (auto sel = combo.SelectedItem().try_as<ComboBoxItem>())
            {
                auto boxed = sel.Tag();
                if (boxed) tag = winrt::unbox_value_or<hstring>(boxed, L"");
            }
        }

        if (tag.empty()) return;

        // 将标签转换为 ElementTheme
        ElementTheme desired = ElementTheme::Default;
        if (tag == L"Light") desired = ElementTheme::Light;
        else if (tag == L"Dark") desired = ElementTheme::Dark;
        else desired = ElementTheme::Default;

        // 使用 ThemeHelper 更新主题（持久保存到存储）
        ::NexusCore::Helpers::ThemeHelper::RootTheme(desired);

        // 应用到当前窗口
        auto window = ::NexusCore::Helpers::WinUIWindowHelper::WindowHelper::GetWindowForElement(*this);
        if (window)
        {
            OutputDebugStringW((L"获取到窗口，准备应用主题: " + tag + L"\n").c_str());
            ::NexusCore::Helpers::ThemeHelper::UpdateThemeForWindow(window);
            OutputDebugStringW(L"主题已应用到窗口\n");
        }
        else
        {
            OutputDebugStringW(L"无法获取窗口对象\n");
        }
    }

    void SettingsPage::OnSettingsPageLoaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        // 从 ThemeHelper 加载当前主题
        ElementTheme currentTheme = ::NexusCore::Helpers::ThemeHelper::RootTheme();

        // 根据保存的主题设置 ComboBox 选择
        if (auto combo = ThemeComboBox())
        {
            try
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
            catch (...)
            {
                // ComboBox 设置失败，静默处理
                OutputDebugStringW(L"无法设置 ComboBox 选定索引\n");
            }
        }
    }

}

