#pragma once

#include <winrt/Microsoft.UI.Xaml.h>
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.UI.ViewManagement.h>

namespace NexusCore::Helpers
{

    /// <摘要>
    /// 用于管理应用程序主题的帮助程序类
    /// 基于WinUI Gallery ThemeHelper模式
    /// </摘要>

    class ThemeHelper
    {
    public:
        /// <summary>
        /// 获取或设置应用程序的根主题
        /// </summary>
        static winrt::Microsoft::UI::Xaml::ElementTheme RootTheme();
        static void RootTheme(winrt::Microsoft::UI::Xaml::ElementTheme value);

        /// <summary>
        /// 获取实际主题（根据系统将默认值解析为浅色或深色）
        /// </summary>
        static winrt::Microsoft::UI::Xaml::ElementTheme ActualTheme();

        /// <summary>
        /// 获取应用是否使用浅色主题
        /// </summary>
        static bool IsDarkTheme();

        /// <summary>
        /// 在应用程序启动时初始化主题
        /// </summary>
        static void Initialize();

        /// <summary>
        /// 更新特定窗口的主题
        /// </summary>
        static void UpdateThemeForWindow(winrt::Microsoft::UI::Xaml::Window const& window);

        /// <summary>
        /// 将当前主题保存到本地设置
        /// </summary>
        static void SaveThemeToSettings();

        /// <summary>
        /// 从本地设置加载主题
        /// </summary>
        static winrt::Microsoft::UI::Xaml::ElementTheme LoadThemeFromSettings();

        /// <summary>
        /// 将 ElementTheme 转换为字符串以供 UI 显示
        /// </summary>
        static winrt::hstring ThemeToString(winrt::Microsoft::UI::Xaml::ElementTheme theme);

        /// <summary>
        /// 将字符串转换为 ElementTheme
        /// </summary>
        static winrt::Microsoft::UI::Xaml::ElementTheme StringToTheme(winrt::hstring const& themeString);

    private:
        static winrt::Microsoft::UI::Xaml::ElementTheme s_rootTheme;
        static winrt::event_token s_actualThemeChangedToken;

        static constexpr const wchar_t* THEME_SETTING_KEY = L"AppTheme";

        /// <summary>
        /// 获取系统当前主题（浅色或深色）
        /// </summary>
        static winrt::Microsoft::UI::Xaml::ElementTheme GetSystemTheme();

        /// <summary>
        /// 更新给定窗口的标题栏主题
        /// </summary>
        static void UpdateTitleBarTheme(winrt::Microsoft::UI::Xaml::Window const& window);
    };
}