// Company: Icelabs Inc.

#pragma once

// Including some important header files.
#include "Common.h"
#include "Console.h"

namespace TkinterWindow
{
    class EXPORTIMPORT Border : public __TkinterWindow::Widget
    {
    private:
        // [ Starting ] - Variables.
        std::string __sClassName;
        int __nIndex;
        __TkinterWindow::Widget *__widget;
        TkinterWindow::Console __console;
        int __nXPosition = -1, __nYPosition = -1;
        int __nWidth = -1, __nHeight = -1;
        int __transparency;
        COLORREF __borderColor;
        __TkinterWindow::WINDOWTHEME *__windowTheme;
        bool __bIsUpdateBorder = true;
        // [ Ending ] - Variables.

        // [ Starting ] - Private Functions.
        static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
        LRESULT BorderProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
        void __CheckWarning(std::string sFunctionName);
        // [ Ending ] - Private Functions.

    public:
        // [ Starting ] - Variables.
        // [ Ending ] - Variables.

        // [ Starting ] - Functions.
        // [ Starting ] - Initializer.
        bool InitializeBorder(__TkinterWindow::Widget *lpWidget, std::string sClassName, int nIndex, __TkinterWindow::WINDOWTHEME * windowTheme);
        bool Initialize(__TkinterWindow::Widget *lpWidget, std::string sClassName, int nIndex, __TkinterWindow::WINDOWTHEME * windowTheme);
        // [ Ending ] - Initializer.

        // [ Starting ] - Transparency.
        bool SetBorderTransparency(int nTransparency);
        bool SetTransparency(int nTransparency);
        // [ Ending ] - Transparency.

        // [ Starting ] - Color Control.
        bool SetBorderColor(COLORREF color);
        bool SetBorderColor(int nRed, int nGreen, int nBlue);
        bool SetColor(COLORREF color);
        bool SetColor(int nRed, int nGreen, int nBlue);
        bool __SetBorderColor(COLORREF color);
        // [ Ending ] - Color Control.

        // [ Starting ] - Debugger control.
        bool EnableDebugger(void);
        bool DisableDebugger(void);
        // [ Ending ] - Debugger control.

        // [ Starting ] - border update.
        bool UpdateBorder();
        bool DisableUpdate();
        bool EnableUpdate();
        bool Update();
        // [ Ending ] - border update.
        // [ Ending ] - Functions.
    };
}
