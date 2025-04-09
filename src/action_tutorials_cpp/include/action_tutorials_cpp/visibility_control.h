#ifndef ACTION_TUTORIALS_CPP__VISIBILITY_CONTROL_H_
#define ACTION_TUTORIALS_CPP__VISIBILITY_CONTROL_H_
//这段代码用于确保 C++ 代码 在C 语言编译器下也能正确编译，避免 C++ 名字修饰（Name Mangling）的问题。
#ifdef __cplusplus
extern "C"
{
#endif

// 这段 visibility_control.h 代码的主要用途是 控制 C++ 库的符号可见性，确保在不同平台
//（Windows、Linux、macOS）上正确编译和使用 共享库（动态库，.so、.dll、.dylib），主要用于 ROS 2 以及 C++ 动态库开发。
// 这段逻辑参考了 GCC 官方 Wiki 上的示例：https://gcc.gnu.org/wiki/Visibility

#if defined _WIN32 || defined __CYGWIN__
  // Windows 或 Cygwin 平台
  #ifdef __GNUC__
    // 在 Windows 平台上，GCC 使用 `__attribute__ ((dllexport))` 和 `__attribute__ ((dllimport))`
    #define ACTION_TUTORIALS_CPP_EXPORT __attribute__ ((dllexport))  // 导出符号
    #define ACTION_TUTORIALS_CPP_IMPORT __attribute__ ((dllimport))  // 导入符号
  #else
    // 在 MSVC（Visual Studio 编译器）下，使用 `__declspec(dllexport)` 和 `__declspec(dllimport)`
    #define ACTION_TUTORIALS_CPP_EXPORT __declspec(dllexport)  // 导出符号
    #define ACTION_TUTORIALS_CPP_IMPORT __declspec(dllimport)  // 导入符号
  #endif

  // 当构建动态库（定义了 `ACTION_TUTORIALS_CPP_BUILDING_DLL`）时，使用 `EXPORT` 导出符号
  // 否则，使用 `IMPORT` 以便其他项目可以使用该库
  #ifdef ACTION_TUTORIALS_CPP_BUILDING_DLL
    #define ACTION_TUTORIALS_CPP_PUBLIC ACTION_TUTORIALS_CPP_EXPORT
  #else
    #define ACTION_TUTORIALS_CPP_PUBLIC ACTION_TUTORIALS_CPP_IMPORT
  #endif

  // `PUBLIC_TYPE` 用于类和结构体的可见性定义
  #define ACTION_TUTORIALS_CPP_PUBLIC_TYPE ACTION_TUTORIALS_CPP_PUBLIC

  // `LOCAL` 定义为空，在 Windows 平台上不需要额外的隐藏属性
  #define ACTION_TUTORIALS_CPP_LOCAL

#else
  // Linux/macOS 平台
  // `visibility("default")` 允许符号在共享库中可见，等同于 Windows 的 `dllexport`
  #define ACTION_TUTORIALS_CPP_EXPORT __attribute__ ((visibility("default")))
  #define ACTION_TUTORIALS_CPP_IMPORT  // Linux/macOS 不需要 `import`，因此为空

  // GCC 4.0 及以上支持 `visibility` 属性
  #if __GNUC__ >= 4
    #define ACTION_TUTORIALS_CPP_PUBLIC __attribute__ ((visibility("default")))  // 公开符号
    #define ACTION_TUTORIALS_CPP_LOCAL  __attribute__ ((visibility("hidden")))   // 隐藏符号
  #else
    // 旧版 GCC（4.0 以下）不支持 `visibility`，直接定义为空
    #define ACTION_TUTORIALS_CPP_PUBLIC
    #define ACTION_TUTORIALS_CPP_LOCAL
  #endif

  // `PUBLIC_TYPE` 在 Linux/macOS 平台上等同于 `PUBLIC`
  #define ACTION_TUTORIALS_CPP_PUBLIC_TYPE ACTION_TUTORIALS_CPP_PUBLIC
#endif
//关闭 extern "C" 以恢复 C++ 作用域。
#ifdef __cplusplus
}
#endif

#endif  // ACTION_TUTORIALS_CPP__VISIBILITY_CONTROL_H_
