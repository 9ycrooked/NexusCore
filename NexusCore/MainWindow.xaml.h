#pragma once

#include "MainWindow.g.h"

namespace winrt::NexusCore::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {
        MainWindow();

        void NavigationViewControl_ItemInvoked(winrt::Microsoft::UI::Xaml::Controls::NavigationView const& sender, 
            winrt::Microsoft::UI::Xaml::Controls::NavigationViewItemInvokedEventArgs const& args);

        void TitleBar_BackRequested(winrt::Microsoft::UI::Xaml::Controls::TitleBar const& sender, 
            winrt::Windows::Foundation::IInspectable const& args);
    private:
        // 初始化窗口设置的私有函数
        void InitWindowSettings();
        // 导航到指定页面的辅助函数
        void NavigateToPage(winrt::hstring const& pageName);
    };
}

namespace winrt::NexusCore::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}
