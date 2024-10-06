// Company: Icelabs Inc.

// Including some important header files.
#include "Border.h"

// Using some important libraries.
#pragma comment(lib, "Build-Data\\Console.lib")

namespace TkinterWindow
{
    // [ Starting ] - Initializer.
    bool Border::InitializeBorder(__TkinterWindow::Widget *lpWidget, std::string sClassName, int nIndex, __TkinterWindow::WINDOWTHEME * windowTheme)
    {
        // Helps to initialze the border for the window.
        __widget = lpWidget;
        __sClassName = sClassName;
        __sClassName += "-";
        __sClassName += std::to_string(nIndex);
        __nIndex = nIndex;
        __windowTheme = windowTheme;

        // Disabiling the error check for console.
        __console.DisableErrorCheck();

        // Setting the class object and name.
        __console.SetLoggerClassObject("Border");
        __console.SetloggerClassName(__sClassName);

        if (sClassName.length() > 256)
        {
            __console.Log("InitializeBorder", "Error: The length of the class name is greater than 256 letters.");
            return false;
        }

        __theme = __widget->__theme;
        __hInstance = __widget->__hInstance;

        // Loading the tkinter window configuration file.
        __console.Log("InitializeBorder", "Getting the information of the border from parent window.");

        RECT windowRect;
        GetWindowRect(__widget->__windowHandle, &windowRect);
        __nXPosition = windowRect.left - nIndex;
        __nYPosition = windowRect.top - nIndex;
        __nHeight = windowRect.bottom - windowRect.top + (nIndex * 2);
        __nWidth = windowRect.right - windowRect.left + (nIndex * 2);

        // Declaring the window class.
        __console.Log("InitializeBorder", "Initializing the class for the border.");
        WNDCLASSEXA borderClass = {0};
        borderClass.cbSize = sizeof(WNDCLASSEXA);
        borderClass.cbClsExtra = 0;
        borderClass.hbrBackground = NULL;
        borderClass.cbWndExtra = 0;
        borderClass.hCursor = NULL;
        borderClass.hIcon = NULL;
        borderClass.hIconSm = NULL;
        borderClass.hInstance = __hInstance;
        borderClass.lpfnWndProc = WndProc;
        borderClass.lpszClassName = __sClassName.c_str();
        borderClass.lpszMenuName = 0;
        borderClass.style = CS_HREDRAW | CS_VREDRAW;

        __console.Log("InitializeBorder", "Registering the class of the border.");
        if (!RegisterClassExA(&borderClass))
        {
            __console.Log("InitializeBorder", "Error: Registeration of the border class failed.");
            return false;
        }

        // Creating the window.
        __console.Log("InitializeBorder", "Creating the border window. X: %d, Y: %d, Width: %d, Height: %d", __nXPosition, __nYPosition, __nWidth, __nHeight);

        __windowHandle = CreateWindowExA(WS_EX_TOOLWINDOW | WS_EX_LAYERED, __sClassName.c_str(), __sClassName.c_str(), WS_OVERLAPPEDWINDOW, __nXPosition, __nYPosition, __nWidth, __nHeight, __widget->__windowHandle, 0, __hInstance, this);

        if (__windowHandle == NULL)
        {
            __console.Log("InitializeBorder", "Error: Creating of the border window failed.");

            return false;
        }

        // Setting the transparency.
        SetLayeredWindowAttributes(__windowHandle, __theme->transparentColor, __transparency, LWA_COLORKEY | LWA_ALPHA);

        // Showing the window
        ShowWindow(__windowHandle, SW_SHOW);
        UpdateWindow(__windowHandle);

        return true;
    }

    bool Border::Initialize(__TkinterWindow::Widget *lpWidget, std::string sClassName, int nIndex, __TkinterWindow::WINDOWTHEME * windowTheme)
    {
        // Same as InitializeBorder.
        return InitializeBorder(lpWidget, sClassName, nIndex, windowTheme);
    }
    // [ Ending ] - Initializer.

    // [ Starting ] - Transparency.
    bool Border::SetBorderTransparency(int nTransparency)
    {
        __CheckWarning("SetBorderTransparency");

        // Helps to set the transparency.
        __console.Log("SetBorderTransparency", "Setting the transparency of the border. Transparency: %d", nTransparency);
        __transparency = nTransparency;

        if (__windowHandle != NULL)
        {
            SetLayeredWindowAttributes(__windowHandle, __theme->transparentColor, __transparency, LWA_ALPHA | LWA_COLORKEY);
        }

        return true;
    }

    bool Border::SetTransparency(int nTransparency)
    {
        // Same as SetBorderTransparency.
        return SetBorderTransparency(nTransparency);
    }
    // [ Ending ] - Transparency.

    // [ Starting ] - Color Control.
    bool Border::SetBorderColor(COLORREF color)
    {
        __CheckWarning("SetBorderColor");

        // Helps to set the border color with colorref.
        __console.Log("SetBorderColor", "Setting the color for the border. Color: %d, %d, %d.", GetRValue(color), GetGValue(color), GetBValue(color));
        __borderColor = color;

        if (__windowHandle != NULL)
        {
            InvalidateRect(__windowHandle, NULL, TRUE);
        }

        return true;
    }

    bool Border::SetBorderColor(int nRed, int nGreen, int nBlue)
    {
        __CheckWarning("SetBorderColor");

        // Helps to set the border color with values.
        __console.Log("SetBorderColor", "Setting the color for the border. Color: %d, %d, %d.", nRed, nGreen, nBlue);
        __borderColor = RGB(nRed, nGreen, nBlue);

        if (__windowHandle != NULL)
        {
            InvalidateRect(__windowHandle, NULL, TRUE);
        }

        return true;
    }

    bool Border::SetColor(COLORREF color)
    {
        // Same as SetBorderColor.
        return SetBorderColor(color);
    }
    bool Border::SetColor(int nRed, int nGreen, int nBlue)
    {
        // Same as SetBorderColor.
        return SetBorderColor(nRed, nGreen, nBlue);
    }

    bool Border::__SetBorderColor(COLORREF color)
    {
        __CheckWarning("SetBorderColor");

        // Helps to set the border color with colorref.
        __borderColor = color;

        if (__windowHandle != NULL)
        {
            InvalidateRect(__windowHandle, NULL, TRUE);
        }

        return true;
    }
    // [ Ending ] - Color Control.

    // [ Starting ] - Debugger control.
    bool Border::EnableDebugger(void)
    {
        __CheckWarning("EnableDebugger");
        // Helps to enable the debugger.
        return __console.EnableDebugger();
    }

    bool Border::DisableDebugger(void)
    {
        __CheckWarning("DisableDebugger");
        // Helps to disable the debugger.
        return __console.DisableDebugger();
    }
    // [ Ending ] - Debugger control.

    // [ Starting ] - border update.
    bool Border::UpdateBorder()
    {
        __CheckWarning("UpdateBorder");

        // Helps to update the border configuration.
        return SendMessageA(__windowHandle, WM_SIZE, NULL, NULL);
    }

    bool Border::DisableUpdate()
    {
        __CheckWarning("DisableUpdate");

        // Helps to disable the border updation.
        __bIsUpdateBorder = false;

        return true;
    }
    bool Border::EnableUpdate()
    {
        __CheckWarning("EnableUpdate");

        // Helps to enable the border updation.
        __bIsUpdateBorder = true;

        return true;
    }

    bool Border::Update()
    {
        // Same as UpdateBorder.
        return UpdateBorder();
    }
    // [ Ending ] - border update.

    // [ Starting ] - Private Functions.
    LRESULT Border::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        // Assigning the procedure to the class procedure.

        if (message == WM_NCCREATE)
        {
            // Setting the class as user data.
            CREATESTRUCT *lParamStruct = (CREATESTRUCT *)lParam;
            TkinterWindow::Border *lpLabelClass = (TkinterWindow::Border *)lParamStruct->lpCreateParams;
            SetWindowLongPtrA(hWnd, GWLP_USERDATA, (LONG_PTR)lpLabelClass);

            return DefWindowProcA(hWnd, message, wParam, lParam);
        }
        else
        {
            // Getting the class as user data that stored in NC_CREATE.
            TkinterWindow::Border *windowObject = reinterpret_cast<TkinterWindow::Border *>(static_cast<LONG_PTR>(GetWindowLongPtrA(hWnd, GWLP_USERDATA)));

            if (windowObject)
            {
                // Returning and calling to the class procedure.

                return windowObject->BorderProcedure(hWnd, message, wParam, lParam);
            }
            else
            {
                // Returning and calling to the default window procedure.
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }

        return 0;
    }

    LRESULT Border::BorderProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        switch (message)
        {
        case WM_NCCALCSIZE:
        {
            // Removing the background.
            if (wParam == TRUE)
            {
                return 0;
            }
        }

        case WM_PAINT:
        {
            if (__bIsUpdateBorder)
            {
                // Painting the window.
                PAINTSTRUCT paintStruct;
                HDC hDC = BeginPaint(hWnd, &paintStruct);

                // Painting with transparent brush.
                HBRUSH transparentBrush = CreateSolidBrush(__theme->transparentColor);
                FillRect(hDC, &paintStruct.rcPaint, transparentBrush);

                // Painting the border.
                HPEN borderPen = CreatePen(PS_SOLID, 1, __borderColor);
                SelectObject(hDC, borderPen);
                SelectObject(hDC, transparentBrush);
                RoundRect(hDC, 0, 0, paintStruct.rcPaint.right - paintStruct.rcPaint.left, paintStruct.rcPaint.bottom - paintStruct.rcPaint.top, __windowTheme->windowBorderRadius, __windowTheme->windowBorderRadius);
                DeleteObject(transparentBrush);
                DeleteObject(borderPen);

                EndPaint(hWnd, &paintStruct);
            }
            break;
        }

        case WM_SIZE:
        {
            if (__bIsUpdateBorder)
            {
                // Resizing the borders.
                RECT windowRect;
                GetWindowRect(__widget->__windowHandle, &windowRect);

                SetWindowPos(hWnd, NULL, windowRect.left - __nIndex, windowRect.top - __nIndex, windowRect.right - windowRect.left + (__nIndex * 2), windowRect.bottom - windowRect.top + (__nIndex * 2), 0);
                InvalidateRect(hWnd, NULL, TRUE);
            }
            break;
        }

        default:
        {
            return DefWindowProc(hWnd, message, wParam, lParam);
            break;
        }
        }

        return 0;
    }

    void Border::__CheckWarning(std::string sFunctionName)
    {
        if (__windowHandle == NULL)
        {
            __console.Log(sFunctionName, "Warning: The function is called before the initalization. It can lead to some major problems.");
        }
    }
    // [ Ending ] - Private Functions.
}
