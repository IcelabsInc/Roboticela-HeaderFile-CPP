// Created by Muhammad Shahsawar
// Company: Muhamamd Technology

#pragma once

// Including some header files.
#include <Windows.h>
#include <string>

// using some libraries
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")

// Declaration EXPORTFUNCTION for dll exportation.
#ifdef BUILD_DLL
#define EXPORTIMPORT __declspec(dllexport)
#else
#define EXPORTIMPORT __declspec(dllimport)
#endif

namespace __TkinterWindow
{
    // Declaring a class for common interpretation.
    typedef struct
    {
        COLORREF labelBackgroundColor = NULL;
        COLORREF labelTextColor = NULL;
    } LABELTHEME;
    
    typedef struct
    {
        int windowBorderRadius = -1;
        COLORREF windowBorderFocusColor = NULL, windowBorderUnfocusColor = NULL;
        int windowBorderOpacity = -1;

        COLORREF windowBackgroundColor = NULL;

        HCURSOR windowCursor = NULL;
        HCURSOR windowLeftResizeCursor = NULL;
        HCURSOR windowRightResizeCursor = NULL;
        HCURSOR windowTopResizeCursor = NULL;
        HCURSOR windowBottomResizeCursor = NULL;
        HCURSOR windowTopLeftResizeCursor = NULL;
        HCURSOR windowTopRightResizeCursor = NULL;
        HCURSOR windowBottomLeftResizeCursor = NULL;
        HCURSOR windowBottomRightResizeCursor = NULL;

        COLORREF windowTitleBarBackgroundColor = NULL;

        HICON windowTaskBarIcon = NULL;
        HICON windowFocusIcon = NULL, windowUnfocusIcon = NULL;

        COLORREF windowTitleBarTextFocusColor = NULL, windowTitleBarTextUnfocusColor = NULL;

        COLORREF windowTitleBarCloseButtonHoverBackgroundColor = NULL, windowTitleBarCloseButtonFocusBackgroundColor = NULL, windowTitleBarCloseButtonUnfocusBackgroundColor = NULL;
        COLORREF windowTitleBarCloseButtonHoverTextColor = NULL, windowTitleBarCloseButtonFocusTextColor = NULL, windowTitleBarCloseButtonUnfocusTextColor = NULL;
   
        COLORREF windowTitleBarMaximizeButtonHoverBackgroundColor = NULL, windowTitleBarMaximizeButtonFocusBackgroundColor = NULL, windowTitleBarMaximizeButtonUnfocusBackgroundColor = NULL;
        COLORREF windowTitleBarMaximizeButtonHoverTextColor = NULL, windowTitleBarMaximizeButtonFocusTextColor = NULL, windowTitleBarMaximizeButtonUnfocusTextColor = NULL;
   
        COLORREF windowTitleBarMinimizeButtonHoverBackgroundColor = NULL, windowTitleBarMinimizeButtonFocusBackgroundColor = NULL, windowTitleBarMinimizeButtonUnfocusBackgroundColor = NULL;
        COLORREF windowTitleBarMinimizeButtonHoverTextColor = NULL, windowTitleBarMinimizeButtonFocusTextColor = NULL, windowTitleBarMinimizeButtonUnfocusTextColor = NULL;
   
        COLORREF windowTitleBarSettingButtonHoverBackgroundColor = NULL, windowTitleBarSettingButtonFocusBackgroundColor = NULL, windowTitleBarSettingButtonUnfocusBackgroundColor = NULL;
        COLORREF windowTitleBarSettingButtonHoverTextColor = NULL, windowTitleBarSettingButtonFocusTextColor = NULL, windowTitleBarSettingButtonUnfocusTextColor = NULL;
        
        COLORREF windowStatusBarBackgroundColor = NULL;
        COLORREF windowStatusBarTextFocusColor = NULL, windowStatusBarTextUnfocusColor = NULL;
    } WINDOWTHEME;

    typedef struct
    {
        // Common objects.
        COLORREF transparentColor;
        COLORREF widgetTransparentColor;
        int __positionDifference = 0;
        const int __nTitleBarHeight = 31;
        const int __nStatusBarHeight = 22;
        // Common Objects.

        WINDOWTHEME windowTheme;
        LABELTHEME labelTheme;
    } THEME;

    class Widget
    {
    public:
        HWND __windowHandle = NULL;
        HINSTANCE __hInstance;
        THEME *__theme;
    };
}
