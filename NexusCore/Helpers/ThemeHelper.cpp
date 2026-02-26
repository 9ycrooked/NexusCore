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
    winrt::Microsoft::UI::Xaml::ElementTheme ThemeHelper::s_rootTheme =
        winrt::Microsoft::UI::Xaml::ElementTheme::Default;
    winrt::event_token ThemeHelper::s_actualThemeChangedToken{};

    winrt::Microsoft::UI::Xaml::ElementTheme NexusCore::Helpers::ThemeHelper::RootTheme()
    {
        return s_rootTheme;
    }

    void NexusCore::Helpers::ThemeHelper::RootTheme(winrt::Microsoft::UI::Xaml::ElementTheme value)
    {
        s_rootTheme = value;
        SaveThemeToSettings();
    }

    winrt::Microsoft::UI::Xaml::ElementTheme ThemeHelper::ActualTheme()
    {
        // 检查主题是否为默认，如果是返回系统主题
        if (s_rootTheme == ElementTheme::Default)
        {
            return GetSystemTheme();
        }
        // 如果不是"默认", 返回用户选择的主题（Light 或 Dark）
        return s_rootTheme;
    }

    bool ThemeHelper::IsDarkTheme()
    {
        return ActualTheme() == ElementTheme::Dark;
    }

    void ThemeHelper::Initialize()
    {
        // 从本地加载主题
        s_rootTheme = LoadThemeFromSettings();

        try
        {
            UISettings uiSettings;

            // 监听系统主题变化的实现，用于在系统主题改变时自动更新应用主题。
            s_actualThemeChangedToken = uiSettings.ColorValuesChanged([](auto&&, auto&&)
            {
                if (s_rootTheme == ElementTheme::Default)
                {
                    // 系统主题已更改
                }
            });
        }
        catch (...)
        {
        }
    }

    void ThemeHelper::UpdateThemeForWindow(winrt::Microsoft::UI::Xaml::Window const& window)
    {
        if (!window) return;

        try
        {
            auto content = window.Content();
            if (!content) return;

            auto rootElement = content.try_as<winrt::Microsoft::UI::Xaml::FrameworkElement>();
            if (!rootElement) return;

            rootElement.RequestedTheme(s_rootTheme);
            UpdateTitleBarTheme(window);
        }
        catch (...)
        {
        }
    }

    void ThemeHelper::SaveThemeToSettings()
    {
        try
        {
            auto localSettings = ApplicationData::Current().LocalSettings();
            auto values = localSettings.Values();
            int32_t themeValue = static_cast<int32_t>(s_rootTheme);
            values.Insert(THEME_SETTING_KEY, box_value(themeValue));
        }
        catch (...)
        {
        }
    }

    winrt::Microsoft::UI::Xaml::ElementTheme ThemeHelper::LoadThemeFromSettings()
    {
        try
        {
            // 提供对本地设置存储的访问入口
            auto localSettings = ApplicationData::Current().LocalSettings();
            // 返回一个可操作的键值对集合，用于读取/写入设置
            auto values = localSettings.Values();
            // 防止读取不存在的键导致异常
            if (values.HasKey(THEME_SETTING_KEY))
            {
                // 获取存储的主题值（被包装成 WinRT 类型）
                auto stored = values.Lookup(THEME_SETTING_KEY);
                // 将存储的整数转换回原生 C++ 类型
                int32_t themeValue = unbox_value<int32_t>(stored);
                //将整数 0 / 1 / 2 转换为 ElementTheme::Default / Light / Dark
                return static_cast<ElementTheme>(themeValue);
            }
            // 路径 2：设置不存在（跳过 if，执行到函数末尾）
            // 继续执行到最后的 return
        }
        catch (...)
        {
            // 路径 3：发生异常
            // 捕获异常后，继续执行到函数末尾
        }
        // 如果if生效将不会执行到这里，如果发生异常/跳过 if 会继续执行到这里
        return ElementTheme::Default;
    }

    winrt::hstring ThemeHelper::ThemeToString(winrt::Microsoft::UI::Xaml::ElementTheme theme)
    {
        // 将 ElementTheme 枚举值转换为字符串以供 UI 显示
        switch (theme)
        {
        case ElementTheme::Default: return L"Default";
        case ElementTheme::Light: return L"Light";
        case ElementTheme::Dark: return L"Dark";
        default: return L"Default";
        }
    }

    winrt::Microsoft::UI::Xaml::ElementTheme ThemeHelper::StringToTheme(winrt::hstring const& themeString)
    {
        if (themeString == L"Light") return ElementTheme::Light;
        else if (themeString == L"Dark") return ElementTheme::Dark;
        else return ElementTheme::Default;
    }


    winrt::Microsoft::UI::Xaml::ElementTheme ThemeHelper::GetSystemTheme()
    {
        try
        {
            UISettings uiSettings;
            auto background = uiSettings.GetColorValue(UIColorType::Background);
            int luminance = background.R + background.G + background.B;
            return (luminance < 384) ? ElementTheme::Dark : ElementTheme::Light;
        }
        catch (...)
        {
            return ElementTheme::Light;
        }
    }

    void ThemeHelper::UpdateTitleBarTheme(winrt::Microsoft::UI::Xaml::Window const& window)
    {
        try
        {
            auto appWindow = window.AppWindow();
            if (!appWindow) return;

            auto titleBar = appWindow.TitleBar();
            if (!titleBar) return;

            bool isDark = IsDarkTheme();

            Windows::UI::Color buttonForeground, buttonBackground;
            Windows::UI::Color buttonHoverForeground, buttonHoverBackground;
            Windows::UI::Color buttonPressedForeground, buttonPressedBackground;

            if (isDark)
            {
                buttonForeground = Windows::UI::ColorHelper::FromArgb(255, 255, 255, 255);
                buttonBackground = Windows::UI::ColorHelper::FromArgb(0, 255, 255, 255);
                buttonHoverForeground = Windows::UI::ColorHelper::FromArgb(255, 255, 255, 255);
                buttonHoverBackground = Windows::UI::ColorHelper::FromArgb(20, 255, 255, 255);
                buttonPressedForeground = Windows::UI::ColorHelper::FromArgb(255, 255, 255, 255);
                buttonPressedBackground = Windows::UI::ColorHelper::FromArgb(30, 255, 255, 255);
            }
            else
            {
                buttonForeground = Windows::UI::ColorHelper::FromArgb(255, 0, 0, 0);
                buttonBackground = Windows::UI::ColorHelper::FromArgb(0, 0, 0, 0);
                buttonHoverForeground = Windows::UI::ColorHelper::FromArgb(255, 0, 0, 0);
                buttonHoverBackground = Windows::UI::ColorHelper::FromArgb(20, 0, 0, 0);
                buttonPressedForeground = Windows::UI::ColorHelper::FromArgb(255, 0, 0, 0);
                buttonPressedBackground = Windows::UI::ColorHelper::FromArgb(30, 0, 0, 0);
            }

            titleBar.ButtonForegroundColor(buttonForeground);
            titleBar.ButtonBackgroundColor(buttonBackground);
            titleBar.ButtonHoverForegroundColor(buttonHoverForeground);
            titleBar.ButtonHoverBackgroundColor(buttonHoverBackground);
            titleBar.ButtonPressedForegroundColor(buttonPressedForeground);
            titleBar.ButtonPressedBackgroundColor(buttonPressedBackground);
        }
        catch (...)
        {
        }
    }
}
