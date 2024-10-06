// Company: Icelabs Inc.

#pragma once

// Including some important header files.
#include "Common.h"
#include "Console.h"
#include <gdiplus.h>
#include "Border.h"
#include "Font.h"
#include "Event.h"

namespace TkinterWindow
{
    // Declaring the window class for the main window creation.
    class EXPORTIMPORT Window : public __TkinterWindow::Widget, public TkinterWindow::Event
    {
    private:
        // [ Starting ] - Variables.
        std::string __sClassName = "TkinterWindow-Window-Roboticela";
        std::string __sWindowName = "TkinterWindow-Window-Roboticela";
        std::string __sStatusBarText = "Ready...";
        TkinterWindow::Console __console;
        int __nXPosition = -1, __nYPosition = -1;
        int __nWidth = -1, __nHeight = -1;
        bool __bIsMoveSize = true;
        bool __bIsFocusedWindow = true;
        ULONG_PTR __gdiplusToken;
        __TkinterWindow::WINDOWTHEME __windowTheme;
        bool __bIsCloseButtonResizeWindow = false, __bOtherButtonResizeWindow = false;
        const int __nTitleBarButtonWidth = 42, __nTitleBarButtonHeight = 31;
        Gdiplus::GdiplusStartupInput __gdiplusStartupInput;
        TkinterWindow::Border __border1, __border2, __border3, __border4, __border5;
        TkinterWindow::Font __taskBarTitle;
        TkinterWindow::Font __statusBarFont;
        bool __bIsPaintChildWindows = true;
        bool __bIsCloseButtonHover = false, __bIsMaximizeButtonHover = false, __bIsMinimizeButtonHover = false, __bIsSettingButtonHover = false;
        bool __bIsShowStatusBar = true;
        bool __bIsDefaultWindowDestroyFunction = true;
        // [ Ending ] - Variables.

        // [ Starting ] - Private Functions.
        static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
        LRESULT WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
        void __CheckWarning(std::string sFunctionName);
        void __DrawCloseButton(HDC hDC, RECT windowRect, COLORREF borderPen);
        void __DrawMaximizeButton(HDC hDC, RECT windowRect);
        void __DrawMinimizeButton(HDC hDC, RECT windowRect);
        void __DrawSettingsButton(HDC hDC, RECT windowRect);
        RECT __GetButtonRect(RECT windowRect, int nRightSideMargin, int nLeftSideMargin);
        void __LoadWindowThemeFromTheme();
        // [ Ending ] - Private Functions.

    public:
        // [ Starting ] - Variables.
        // [ Ending ] - Variables.

        // [ Starting ] - Functions.
        // [ Starting ] - WindowClassInitializers.
        bool InitializeWindow(HINSTANCE hInstance, std::string sClassName);
        bool InitializeWindow(std::string sClassName, HINSTANCE hInstance);
        bool InitializeWindow(HINSTANCE hInstance);
        bool InitializeWindow(std::string sClassName);
        bool InitializeWindow(void);

        bool Initialize(HINSTANCE hInstance, std::string sClassName);
        bool Initialize(std::string sClassName, HINSTANCE hInstance);
        bool Initialize(HINSTANCE hInstance);
        bool Initialize(std::string sClassName);
        bool Initialize(void);
        // [ Ending ] - WindowClassInitializers.

        // [ Starting ] - StartMainLoop().
        bool StartMainLoop(int nMin, int nMax);
        bool StartMainLoop(void);

        bool MainLoop(int nMin, int nMax);
        bool MainLoop(void);
        // [ Ending ] - StartMainLoop().

        // [ Starting ] - SetWindowBorderRadius().
        bool SetWindowBorderRadius(int nRadius);
        bool SetBorderRadius(int nRadius);
        bool SetWindowBorderRoundness(int nRoundness);
        bool SetBorderRoundness(int nRoundness);
        // [ Ending ] - SetWindowBorderRadius().

        // [ Starting ] - SetWindowBorderFocusColor().
        bool SetWindowBorderFocusColor(int nRed, int nGreen, int nBlue);
        bool SetWindowBorderFocusColor(COLORREF color);

        bool SetBorderFocusColor(int nRed, int nGreen, int nBlue);
        bool SetBorderFocusColor(COLORREF color);
        // [ Ending ] - SetWindowBorderFocusColor().

        // [ Starting ] - SetWindowBorderUnfocusColor().
        bool SetWindowBorderUnfocusColor(int nRed, int nGreen, int nBlue);
        bool SetWindowBorderUnfocusColor(COLORREF color);

        bool SetBorderUnfocusColor(int nRed, int nGreen, int nBlue);
        bool SetBorderUnfocusColor(COLORREF color);
        // [ Ending ] - SetWindowBorderUnfocusColor().

        // [ Starting ] - SetWindowBorderOpacity() ranges from 0 to 255.
        bool SetWindowBorderOpacity(int nOpacity);
        bool SetBorderOpacity(int nOpacity);
        bool SetWindowShadowOpacity(int nOpacity);
        bool SetShadowOpacity(int nOpacity);
        // [ Ending ] - SetWindowBorderOpacity() ranges from 0 to 255.

        // [ Starting ] - SetWindowBackgroundColor().
        bool SetWindowBackgroundColor(int nRed, int nGreen, int nBlue);
        bool SetWindowBackgroundColor(COLORREF color);

        bool SetBackgroundColor(int nRed, int nGreen, int nBlue);
        bool SetBackgroundColor(COLORREF color);
        // [ Ending ] - SetWindowBackgrounbdColor().

        // [ Starting ] - Debugger control.
        bool EnableDebugger(void);
        bool DisableDebugger(void);
        // [ Ending ] - Debugger control.

        // [ Starting ] - Cursor controls.
        bool SetWindowCursor(std::string sCursorPath);
        bool SetCursor(std::string sCursorPath);

        bool SetWindowLeftResizeCursor(std::string sCursorPath);
        bool SetLeftResizeCursor(std::string sCursorPath);

        bool SetWindowRightResizeCursor(std::string sCursorPath);
        bool SetRightResizeCursor(std::string sCursorPath);

        bool SetWindowTopResizeCursor(std::string sCursorPath);
        bool SetTopResizeCursor(std::string sCursorPath);

        bool SetWindowBottomResizeCursor(std::string sCursorPath);
        bool SetBottomResizeCursor(std::string sCursorPath);

        bool SetWindowTopLeftResizeCursor(std::string sCursorPath);
        bool SetTopLeftResizeCursor(std::string sCursorPath);

        bool SetWindowTopRightResizeCursor(std::string sCursorPath);
        bool SetTopRightResizeCursor(std::string sCursorPath);

        bool SetWindowBottomLeftResizeCursor(std::string sCursorPath);
        bool SetBottomLeftResizeCursor(std::string sCursorPath);

        bool SetWindowBottomRightResizeCursor(std::string sCursorPath);
        bool SetBottomRightResizeCursor(std::string sCursorPath);
        // [ Starting ] - Cursor controls.

        // [ Starting ] - TitleBar Controls.
        bool SetWindowTitleBarBackgroundColor(int nRed, int nGreen, int nBlue);
        bool SetWindowTitleBarBackgroundColor(COLORREF color);
        bool SetTitleBarBackgroundColor(int nRed, int nGreen, int nBlue);
        bool SetTitleBarBackgroundColor(COLORREF color);

        bool SetWindowTitleBarTextFocusColor(int nRed, int nGreen, int nBlue);
        bool SetWindowTitleBarTextFocusColor(COLORREF color);
        bool SetTitleBarTextFocusColor(int nRed, int nGreen, int nBlue);
        bool SetTitleBarTextFocusColor(COLORREF color);

        bool SetWindowTitleBarTextUnfocusColor(int nRed, int nGreen, int nBlue);
        bool SetWindowTitleBarTextUnfocusColor(COLORREF color);
        bool SetTitleBarTextUnfocusColor(int nRed, int nGreen, int nBlue);
        bool SetTitleBarTextUnfocusColor(COLORREF color);
        // [ Ending ] - TitleBar Controls.

        // [ Starting ] - Title bar close button controls.
        bool SetWindowTitleBarCloseButtonHoverBackgroundColor(COLORREF color);
        bool SetWindowTitleBarCloseButtonHoverBackgroundColor(int nRed, int nGreen, int nBlue);
        bool SetTitleBarCloseButtonHoverBackgroundColor(COLORREF color);
        bool SetTitleBarCloseButtonHoverBackgroundColor(int nRed, int nGreen, int nBlue);

        bool SetWindowTitleBarCloseButtonFocusBackgroundColor(COLORREF color);
        bool SetWindowTitleBarCloseButtonFocusBackgroundColor(int nRed, int nGreen, int nBlue);
        bool SetTitleBarCloseButtonFocusBackgroundColor(COLORREF color);
        bool SetTitleBarCloseButtonFocusBackgroundColor(int nRed, int nGreen, int nBlue);

        bool SetWindowTitleBarCloseButtonUnfocusBackgroundColor(COLORREF color);
        bool SetWindowTitleBarCloseButtonUnfocusBackgroundColor(int nRed, int nGreen, int nBlue);
        bool SetTitleBarCloseButtonUnfocusBackgroundColor(COLORREF color);
        bool SetTitleBarCloseButtonUnfocusBackgroundColor(int nRed, int nGreen, int nBlue);

        bool SetWindowTitleBarCloseButtonHoverTextColor(COLORREF color);
        bool SetWindowTitleBarCloseButtonHoverTextColor(int nRed, int nGreen, int nBlue);
        bool SetTitleBarCloseButtonHoverTextColor(COLORREF color);
        bool SetTitleBarCloseButtonHoverTextColor(int nRed, int nGreen, int nBlue);

        bool SetWindowTitleBarCloseButtonFocusTextColor(COLORREF color);
        bool SetWindowTitleBarCloseButtonFocusTextColor(int nRed, int nGreen, int nBlue);
        bool SetTitleBarCloseButtonFocusTextColor(COLORREF color);
        bool SetTitleBarCloseButtonFocusTextColor(int nRed, int nGreen, int nBlue);

        bool SetWindowTitleBarCloseButtonUnfocusTextColor(COLORREF color);
        bool SetWindowTitleBarCloseButtonUnfocusTextColor(int nRed, int nGreen, int nBlue);
        bool SetTitleBarCloseButtonUnfocusTextColor(COLORREF color);
        bool SetTitleBarCloseButtonUnfocusTextColor(int nRed, int nGreen, int nBlue);
        // [ Ending ] - Title bar close button controls.

        // [ Starting ] - Title bar maximize button controls.
        bool SetWindowTitleBarMaximizeButtonHoverBackgroundColor(COLORREF color);
        bool SetWindowTitleBarMaximizeButtonHoverBackgroundColor(int nRed, int nGreen, int nBlue);
        bool SetTitleBarMaximizeButtonHoverBackgroundColor(COLORREF color);
        bool SetTitleBarMaximizeButtonHoverBackgroundColor(int nRed, int nGreen, int nBlue);

        bool SetWindowTitleBarMaximizeButtonFocusBackgroundColor(COLORREF color);
        bool SetWindowTitleBarMaximizeButtonFocusBackgroundColor(int nRed, int nGreen, int nBlue);
        bool SetTitleBarMaximizeButtonFocusBackgroundColor(COLORREF color);
        bool SetTitleBarMaximizeButtonFocusBackgroundColor(int nRed, int nGreen, int nBlue);

        bool SetWindowTitleBarMaximizeButtonUnfocusBackgroundColor(COLORREF color);
        bool SetWindowTitleBarMaximizeButtonUnfocusBackgroundColor(int nRed, int nGreen, int nBlue);
        bool SetTitleBarMaximizeButtonUnfocusBackgroundColor(COLORREF color);
        bool SetTitleBarMaximizeButtonUnfocusBackgroundColor(int nRed, int nGreen, int nBlue);

        bool SetWindowTitleBarMaximizeButtonHoverTextColor(COLORREF color);
        bool SetWindowTitleBarMaximizeButtonHoverTextColor(int nRed, int nGreen, int nBlue);
        bool SetTitleBarMaximizeButtonHoverTextColor(COLORREF color);
        bool SetTitleBarMaximizeButtonHoverTextColor(int nRed, int nGreen, int nBlue);

        bool SetWindowTitleBarMaximizeButtonFocusTextColor(COLORREF color);
        bool SetWindowTitleBarMaximizeButtonFocusTextColor(int nRed, int nGreen, int nBlue);
        bool SetTitleBarMaximizeButtonFocusTextColor(COLORREF color);
        bool SetTitleBarMaximizeButtonFocusTextColor(int nRed, int nGreen, int nBlue);

        bool SetWindowTitleBarMaximizeButtonUnfocusTextColor(COLORREF color);
        bool SetWindowTitleBarMaximizeButtonUnfocusTextColor(int nRed, int nGreen, int nBlue);
        bool SetTitleBarMaximizeButtonUnfocusTextColor(COLORREF color);
        bool SetTitleBarMaximizeButtonUnfocusTextColor(int nRed, int nGreen, int nBlue);
        // [ Ending ] - Title bar maximize button controls.

        // [ Starting ] - Title bar minimize button controls.
        bool SetWindowTitleBarMinimizeButtonHoverBackgroundColor(COLORREF color);
        bool SetWindowTitleBarMinimizeButtonHoverBackgroundColor(int nRed, int nGreen, int nBlue);
        bool SetTitleBarMinimizeButtonHoverBackgroundColor(COLORREF color);
        bool SetTitleBarMinimizeButtonHoverBackgroundColor(int nRed, int nGreen, int nBlue);

        bool SetWindowTitleBarMinimizeButtonFocusBackgroundColor(COLORREF color);
        bool SetWindowTitleBarMinimizeButtonFocusBackgroundColor(int nRed, int nGreen, int nBlue);
        bool SetTitleBarMinimizeButtonFocusBackgroundColor(COLORREF color);
        bool SetTitleBarMinimizeButtonFocusBackgroundColor(int nRed, int nGreen, int nBlue);

        bool SetWindowTitleBarMinimizeButtonUnfocusBackgroundColor(COLORREF color);
        bool SetWindowTitleBarMinimizeButtonUnfocusBackgroundColor(int nRed, int nGreen, int nBlue);
        bool SetTitleBarMinimizeButtonUnfocusBackgroundColor(COLORREF color);
        bool SetTitleBarMinimizeButtonUnfocusBackgroundColor(int nRed, int nGreen, int nBlue);

        bool SetWindowTitleBarMinimizeButtonHoverTextColor(COLORREF color);
        bool SetWindowTitleBarMinimizeButtonHoverTextColor(int nRed, int nGreen, int nBlue);
        bool SetTitleBarMinimizeButtonHoverTextColor(COLORREF color);
        bool SetTitleBarMinimizeButtonHoverTextColor(int nRed, int nGreen, int nBlue);

        bool SetWindowTitleBarMinimizeButtonFocusTextColor(COLORREF color);
        bool SetWindowTitleBarMinimizeButtonFocusTextColor(int nRed, int nGreen, int nBlue);
        bool SetTitleBarMinimizeButtonFocusTextColor(COLORREF color);
        bool SetTitleBarMinimizeButtonFocusTextColor(int nRed, int nGreen, int nBlue);

        bool SetWindowTitleBarMinimizeButtonUnfocusTextColor(COLORREF color);
        bool SetWindowTitleBarMinimizeButtonUnfocusTextColor(int nRed, int nGreen, int nBlue);
        bool SetTitleBarMinimizeButtonUnfocusTextColor(COLORREF color);
        bool SetTitleBarMinimizeButtonUnfocusTextColor(int nRed, int nGreen, int nBlue);
        // [ Ending ] - Title bar minimize button controls.

        // [ Starting ] - Title bar setting button controls.
        bool SetWindowTitleBarSettingButtonHoverBackgroundColor(COLORREF color);
        bool SetWindowTitleBarSettingButtonHoverBackgroundColor(int nRed, int nGreen, int nBlue);
        bool SetTitleBarSettingButtonHoverBackgroundColor(COLORREF color);
        bool SetTitleBarSettingButtonHoverBackgroundColor(int nRed, int nGreen, int nBlue);

        bool SetWindowTitleBarSettingButtonFocusBackgroundColor(COLORREF color);
        bool SetWindowTitleBarSettingButtonFocusBackgroundColor(int nRed, int nGreen, int nBlue);
        bool SetTitleBarSettingButtonFocusBackgroundColor(COLORREF color);
        bool SetTitleBarSettingButtonFocusBackgroundColor(int nRed, int nGreen, int nBlue);

        bool SetWindowTitleBarSettingButtonUnfocusBackgroundColor(COLORREF color);
        bool SetWindowTitleBarSettingButtonUnfocusBackgroundColor(int nRed, int nGreen, int nBlue);
        bool SetTitleBarSettingButtonUnfocusBackgroundColor(COLORREF color);
        bool SetTitleBarSettingButtonUnfocusBackgroundColor(int nRed, int nGreen, int nBlue);

        bool SetWindowTitleBarSettingButtonHoverTextColor(COLORREF color);
        bool SetWindowTitleBarSettingButtonHoverTextColor(int nRed, int nGreen, int nBlue);
        bool SetTitleBarSettingButtonHoverTextColor(COLORREF color);
        bool SetTitleBarSettingButtonHoverTextColor(int nRed, int nGreen, int nBlue);

        bool SetWindowTitleBarSettingButtonFocusTextColor(COLORREF color);
        bool SetWindowTitleBarSettingButtonFocusTextColor(int nRed, int nGreen, int nBlue);
        bool SetTitleBarSettingButtonFocusTextColor(COLORREF color);
        bool SetTitleBarSettingButtonFocusTextColor(int nRed, int nGreen, int nBlue);

        bool SetWindowTitleBarSettingButtonUnfocusTextColor(COLORREF color);
        bool SetWindowTitleBarSettingButtonUnfocusTextColor(int nRed, int nGreen, int nBlue);
        bool SetTitleBarSettingButtonUnfocusTextColor(COLORREF color);
        bool SetTitleBarSettingButtonUnfocusTextColor(int nRed, int nGreen, int nBlue);
        // [ Ending ] - Title bar setting button controls.

        // [ Starting ] - Icon Controls.
        bool SetWindowTaskBarIcon(std::string sIconPath);
        bool SetTaskBarIcon(std::string sIconPath);
        // [ Ending ] - Icon Controls.

        // [ Starting ] - Window name controls.
        bool SetWindowTitle(std::string sWindowName);
        bool SetTitle(std::string sWindowName);

        bool SetWindowCaption(std::string sWindowName);
        bool SetCaption(std::string sWindowName);
        // [ Ending ] - Window name controls.

        // [ Starting ] - Status bar controls.
        bool SetWindowStatusBarText(std::string sText);
        bool SetStatusBarText(std::string sText);

        bool HideWindowStatusBar();
        bool HideStatusBar();

        bool ShowWindowStatusBar();
        bool ShowStatusBar();
        // [ Ending ] - status bar controls.

        // [ Starting ] - Status bar coloring.
        bool SetWindowStatusBarBackgroundColor(COLORREF color);
        bool SetWindowStatusBarBackgroundColor(int nRed, int nGreen, int nBlue);
        bool SetStatusBarBackgroundColor(COLORREF color);
        bool SetStatusBarBackgroundColor(int nRed, int nGreen, int nBlue);

        bool SetWindowStatusBarTextFocusColor(COLORREF color);
        bool SetWindowStatusBarTextFocusColor(int nRed, int nGreen, int nBlue);
        bool SetStatusBarTextFocusColor(COLORREF color);
        bool SetStatusBarTextFocusColor(int nRed, int nGreen, int nBlue);

        bool SetWindowStatusBarTextUnfocusColor(COLORREF color);
        bool SetWindowStatusBarTextUnfocusColor(int nRed, int nGreen, int nBlue);
        bool SetStatusBarTextUnfocusColor(COLORREF color);
        bool SetStatusBarTextUnfocusColor(int nRed, int nGreen, int nBlue);
        // [ Ending ] - Status bar coloring.

        // [ Starting ] - destroy window functions.
        bool DestroyWindow(void);
        bool Destroy(void);

        bool SetDefaultWindowDestroyFunction(void);
        bool SetDefaultDestroyFunction(void);

        bool DisableDefaultWindowDestroyFunction(void);
        bool DisableDefaultDestroyFunction(void);
        // [ Ending ] - destroy window functions.

        void __SetChildWindowRepainter(bool bPainter);
        // [ Ending ] - Functions.
    };
}
