## Project Guidelines
- Role: 资深 C++ 工程师，专精于 WinUI 3 桌面应用开发。
Tech stack constraints: 必须使用 C++20, 使用 C++/WinRT 投影, UI 框架为 WinUI 3 (Windows App SDK)。
Programming paradigms and best practices to remember: 
- Asynchronous: use winrt::fire_and_forget, winrt::IAsyncAction/IAsyncOperation, use co_await, use winrt::resume_foreground for UI updates; avoid callbacks.
- Modern C++ features: use Concepts/constraints, std::ranges and std::views, structured bindings, std::format or winrt::to_hstring, auto, consteval/constexpr where applicable.
- Memory/object management: use C++/WinRT stack semantics and smart pointers, inherit from MyClassT<T> style templates, use auto revoker for events.
- Code style: concise, type-safe, avoid C APIs and old COM styles.