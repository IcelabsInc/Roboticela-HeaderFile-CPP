// Company: Munammad Technology.

// Including the header files.
#include "Window.h"
#include <fstream>
#include <Windowsx.h>

// using some important libraries.
#pragma comment(lib, "Gdiplus.lib")
#pragma comment(lib, "Build-Data\\Console.lib")
#pragma comment(lib, "Build-Data\\Border.lib")
#pragma comment(lib, "Build-Data\\Font.lib")
#pragma comment(lib, "Build-Data\\Event.lib")

namespace __TkinterWindow
{
    void ActivateWindow(HWND hWnd)
    {
        // Helps to fix the focus and unfocus problem.
        Sleep(500);
        SendMessageA(hWnd, WM_ACTIVATE, WA_INACTIVE, NULL);
        ShowWindow(hWnd, SW_NORMAL);
    }

    void UpdateChildWindows(TkinterWindow::Window *windowObject)
    {
        // Helps to repaint all the child windows.
        Sleep(1000);

        for (HWND hWndChild = GetWindow(windowObject->__windowHandle, GW_CHILD); hWndChild != NULL; hWndChild = GetNextWindow(hWndChild, GW_HWNDNEXT))
        {
            SendMessageA(hWndChild, WM_SIZE, NULL, NULL);
        }

        windowObject->__SetChildWindowRepainter(true);
    }

    void SetDefaultConfiguration(TkinterWindow::Console *console)
    {
        // Setting the default configuration.
        console->Log("SetDefaultConfiguration", "Setting the default configuration for the TkinterWindow.");
    }

    std::string GetConfigurationValue(std::string value, TkinterWindow::Console *console)
    {
        // Getting the value from the configuration file.
        console->Log("GetConfigurationValue", "Getting the configuration value. Value: %s.", value.c_str());

        std::ifstream existFileCheck("TkinterWindow.Config");

        if (!existFileCheck.is_open())
        {
            SetDefaultConfiguration(console);
        }
        else
        {
            existFileCheck.close();
        }

        std::ifstream filein("TkinterWindow.Config");

        for (std::string line; std::getline(filein, line);)
        {
            if (line.find(value) != std::string::npos)
            {
                std::string value = line.substr(line.find("=") + 1);
                filein.close();

                return value;
            }
        }

        console->Log("GetConfigurationValue", "Error: Failed to get the configuration value. Value: %s", value.c_str());

        return "0";
    }

    std::string GetThemeConfigValue(std::string value, TkinterWindow::Console *console)
    {
        // Getting the value of the theme.
        console->Log("GetThemeConfigValue", "Getting the theme configuration value. Value: %s", value.c_str());
        std::ifstream themeFile("Themes\\" + GetConfigurationValue("Theme", console) + "\\" + GetConfigurationValue("Theme", console) + ".Config", std::ios::in);

        if (!themeFile.is_open())
        {
            console->Log("GetThemeConfigValue", "Error: Failed to get the theme file.");
            return "";
        }

        for (std::string line; std::getline(themeFile, line);)
        {
            if (line.find(value) != std::string::npos)
            {
                std::string value = line.substr(line.find("=") + 1);
                themeFile.close();

                return value;
            }
        }

        if ("Themes\\" + GetConfigurationValue("Theme", console) + "\\" + GetConfigurationValue("Theme", console) + ".Config" == "Themes\\RandomTheme.Config")
        {
            return "";
        }
        else
        {
            std::ifstream themeFileD("Themes\\" + GetConfigurationValue("Theme", console) + "\\" + GetConfigurationValue("Theme", console) + ".Config", std::ios::in);

            if (!themeFileD.is_open())
            {
                console->Log("GetThemeConfigValue", "Error: Failed to get the theme file.");
                return "";
            }

            for (std::string line; std::getline(themeFileD, line);)
            {
                if (line.find(value) != std::string::npos)
                {
                    std::string value = line.substr(line.find("=") + 1);
                    themeFileD.close();

                    return value;
                }
            }

            console->Log("GetThemeConfigurationValue", "Error: Failed to get the theme configuration value. Value: %s", value.c_str());

            return "";
        }
    }

    COLORREF GetColorFromText(std::string text, TkinterWindow::Console *console)
    {
        // Getting the color from the text.
        console->Log("GetColorFromText", "Getting the color from the text. Text: %s", text.c_str());

        if (text.find(",") != std::string::npos)
        {
            std::string color = text.substr(text.find("=") + 1);
            std::string red = color.substr(0, color.find(","));
            color.replace(0, color.find(",") + 1, "");
            std::string green = color.substr(0, color.find(","));
            color.replace(0, color.find(",") + 1, "");
            std::string blue = color.substr(0, color.length());
            int redInt = std::stoi(red);
            int greenInt = std::stoi(green);
            int blueInt = std::stoi(blue);

            return RGB(redInt, greenInt, blueInt);
        }

        console->Log("GetColorFromText", "Error: Failed the getting of color from the text. Text: %s", text.c_str());
        return RGB(0, 0, 0);
    }

    HICON LoadImageFromFile(std::string path, TkinterWindow::Console *console)
    {
        // Important for the loading of the icon from a local file.
        console->Log("LoadImageFromFile", "Loading the image from the path. Path: %s.", path.c_str());

        HICON image = NULL;
        std::wstring pathWString = std::wstring(path.begin(), path.end());
        const WCHAR *pathWChar = pathWString.c_str();
        Gdiplus::Bitmap bitmap(pathWChar, false);
        bitmap.GetHICON(&image);

        if (image == NULL)
        {
            console->Log("LoadImageFromFile", "Error: Loading of the image from the path is failed. Path: %s.", path.c_str());
        }

        return image;
    }

    void LoadThemeData(__TkinterWindow::THEME *theme, HINSTANCE hInstance, TkinterWindow::Console *console)
    {
        // Helps to load the specific theme data.
        console->Log("LoadThemeData", "Loading the default theme data.");

        // Common objects.
        theme->transparentColor = GetColorFromText(GetThemeConfigValue("TransparentColor", console), console);
        theme->widgetTransparentColor = GetColorFromText(GetThemeConfigValue("WidgetTransparentColor", console), console);
        // Common Objects.

        // Window Styles.
        theme->windowTheme.windowBorderRadius = std::stoi(GetThemeConfigValue("WindowBorderRadius", console));
        theme->windowTheme.windowBorderFocusColor = GetColorFromText(GetThemeConfigValue("WindowBorderFocusColor", console), console);
        theme->windowTheme.windowBorderUnfocusColor = GetColorFromText(GetThemeConfigValue("WindowBorderUnfocusColor", console), console);
        theme->windowTheme.windowBorderOpacity = std::stoi(GetThemeConfigValue("WindowBorderOpacity", console));

        theme->windowTheme.windowBackgroundColor = GetColorFromText(GetThemeConfigValue("WindowBackgroundColor", console), console);

        theme->windowTheme.windowCursor = (HCURSOR)LoadImageA(hInstance, (LPCSTR)GetThemeConfigValue("WindowCursor", console).c_str(), IMAGE_CURSOR, 0, 0, LR_LOADFROMFILE | LR_LOADTRANSPARENT);
        theme->windowTheme.windowLeftResizeCursor = (HCURSOR)LoadImageA(hInstance, (LPCSTR)GetThemeConfigValue("WindowLeftResizeCursor", console).c_str(), IMAGE_CURSOR, 0, 0, LR_LOADFROMFILE | LR_LOADTRANSPARENT);
        theme->windowTheme.windowRightResizeCursor = (HCURSOR)LoadImageA(hInstance, (LPCSTR)GetThemeConfigValue("WindowRightResizeCursor", console).c_str(), IMAGE_CURSOR, 0, 0, LR_LOADFROMFILE | LR_LOADTRANSPARENT);
        theme->windowTheme.windowTopResizeCursor = (HCURSOR)LoadImageA(hInstance, (LPCSTR)GetThemeConfigValue("WindowTopResizeCursor", console).c_str(), IMAGE_CURSOR, 0, 0, LR_LOADFROMFILE | LR_LOADTRANSPARENT);
        theme->windowTheme.windowBottomResizeCursor = (HCURSOR)LoadImageA(hInstance, (LPCSTR)GetThemeConfigValue("WindowBottomResizeCursor", console).c_str(), IMAGE_CURSOR, 0, 0, LR_LOADFROMFILE | LR_LOADTRANSPARENT);

        theme->windowTheme.windowTopLeftResizeCursor = (HCURSOR)LoadImageA(hInstance, (LPCSTR)GetThemeConfigValue("WindowTopLeftResizeCursor", console).c_str(), IMAGE_CURSOR, 0, 0, LR_LOADFROMFILE | LR_LOADTRANSPARENT);
        theme->windowTheme.windowTopRightResizeCursor = (HCURSOR)LoadImageA(hInstance, (LPCSTR)GetThemeConfigValue("WindowTopRightResizeCursor", console).c_str(), IMAGE_CURSOR, 0, 0, LR_LOADFROMFILE | LR_LOADTRANSPARENT);
        theme->windowTheme.windowBottomLeftResizeCursor = (HCURSOR)LoadImageA(hInstance, (LPCSTR)GetThemeConfigValue("WindowBottomLeftResizeCursor", console).c_str(), IMAGE_CURSOR, 0, 0, LR_LOADFROMFILE | LR_LOADTRANSPARENT);
        theme->windowTheme.windowBottomRightResizeCursor = (HCURSOR)LoadImageA(hInstance, (LPCSTR)GetThemeConfigValue("WindowBottomRightResizeCursor", console).c_str(), IMAGE_CURSOR, 0, 0, LR_LOADFROMFILE | LR_LOADTRANSPARENT);

        theme->windowTheme.windowTitleBarBackgroundColor = GetColorFromText(GetThemeConfigValue("WindowTitleBarBackgroundColor", console), console);

        theme->windowTheme.windowTaskBarIcon = LoadImageFromFile(GetThemeConfigValue("WindowTaskBarIcon", console), console);
        theme->windowTheme.windowFocusIcon = LoadImageFromFile(GetThemeConfigValue("WindowFocusIcon", console), console);
        theme->windowTheme.windowUnfocusIcon = LoadImageFromFile(GetThemeConfigValue("WindowUnfocusIcon", console), console);

        theme->windowTheme.windowTitleBarTextFocusColor = GetColorFromText(GetThemeConfigValue("WindowTitleBarTextFocusColor", console), console);
        theme->windowTheme.windowTitleBarTextUnfocusColor = GetColorFromText(GetThemeConfigValue("WindowTitleBarTextUnfocusColor", console), console);

        theme->windowTheme.windowTitleBarCloseButtonHoverBackgroundColor = GetColorFromText(GetThemeConfigValue("WindowTitleBarCloseButtonHoverBackgroundColor", console), console);
        theme->windowTheme.windowTitleBarCloseButtonFocusBackgroundColor = GetColorFromText(GetThemeConfigValue("WindowTitleBarCloseButtonFocusBackgroundColor", console), console);
        theme->windowTheme.windowTitleBarCloseButtonUnfocusBackgroundColor = GetColorFromText(GetThemeConfigValue("WindowTitleBarCloseButtonUnfocusBackgroundColor", console), console);
        theme->windowTheme.windowTitleBarCloseButtonHoverTextColor = GetColorFromText(GetThemeConfigValue("WindowTitleBarCloseButtonHoverTextColor", console), console);
        theme->windowTheme.windowTitleBarCloseButtonFocusTextColor = GetColorFromText(GetThemeConfigValue("WindowTitleBarCloseButtonFocusTextColor", console), console);
        theme->windowTheme.windowTitleBarCloseButtonUnfocusTextColor = GetColorFromText(GetThemeConfigValue("WindowTitleBarCloseButtonUnfocusTextColor", console), console);

        theme->windowTheme.windowTitleBarMaximizeButtonHoverBackgroundColor = GetColorFromText(GetThemeConfigValue("WindowTitleBarMaximizeButtonHoverBackgroundColor", console), console);
        theme->windowTheme.windowTitleBarMaximizeButtonFocusBackgroundColor = GetColorFromText(GetThemeConfigValue("WindowTitleBarMaximizeButtonFocusBackgroundColor", console), console);
        theme->windowTheme.windowTitleBarMaximizeButtonUnfocusBackgroundColor = GetColorFromText(GetThemeConfigValue("WindowTitleBarMaximizeButtonUnfocusBackgroundColor", console), console);
        theme->windowTheme.windowTitleBarMaximizeButtonHoverTextColor = GetColorFromText(GetThemeConfigValue("WindowTitleBarMaximizeButtonHoverTextColor", console), console);
        theme->windowTheme.windowTitleBarMaximizeButtonFocusTextColor = GetColorFromText(GetThemeConfigValue("WindowTitleBarMaximizeButtonFocusTextColor", console), console);
        theme->windowTheme.windowTitleBarMaximizeButtonUnfocusTextColor = GetColorFromText(GetThemeConfigValue("WindowTitleBarMaximizeButtonUnfocusTextColor", console), console);

        theme->windowTheme.windowTitleBarMinimizeButtonHoverBackgroundColor = GetColorFromText(GetThemeConfigValue("WindowTitleBarMinimizeButtonHoverBackgroundColor", console), console);
        theme->windowTheme.windowTitleBarMinimizeButtonFocusBackgroundColor = GetColorFromText(GetThemeConfigValue("WindowTitleBarMinimizeButtonFocusBackgroundColor", console), console);
        theme->windowTheme.windowTitleBarMinimizeButtonUnfocusBackgroundColor = GetColorFromText(GetThemeConfigValue("WindowTitleBarMinimizeButtonUnfocusBackgroundColor", console), console);
        theme->windowTheme.windowTitleBarMinimizeButtonHoverTextColor = GetColorFromText(GetThemeConfigValue("WindowTitleBarMinimizeButtonHoverTextColor", console), console);
        theme->windowTheme.windowTitleBarMinimizeButtonFocusTextColor = GetColorFromText(GetThemeConfigValue("WindowTitleBarMinimizeButtonFocusTextColor", console), console);
        theme->windowTheme.windowTitleBarMinimizeButtonUnfocusTextColor = GetColorFromText(GetThemeConfigValue("WindowTitleBarMinimizeButtonUnfocusTextColor", console), console);

        theme->windowTheme.windowTitleBarSettingButtonHoverBackgroundColor = GetColorFromText(GetThemeConfigValue("WindowTitleBarSettingButtonHoverBackgroundColor", console), console);
        theme->windowTheme.windowTitleBarSettingButtonFocusBackgroundColor = GetColorFromText(GetThemeConfigValue("WindowTitleBarSettingButtonFocusBackgroundColor", console), console);
        theme->windowTheme.windowTitleBarSettingButtonUnfocusBackgroundColor = GetColorFromText(GetThemeConfigValue("WindowTitleBarSettingButtonUnfocusBackgroundColor", console), console);
        theme->windowTheme.windowTitleBarSettingButtonHoverTextColor = GetColorFromText(GetThemeConfigValue("WindowTitleBarSettingButtonHoverTextColor", console), console);
        theme->windowTheme.windowTitleBarSettingButtonFocusTextColor = GetColorFromText(GetThemeConfigValue("WindowTitleBarSettingButtonFocusTextColor", console), console);
        theme->windowTheme.windowTitleBarSettingButtonUnfocusTextColor = GetColorFromText(GetThemeConfigValue("WindowTitleBarSettingButtonUnfocusTextColor", console), console);

        theme->windowTheme.windowStatusBarBackgroundColor = GetColorFromText(GetThemeConfigValue("WindowStatusBarBackgroundColor", console), console);

        theme->windowTheme.windowStatusBarTextFocusColor = GetColorFromText(GetThemeConfigValue("WindowStatusBarTextFocusColor", console), console);
        theme->windowTheme.windowStatusBarTextUnfocusColor = GetColorFromText(GetThemeConfigValue("WindowStatusBarTextUnfocusColor", console), console);
        // Window Styles.

        // Label Styles.
        theme->labelTheme.labelBackgroundColor = GetColorFromText(GetThemeConfigValue("LabelBackgroundColor", console), console);
        theme->labelTheme.labelTextColor = GetColorFromText(GetThemeConfigValue("LabelTextColor", console), console);
    }

    HCURSOR SetCursorF(HCURSOR cursor)
    {
        // Helps to set the cursor of the window.
        return SetCursor(cursor);
    }

    static BOOL GetWindowMaximizedStatus(HWND hWnd)
    {
        // Help to check wether the window is maximized or not.
        WINDOWPLACEMENT placement = {0};
        placement.length = sizeof(WINDOWPLACEMENT);
        if (GetWindowPlacement(hWnd, &placement))
        {
            return placement.showCmd == SW_SHOWMAXIMIZED;
        }

        return FALSE;
    }

    bool DestroyWindowF(HWND hWnd)
    {
        // Helps to destroy the window.
        return DestroyWindow(hWnd);
    }
}

namespace TkinterWindow
{
    // [ Starting ] - WindowClassInitializers.
    bool EXPORTIMPORT Window::InitializeWindow(HINSTANCE hInstance, std::string sClassName)
    {
        __hInstance = hInstance;
        __sClassName = sClassName;

        // Disabling the error of the console.
        __console.DisableErrorCheck();

        // Setting the class object and class name.
        __console.SetLoggerClassObject("Window");
        __console.SetloggerClassName(__sClassName);

        // Initializing the events.
        __InitializeEvents(&__console);

        if (sClassName.length() > 255)
        {
            __console.Log("InitializeWindow", "Error: The length of the class name is greater than 255 letters.");
            return false;
        }

        // Initializing theme.
        __theme = new __TkinterWindow::THEME;

        // Loading the tkinter window configuration file.
        __console.Log("InitializeWindow", "Getting positon and size for the window.");

        if (__nXPosition == -1)
        {
            __nXPosition = std::stoi(__TkinterWindow::GetConfigurationValue("WindowXPosition", &__console));
        }

        if (__nYPosition == -1)
        {
            __nYPosition = std::stoi(__TkinterWindow::GetConfigurationValue("WindowYPosition", &__console));
        }

        if (__nWidth == -1)
        {
            __nWidth = std::stoi(__TkinterWindow::GetConfigurationValue("WindowWidth", &__console));
        }

        if (__nHeight == -1)
        {
            __nHeight = std::stoi(__TkinterWindow::GetConfigurationValue("WindowHeight", &__console));
        }

        // Initializing GDI+
        __console.Log("InitializeWindow", "Initializing the GDI+ for the window.");
        Gdiplus::GdiplusStartup(&__gdiplusToken, &__gdiplusStartupInput, NULL);

        // Loading the theme data.
        __TkinterWindow::LoadThemeData(__theme, __hInstance, &__console);

        // Loading the window theme.
        __LoadWindowThemeFromTheme();

        // Declaring the window class.
        __console.Log("InitializeWindow", "Initializing the class for the window.");
        WNDCLASSEXA windowClass = {0};
        windowClass.cbSize = sizeof(WNDCLASSEXA);
        windowClass.cbClsExtra = 0;
        windowClass.hbrBackground = NULL;
        windowClass.cbWndExtra = 0;
        windowClass.hCursor = NULL;
        windowClass.hIcon = __windowTheme.windowTaskBarIcon;
        windowClass.hIconSm = __windowTheme.windowTaskBarIcon;
        windowClass.hInstance = hInstance;
        windowClass.lpfnWndProc = WndProc;
        windowClass.lpszClassName = __sClassName.c_str();
        windowClass.lpszMenuName = 0;
        windowClass.style = CS_HREDRAW | CS_VREDRAW;

        // Setting the console window icons.
        SendMessageA(GetConsoleWindow(), WM_SETICON, ICON_BIG, (LPARAM)__windowTheme.windowTaskBarIcon);
        SendMessageA(GetConsoleWindow(), WM_SETICON, ICON_SMALL, (LPARAM)__windowTheme.windowTaskBarIcon);

        __console.Log("InitializeWindow", "Registering the class for the window.");
        if (!RegisterClassExA(&windowClass))
        {
            __console.Log("InitializeWindow", "Error: Registeration of the class for the window failed.");
            return false;
        }

        // Creating the window.
        __console.Log("InitializeWindow", "Creating the the window. X: %d, Y: %d, Width: %d, Height: %d.", __nXPosition, __nYPosition, __nWidth, __nHeight);

        __windowHandle = CreateWindowExA(WS_EX_APPWINDOW | WS_EX_LAYERED, __sClassName.c_str(), __sWindowName.c_str(), WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW, __nXPosition, __nYPosition, __nWidth, __nHeight, NULL, 0, hInstance, this);

        if (__windowHandle == NULL)
        {
            __console.Log("InitializeWindow", "Error: The window creation failed.");

            return false;
        }

        // Setting the transparency.
        SetLayeredWindowAttributes(__windowHandle, __theme->transparentColor, 255, LWA_COLORKEY);

        // Initializing the borders.
        __border1.InitializeBorder(this, __sClassName, 1, &__windowTheme);
        __border2.InitializeBorder(this, __sClassName, 2, &__windowTheme);
        __border3.InitializeBorder(this, __sClassName, 3, &__windowTheme);
        __border4.InitializeBorder(this, __sClassName, 4, &__windowTheme);
        __border5.InitializeBorder(this, __sClassName, 5, &__windowTheme);

        int increaseBorderOpacity = __windowTheme.windowBorderOpacity / 5;

        __border1.SetBorderTransparency(increaseBorderOpacity * 5);
        __border2.SetBorderTransparency(increaseBorderOpacity * 4);
        __border3.SetBorderTransparency(increaseBorderOpacity * 3);
        __border4.SetBorderTransparency(increaseBorderOpacity * 2);
        __border5.SetBorderTransparency(increaseBorderOpacity);

        InvalidateRect(__windowHandle, NULL, TRUE);

        // Initializing the fonts for the window.
        __taskBarTitle.InitializeFont("TitleBarTitleText");
        __taskBarTitle.SetFontSize(16);
        __taskBarTitle.SetFontFamily("Segoe UI");
        __taskBarTitle.SetFontWeight(400);

        __statusBarFont.InitializeFont("StatusBarStatusText");
        __statusBarFont.SetFontSize(14);
        __statusBarFont.SetFontFamily("Segoe UI");
        __statusBarFont.SetFontWeight(400);

        // Showing the window
        std::string status = __TkinterWindow::GetConfigurationValue("WindowStatus", &__console);
        __console.Log("InitializeWindow", "Showing and updating the window. WindowState: %s", status.c_str());

        if (status == "Normal")
        {
            ShowWindow(__windowHandle, SW_NORMAL);
        }
        else if (status == "Maximized")
        {
            ShowWindow(__windowHandle, SW_SHOWMAXIMIZED);
        }
        else if (status == "Minimized")
        {
            ShowWindow(__windowHandle, SW_SHOWMINIMIZED);
        }
        else
        {
            ShowWindow(__windowHandle, SW_SHOW);
        }

        UpdateWindow(__windowHandle);

        return true;
    }

    bool Window::InitializeWindow(std::string sClassName, HINSTANCE hInstance)
    {
        // Same as InitializeWindow but with different arguments.
        return InitializeWindow(hInstance, sClassName);
    }

    bool Window::InitializeWindow(HINSTANCE hInstance)
    {
        // Same as InitializeWindow but with different arguments.
        return InitializeWindow(hInstance, __sClassName);
    }
    bool Window::InitializeWindow(std::string sClassName)
    {
        // Same as InitializeWindow but with different arguments.
        return InitializeWindow((HINSTANCE)GetModuleHandleA(NULL), sClassName);
    }

    bool Window::InitializeWindow(void)
    {
        // Same as InitializeWindow but with different arguments.
        return InitializeWindow((HINSTANCE)GetModuleHandleA(NULL), __sClassName);
    }

    bool Window::Initialize(HINSTANCE hInstance, std::string sClassName)
    {
        // Same as InitializeWindow but with different arguments.
        return InitializeWindow(hInstance, sClassName);
    }

    bool Window::Initialize(std::string sClassName, HINSTANCE hInstance)
    {
        // Same as InitializeWindow but with different arguments.
        return InitializeWindow(hInstance, sClassName);
    }

    bool Window::Initialize(HINSTANCE hInstance)
    {
        // Same as InitializeWindow but with different arguments.
        return InitializeWindow(hInstance, __sClassName);
    }

    bool Window::Initialize(std::string sClassName)
    {
        // Same as InitializeWindow but with different arguments.
        return InitializeWindow((HINSTANCE)GetModuleHandleA(NULL), sClassName);
    }

    bool Window::Initialize(void)
    {
        // Same as InitializeWindow but with different arguments.
        return InitializeWindow((HINSTANCE)GetModuleHandleA(NULL), __sClassName);
    }
    // [ Ending ] - WindowClassInitializers.

    // [ Starting ] - StartMainLoop().
    bool Window::StartMainLoop(int nMin, int nMax)
    {
        __CheckWarning("StartMainLoop");

        // Initializes the main loop for the window.
        __console.Log("StartMainLoop", "Starting the mainloop of the window. Min MSG: %d, Max MSG: %d", nMin, nMax);

        MSG msg;

        while (GetMessageA(&msg, NULL, nMin, nMax))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        // Shutting down the GDI+
        __console.Log("StartMainLoop", "Shutting down the GDI+.");
        Gdiplus::GdiplusShutdown(__gdiplusToken);

        return true;
    }

    bool Window::StartMainLoop(void)
    {
        // Same as StartMainLoop().
        return StartMainLoop(0, 0);
    }

    bool Window::MainLoop(int nMin, int nMax)
    {
        // Same as StartMainLoop().
        return StartMainLoop(nMin, nMax);
    }

    bool Window::MainLoop(void)
    {
        // Same as StartMainLoop().
        return StartMainLoop(0, 0);
    }
    // [ Ending ] - StartMainLoop().

    // [ Starting ] - SetWindowBorderRadius().
    bool Window::SetWindowBorderRadius(int nRadius)
    {
        __CheckWarning("SetWindowBorderRadius");

        // Helps to set the roundness of the borders.
        __console.Log("SetWindowBorderRadius", "Setting the border window border radius. Radius: %d", nRadius);

        __windowTheme.windowBorderRadius = nRadius;

        if (__windowHandle != NULL)
        {
            InvalidateRect(__windowHandle, NULL, TRUE);
        }

        return true;
    }

    bool Window::SetBorderRadius(int nRadius)
    {
        // Same as SetWindowBorderRadius.
        return SetWindowBorderRadius(nRadius);
    }

    bool Window::SetWindowBorderRoundness(int nRoundness)
    {
        // Same as SetWindowBorderRadius.
        return SetWindowBorderRadius(nRoundness);
    }

    bool Window::SetBorderRoundness(int nRoundness)
    {
        // Same as SetWindowBorderRadius.
        return SetWindowBorderRadius(nRoundness);
    }
    // [ Ending ] - SetWindowBorderRadius().

    // [ Starting ] - SetWindowBorderFocusColor().
    bool Window::SetWindowBorderFocusColor(int nRed, int nGreen, int nBlue)
    {
        __CheckWarning("SetWindowBorderFocusColor");

        // Helps to set the focused border color.
        __console.Log("SetWindowBorderFocusColor", "Setting the border focus color for the window. Color: %d, %d, %d.", nRed, nGreen, nBlue);

        __windowTheme.windowBorderFocusColor = RGB(nRed, nGreen, nBlue);

        if (__windowHandle != NULL)
        {
            InvalidateRect(__windowHandle, NULL, TRUE);
        }

        return true;
    }

    bool Window::SetWindowBorderFocusColor(COLORREF color)
    {
        __CheckWarning("SetWindowBorderFocusColor");

        // Helps to set the focused border color.
        __console.Log("SetWindowBorderFocusColor", "Setting the border focus color for the window. Color: %d, %d, %d.", GetRValue(color), GetGValue(color), GetBValue(color));

        __windowTheme.windowBorderFocusColor = color;

        if (__windowHandle != NULL)
        {
            InvalidateRect(__windowHandle, NULL, TRUE);
        }

        return true;
    }

    bool Window::SetBorderFocusColor(int nRed, int nGreen, int nBlue)
    {
        // Same as SetWindowBorderFocusColor()
        return SetWindowBorderFocusColor(nRed, nGreen, nBlue);
    }

    bool Window::SetBorderFocusColor(COLORREF color)
    {
        // Same as SetWindowBorderFocusColor().
        return SetWindowBorderFocusColor(color);
    }
    // [ Ending ] - SetWindowBorderFocusColor().

    // [ Starting ] - SetWindowBorderUnfocusColor().
    bool Window::SetWindowBorderUnfocusColor(int nRed, int nGreen, int nBlue)
    {
        __CheckWarning("SetWindowBorderUnfocusColor");

        // Helps to set the unfocused border color.
        __console.Log("SetWindowBorderUnfocusColor", "Setting the border unfocus color for the window. Color: %d, %d, %d.", nRed, nGreen, nBlue);

        __windowTheme.windowBorderUnfocusColor = RGB(nRed, nGreen, nBlue);

        if (__windowHandle != NULL)
        {
            InvalidateRect(__windowHandle, NULL, TRUE);
        }

        return true;
    }

    bool Window::SetWindowBorderUnfocusColor(COLORREF color)
    {
        __CheckWarning("SetWindowBorderUnfocusColor");

        // Helps to set the unfocused border color.
        __console.Log("SetWindowBorderUnfocusColor", "Setting the border unfocus color for the window. Color: %d, %d, %d.", GetRValue(color), GetGValue(color), GetBValue(color));

        __windowTheme.windowBorderUnfocusColor = color;

        if (__windowHandle != NULL)
        {
            InvalidateRect(__windowHandle, NULL, TRUE);
        }

        return true;
    }

    bool Window::SetBorderUnfocusColor(int nRed, int nGreen, int nBlue)
    {
        // Same as SetWindowBorderUnfocusColor()
        return SetWindowBorderUnfocusColor(nRed, nGreen, nBlue);
    }

    bool Window::SetBorderUnfocusColor(COLORREF color)
    {
        // Same as SetWindowBorderUnfocusColor().
        return SetWindowBorderUnfocusColor(color);
    }
    // [ Ending ] - SetWindowBorderUnfocusColor().

    // [ Starting ] - SetWindowBorderOpacity() ranges from 0 to 255.
    bool Window::SetWindowBorderOpacity(int nOpacity)
    {
        __CheckWarning("SetWindowBorderOpacity");

        // Helps to set the opacity of the border.
        __console.Log("SetWindowBorderOpacity", "Setting the opacity of the borer. Opacity: %d", nOpacity);

        __windowTheme.windowBorderOpacity = nOpacity;
        int increaseBorderOpacity = __windowTheme.windowBorderOpacity / 5;

        __border1.SetBorderTransparency(increaseBorderOpacity * 5);
        __border2.SetBorderTransparency(increaseBorderOpacity * 4);
        __border3.SetBorderTransparency(increaseBorderOpacity * 3);
        __border4.SetBorderTransparency(increaseBorderOpacity * 2);
        __border5.SetBorderTransparency(increaseBorderOpacity);

        if (__windowHandle != NULL)
        {
            SendMessageA(__windowHandle, WM_SIZE, NULL, NULL);
        }

        return true;
    }

    bool Window::SetBorderOpacity(int nOpacity)
    {
        // Same as SetWindowBorderOpacity().
        return SetWindowBorderOpacity(nOpacity);
    }

    bool Window::SetWindowShadowOpacity(int nOpacity)
    {
        // Same as SetWindowShadowOpacity().
        return SetWindowBorderOpacity(nOpacity);
    }

    bool Window::SetShadowOpacity(int nOpacity)
    {
        // Same as SetwindowShadowOpacity().
        return SetWindowBorderOpacity(nOpacity);
    }
    // [ Ending ] - SetWindowBorderOpacity() ranges from 0 to 255.

    // [ Starting ] - SetWindowBackgroundColor().
    bool Window::SetWindowBackgroundColor(int nRed, int nGreen, int nBlue)
    {
        __CheckWarning("SetWindowBackgroundColor");

        // Helps to set the background color of the window.
        __console.Log("SetWindowBackgroundColor", "Setting the background color for the window. Color: %d, %d, %d.", nRed, nGreen, nBlue);

        __windowTheme.windowBackgroundColor = RGB(nRed, nGreen, nBlue);

        if (__windowHandle != NULL)
        {
            InvalidateRect(__windowHandle, NULL, TRUE);
        }

        return true;
    }

    bool Window::SetWindowBackgroundColor(COLORREF color)
    {
        __CheckWarning("SetWindowBackgroundColor");

        // Helps to set the background color with the color object.
        __console.Log("SetWindowBackgroundColor", "Setting the background color for the window. Color: %d, %d, %d.", GetRValue(color), GetGValue(color), GetBValue(color));

        __windowTheme.windowBackgroundColor = color;

        if (__windowHandle != NULL)
        {
            InvalidateRect(__windowHandle, NULL, TRUE);
        }

        return true;
    }

    bool Window::SetBackgroundColor(int nRed, int nGreen, int nBlue)
    {
        // Same as SetWindowBackgroundColor().
        return SetWindowBackgroundColor(nRed, nGreen, nBlue);
    }

    bool Window::SetBackgroundColor(COLORREF color)
    {
        // Same as SetwindowBackgroundColor.
        return SetWindowBackgroundColor(color);
    }
    // [ Ending ] - SetWindowBackgrounbdColor().

    // [ Starting ] - Debugger control.
    bool Window::EnableDebugger(void)
    {
        // Helps to enable the debugger.
        return __console.EnableDebugger();
    }

    bool Window::DisableDebugger(void)
    {
        // Helps to disable the debugger.
        return __console.DisableDebugger();
    }
    // [ Ending ] - Debugger control.

    // [ Starting ] - Cursor controls.
    bool Window::SetWindowCursor(std::string sCursorPath)
    {
        __CheckWarning("SetWindowCursor");

        // Helps to set the client area cursor of the window.
        __console.Log("SetWindowCursor", "Setting the window client area cursor. CursorPath: %s", sCursorPath.c_str());

        __windowTheme.windowCursor = (HCURSOR)LoadImageA(__hInstance, (LPCSTR)sCursorPath.c_str(), IMAGE_CURSOR, 0, 0, LR_LOADFROMFILE | LR_LOADTRANSPARENT);

        if (!__windowTheme.windowCursor)
        {
            __console.Log("SetWindowCursor", "Error: Setting of the window client area cursor failed.");
            return false;
        }

        if (__windowHandle != NULL)
        {
            SendMessageA(__windowHandle, WM_SETCURSOR, NULL, NULL);
        }

        return true;
    }

    bool Window::SetCursor(std::string sCursorPath)
    {
        // Same as SetWindowCursor.
        return SetWindowCursor(sCursorPath);
    }

    bool Window::SetWindowLeftResizeCursor(std::string sCursorPath)
    {
        __CheckWarning("SetWindowLeftResizeCursor");

        // Helps to set the left resize cursor of the window.
        __console.Log("SetWindowLeftResizeCursor", "Setting the window left resize cursor. CursorPath: %s", sCursorPath.c_str());

        __windowTheme.windowLeftResizeCursor = (HCURSOR)LoadImageA(__hInstance, (LPCSTR)sCursorPath.c_str(), IMAGE_CURSOR, 0, 0, LR_LOADFROMFILE | LR_LOADTRANSPARENT);

        if (!__windowTheme.windowLeftResizeCursor)
        {
            __console.Log("SetWindowLeftResizeCursor", "Error: Setting of the window left resize cursor failed.");
            return false;
        }

        if (__windowHandle != NULL)
        {
            SendMessageA(__windowHandle, WM_SETCURSOR, NULL, NULL);
        }

        return true;
    }

    bool Window::SetLeftResizeCursor(std::string sCursorPath)
    {
        // Same as SetWindowLeftResizeCursor.
        return SetWindowLeftResizeCursor(sCursorPath);
    }

    bool Window::SetWindowRightResizeCursor(std::string sCursorPath)
    {
        __CheckWarning("SetWindowRightResizeCursor");

        // Helps to set the right resize cursor of the window.
        __console.Log("SetWindowRightResizeCursor", "Setting the window right resize cursor. CursorPath: %s", sCursorPath.c_str());

        __windowTheme.windowRightResizeCursor = (HCURSOR)LoadImageA(__hInstance, (LPCSTR)sCursorPath.c_str(), IMAGE_CURSOR, 0, 0, LR_LOADFROMFILE | LR_LOADTRANSPARENT);

        if (!__windowTheme.windowRightResizeCursor)
        {
            __console.Log("SetWindowRightResizeCursor", "Error: Setting of the window right resize cursor failed.");
            return false;
        }

        if (__windowHandle != NULL)
        {
            SendMessageA(__windowHandle, WM_SETCURSOR, NULL, NULL);
        }

        return true;
    }

    bool Window::SetRightResizeCursor(std::string sCursorPath)
    {
        // Same as SetWindowRightResizeCursor.
        return SetWindowRightResizeCursor(sCursorPath);
    }

    bool Window::SetWindowTopResizeCursor(std::string sCursorPath)
    {
        __CheckWarning("SetWindowTopResizeCursor");

        // Helps to set the top resize cursor of the window.
        __console.Log("SetWindowTopResizeCursor", "Setting the window top resize cursor. CursorPath: %s", sCursorPath.c_str());

        __windowTheme.windowTopResizeCursor = (HCURSOR)LoadImageA(__hInstance, (LPCSTR)sCursorPath.c_str(), IMAGE_CURSOR, 0, 0, LR_LOADFROMFILE | LR_LOADTRANSPARENT);

        if (!__windowTheme.windowTopResizeCursor)
        {
            __console.Log("SetWindowTopResizeCursor", "Error: Setting of the window top resize cursor failed.");
            return false;
        }

        if (__windowHandle != NULL)
        {
            SendMessageA(__windowHandle, WM_SETCURSOR, NULL, NULL);
        }

        return true;
    }

    bool Window::SetTopResizeCursor(std::string sCursorPath)
    {
        // Same as SetWindowTopResizeCursor.
        return SetWindowTopResizeCursor(sCursorPath);
    }

    bool Window::SetWindowBottomResizeCursor(std::string sCursorPath)
    {
        __CheckWarning("SetWindowBottomResizeCursor");

        // Helps to set the bottom resize cursor of the window.
        __console.Log("SetWindowBottomResizeCursor", "Setting the window bottom resize cursor. CursorPath: %s", sCursorPath.c_str());

        __windowTheme.windowBottomResizeCursor = (HCURSOR)LoadImageA(__hInstance, (LPCSTR)sCursorPath.c_str(), IMAGE_CURSOR, 0, 0, LR_LOADFROMFILE | LR_LOADTRANSPARENT);

        if (!__windowTheme.windowBottomResizeCursor)
        {
            __console.Log("SetWindowBottomResizeCursor", "Error: Setting of the window bottom resize cursor failed.");
            return false;
        }

        if (__windowHandle != NULL)
        {
            SendMessageA(__windowHandle, WM_SETCURSOR, NULL, NULL);
        }

        return true;
    }

    bool Window::SetBottomResizeCursor(std::string sCursorPath)
    {
        // Same as SetWindowBottomResizeCursor.
        return SetWindowBottomResizeCursor(sCursorPath);
    }

    bool Window::SetWindowTopLeftResizeCursor(std::string sCursorPath)
    {
        __CheckWarning("SetWindowTopLeftResizeCursor");

        // Helps to set the top left resize cursor of the window.
        __console.Log("SetWindowTopLeftResizeCursor", "Setting the window top left resize cursor. CursorPath: %s", sCursorPath.c_str());

        __windowTheme.windowTopLeftResizeCursor = (HCURSOR)LoadImageA(__hInstance, (LPCSTR)sCursorPath.c_str(), IMAGE_CURSOR, 0, 0, LR_LOADFROMFILE | LR_LOADTRANSPARENT);

        if (!__windowTheme.windowTopLeftResizeCursor)
        {
            __console.Log("SetWindowTopLeftResizeCursor", "Error: Setting of the window top left resize cursor failed.");
            return false;
        }

        if (__windowHandle != NULL)
        {
            SendMessageA(__windowHandle, WM_SETCURSOR, NULL, NULL);
        }

        return true;
    }

    bool Window::SetTopLeftResizeCursor(std::string sCursorPath)
    {
        // Same as SetWindowTopLeftResizeCursor.
        return SetWindowTopLeftResizeCursor(sCursorPath);
    }

    bool Window::SetWindowTopRightResizeCursor(std::string sCursorPath)
    {
        __CheckWarning("SetWindowTopRightResizeCursor");

        // Helps to set the top right resize cursor of the window.
        __console.Log("SetWindowTopRightResizeCursor", "Setting the window top right resize cursor. CursorPath: %s", sCursorPath.c_str());

        __windowTheme.windowTopRightResizeCursor = (HCURSOR)LoadImageA(__hInstance, (LPCSTR)sCursorPath.c_str(), IMAGE_CURSOR, 0, 0, LR_LOADFROMFILE | LR_LOADTRANSPARENT);

        if (!__windowTheme.windowTopRightResizeCursor)
        {
            __console.Log("SetWindowTopRightResizeCursor", "Error: Setting of the window top right resize cursor failed.");
            return false;
        }

        if (__windowHandle != NULL)
        {
            SendMessageA(__windowHandle, WM_SETCURSOR, NULL, NULL);
        }

        return true;
    }

    bool Window::SetTopRightResizeCursor(std::string sCursorPath)
    {
        // Same as SetWidnowTopRightResizeCursor.
        return SetWindowTopRightResizeCursor(sCursorPath);
    }

    bool Window::SetWindowBottomLeftResizeCursor(std::string sCursorPath)
    {
        __CheckWarning("SetWindowBottomLeftResizeCursor");

        // Helps to set the bottom left resize cursor of the window.
        __console.Log("SetWindowBottomLeftResizeCursor", "Setting the window bottom left resize cursor. CursorPath: %s", sCursorPath.c_str());

        __windowTheme.windowBottomLeftResizeCursor = (HCURSOR)LoadImageA(__hInstance, (LPCSTR)sCursorPath.c_str(), IMAGE_CURSOR, 0, 0, LR_LOADFROMFILE | LR_LOADTRANSPARENT);

        if (!__windowTheme.windowBottomLeftResizeCursor)
        {
            __console.Log("SetWindowBottomLeftResizeCursor", "Error: Setting of the window bottom left resize cursor failed.");
            return false;
        }

        if (__windowHandle != NULL)
        {
            SendMessageA(__windowHandle, WM_SETCURSOR, NULL, NULL);
        }

        return true;
    }

    bool Window::SetBottomLeftResizeCursor(std::string sCursorPath)
    {
        // Same as SetWindowBottomLeftResizeCursor.
        return SetWindowBottomLeftResizeCursor(sCursorPath);
    }

    bool Window::SetWindowBottomRightResizeCursor(std::string sCursorPath)
    {
        __CheckWarning("SetWindowBottomRightResizeCursor");

        // Helps to set the bottom right resize cursor of the window.
        __console.Log("SetWindowBottomRightResizeCursor", "Setting the window bottom right resize cursor. CursorPath: %s", sCursorPath.c_str());

        __windowTheme.windowBottomRightResizeCursor = (HCURSOR)LoadImageA(__hInstance, (LPCSTR)sCursorPath.c_str(), IMAGE_CURSOR, 0, 0, LR_LOADFROMFILE | LR_LOADTRANSPARENT);

        if (!__windowTheme.windowBottomRightResizeCursor)
        {
            __console.Log("SetWindowBottomRightResizeCursor", "Error: Setting of the window bottom right resize cursor failed.");
            return false;
        }

        if (__windowHandle != NULL)
        {
            SendMessageA(__windowHandle, WM_SETCURSOR, NULL, NULL);
        }

        return true;
    }

    bool Window::SetBottomRightResizeCursor(std::string sCursorPath)
    {
        // Same as SetWidnowBottomRightResizeCursor.
        return SetWindowBottomRightResizeCursor(sCursorPath);
    }
    // [ Starting ] - Cursor controls.

    // [ Starting ] - TitleBar Controls.
    bool Window::SetWindowTitleBarBackgroundColor(int nRed, int nGreen, int nBlue)
    {
        // Same as SetWindowTitleBarBackgroundColor.
        return SetWindowTitleBarBackgroundColor(RGB(nRed, nGreen, nBlue));
    }

    bool Window::SetWindowTitleBarBackgroundColor(COLORREF color)
    {
        __CheckWarning("SetWindowTitleBarBackgroundColor");

        // Helps to set the title bar background color with the color object.
        __console.Log("SetWindowTitleBarBackgroundColor", "Setting the title bar background color for the window. Color: %d, %d, %d.", GetRValue(color), GetGValue(color), GetBValue(color));

        __windowTheme.windowTitleBarBackgroundColor = color;

        if (__windowHandle != NULL)
        {
            InvalidateRect(__windowHandle, NULL, TRUE);
        }

        return true;
    }

    bool Window::SetTitleBarBackgroundColor(int nRed, int nGreen, int nBlue)
    {
        // Same as SetWindowTitleBarBackgroundColor.
        return SetWindowTitleBarBackgroundColor(RGB(nRed, nGreen, nBlue));
    }

    bool Window::SetTitleBarBackgroundColor(COLORREF color)
    {
        // Same as SetWindowTitleBarBackgroundColor.
        return SetWindowTitleBarBackgroundColor(color);
    }

    bool Window::SetWindowTitleBarTextFocusColor(int nRed, int nGreen, int nBlue)
    {
        // Same as SetWindowTitleBarTextFocusColor.
        return SetWindowTitleBarTextFocusColor(RGB(nRed, nGreen, nBlue));
    }

    bool Window::SetWindowTitleBarTextFocusColor(COLORREF color)
    {
        __CheckWarning("SetWindowTitleBarTextFocusColor");

        // Helps to set the title bar text focus color with the color object.
        __console.Log("SetWindowTitleBarTextFocusColor", "Setting the title bar text focus color for the window. Color: %d, %d, %d.", GetRValue(color), GetGValue(color), GetBValue(color));

        __windowTheme.windowTitleBarTextFocusColor = color;

        if (__windowHandle != NULL)
        {
            InvalidateRect(__windowHandle, NULL, TRUE);
        }

        return true;
    }

    bool Window::SetTitleBarTextFocusColor(int nRed, int nGreen, int nBlue)
    {
        // Same as SetWindowTitleBarTextFocusColor.
        return SetWindowTitleBarTextFocusColor(RGB(nRed, nGreen, nBlue));
    }

    bool Window::SetTitleBarTextFocusColor(COLORREF color)
    {
        // Same as SetWindowTitleBarTextFocusColor.
        return SetWindowTitleBarTextFocusColor(color);
    }

    bool Window::SetWindowTitleBarTextUnfocusColor(int nRed, int nGreen, int nBlue)
    {
        // Same as SetWindowTitleBarTextUnfocusColor.
        return SetWindowTitleBarTextUnfocusColor(RGB(nRed, nGreen, nBlue));
    }

    bool Window::SetWindowTitleBarTextUnfocusColor(COLORREF color)
    {
        __CheckWarning("SetWindowTitleBarTextUnfocusColor");

        // Helps to set the title bar text unfocus color with the color object.
        __console.Log("SetWindowTitleBarTextUnfocusColor", "Setting the title bar text unfocus color for the window. Color: %d, %d, %d.", GetRValue(color), GetGValue(color), GetBValue(color));

        __windowTheme.windowTitleBarTextUnfocusColor = color;

        if (__windowHandle != NULL)
        {
            InvalidateRect(__windowHandle, NULL, TRUE);
        }

        return true;
    }

    bool Window::SetTitleBarTextUnfocusColor(int nRed, int nGreen, int nBlue)
    {
        // Same as SetWindowTitleBarTextUnfocusColor.
        return SetWindowTitleBarTextUnfocusColor(RGB(nRed, nGreen, nBlue));
    }

    bool Window::SetTitleBarTextUnfocusColor(COLORREF color)
    {
        // Same as SetWindowTitleBarTextUnfocusColor.
        return SetWindowTitleBarTextUnfocusColor(color);
    }
    // [ Ending ] - TitleBar Controls.

    // [ Starting ] - Title bar close button controls.
    bool Window::SetWindowTitleBarCloseButtonHoverBackgroundColor(COLORREF color)
    {
        __CheckWarning("SetWindowTitleBarCloseButtonHoverBackgroundColor");

        // Helps to set the title bar text unfocus color with the color object.
        __console.Log("SetWindowTitleBarCloseButtonHoverBackgroundColor", "Setting the title bar close button hover background color for the window. Color: %d, %d, %d.", GetRValue(color), GetGValue(color), GetBValue(color));

        __windowTheme.windowTitleBarCloseButtonHoverBackgroundColor = color;

        if (__windowHandle != NULL)
        {
            InvalidateRect(__windowHandle, NULL, TRUE);
        }

        return true;
    }

    bool Window::SetWindowTitleBarCloseButtonHoverBackgroundColor(int nRed, int nGreen, int nBlue)
    {
        // Same as SetWindowTitleBarCloseButtonHoverBackgroundColor.
        return SetWindowTitleBarCloseButtonHoverBackgroundColor(RGB(nRed, nGreen, nBlue));
    }

    bool Window::SetTitleBarCloseButtonHoverBackgroundColor(COLORREF color)
    {
        // Same as SetWindowTitleBarCloseButtonHoverBackgroundColor.
        return SetWindowTitleBarCloseButtonHoverBackgroundColor(color);
    }

    bool Window::SetTitleBarCloseButtonHoverBackgroundColor(int nRed, int nGreen, int nBlue)
    {
        // Same as SetWindowTitleBarCloseButtonHoverBackgroundColor.
        return SetWindowTitleBarCloseButtonHoverBackgroundColor(RGB(nRed, nGreen, nBlue));
    }

    bool Window::SetWindowTitleBarCloseButtonFocusBackgroundColor(COLORREF color)
    {
        __CheckWarning("SetWindowTitleBarCloseButtonFocusBackgroundColor");

        // Helps to set the title bar text unfocus color with the color object.
        __console.Log("SetWindowTitleBarCloseButtonFocusBackgroundColor", "Setting the title bar close button focus background color for the window. Color: %d, %d, %d.", GetRValue(color), GetGValue(color), GetBValue(color));

        __windowTheme.windowTitleBarCloseButtonFocusBackgroundColor = color;

        if (__windowHandle != NULL)
        {
            InvalidateRect(__windowHandle, NULL, TRUE);
        }

        return true;
    }

    bool Window::SetWindowTitleBarCloseButtonFocusBackgroundColor(int nRed, int nGreen, int nBlue)
    {
        // Same as SetWindowTitleBarCloseButtonFocusBackgroundColor.
        return SetWindowTitleBarCloseButtonFocusBackgroundColor(RGB(nRed, nGreen, nBlue));
    }

    bool Window::SetTitleBarCloseButtonFocusBackgroundColor(COLORREF color)
    {
        // Same as SetWindowTitleBarCloseButtonFocusBackgroundColor.
        return SetWindowTitleBarCloseButtonFocusBackgroundColor(color);
    }

    bool Window::SetTitleBarCloseButtonFocusBackgroundColor(int nRed, int nGreen, int nBlue)
    {
        // Same as SetWindowTitleBarCloseButtonFocusBackgroundColor.
        return SetWindowTitleBarCloseButtonFocusBackgroundColor(RGB(nRed, nGreen, nBlue));
    }

    bool Window::SetWindowTitleBarCloseButtonUnfocusBackgroundColor(COLORREF color)
    {
        __CheckWarning("SetWindowTitleBarCloseButtonUnfocusBackgroundColor");

        // Helps to set the title bar text unfocus color with the color object.
        __console.Log("SetWindowTitleBarCloseButtonUnfocusBackgroundColor", "Setting the title bar close button unfocus background color for the window. Color: %d, %d, %d.", GetRValue(color), GetGValue(color), GetBValue(color));

        __windowTheme.windowTitleBarCloseButtonFocusBackgroundColor = color;

        if (__windowHandle != NULL)
        {
            InvalidateRect(__windowHandle, NULL, TRUE);
        }

        return true;
    }

    bool Window::SetWindowTitleBarCloseButtonUnfocusBackgroundColor(int nRed, int nGreen, int nBlue)
    {
        // Same as SetWindowTitleBarCloseButtonUnfocusBackgroundColor.
        return SetWindowTitleBarCloseButtonUnfocusBackgroundColor(RGB(nRed, nGreen, nBlue));
    }

    bool Window::SetTitleBarCloseButtonUnfocusBackgroundColor(COLORREF color)
    {
        // Same as SetWindowTitleBarCloseButtonUnfocusBackgroundColor.
        return SetWindowTitleBarCloseButtonUnfocusBackgroundColor(color);
    }

    bool Window::SetTitleBarCloseButtonUnfocusBackgroundColor(int nRed, int nGreen, int nBlue)
    {
        // Same as SetWindowTitleBarCloseButtonUnfocusBackgroundColor.
        return SetWindowTitleBarCloseButtonUnfocusBackgroundColor(RGB(nRed, nGreen, nBlue));
    }

    bool Window::SetWindowTitleBarCloseButtonHoverTextColor(COLORREF color)
    {
        __CheckWarning("SetWindowTitleBarCloseButtonHoverTextColor");

        // Helps to set the title bar text unfocus color with the color object.
        __console.Log("SetWindowTitleBarCloseButtonHoverTextColor", "Setting the title bar close button hover text color for the window. Color: %d, %d, %d.", GetRValue(color), GetGValue(color), GetBValue(color));

        __windowTheme.windowTitleBarCloseButtonHoverTextColor = color;

        if (__windowHandle != NULL)
        {
            InvalidateRect(__windowHandle, NULL, TRUE);
        }

        return true;
    }

    bool Window::SetWindowTitleBarCloseButtonHoverTextColor(int nRed, int nGreen, int nBlue)
    {
        // Same as SetWindowTitleBarCloseButtonHoverTextColor.
        return SetWindowTitleBarCloseButtonHoverTextColor(RGB(nRed, nGreen, nBlue));
    }

    bool Window::SetTitleBarCloseButtonHoverTextColor(COLORREF color)
    {
        // Same as SetWindowTitleBarCloseButtonHoverTextColor.
        return SetWindowTitleBarCloseButtonHoverTextColor(color);
    }

    bool Window::SetTitleBarCloseButtonHoverTextColor(int nRed, int nGreen, int nBlue)
    {
        // Same as SetWindowTitleBarCloseButtonHoverTextColor.
        return SetWindowTitleBarCloseButtonHoverTextColor(RGB(nRed, nGreen, nBlue));
    }

    bool Window::SetWindowTitleBarCloseButtonFocusTextColor(COLORREF color)
    {
        __CheckWarning("SetWindowTitleBarCloseButtonFocusTextColor");

        // Helps to set the title bar text unfocus color with the color object.
        __console.Log("SetWindowTitleBarCloseButtonFocusTextColor", "Setting the title bar close button focus text color for the window. Color: %d, %d, %d.", GetRValue(color), GetGValue(color), GetBValue(color));

        __windowTheme.windowTitleBarCloseButtonFocusTextColor = color;

        if (__windowHandle != NULL)
        {
            InvalidateRect(__windowHandle, NULL, TRUE);
        }

        return true;
    }

    bool Window::SetWindowTitleBarCloseButtonFocusTextColor(int nRed, int nGreen, int nBlue)
    {
        // Same as SetWindowTitleBarCloseButtonFocusTextColor.
        return SetWindowTitleBarCloseButtonFocusTextColor(RGB(nRed, nGreen, nBlue));
    }

    bool Window::SetTitleBarCloseButtonFocusTextColor(COLORREF color)
    {
        // Same as SetWindowTitleBarCloseButtonFocusTextColor.
        return SetWindowTitleBarCloseButtonFocusTextColor(color);
    }

    bool Window::SetTitleBarCloseButtonFocusTextColor(int nRed, int nGreen, int nBlue)
    {
        // Same as SetWindowTitleBarCloseButtonFocusTextColor.
        return SetWindowTitleBarCloseButtonFocusTextColor(RGB(nRed, nGreen, nBlue));
    }

    bool Window::SetWindowTitleBarCloseButtonUnfocusTextColor(COLORREF color)
    {
        __CheckWarning("SetWindowTitleBarCloseButtonUnfocusTextColor");

        // Helps to set the title bar text unfocus color with the color object.
        __console.Log("SetWindowTitleBarCloseButtonUnfocusTextColor", "Setting the title bar close button unfocus text color for the window. Color: %d, %d, %d.", GetRValue(color), GetGValue(color), GetBValue(color));

        __windowTheme.windowTitleBarCloseButtonFocusTextColor = color;

        if (__windowHandle != NULL)
        {
            InvalidateRect(__windowHandle, NULL, TRUE);
        }

        return true;
    }

    bool Window::SetWindowTitleBarCloseButtonUnfocusTextColor(int nRed, int nGreen, int nBlue)
    {
        // Same as SetWindowTitleBarCloseButtonUnfocusTextColor.
        return SetWindowTitleBarCloseButtonUnfocusTextColor(RGB(nRed, nGreen, nBlue));
    }

    bool Window::SetTitleBarCloseButtonUnfocusTextColor(COLORREF color)
    {
        // Same as SetWindowTitleBarCloseButtonUnfocusTextColor.
        return SetWindowTitleBarCloseButtonUnfocusTextColor(color);
    }

    bool Window::SetTitleBarCloseButtonUnfocusTextColor(int nRed, int nGreen, int nBlue)
    {
        // Same as SetWindowTitleBarCloseButtonUnfocusTextColor.
        return SetWindowTitleBarCloseButtonUnfocusTextColor(RGB(nRed, nGreen, nBlue));
    }
    // [ Ending ] - Title bar close button controls.

    // [ Starting ] - Title bar maximize button controls.
    bool Window::SetWindowTitleBarMaximizeButtonHoverBackgroundColor(COLORREF color)
    {
        __CheckWarning("SetWindowTitleBarMaximizeButtonHoverBackgroundColor");

        // Helps to set the title bar text unfocus color with the color object.
        __console.Log("SetWindowTitleBarMaximizeButtonHoverBackgroundColor", "Setting the title bar maximize button hover background color for the window. Color: %d, %d, %d.", GetRValue(color), GetGValue(color), GetBValue(color));

        __windowTheme.windowTitleBarMaximizeButtonHoverBackgroundColor = color;

        if (__windowHandle != NULL)
        {
            InvalidateRect(__windowHandle, NULL, TRUE);
        }

        return true;
    }

    bool Window::SetWindowTitleBarMaximizeButtonHoverBackgroundColor(int nRed, int nGreen, int nBlue)
    {
        // Same as SetWindowTitleBarMaximizeButtonHoverBackgroundColor.
        return SetWindowTitleBarMaximizeButtonHoverBackgroundColor(RGB(nRed, nGreen, nBlue));
    }

    bool Window::SetTitleBarMaximizeButtonHoverBackgroundColor(COLORREF color)
    {
        // Same as SetWindowTitleBarMaximizeButtonHoverBackgroundColor.
        return SetWindowTitleBarMaximizeButtonHoverBackgroundColor(color);
    }

    bool Window::SetTitleBarMaximizeButtonHoverBackgroundColor(int nRed, int nGreen, int nBlue)
    {
        // Same as SetWindowTitleBarMaximizeButtonHoverBackgroundColor.
        return SetWindowTitleBarMaximizeButtonHoverBackgroundColor(RGB(nRed, nGreen, nBlue));
    }

    bool Window::SetWindowTitleBarMaximizeButtonFocusBackgroundColor(COLORREF color)
    {
        __CheckWarning("SetWindowTitleBarMaximizeButtonFocusBackgroundColor");

        // Helps to set the title bar text unfocus color with the color object.
        __console.Log("SetWindowTitleBarMaximizeButtonFocusBackgroundColor", "Setting the title bar maximize button focus background color for the window. Color: %d, %d, %d.", GetRValue(color), GetGValue(color), GetBValue(color));

        __windowTheme.windowTitleBarMaximizeButtonFocusBackgroundColor = color;

        if (__windowHandle != NULL)
        {
            InvalidateRect(__windowHandle, NULL, TRUE);
        }

        return true;
    }

    bool Window::SetWindowTitleBarMaximizeButtonFocusBackgroundColor(int nRed, int nGreen, int nBlue)
    {
        // Same as SetWindowTitleBarMaximizeButtonFocusBackgroundColor.
        return SetWindowTitleBarMaximizeButtonFocusBackgroundColor(RGB(nRed, nGreen, nBlue));
    }

    bool Window::SetTitleBarMaximizeButtonFocusBackgroundColor(COLORREF color)
    {
        // Same as SetWindowTitleBarMaximizeButtonFocusBackgroundColor.
        return SetWindowTitleBarMaximizeButtonFocusBackgroundColor(color);
    }

    bool Window::SetTitleBarMaximizeButtonFocusBackgroundColor(int nRed, int nGreen, int nBlue)
    {
        // Same as SetWindowTitleBarMaximizeButtonFocusBackgroundColor.
        return SetWindowTitleBarMaximizeButtonFocusBackgroundColor(RGB(nRed, nGreen, nBlue));
    }

    bool Window::SetWindowTitleBarMaximizeButtonUnfocusBackgroundColor(COLORREF color)
    {
        __CheckWarning("SetWindowTitleBarMaximizeButtonUnfocusBackgroundColor");

        // Helps to set the title bar text unfocus color with the color object.
        __console.Log("SetWindowTitleBarMaximizeButtonUnfocusBackgroundColor", "Setting the title bar maximize button unfocus background color for the window. Color: %d, %d, %d.", GetRValue(color), GetGValue(color), GetBValue(color));

        __windowTheme.windowTitleBarMaximizeButtonFocusBackgroundColor = color;

        if (__windowHandle != NULL)
        {
            InvalidateRect(__windowHandle, NULL, TRUE);
        }

        return true;
    }

    bool Window::SetWindowTitleBarMaximizeButtonUnfocusBackgroundColor(int nRed, int nGreen, int nBlue)
    {
        // Same as SetWindowTitleBarMaximizeButtonUnfocusBackgroundColor.
        return SetWindowTitleBarMaximizeButtonUnfocusBackgroundColor(RGB(nRed, nGreen, nBlue));
    }

    bool Window::SetTitleBarMaximizeButtonUnfocusBackgroundColor(COLORREF color)
    {
        // Same as SetWindowTitleBarMaximizeButtonUnfocusBackgroundColor.
        return SetWindowTitleBarMaximizeButtonUnfocusBackgroundColor(color);
    }

    bool Window::SetTitleBarMaximizeButtonUnfocusBackgroundColor(int nRed, int nGreen, int nBlue)
    {
        // Same as SetWindowTitleBarMaximizeButtonUnfocusBackgroundColor.
        return SetWindowTitleBarMaximizeButtonUnfocusBackgroundColor(RGB(nRed, nGreen, nBlue));
    }

    bool Window::SetWindowTitleBarMaximizeButtonHoverTextColor(COLORREF color)
    {
        __CheckWarning("SetWindowTitleBarMaximizeButtonHoverTextColor");

        // Helps to set the title bar text unfocus color with the color object.
        __console.Log("SetWindowTitleBarMaximizeButtonHoverTextColor", "Setting the title bar maximize button hover text color for the window. Color: %d, %d, %d.", GetRValue(color), GetGValue(color), GetBValue(color));

        __windowTheme.windowTitleBarMaximizeButtonHoverTextColor = color;

        if (__windowHandle != NULL)
        {
            InvalidateRect(__windowHandle, NULL, TRUE);
        }

        return true;
    }

    bool Window::SetWindowTitleBarMaximizeButtonHoverTextColor(int nRed, int nGreen, int nBlue)
    {
        // Same as SetWindowTitleBarMaximizeButtonHoverTextColor.
        return SetWindowTitleBarMaximizeButtonHoverTextColor(RGB(nRed, nGreen, nBlue));
    }

    bool Window::SetTitleBarMaximizeButtonHoverTextColor(COLORREF color)
    {
        // Same as SetWindowTitleBarMaximizeButtonHoverTextColor.
        return SetWindowTitleBarMaximizeButtonHoverTextColor(color);
    }

    bool Window::SetTitleBarMaximizeButtonHoverTextColor(int nRed, int nGreen, int nBlue)
    {
        // Same as SetWindowTitleBarMaximizeButtonHoverTextColor.
        return SetWindowTitleBarMaximizeButtonHoverTextColor(RGB(nRed, nGreen, nBlue));
    }

    bool Window::SetWindowTitleBarMaximizeButtonFocusTextColor(COLORREF color)
    {
        __CheckWarning("SetWindowTitleBarMaximizeButtonFocusTextColor");

        // Helps to set the title bar text unfocus color with the color object.
        __console.Log("SetWindowTitleBarMaximizeButtonFocusTextColor", "Setting the title bar maximize button focus text color for the window. Color: %d, %d, %d.", GetRValue(color), GetGValue(color), GetBValue(color));

        __windowTheme.windowTitleBarMaximizeButtonFocusTextColor = color;

        if (__windowHandle != NULL)
        {
            InvalidateRect(__windowHandle, NULL, TRUE);
        }

        return true;
    }

    bool Window::SetWindowTitleBarMaximizeButtonFocusTextColor(int nRed, int nGreen, int nBlue)
    {
        // Same as SetWindowTitleBarMaximizeButtonFocusTextColor.
        return SetWindowTitleBarMaximizeButtonFocusTextColor(RGB(nRed, nGreen, nBlue));
    }

    bool Window::SetTitleBarMaximizeButtonFocusTextColor(COLORREF color)
    {
        // Same as SetWindowTitleBarMaximizeButtonFocusTextColor.
        return SetWindowTitleBarMaximizeButtonFocusTextColor(color);
    }

    bool Window::SetTitleBarMaximizeButtonFocusTextColor(int nRed, int nGreen, int nBlue)
    {
        // Same as SetWindowTitleBarMaximizeButtonFocusTextColor.
        return SetWindowTitleBarMaximizeButtonFocusTextColor(RGB(nRed, nGreen, nBlue));
    }

    bool Window::SetWindowTitleBarMaximizeButtonUnfocusTextColor(COLORREF color)
    {
        __CheckWarning("SetWindowTitleBarMaximizeButtonUnfocusTextColor");

        // Helps to set the title bar text unfocus color with the color object.
        __console.Log("SetWindowTitleBarMaximizeButtonUnfocusTextColor", "Setting the title bar maximize button unfocus text color for the window. Color: %d, %d, %d.", GetRValue(color), GetGValue(color), GetBValue(color));

        __windowTheme.windowTitleBarMaximizeButtonFocusTextColor = color;

        if (__windowHandle != NULL)
        {
            InvalidateRect(__windowHandle, NULL, TRUE);
        }

        return true;
    }

    bool Window::SetWindowTitleBarMaximizeButtonUnfocusTextColor(int nRed, int nGreen, int nBlue)
    {
        // Same as SetWindowTitleBarMaximizeButtonUnfocusTextColor.
        return SetWindowTitleBarMaximizeButtonUnfocusTextColor(RGB(nRed, nGreen, nBlue));
    }

    bool Window::SetTitleBarMaximizeButtonUnfocusTextColor(COLORREF color)
    {
        // Same as SetWindowTitleBarMaximizeButtonUnfocusTextColor.
        return SetWindowTitleBarMaximizeButtonUnfocusTextColor(color);
    }

    bool Window::SetTitleBarMaximizeButtonUnfocusTextColor(int nRed, int nGreen, int nBlue)
    {
        // Same as SetWindowTitleBarMaximizeButtonUnfocusTextColor.
        return SetWindowTitleBarMaximizeButtonUnfocusTextColor(RGB(nRed, nGreen, nBlue));
    }
    // [ Ending ] - Title bar maximize button controls.

    // [ Starting ] - Title bar minimize button controls.
    bool Window::SetWindowTitleBarMinimizeButtonHoverBackgroundColor(COLORREF color)
    {
        __CheckWarning("SetWindowTitleBarMinimizeButtonHoverBackgroundColor");

        // Helps to set the title bar text unfocus color with the color object.
        __console.Log("SetWindowTitleBarMinimizeButtonHoverBackgroundColor", "Setting the title bar minimize button hover background color for the window. Color: %d, %d, %d.", GetRValue(color), GetGValue(color), GetBValue(color));

        __windowTheme.windowTitleBarMinimizeButtonHoverBackgroundColor = color;

        if (__windowHandle != NULL)
        {
            InvalidateRect(__windowHandle, NULL, TRUE);
        }

        return true;
    }

    bool Window::SetWindowTitleBarMinimizeButtonHoverBackgroundColor(int nRed, int nGreen, int nBlue)
    {
        // Same as SetWindowTitleBarMinimizeButtonHoverBackgroundColor.
        return SetWindowTitleBarMinimizeButtonHoverBackgroundColor(RGB(nRed, nGreen, nBlue));
    }

    bool Window::SetTitleBarMinimizeButtonHoverBackgroundColor(COLORREF color)
    {
        // Same as SetWindowTitleBarMinimizeButtonHoverBackgroundColor.
        return SetWindowTitleBarMinimizeButtonHoverBackgroundColor(color);
    }

    bool Window::SetTitleBarMinimizeButtonHoverBackgroundColor(int nRed, int nGreen, int nBlue)
    {
        // Same as SetWindowTitleBarMinimizeButtonHoverBackgroundColor.
        return SetWindowTitleBarMinimizeButtonHoverBackgroundColor(RGB(nRed, nGreen, nBlue));
    }

    bool Window::SetWindowTitleBarMinimizeButtonFocusBackgroundColor(COLORREF color)
    {
        __CheckWarning("SetWindowTitleBarMinimizeButtonFocusBackgroundColor");

        // Helps to set the title bar text unfocus color with the color object.
        __console.Log("SetWindowTitleBarMinimizeButtonFocusBackgroundColor", "Setting the title bar minimize button focus background color for the window. Color: %d, %d, %d.", GetRValue(color), GetGValue(color), GetBValue(color));

        __windowTheme.windowTitleBarMinimizeButtonFocusBackgroundColor = color;

        if (__windowHandle != NULL)
        {
            InvalidateRect(__windowHandle, NULL, TRUE);
        }

        return true;
    }

    bool Window::SetWindowTitleBarMinimizeButtonFocusBackgroundColor(int nRed, int nGreen, int nBlue)
    {
        // Same as SetWindowTitleBarMinimizeButtonFocusBackgroundColor.
        return SetWindowTitleBarMinimizeButtonFocusBackgroundColor(RGB(nRed, nGreen, nBlue));
    }

    bool Window::SetTitleBarMinimizeButtonFocusBackgroundColor(COLORREF color)
    {
        // Same as SetWindowTitleBarMinimizeButtonFocusBackgroundColor.
        return SetWindowTitleBarMinimizeButtonFocusBackgroundColor(color);
    }

    bool Window::SetTitleBarMinimizeButtonFocusBackgroundColor(int nRed, int nGreen, int nBlue)
    {
        // Same as SetWindowTitleBarMinimizeButtonFocusBackgroundColor.
        return SetWindowTitleBarMinimizeButtonFocusBackgroundColor(RGB(nRed, nGreen, nBlue));
    }

    bool Window::SetWindowTitleBarMinimizeButtonUnfocusBackgroundColor(COLORREF color)
    {
        __CheckWarning("SetWindowTitleBarMinimizeButtonUnfocusBackgroundColor");

        // Helps to set the title bar text unfocus color with the color object.
        __console.Log("SetWindowTitleBarMinimizeButtonUnfocusBackgroundColor", "Setting the title bar minimize button unfocus background color for the window. Color: %d, %d, %d.", GetRValue(color), GetGValue(color), GetBValue(color));

        __windowTheme.windowTitleBarMinimizeButtonFocusBackgroundColor = color;

        if (__windowHandle != NULL)
        {
            InvalidateRect(__windowHandle, NULL, TRUE);
        }

        return true;
    }

    bool Window::SetWindowTitleBarMinimizeButtonUnfocusBackgroundColor(int nRed, int nGreen, int nBlue)
    {
        // Same as SetWindowTitleBarMinimizeButtonUnfocusBackgroundColor.
        return SetWindowTitleBarMinimizeButtonUnfocusBackgroundColor(RGB(nRed, nGreen, nBlue));
    }

    bool Window::SetTitleBarMinimizeButtonUnfocusBackgroundColor(COLORREF color)
    {
        // Same as SetWindowTitleBarMinimizeButtonUnfocusBackgroundColor.
        return SetWindowTitleBarMinimizeButtonUnfocusBackgroundColor(color);
    }

    bool Window::SetTitleBarMinimizeButtonUnfocusBackgroundColor(int nRed, int nGreen, int nBlue)
    {
        // Same as SetWindowTitleBarMinimizeButtonUnfocusBackgroundColor.
        return SetWindowTitleBarMinimizeButtonUnfocusBackgroundColor(RGB(nRed, nGreen, nBlue));
    }

    bool Window::SetWindowTitleBarMinimizeButtonHoverTextColor(COLORREF color)
    {
        __CheckWarning("SetWindowTitleBarMinimizeButtonHoverTextColor");

        // Helps to set the title bar text unfocus color with the color object.
        __console.Log("SetWindowTitleBarMinimizeButtonHoverTextColor", "Setting the title bar minimize button hover text color for the window. Color: %d, %d, %d.", GetRValue(color), GetGValue(color), GetBValue(color));

        __windowTheme.windowTitleBarMinimizeButtonHoverTextColor = color;

        if (__windowHandle != NULL)
        {
            InvalidateRect(__windowHandle, NULL, TRUE);
        }

        return true;
    }

    bool Window::SetWindowTitleBarMinimizeButtonHoverTextColor(int nRed, int nGreen, int nBlue)
    {
        // Same as SetWindowTitleBarMinimizeButtonHoverTextColor.
        return SetWindowTitleBarMinimizeButtonHoverTextColor(RGB(nRed, nGreen, nBlue));
    }

    bool Window::SetTitleBarMinimizeButtonHoverTextColor(COLORREF color)
    {
        // Same as SetWindowTitleBarMinimizeButtonHoverTextColor.
        return SetWindowTitleBarMinimizeButtonHoverTextColor(color);
    }

    bool Window::SetTitleBarMinimizeButtonHoverTextColor(int nRed, int nGreen, int nBlue)
    {
        // Same as SetWindowTitleBarMinimizeButtonHoverTextColor.
        return SetWindowTitleBarMinimizeButtonHoverTextColor(RGB(nRed, nGreen, nBlue));
    }

    bool Window::SetWindowTitleBarMinimizeButtonFocusTextColor(COLORREF color)
    {
        __CheckWarning("SetWindowTitleBarMinimizeButtonFocusTextColor");

        // Helps to set the title bar text unfocus color with the color object.
        __console.Log("SetWindowTitleBarMinimizeButtonFocusTextColor", "Setting the title bar minimize button focus text color for the window. Color: %d, %d, %d.", GetRValue(color), GetGValue(color), GetBValue(color));

        __windowTheme.windowTitleBarMinimizeButtonFocusTextColor = color;

        if (__windowHandle != NULL)
        {
            InvalidateRect(__windowHandle, NULL, TRUE);
        }

        return true;
    }

    bool Window::SetWindowTitleBarMinimizeButtonFocusTextColor(int nRed, int nGreen, int nBlue)
    {
        // Same as SetWindowTitleBarMinimizeButtonFocusTextColor.
        return SetWindowTitleBarMinimizeButtonFocusTextColor(RGB(nRed, nGreen, nBlue));
    }

    bool Window::SetTitleBarMinimizeButtonFocusTextColor(COLORREF color)
    {
        // Same as SetWindowTitleBarMinimizeButtonFocusTextColor.
        return SetWindowTitleBarMinimizeButtonFocusTextColor(color);
    }

    bool Window::SetTitleBarMinimizeButtonFocusTextColor(int nRed, int nGreen, int nBlue)
    {
        // Same as SetWindowTitleBarMinimizeButtonFocusTextColor.
        return SetWindowTitleBarMinimizeButtonFocusTextColor(RGB(nRed, nGreen, nBlue));
    }

    bool Window::SetWindowTitleBarMinimizeButtonUnfocusTextColor(COLORREF color)
    {
        __CheckWarning("SetWindowTitleBarMinimizeButtonUnfocusTextColor");

        // Helps to set the title bar text unfocus color with the color object.
        __console.Log("SetWindowTitleBarMinimizeButtonUnfocusTextColor", "Setting the title bar minimize button unfocus text color for the window. Color: %d, %d, %d.", GetRValue(color), GetGValue(color), GetBValue(color));

        __windowTheme.windowTitleBarMinimizeButtonFocusTextColor = color;

        if (__windowHandle != NULL)
        {
            InvalidateRect(__windowHandle, NULL, TRUE);
        }

        return true;
    }

    bool Window::SetWindowTitleBarMinimizeButtonUnfocusTextColor(int nRed, int nGreen, int nBlue)
    {
        // Same as SetWindowTitleBarMinimizeButtonUnfocusTextColor.
        return SetWindowTitleBarMinimizeButtonUnfocusTextColor(RGB(nRed, nGreen, nBlue));
    }

    bool Window::SetTitleBarMinimizeButtonUnfocusTextColor(COLORREF color)
    {
        // Same as SetWindowTitleBarMinimizeButtonUnfocusTextColor.
        return SetWindowTitleBarMinimizeButtonUnfocusTextColor(color);
    }

    bool Window::SetTitleBarMinimizeButtonUnfocusTextColor(int nRed, int nGreen, int nBlue)
    {
        // Same as SetWindowTitleBarMinimizeButtonUnfocusTextColor.
        return SetWindowTitleBarMinimizeButtonUnfocusTextColor(RGB(nRed, nGreen, nBlue));
    }
    // [ Ending ] - Title bar minimize button controls.

    // [ Starting ] - Title bar setting button controls.
    bool Window::SetWindowTitleBarSettingButtonHoverBackgroundColor(COLORREF color)
    {
        __CheckWarning("SetWindowTitleBarSettingButtonHoverBackgroundColor");

        // Helps to set the title bar text unfocus color with the color object.
        __console.Log("SetWindowTitleBarSettingButtonHoverBackgroundColor", "Setting the title bar setting button hover background color for the window. Color: %d, %d, %d.", GetRValue(color), GetGValue(color), GetBValue(color));

        __windowTheme.windowTitleBarSettingButtonHoverBackgroundColor = color;

        if (__windowHandle != NULL)
        {
            InvalidateRect(__windowHandle, NULL, TRUE);
        }

        return true;
    }

    bool Window::SetWindowTitleBarSettingButtonHoverBackgroundColor(int nRed, int nGreen, int nBlue)
    {
        // Same as SetWindowTitleBarSettingButtonHoverBackgroundColor.
        return SetWindowTitleBarSettingButtonHoverBackgroundColor(RGB(nRed, nGreen, nBlue));
    }

    bool Window::SetTitleBarSettingButtonHoverBackgroundColor(COLORREF color)
    {
        // Same as SetWindowTitleBarSettingButtonHoverBackgroundColor.
        return SetWindowTitleBarSettingButtonHoverBackgroundColor(color);
    }

    bool Window::SetTitleBarSettingButtonHoverBackgroundColor(int nRed, int nGreen, int nBlue)
    {
        // Same as SetWindowTitleBarSettingButtonHoverBackgroundColor.
        return SetWindowTitleBarSettingButtonHoverBackgroundColor(RGB(nRed, nGreen, nBlue));
    }

    bool Window::SetWindowTitleBarSettingButtonFocusBackgroundColor(COLORREF color)
    {
        __CheckWarning("SetWindowTitleBarSettingButtonFocusBackgroundColor");

        // Helps to set the title bar text unfocus color with the color object.
        __console.Log("SetWindowTitleBarSettingButtonFocusBackgroundColor", "Setting the title bar setting button focus background color for the window. Color: %d, %d, %d.", GetRValue(color), GetGValue(color), GetBValue(color));

        __windowTheme.windowTitleBarSettingButtonFocusBackgroundColor = color;

        if (__windowHandle != NULL)
        {
            InvalidateRect(__windowHandle, NULL, TRUE);
        }

        return true;
    }

    bool Window::SetWindowTitleBarSettingButtonFocusBackgroundColor(int nRed, int nGreen, int nBlue)
    {
        // Same as SetWindowTitleBarSettingButtonFocusBackgroundColor.
        return SetWindowTitleBarSettingButtonFocusBackgroundColor(RGB(nRed, nGreen, nBlue));
    }

    bool Window::SetTitleBarSettingButtonFocusBackgroundColor(COLORREF color)
    {
        // Same as SetWindowTitleBarSettingButtonFocusBackgroundColor.
        return SetWindowTitleBarSettingButtonFocusBackgroundColor(color);
    }

    bool Window::SetTitleBarSettingButtonFocusBackgroundColor(int nRed, int nGreen, int nBlue)
    {
        // Same as SetWindowTitleBarSettingButtonFocusBackgroundColor.
        return SetWindowTitleBarSettingButtonFocusBackgroundColor(RGB(nRed, nGreen, nBlue));
    }

    bool Window::SetWindowTitleBarSettingButtonUnfocusBackgroundColor(COLORREF color)
    {
        __CheckWarning("SetWindowTitleBarSettingButtonUnfocusBackgroundColor");

        // Helps to set the title bar text unfocus color with the color object.
        __console.Log("SetWindowTitleBarSettingButtonUnfocusBackgroundColor", "Setting the title bar setting button unfocus background color for the window. Color: %d, %d, %d.", GetRValue(color), GetGValue(color), GetBValue(color));

        __windowTheme.windowTitleBarSettingButtonFocusBackgroundColor = color;

        if (__windowHandle != NULL)
        {
            InvalidateRect(__windowHandle, NULL, TRUE);
        }

        return true;
    }

    bool Window::SetWindowTitleBarSettingButtonUnfocusBackgroundColor(int nRed, int nGreen, int nBlue)
    {
        // Same as SetWindowTitleBarSettingButtonUnfocusBackgroundColor.
        return SetWindowTitleBarSettingButtonUnfocusBackgroundColor(RGB(nRed, nGreen, nBlue));
    }

    bool Window::SetTitleBarSettingButtonUnfocusBackgroundColor(COLORREF color)
    {
        // Same as SetWindowTitleBarSettingButtonUnfocusBackgroundColor.
        return SetWindowTitleBarSettingButtonUnfocusBackgroundColor(color);
    }

    bool Window::SetTitleBarSettingButtonUnfocusBackgroundColor(int nRed, int nGreen, int nBlue)
    {
        // Same as SetWindowTitleBarSettingButtonUnfocusBackgroundColor.
        return SetWindowTitleBarSettingButtonUnfocusBackgroundColor(RGB(nRed, nGreen, nBlue));
    }

    bool Window::SetWindowTitleBarSettingButtonHoverTextColor(COLORREF color)
    {
        __CheckWarning("SetWindowTitleBarSettingButtonHoverTextColor");

        // Helps to set the title bar text unfocus color with the color object.
        __console.Log("SetWindowTitleBarSettingButtonHoverTextColor", "Setting the title bar setting button hover text color for the window. Color: %d, %d, %d.", GetRValue(color), GetGValue(color), GetBValue(color));

        __windowTheme.windowTitleBarSettingButtonHoverTextColor = color;

        if (__windowHandle != NULL)
        {
            InvalidateRect(__windowHandle, NULL, TRUE);
        }

        return true;
    }

    bool Window::SetWindowTitleBarSettingButtonHoverTextColor(int nRed, int nGreen, int nBlue)
    {
        // Same as SetWindowTitleBarSettingButtonHoverTextColor.
        return SetWindowTitleBarSettingButtonHoverTextColor(RGB(nRed, nGreen, nBlue));
    }

    bool Window::SetTitleBarSettingButtonHoverTextColor(COLORREF color)
    {
        // Same as SetWindowTitleBarSettingButtonHoverTextColor.
        return SetWindowTitleBarSettingButtonHoverTextColor(color);
    }

    bool Window::SetTitleBarSettingButtonHoverTextColor(int nRed, int nGreen, int nBlue)
    {
        // Same as SetWindowTitleBarSettingButtonHoverTextColor.
        return SetWindowTitleBarSettingButtonHoverTextColor(RGB(nRed, nGreen, nBlue));
    }

    bool Window::SetWindowTitleBarSettingButtonFocusTextColor(COLORREF color)
    {
        __CheckWarning("SetWindowTitleBarSettingButtonFocusTextColor");

        // Helps to set the title bar text unfocus color with the color object.
        __console.Log("SetWindowTitleBarSettingButtonFocusTextColor", "Setting the title bar setting button focus text color for the window. Color: %d, %d, %d.", GetRValue(color), GetGValue(color), GetBValue(color));

        __windowTheme.windowTitleBarSettingButtonFocusTextColor = color;

        if (__windowHandle != NULL)
        {
            InvalidateRect(__windowHandle, NULL, TRUE);
        }

        return true;
    }

    bool Window::SetWindowTitleBarSettingButtonFocusTextColor(int nRed, int nGreen, int nBlue)
    {
        // Same as SetWindowTitleBarSettingButtonFocusTextColor.
        return SetWindowTitleBarSettingButtonFocusTextColor(RGB(nRed, nGreen, nBlue));
    }

    bool Window::SetTitleBarSettingButtonFocusTextColor(COLORREF color)
    {
        // Same as SetWindowTitleBarSettingButtonFocusTextColor.
        return SetWindowTitleBarSettingButtonFocusTextColor(color);
    }

    bool Window::SetTitleBarSettingButtonFocusTextColor(int nRed, int nGreen, int nBlue)
    {
        // Same as SetWindowTitleBarSettingButtonFocusTextColor.
        return SetWindowTitleBarSettingButtonFocusTextColor(RGB(nRed, nGreen, nBlue));
    }

    bool Window::SetWindowTitleBarSettingButtonUnfocusTextColor(COLORREF color)
    {
        __CheckWarning("SetWindowTitleBarSettingButtonUnfocusTextColor");

        // Helps to set the title bar text unfocus color with the color object.
        __console.Log("SetWindowTitleBarSettingButtonUnfocusTextColor", "Setting the title bar setting button unfocus text color for the window. Color: %d, %d, %d.", GetRValue(color), GetGValue(color), GetBValue(color));

        __windowTheme.windowTitleBarSettingButtonFocusTextColor = color;

        if (__windowHandle != NULL)
        {
            InvalidateRect(__windowHandle, NULL, TRUE);
        }

        return true;
    }

    bool Window::SetWindowTitleBarSettingButtonUnfocusTextColor(int nRed, int nGreen, int nBlue)
    {
        // Same as SetWindowTitleBarSettingButtonUnfocusTextColor.
        return SetWindowTitleBarSettingButtonUnfocusTextColor(RGB(nRed, nGreen, nBlue));
    }

    bool Window::SetTitleBarSettingButtonUnfocusTextColor(COLORREF color)
    {
        // Same as SetWindowTitleBarSettingButtonUnfocusTextColor.
        return SetWindowTitleBarSettingButtonUnfocusTextColor(color);
    }

    bool Window::SetTitleBarSettingButtonUnfocusTextColor(int nRed, int nGreen, int nBlue)
    {
        // Same as SetWindowTitleBarSettingButtonUnfocusTextColor.
        return SetWindowTitleBarSettingButtonUnfocusTextColor(RGB(nRed, nGreen, nBlue));
    }
    // [ Ending ] - Title bar setting button controls.

    // [ Starting ] - Icon Controls.
    bool Window::SetWindowTaskBarIcon(std::string sIconPath)
    {
        __CheckWarning("setWindowTaskBarIcon");

        // Helps to set the window task bar icon.
        __console.Log("SetWindowTaskBarIcon", "Setting the task bar icon. IconPath: %s", sIconPath.c_str());

        __windowTheme.windowTaskBarIcon = __TkinterWindow::LoadImageFromFile(__TkinterWindow::GetThemeConfigValue("WindowTaskBarIcon", &__console), &__console);

        if (__windowHandle != NULL)
        {
            SendMessageA(__windowHandle, WM_SETICON, ICON_BIG, (LPARAM)__windowTheme.windowTaskBarIcon);
            SendMessageA(__windowHandle, WM_SETICON, ICON_SMALL, (LPARAM)__windowTheme.windowTaskBarIcon);
            SendMessageA(GetConsoleWindow(), WM_SETICON, ICON_BIG, (LPARAM)__windowTheme.windowTaskBarIcon);
            SendMessageA(GetConsoleWindow(), WM_SETICON, ICON_SMALL, (LPARAM)__windowTheme.windowTaskBarIcon);
        }

        return true;
    }

    bool Window::SetTaskBarIcon(std::string sIconPath)
    {
        // Same as SetWindowTaskBarIcon.
        return SetWindowTaskBarIcon(sIconPath);
    }
    // [ Ending ] - Icon Controls.

    // [ Starting ] - Window name controls.
    bool Window::SetWindowTitle(std::string sWindowName)
    {
        __CheckWarning("SetWindowTitle");

        // Helps to set the title of the window.
        __console.Log("SetWindowTitle", "Setting the window title. Title: %s", sWindowName.c_str());

        __sWindowName = sWindowName;

        if (__windowHandle != NULL)
        {
            SetWindowTextA(__windowHandle, sWindowName.c_str());

            InvalidateRect(__windowHandle, NULL, TRUE);
        }

        return true;
    }

    bool Window::SetTitle(std::string sWindowName)
    {
        // Same as SetWindowTitle.
        return SetWindowTitle(sWindowName);
    }

    bool Window::SetWindowCaption(std::string sWindowName)
    {
        // Same as SetWindowTitle.
        return SetWindowTitle(sWindowName);
    }

    bool Window::SetCaption(std::string sWindowName)
    {
        // Same as SetWindowTitle.
        return SetWindowTitle(sWindowName);
    }
    // [ Ending ] - Window name controls.

    // [ Starting ] - Status bar controls.
    bool Window::SetWindowStatusBarText(std::string sText)
    {
        __CheckWarning("SetWindowStatusBarText");

        // Helps to set the text of the status bar.
        __console.Log("SetWindowStatusBarText", "Setting the text of the status bar. Text: %s.", sText.c_str());

        __sStatusBarText = sText;

        if (__windowHandle != NULL)
        {
            InvalidateRect(__windowHandle, NULL, TRUE);
        }

        return true;
    }

    bool Window::SetStatusBarText(std::string sText)
    {
        // Same as SetWindowStatusBarText.
        return SetWindowStatusBarText(sText);
    }

    bool Window::HideWindowStatusBar()
    {
        __CheckWarning("HideWindowStatusBar");

        // Helps to hide the status bar.
        __console.Log("HideWindowStatusBar", "Hiding the window status bar.");

        __bIsShowStatusBar = false;

        if (__windowHandle != NULL)
        {
            InvalidateRect(__windowHandle, NULL, TRUE);
        }

        return true;
    }

    bool Window::HideStatusBar()
    {
        // Same as HideWindowStatusBar.
        return HideWindowStatusBar();
    }

    bool Window::ShowWindowStatusBar()
    {
        __CheckWarning("ShowWindowStatusBar");

        // Helps to show the status bar.
        __console.Log("ShowWindowStatusBar", "Showing the window status bar.");

        __bIsShowStatusBar = true;

        if (__windowHandle != NULL)
        {
            InvalidateRect(__windowHandle, NULL, TRUE);
        }

        return true;
    }

    bool Window::ShowStatusBar()
    {
        // Same as ShowWindowStatusBar.
        return ShowWindowStatusBar();
    }
    // [ Ending ] - status bar controls.

    // [ Starting ] - Status bar coloring.
    bool Window::SetWindowStatusBarBackgroundColor(COLORREF color)
    {
        __CheckWarning("SetWindowStatusBarBackgroundColor");

        // Helps to set the title bar text unfocus color with the color object.
        __console.Log("SetWindowStatusBarBackgroundColor", "Setting the status bar background color. Color: %d, %d, %d.", GetRValue(color), GetGValue(color), GetBValue(color));

        __windowTheme.windowStatusBarBackgroundColor = color;

        if (__windowHandle != NULL)
        {
            InvalidateRect(__windowHandle, NULL, TRUE);
        }

        return true;
    }

    bool Window::SetWindowStatusBarBackgroundColor(int nRed, int nGreen, int nBlue)
    {
        // Same as SetWindowStatusBarBackgroundColor.
        return SetWindowStatusBarBackgroundColor(RGB(nRed, nGreen, nBlue));
    }

    bool Window::SetStatusBarBackgroundColor(COLORREF color)
    {
        // Same as SetWindowStatusBarBackgroundColor.
        return SetWindowStatusBarBackgroundColor(color);
    }

    bool Window::SetStatusBarBackgroundColor(int nRed, int nGreen, int nBlue)
    {
        // Same as SetWindowStatusBarBackgroundColor.
        return SetWindowStatusBarBackgroundColor(RGB(nRed, nGreen, nBlue));
    }

    bool Window::SetWindowStatusBarTextFocusColor(COLORREF color)
    {
        __CheckWarning("SetWindowStatusBarTextFocusColor");

        // Helps to set the title bar text unfocus color with the color object.
        __console.Log("SetWindowStatusBarTextFocusColor", "Setting the status bar text focus color. Color: %d, %d, %d.", GetRValue(color), GetGValue(color), GetBValue(color));

        __windowTheme.windowStatusBarTextFocusColor = color;

        if (__windowHandle != NULL)
        {
            InvalidateRect(__windowHandle, NULL, TRUE);
        }

        return true;
    }

    bool Window::SetWindowStatusBarTextFocusColor(int nRed, int nGreen, int nBlue)
    {
        // Same as SetWindowStatusBarTextFocusColor.
        return SetWindowStatusBarTextFocusColor(RGB(nRed, nGreen, nBlue));
    }

    bool Window::SetStatusBarTextFocusColor(COLORREF color)
    {
        // Same as SetWindowStatusBarTextFocusColor.
        return SetWindowStatusBarTextFocusColor(color);
    }

    bool Window::SetStatusBarTextFocusColor(int nRed, int nGreen, int nBlue)
    {
        // Same as SetWindowStatusBarTextFocusColor.
        return SetWindowStatusBarTextFocusColor(RGB(nRed, nGreen, nBlue));
    }

    bool Window::SetWindowStatusBarTextUnfocusColor(COLORREF color)
    {
        __CheckWarning("SetWindowStatusBarTextUnfocusColor");

        // Helps to set the title bar text unfocus color with the color object.
        __console.Log("SetWindowStatusBarTextUnfocusColor", "Setting the status bar text unfocus color. Color: %d, %d, %d.", GetRValue(color), GetGValue(color), GetBValue(color));

        __windowTheme.windowStatusBarTextUnfocusColor = color;

        if (__windowHandle != NULL)
        {
            InvalidateRect(__windowHandle, NULL, TRUE);
        }

        return true;
    }

    bool Window::SetWindowStatusBarTextUnfocusColor(int nRed, int nGreen, int nBlue)
    {
        // Same as SetWindowStatusBarTextUnfocusColor.
        return SetWindowStatusBarTextUnfocusColor(RGB(nRed, nGreen, nBlue));
    }

    bool Window::SetStatusBarTextUnfocusColor(COLORREF color)
    {
        // Same as SetWindowStatusBarTextUnfocusColor.
        return SetWindowStatusBarTextUnfocusColor(color);
    }

    bool Window::SetStatusBarTextUnfocusColor(int nRed, int nGreen, int nBlue)
    {
        // Same as SetWindowStatusBarTextUnfocusColor.
        return SetWindowStatusBarTextUnfocusColor(RGB(nRed, nGreen, nBlue));
    }
    // [ Ending ] - Status bar coloring.

    // [ Starting ] - Other Public functions.
    void Window::__SetChildWindowRepainter(bool bPainter)
    {
        // Helps to set the child window repainter stratageus.
        __bIsPaintChildWindows = bPainter;
    }
    // [ Ending ] - Other public functions.

    // [ Starting ] - destroy window functions.
    bool Window::DestroyWindow(void)
    {
        // helps to destroy the window.
        __CheckWarning("DestroyWindow");

        __console.Log("DestroyWindow", "Destroying the window.");

        return __TkinterWindow::DestroyWindowF(__windowHandle);
    }

    bool Window::Destroy(void)
    {
        // Same as DestroyWindow.
        return DestroyWindow();
    }

    bool Window::SetDefaultWindowDestroyFunction(void)
    {
        // Helps to set the default function for the destruction of the window.
        __CheckWarning("SetDefaultWidnowDestroyFunction");

        __console.Log("SetDefaultWindowDestroyFunction", "Setting the default window destroy function.");

        __bIsDefaultWindowDestroyFunction = true;

        return true;
    }

    bool Window::SetDefaultDestroyFunction(void)
    {
        // Same as SetDefaultWindowDestroyFunction.
        return SetDefaultWindowDestroyFunction();
    }

    bool Window::DisableDefaultWindowDestroyFunction(void)
    {
        // Helps to set the default function for the destruction of the window.
        __CheckWarning("DisableDefaultWindowDestroyFunction");

        __console.Log("DisableDefaultWindowDestroyFunction", "Setting the default window destroy function.");

        __bIsDefaultWindowDestroyFunction = false;

        return true;
    }

    bool Window::DisableDefaultDestroyFunction(void)
    {
        // Same as SetDefaultWindowDestroyFunction.
        return SetDefaultWindowDestroyFunction();
    }
    // [ Ending ] - destroy window functions.

    // [ Ending ] - Public functions.

    // [ Starting ] - Private Functions.
    LRESULT Window::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        // Assigning the procedure to the class procedure.

        if (message == WM_NCCREATE)
        {
            // Setting the class as user data.
            CREATESTRUCT *lParamStruct = (CREATESTRUCT *)lParam;
            TkinterWindow::Window *lpLabelClass = (TkinterWindow::Window *)lParamStruct->lpCreateParams;
            SetWindowLongPtrA(hWnd, GWLP_USERDATA, (LONG_PTR)lpLabelClass);

            return DefWindowProcA(hWnd, message, wParam, lParam);
        }
        else
        {
            // Getting the class as user data that stored in NC_CREATE.
            TkinterWindow::Window *windowObject = reinterpret_cast<TkinterWindow::Window *>(static_cast<LONG_PTR>(GetWindowLongPtrA(hWnd, GWLP_USERDATA)));

            if (windowObject)
            {
                // Returning and calling to the class procedure.

                return windowObject->WindowProcedure(hWnd, message, wParam, lParam);
            }
            else
            {
                // Returning and calling to the default window procedure.
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }

        return 0;
    }

    LRESULT Window::WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        // Helps to check the procedure.

        // Checking for the events.
        __CheckEvents(hWnd, message, wParam, lParam);

        switch (message)
        {
        case WM_PAINT:
        {
            PAINTSTRUCT paintStruct;
            HDC paintDC = BeginPaint(hWnd, &paintStruct);

            HDC hDC = CreateCompatibleDC(paintDC);

            RECT rcClientRect;
            GetClientRect(hWnd, &rcClientRect);

            HBITMAP bmp = CreateCompatibleBitmap(paintDC, rcClientRect.right - rcClientRect.left, rcClientRect.bottom - rcClientRect.top);

            HBITMAP oldBmp = (HBITMAP)SelectObject(hDC, bmp);

            // Painting with the transparent brush.
            HBRUSH transparentBrush = CreateSolidBrush(__theme->transparentColor);
            RECT rectLeftTop;
            rectLeftTop.left = 0;
            rectLeftTop.right = __windowTheme.windowBorderRadius;
            rectLeftTop.top = 0;
            rectLeftTop.bottom = __windowTheme.windowBorderRadius;

            RECT rectRightTop;
            rectRightTop.left = paintStruct.rcPaint.right - __windowTheme.windowBorderRadius;
            rectRightTop.right = paintStruct.rcPaint.right;
            rectRightTop.top = 0;
            rectRightTop.bottom = __windowTheme.windowBorderRadius;

            RECT rectLeftBottom;
            rectLeftBottom.left = 0;
            rectLeftBottom.right = __windowTheme.windowBorderRadius;
            rectLeftBottom.top = paintStruct.rcPaint.bottom - __windowTheme.windowBorderRadius;
            rectLeftBottom.bottom = paintStruct.rcPaint.bottom;

            RECT rectRightBottom;
            rectRightBottom.left = paintStruct.rcPaint.right - __windowTheme.windowBorderRadius;
            rectRightBottom.right = paintStruct.rcPaint.right;
            rectRightBottom.top = paintStruct.rcPaint.bottom - __windowTheme.windowBorderRadius;
            rectRightBottom.bottom = paintStruct.rcPaint.bottom;

            FillRect(hDC, &rectLeftTop, transparentBrush);
            FillRect(hDC, &rectRightTop, transparentBrush);
            FillRect(hDC, &rectLeftBottom, transparentBrush);
            FillRect(hDC, &rectRightBottom, transparentBrush);
            DeleteObject(transparentBrush);

            // Painting the border.
            HBRUSH backgroundBrush = CreateSolidBrush(__windowTheme.windowBackgroundColor);

            // Getting the focused window.
            bool isFocused = !!GetFocus();

            COLORREF borderColor;

            if (isFocused)
            {
                borderColor = __windowTheme.windowBorderFocusColor;
            }
            else
            {
                borderColor = __windowTheme.windowBorderUnfocusColor;
            }

            // Setting the borders colors.
            __border1.__SetBorderColor(borderColor);
            __border2.__SetBorderColor(borderColor);
            __border3.__SetBorderColor(borderColor);
            __border4.__SetBorderColor(borderColor);
            __border5.__SetBorderColor(borderColor);

            HPEN borderPen = CreatePen(PS_SOLID, 1, borderColor);
            SelectObject(hDC, backgroundBrush);
            SelectObject(hDC, borderPen);
            RoundRect(hDC, 0, 0, paintStruct.rcPaint.right - paintStruct.rcPaint.left, paintStruct.rcPaint.bottom - paintStruct.rcPaint.top, __windowTheme.windowBorderRadius, __windowTheme.windowBorderRadius);
            DeleteObject(backgroundBrush);

            // Painting the title bar.
            HBRUSH titleBarBrush = CreateSolidBrush(__windowTheme.windowTitleBarBackgroundColor);
            HPEN titleBarPen = CreatePen(PS_SOLID, 1, __windowTheme.windowTitleBarBackgroundColor);
            SelectObject(hDC, titleBarBrush);
            RoundRect(hDC, 0, 0, paintStruct.rcPaint.right - paintStruct.rcPaint.left - __theme->__positionDifference, __theme->__nTitleBarHeight + __theme->__positionDifference, __windowTheme.windowBorderRadius, __windowTheme.windowBorderRadius);
            DeleteObject(borderPen);

            SelectObject(hDC, titleBarPen);
            Rectangle(hDC, 1, 10, paintStruct.rcPaint.right - paintStruct.rcPaint.left - 1 - __theme->__positionDifference, __theme->__nTitleBarHeight + __theme->__positionDifference);
            DeleteObject(titleBarPen);
            DeleteObject(titleBarBrush);

            // Drawing the icon.
            if (isFocused)
            {
                DrawIconEx(hDC, 10 + __theme->__positionDifference, 5 + __theme->__positionDifference, __windowTheme.windowFocusIcon, 20, 20, 0, NULL, DI_NORMAL);
            }
            else
            {
                DrawIconEx(hDC, 10 + __theme->__positionDifference, 5 + __theme->__positionDifference, __windowTheme.windowUnfocusIcon, 20, 20, 0, NULL, DI_NORMAL);
            }

            // Drawing the title.
            SetBkMode(hDC, TRANSPARENT);
            if (isFocused)
            {
                SetTextColor(hDC, __windowTheme.windowTitleBarTextFocusColor);
            }
            else
            {
                SetTextColor(hDC, __windowTheme.windowTitleBarTextUnfocusColor);
            }

            __taskBarTitle.GetFontObject(hDC);

            RECT titleTextRect;
            titleTextRect.left = 35 + __theme->__positionDifference;
            titleTextRect.top = 1 + __theme->__positionDifference;
            titleTextRect.right = paintStruct.rcPaint.right - paintStruct.rcPaint.left - 1 - __theme->__positionDifference;
            titleTextRect.bottom = __theme->__nTitleBarHeight + __theme->__positionDifference;

            DrawTextA(hDC, __sWindowName.c_str(), __sWindowName.length(), &titleTextRect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
            __taskBarTitle.DeleteFontObject();

            // Drawing the buttons.
            __DrawCloseButton(hDC, paintStruct.rcPaint, borderColor);
            __DrawMaximizeButton(hDC, paintStruct.rcPaint);
            __DrawMinimizeButton(hDC, paintStruct.rcPaint);
            __DrawSettingsButton(hDC, paintStruct.rcPaint);

            // Drawing the status bar.
            HBRUSH statusBarBackgroundBrush = CreateSolidBrush(__windowTheme.windowStatusBarBackgroundColor);
            HPEN statusBarBorderPen = CreatePen(PS_SOLID, 1, borderColor);
            HPEN statusBarPen = CreatePen(PS_SOLID, 1, __windowTheme.windowStatusBarBackgroundColor);

            SelectObject(hDC, statusBarBackgroundBrush);
            SelectObject(hDC, statusBarBorderPen);
            RoundRect(hDC, 0, paintStruct.rcPaint.bottom - paintStruct.rcPaint.top - __theme->__nStatusBarHeight - 1 - __theme->__positionDifference, paintStruct.rcPaint.right - paintStruct.rcPaint.left - 1, paintStruct.rcPaint.bottom - paintStruct.rcPaint.top - 1 - __theme->__positionDifference, __windowTheme.windowBorderRadius, __windowTheme.windowBorderRadius);
            DeleteObject(statusBarBorderPen);

            SelectObject(hDC, statusBarPen);
            Rectangle(hDC, 1, paintStruct.rcPaint.bottom - paintStruct.rcPaint.top - __theme->__nStatusBarHeight - 1 - __theme->__positionDifference, paintStruct.rcPaint.right - paintStruct.rcPaint.left - 2, paintStruct.rcPaint.bottom - paintStruct.rcPaint.top - __windowTheme.windowBorderRadius - __theme->__positionDifference);
            DeleteObject(statusBarBackgroundBrush);
            DeleteObject(statusBarPen);

            if (__bIsShowStatusBar)
            {
                // Drawing status bar text.
                SetBkMode(hDC, TRANSPARENT);
                if (isFocused)
                {
                    SetTextColor(hDC, __windowTheme.windowStatusBarTextFocusColor);
                }
                else
                {
                    SetTextColor(hDC, __windowTheme.windowStatusBarTextUnfocusColor);
                }

                __statusBarFont.GetFontObject(hDC);

                RECT statusBarRect;
                statusBarRect.left = 10 + __theme->__positionDifference;
                statusBarRect.right = paintStruct.rcPaint.right - paintStruct.rcPaint.left - 10 - __theme->__positionDifference;
                statusBarRect.top = paintStruct.rcPaint.bottom - paintStruct.rcPaint.top - __theme->__nStatusBarHeight - __theme->__positionDifference;
                statusBarRect.bottom = paintStruct.rcPaint.bottom - paintStruct.rcPaint.top - 1 - __theme->__positionDifference;

                DrawTextA(hDC, __sStatusBarText.c_str(), __sStatusBarText.length(), &statusBarRect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
                __statusBarFont.DeleteFontObject();

                if (!__TkinterWindow::GetWindowMaximizedStatus(hWnd))
                {
                    HPEN resizerPen;

                    int width = paintStruct.rcPaint.right - paintStruct.rcPaint.left;
                    int height = paintStruct.rcPaint.bottom - paintStruct.rcPaint.top - 3;

                    if (isFocused)
                    {
                        resizerPen = CreatePen(PS_SOLID, 1, __windowTheme.windowStatusBarTextFocusColor);
                    }
                    else
                    {
                        resizerPen = CreatePen(PS_SOLID, 1, __windowTheme.windowStatusBarTextUnfocusColor);
                    }

                    SelectObject(hDC, resizerPen);
                    // Line 1
                    MoveToEx(hDC, width - 7, height - 4, NULL);
                    LineTo(hDC, width - 8, height - 4);

                    MoveToEx(hDC, width - 9, height - 4, NULL);
                    LineTo(hDC, width - 10, height - 4);

                    MoveToEx(hDC, width - 11, height - 4, NULL);
                    LineTo(hDC, width - 12, height - 4);

                    MoveToEx(hDC, width - 13, height - 4, NULL);
                    LineTo(hDC, width - 14, height - 4);
                    // Line 1

                    // Line 2
                    MoveToEx(hDC, width - 7, height - 6, NULL);
                    LineTo(hDC, width - 8, height - 6);

                    MoveToEx(hDC, width - 9, height - 6, NULL);
                    LineTo(hDC, width - 10, height - 6);

                    MoveToEx(hDC, width - 11, height - 6, NULL);
                    LineTo(hDC, width - 12, height - 6);
                    // Line 2

                    // Line 3
                    MoveToEx(hDC, width - 7, height - 8, NULL);
                    LineTo(hDC, width - 8, height - 8);

                    MoveToEx(hDC, width - 9, height - 8, NULL);
                    LineTo(hDC, width - 10, height - 8);
                    // Line 3

                    // Line 4
                    MoveToEx(hDC, width - 7, height - 10, NULL);
                    LineTo(hDC, width - 8, height - 10);
                    // Line 4

                    DeleteObject(resizerPen);
                }
            }

            BitBlt(paintDC, 0, 0, rcClientRect.right - rcClientRect.left, rcClientRect.bottom - rcClientRect.top, hDC, 0, 0, SRCCOPY);

            SelectObject(hDC, oldBmp);
            DeleteObject(bmp);
            DeleteDC(hDC);

            EndPaint(hWnd, &paintStruct);

            break;
        }

        case WM_NCPAINT:
        {
            // Helps to paint the borders.
            __border1.UpdateBorder();
            __border2.UpdateBorder();
            __border3.UpdateBorder();
            __border4.UpdateBorder();
            __border5.UpdateBorder();

            return DefWindowProcA(hWnd, message, wParam, lParam);
        }

        case WM_SETCURSOR:
        {
            // Setting the cursor.
            __bIsCloseButtonResizeWindow = false;
            __bOtherButtonResizeWindow = false;

            POINT mousePosition;

            GetCursorPos(&mousePosition);
            ScreenToClient(hWnd, &mousePosition);

            RECT windowRect;
            GetWindowRect(hWnd, &windowRect);

            mousePosition.x -= __theme->__positionDifference;
            mousePosition.y -= __theme->__positionDifference;
            int height = windowRect.bottom - windowRect.top - __theme->__positionDifference;
            int width = windowRect.right - windowRect.left - __theme->__positionDifference;

            if (!__TkinterWindow::GetWindowMaximizedStatus(hWnd))
            {
                if ((mousePosition.x < 10) && (mousePosition.y < 10))
                {
                    __TkinterWindow::SetCursorF(__windowTheme.windowTopLeftResizeCursor);
                }
                else if ((mousePosition.x < 10) && (mousePosition.y > (height - 10)))
                {
                    __TkinterWindow::SetCursorF(__windowTheme.windowTopRightResizeCursor);
                }
                else if ((mousePosition.x > (width - 10)) && (mousePosition.y < 10))
                {
                    __bIsCloseButtonResizeWindow = true;
                    __TkinterWindow::SetCursorF(__windowTheme.windowBottomLeftResizeCursor);
                }
                else if ((mousePosition.x > (width - 10)) && (mousePosition.y > (height - 10)))
                {
                    __TkinterWindow::SetCursorF(__windowTheme.windowBottomRightResizeCursor);
                }
                else if (mousePosition.x < 8)
                {
                    __TkinterWindow::SetCursorF(__windowTheme.windowLeftResizeCursor);
                }
                else if (mousePosition.y < 8)
                {
                    __bIsCloseButtonResizeWindow = true;
                    __bOtherButtonResizeWindow = true;
                    __TkinterWindow::SetCursorF(__windowTheme.windowTopResizeCursor);
                }
                else if (mousePosition.x > (width - 8))
                {
                    __bIsCloseButtonResizeWindow = true;
                    __TkinterWindow::SetCursorF(__windowTheme.windowRightResizeCursor);
                }
                else if (mousePosition.y > (height - 8))
                {
                    __TkinterWindow::SetCursorF(__windowTheme.windowBottomResizeCursor);
                }
                else if (__bIsCloseButtonHover)
                {
                    __TkinterWindow::SetCursorF(__windowTheme.windowCursor);
                }
                else if (__bIsMaximizeButtonHover)
                {
                    __TkinterWindow::SetCursorF(__windowTheme.windowCursor);
                }
                else if (__bIsMinimizeButtonHover)
                {
                    __TkinterWindow::SetCursorF(__windowTheme.windowCursor);
                }
                else
                {
                    __TkinterWindow::SetCursorF(__windowTheme.windowCursor);
                }
            }
            else
            {
                __TkinterWindow::SetCursorF(__windowTheme.windowCursor);
            }

            break;
        }

        case WM_NCHITTEST:
        {
            // Making the window moveable and draggable.
            LRESULT hit = DefWindowProcA(hWnd, message, wParam, lParam);

            if (hit = HTNOWHERE)
            {
                return hit;
            }

            __bIsCloseButtonResizeWindow = false;
            __bOtherButtonResizeWindow = false;

            POINT mousePosition;

            GetCursorPos(&mousePosition);
            ScreenToClient(hWnd, &mousePosition);

            RECT windowRect;
            GetWindowRect(hWnd, &windowRect);

            mousePosition.x -= __theme->__positionDifference;
            mousePosition.y -= __theme->__positionDifference;
            int height = windowRect.bottom - windowRect.top - __theme->__positionDifference;
            int width = windowRect.right - windowRect.left - __theme->__positionDifference;

            if ((mousePosition.x > 9) && (mousePosition.y > 4) && (mousePosition.x < 29 + __theme->__positionDifference) && (mousePosition.y < 24 + __theme->__positionDifference))
            {
                return HTMENU;
            }
            else if (__bIsCloseButtonHover)
            {
                return HTCLOSE;
            }
            else if (__bIsMaximizeButtonHover)
            {
                return HTMAXBUTTON;
            }
            else if (__bIsMinimizeButtonHover)
            {
                return HTMINBUTTON;
            }
            else if ((mousePosition.y > 8) && (mousePosition.y < __theme->__nTitleBarHeight) && (mousePosition.x > 8) && (mousePosition.x < (width - 8)))
            {
                return HTCAPTION;
            }
            else if ((mousePosition.x < 10) && (mousePosition.y < 10))
            {
                __bIsCloseButtonResizeWindow = true;
                return HTTOPLEFT;
            }
            else if ((mousePosition.x < 10) && (mousePosition.y > (height - 10)))
            {
                return HTBOTTOMLEFT;
            }
            else if ((mousePosition.x > (width - 10)) && (mousePosition.y < 10))
            {
                return HTTOPRIGHT;
            }
            else if ((mousePosition.x > (width - 10)) && (mousePosition.y > (height - 10)))
            {
                return HTBOTTOMRIGHT;
            }
            else if (mousePosition.x < 8)
            {
                return HTLEFT;
            }
            else if (mousePosition.y < 8)
            {
                __bIsCloseButtonResizeWindow = true;
                __bOtherButtonResizeWindow = true;
                return HTTOP;
            }
            else if (mousePosition.x > (width - 8))
            {
                __bIsCloseButtonResizeWindow = true;
                return HTRIGHT;
            }
            else if (mousePosition.y > (height - 8))
            {
                return HTBOTTOM;
            }
            else
            {
                return HTCLIENT;
            }

            break;
        }

        case WM_NCLBUTTONDOWN:
        {
            if ((__bIsCloseButtonHover) || (__bIsMaximizeButtonHover) || (__bIsMinimizeButtonHover) || (__bIsSettingButtonHover))
            {
                InvalidateRect(hWnd, NULL, TRUE);
                break;
            }

            return DefWindowProcA(hWnd, message, wParam, lParam);

            break;
        }

        case WM_CLOSE:
        {
            // Helps to destroy the window.
            if (__bIsDefaultWindowDestroyFunction)
            {
                DestroyWindow();
            }

            break;
        }

        case WM_DESTROY:
        {
            // Quitting the main loop of the window.
            PostQuitMessage(0);

            break;
        }

        case WM_NCLBUTTONUP:
        {
            // Checking for the button clicks and actions.
            if (__bIsCloseButtonHover)
            {
                SendMessageA(hWnd, WM_CLOSE, NULL, NULL);
                __bIsCloseButtonHover = false;
                InvalidateRect(hWnd, NULL, TRUE);
            }
            else if (__bIsMaximizeButtonHover)
            {
                if (__TkinterWindow::GetWindowMaximizedStatus(hWnd))
                {
                    ShowWindow(hWnd, SW_NORMAL);
                }
                else
                {
                    ShowWindow(hWnd, SW_MAXIMIZE);
                }
                __bIsMaximizeButtonHover = false;
                InvalidateRect(hWnd, NULL, TRUE);
            }
            else if (__bIsMinimizeButtonHover)
            {
                ShowWindow(hWnd, SW_MINIMIZE);
                __bIsMinimizeButtonHover = false;
                InvalidateRect(hWnd, NULL, TRUE);
            }
            else if (__bIsSettingButtonHover)
            {
                __bIsSettingButtonHover = false;
                InvalidateRect(hWnd, NULL, TRUE);
                // We will do it later.
            }

            break;
        }

        case WM_ACTIVATE:
        {
            // Controls the focus and unfocus events.
            if (LOWORD(wParam) == WA_INACTIVE)
            {
                InvalidateRect(hWnd, NULL, TRUE);
            }
            else
            {
                InvalidateRect(hWnd, NULL, TRUE);
            }

            break;
        }

        case WM_ENTERSIZEMOVE:
        {
            // Setting pixels to visible in order to get rid of fluckkerings.
            SetLayeredWindowAttributes(hWnd, 0, 255, LWA_ALPHA);

            // Disabling border updation.
            __border1.DisableUpdate();
            __border2.DisableUpdate();
            __border3.DisableUpdate();
            __border4.DisableUpdate();
            __border5.DisableUpdate();

            break;
        }

        case WM_EXITSIZEMOVE:
        {
            // Setting the pixels to transparent.
            SetLayeredWindowAttributes(hWnd, __theme->transparentColor, 255, LWA_COLORKEY);

            // Enabling the border updation.
            __border1.EnableUpdate();
            __border2.EnableUpdate();
            __border3.EnableUpdate();
            __border4.EnableUpdate();
            __border5.EnableUpdate();

            // Sending the event to the border window.
            __border1.UpdateBorder();
            __border2.UpdateBorder();
            __border3.UpdateBorder();
            __border4.UpdateBorder();
            __border5.UpdateBorder();

            break;
        }

        case WM_ERASEBKGND:
        {
            return 1;
        }

        case WM_MOVE:
        {
            // Helps to control some moment behaviour of window.
            if (__bIsMoveSize)
            {
                // Sending the event to the border window.
                __border1.UpdateBorder();
                __border2.UpdateBorder();
                __border3.UpdateBorder();
                __border4.UpdateBorder();
                __border5.UpdateBorder();

                __bIsMoveSize = false;
            }

            break;
        }

        case WM_NCCALCSIZE:
        {
            // Removing the background.
            if (wParam == TRUE)
            {
                return 0;
            }

            break;
        }

        case WM_SIZE:
        {
            // Resizing the window.
            // Setting the difference to 0.
            __theme->__positionDifference = 0;

            // Saving the state and repainting the window.
            if (wParam == SIZE_MAXIMIZED)
            {
                // Sending the event to the border window.
                __border1.UpdateBorder();
                __border2.UpdateBorder();
                __border3.UpdateBorder();
                __border4.UpdateBorder();
                __border5.UpdateBorder();

                // Setting the difference to maximize size.
                __theme->__positionDifference = 8;
            }
            else if (wParam == SIZE_MINIMIZED)
            {
                // Sending the event to the border window.
                __border1.UpdateBorder();
                __border2.UpdateBorder();
                __border3.UpdateBorder();
                __border4.UpdateBorder();
                __border5.UpdateBorder();
            }
            else if (wParam == SIZE_RESTORED)
            {
                // Sending the event to the border window.
                __border1.UpdateBorder();
                __border2.UpdateBorder();
                __border3.UpdateBorder();
                __border4.UpdateBorder();
                __border5.UpdateBorder();
            }

            // Updating the child windows.
            for (HWND hWndChild = GetWindow(__windowHandle, GW_CHILD); hWndChild != NULL; hWndChild = GetNextWindow(hWndChild, GW_HWNDNEXT))
            {
                SendMessageA(hWndChild, WM_SIZE, NULL, NULL);
            }
            break;
        }

        case WM_NCMOUSELEAVE:
        {
            // Checking for the unhovering of the button.
            if ((__bIsCloseButtonHover) || (__bIsMaximizeButtonHover) || (__bIsMinimizeButtonHover) || (__bIsSettingButtonHover))
            {
                __bIsCloseButtonHover = false;
                __bIsMaximizeButtonHover = false;
                __bIsMinimizeButtonHover = false;
                __bIsSettingButtonHover = false;
                InvalidateRect(hWnd, NULL, TRUE);
            }

            break;
        }

        case WM_MOUSEMOVE:
        {
            // Checking for Enter and Leave events.
            TRACKMOUSEEVENT tme;
            tme.cbSize = sizeof(TRACKMOUSEEVENT);
            tme.dwFlags = TME_HOVER | TME_LEAVE;
            tme.dwHoverTime = 1;
            tme.hwndTrack = hWnd;
            TrackMouseEvent(&tme);

            if ((__bIsCloseButtonHover) || (__bIsMaximizeButtonHover) || (__bIsMinimizeButtonHover) || (__bIsSettingButtonHover))
            {
                __bIsCloseButtonHover = false;
                __bIsMaximizeButtonHover = false;
                __bIsMinimizeButtonHover = false;
                __bIsSettingButtonHover = false;
                InvalidateRect(hWnd, NULL, TRUE);
            }

            break;
        }

        case WM_CREATE:
        {
            // Helps to fix the kill focus and set focus problem.
            CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)__TkinterWindow::ActivateWindow, hWnd, 0, NULL);
            CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)__TkinterWindow::UpdateChildWindows, this, NULL, NULL);
            break;
        }

        case WM_NCMOUSEMOVE:
        {
            // controlling the hovering functionalities of the buttons.
            POINT cursorPoint;
            GetCursorPos(&cursorPoint);
            ScreenToClient(hWnd, &cursorPoint);

            RECT windowRect;
            GetWindowRect(hWnd, &windowRect);

            // Checking for the close button hovering.
            if ((PtInRect(&__GetButtonRect(windowRect, 43, 0), cursorPoint)) && (!__bIsCloseButtonResizeWindow))
            {
                if (!__bIsCloseButtonHover)
                {
                    __bIsCloseButtonHover = true;
                    InvalidateRect(hWnd, NULL, TRUE);
                }
            }
            else
            {
                if (__bIsCloseButtonHover)
                {
                    __bIsCloseButtonHover = false;
                    InvalidateRect(hWnd, NULL, TRUE);
                }
            }

            // checking for the maximize button hovering.
            if ((PtInRect(&__GetButtonRect(windowRect, 85, 42), cursorPoint)) && (!__bOtherButtonResizeWindow))
            {
                if (!__bIsMaximizeButtonHover)
                {
                    __bIsMaximizeButtonHover = true;
                    InvalidateRect(hWnd, NULL, TRUE);
                }
            }
            else
            {
                if (__bIsMaximizeButtonHover)
                {
                    __bIsMaximizeButtonHover = false;
                    InvalidateRect(hWnd, NULL, TRUE);
                }
            }

            // checking for the minimize button hovering.
            if ((PtInRect(&__GetButtonRect(windowRect, 127, 84), cursorPoint)) && (!__bOtherButtonResizeWindow))
            {
                if (!__bIsMinimizeButtonHover)
                {
                    __bIsMinimizeButtonHover = true;
                    InvalidateRect(hWnd, NULL, TRUE);
                }
            }
            else
            {
                if (__bIsMinimizeButtonHover)
                {
                    __bIsMinimizeButtonHover = false;
                    InvalidateRect(hWnd, NULL, TRUE);
                }
            }

            // checking for the setting button hovering.
            if ((PtInRect(&__GetButtonRect(windowRect, 169, 126), cursorPoint)) && (!__bOtherButtonResizeWindow))
            {
                if (!__bIsSettingButtonHover)
                {
                    __bIsSettingButtonHover = true;
                    InvalidateRect(hWnd, NULL, TRUE);
                }
            }
            else
            {
                if (__bIsSettingButtonHover)
                {
                    __bIsSettingButtonHover = false;
                    InvalidateRect(hWnd, NULL, TRUE);
                }
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

    void Window::__CheckWarning(std::string sFunctionName)
    {
        if (__windowHandle == NULL)
        {
            __console.Log(sFunctionName, "Warning: The function is called before the initalization. It can lead to some major problems.");
        }
    }

    void Window::__DrawCloseButton(HDC hDC, RECT windowRect, COLORREF borderColor)
    {
        // Helps to create the close button.

        // Creating the compatible brush and pen for button.
        HBRUSH backgroundBrush;
        HPEN backgroundPen;

        bool bIsFocused = !!GetFocus();

        if (__bIsCloseButtonHover)
        {
            backgroundBrush = CreateSolidBrush(__windowTheme.windowTitleBarCloseButtonHoverBackgroundColor);
            backgroundPen = CreatePen(PS_SOLID, 1, __windowTheme.windowTitleBarCloseButtonHoverBackgroundColor);
        }
        else
        {
            if (bIsFocused)
            {
                backgroundBrush = CreateSolidBrush(__windowTheme.windowTitleBarCloseButtonFocusBackgroundColor);
                backgroundPen = CreatePen(PS_SOLID, 1, __windowTheme.windowTitleBarCloseButtonFocusBackgroundColor);
            }
            else
            {
                backgroundBrush = CreateSolidBrush(__windowTheme.windowTitleBarCloseButtonUnfocusBackgroundColor);
                backgroundPen = CreatePen(PS_SOLID, 1, __windowTheme.windowTitleBarCloseButtonUnfocusBackgroundColor);
            }
        }

        // border pen.
        HPEN borderPen = CreatePen(PS_SOLID, 1, borderColor);

        // Drawing the box.
        SelectObject(hDC, backgroundBrush);
        SelectObject(hDC, borderPen);
        RoundRect(hDC, windowRect.right - windowRect.left - __nTitleBarButtonWidth - 1 - __theme->__positionDifference, 0 - __theme->__positionDifference, windowRect.right - windowRect.left - 1 + __theme->__positionDifference, __nTitleBarButtonHeight - 1 + __theme->__positionDifference, __windowTheme.windowBorderRadius, __windowTheme.windowBorderRadius);
        DeleteObject(backgroundBrush);
        DeleteObject(borderPen);

        SelectObject(hDC, backgroundPen);
        Rectangle(hDC, windowRect.right - windowRect.left - __nTitleBarButtonWidth - 1 - __theme->__positionDifference, __windowTheme.windowBorderRadius - __theme->__positionDifference, windowRect.right - windowRect.left - 2 + __theme->__positionDifference, __nTitleBarButtonHeight - 1 + __theme->__positionDifference);
        Rectangle(hDC, windowRect.right - windowRect.left - __nTitleBarButtonWidth - 1 - __theme->__positionDifference, 1 - __theme->__positionDifference, windowRect.right - windowRect.left - 10 + __theme->__positionDifference, __nTitleBarButtonHeight - 1 + __theme->__positionDifference);
        DeleteObject(backgroundBrush);
        DeleteObject(backgroundPen);

        // Drawing the shape on the button.

        // Getting the accurate color
        int nRed, nGreen, nBlue;

        if (__bIsCloseButtonHover)
        {
            nRed = GetRValue(__windowTheme.windowTitleBarCloseButtonHoverTextColor);
            nGreen = GetGValue(__windowTheme.windowTitleBarCloseButtonHoverTextColor);
            nBlue = GetBValue(__windowTheme.windowTitleBarCloseButtonHoverTextColor);
        }
        else
        {
            if (bIsFocused)
            {
                nRed = GetRValue(__windowTheme.windowTitleBarCloseButtonFocusTextColor);
                nGreen = GetGValue(__windowTheme.windowTitleBarCloseButtonFocusTextColor);
                nBlue = GetBValue(__windowTheme.windowTitleBarCloseButtonFocusTextColor);
            }
            else
            {
                nRed = GetRValue(__windowTheme.windowTitleBarCloseButtonUnfocusTextColor);
                nGreen = GetGValue(__windowTheme.windowTitleBarCloseButtonUnfocusTextColor);
                nBlue = GetBValue(__windowTheme.windowTitleBarCloseButtonUnfocusTextColor);
            }
        }

        Gdiplus::Graphics graphics(hDC);

        Gdiplus::Pen transparentPen(Gdiplus::Color(150, nRed, nGreen, nBlue), 1);
        Gdiplus::Pen drawingPen(Gdiplus::Color(255, nRed, nGreen, nBlue), 1);

        int x = windowRect.right - windowRect.left - __nTitleBarButtonWidth + 15 - __theme->__positionDifference;
        int y = __nTitleBarButtonHeight - 20 + __theme->__positionDifference;

        // Drawing lines
        graphics.DrawLine(&transparentPen, x + 1, y, x + 9, y + 8);
        graphics.DrawLine(&transparentPen, x, y + 1, x + 8, y + 9);
        graphics.DrawLine(&transparentPen, x + 9, y + 1, x + 1, y + 9);
        graphics.DrawLine(&transparentPen, x + 8, y, x, y + 8);

        // Drawing lines
        graphics.DrawLine(&drawingPen, x, y, x + 9, y + 9);
        graphics.DrawLine(&drawingPen, x + 9, y, x, y + 9);
    }

    void Window::__DrawMaximizeButton(HDC hDC, RECT windowRect)
    {
        // Helps to create the maximize button.

        // Creating the compatible brush and pen for button.
        HBRUSH backgroundBrush;
        HPEN backgroundPen;

        bool bIsFocused = !!GetFocus();

        if (__bIsMaximizeButtonHover)
        {
            backgroundBrush = CreateSolidBrush(__windowTheme.windowTitleBarMaximizeButtonHoverBackgroundColor);
            backgroundPen = CreatePen(PS_SOLID, 1, __windowTheme.windowTitleBarMaximizeButtonHoverBackgroundColor);
        }
        else
        {
            if (bIsFocused)
            {
                backgroundBrush = CreateSolidBrush(__windowTheme.windowTitleBarMaximizeButtonFocusBackgroundColor);
                backgroundPen = CreatePen(PS_SOLID, 1, __windowTheme.windowTitleBarMaximizeButtonFocusBackgroundColor);
            }
            else
            {
                backgroundBrush = CreateSolidBrush(__windowTheme.windowTitleBarMaximizeButtonUnfocusBackgroundColor);
                backgroundPen = CreatePen(PS_SOLID, 1, __windowTheme.windowTitleBarMaximizeButtonUnfocusBackgroundColor);
            }
        }

        // Drawing the box for button.
        SelectObject(hDC, backgroundBrush);
        SelectObject(hDC, backgroundPen);
        Rectangle(hDC, windowRect.right - windowRect.left - __nTitleBarButtonWidth - 43 - __theme->__positionDifference, 1, windowRect.right - windowRect.left - 44 - __theme->__positionDifference, __nTitleBarButtonHeight - 1 + __theme->__positionDifference);
        DeleteObject(backgroundBrush);
        DeleteObject(backgroundPen);

        // Drawing the shape on the button.

        // Getting the accurate color
        int nRed, nGreen, nBlue;

        if (__bIsMaximizeButtonHover)
        {
            nRed = GetRValue(__windowTheme.windowTitleBarMaximizeButtonHoverTextColor);
            nGreen = GetGValue(__windowTheme.windowTitleBarMaximizeButtonHoverTextColor);
            nBlue = GetBValue(__windowTheme.windowTitleBarMaximizeButtonHoverTextColor);
        }
        else
        {
            if (bIsFocused)
            {
                nRed = GetRValue(__windowTheme.windowTitleBarMaximizeButtonFocusTextColor);
                nGreen = GetGValue(__windowTheme.windowTitleBarMaximizeButtonFocusTextColor);
                nBlue = GetBValue(__windowTheme.windowTitleBarMaximizeButtonFocusTextColor);
            }
            else
            {
                nRed = GetRValue(__windowTheme.windowTitleBarMaximizeButtonUnfocusTextColor);
                nGreen = GetGValue(__windowTheme.windowTitleBarMaximizeButtonUnfocusTextColor);
                nBlue = GetBValue(__windowTheme.windowTitleBarMaximizeButtonUnfocusTextColor);
            }
        }

        Gdiplus::Graphics graphics(hDC);

        Gdiplus::Pen transparentPen(Gdiplus::Color(150, nRed, nGreen, nBlue), 1);
        Gdiplus::Pen drawingPen(Gdiplus::Color(255, nRed, nGreen, nBlue), 1);

        int x = windowRect.right - windowRect.left - __nTitleBarButtonWidth - 27 - __theme->__positionDifference;
        int y = __nTitleBarButtonHeight - 20 + __theme->__positionDifference;

        if (__TkinterWindow::GetWindowMaximizedStatus(__windowHandle))
        {
            graphics.DrawLine(&transparentPen, x, y, x + 7, y);
            graphics.DrawLine(&transparentPen, x, y, x, y + 7);
            graphics.DrawLine(&transparentPen, x + 7, y, x + 7, y + 7);
            graphics.DrawLine(&transparentPen, x, y + 7, x + 7, y + 7);
            graphics.DrawLine(&transparentPen, x + 2, y - 2, x + 8, y - 2);
            graphics.DrawLine(&transparentPen, x + 8, y - 1, x + 9, y - 1);
            graphics.DrawLine(&transparentPen, x + 9, y, x + 9, y + 5);

            graphics.DrawLine(&drawingPen, x + 1, y, x + 6, y);
            graphics.DrawLine(&drawingPen, x, y + 1, x, y + 6);
            graphics.DrawLine(&drawingPen, x + 7, y + 1, x + 7, y + 6);
            graphics.DrawLine(&drawingPen, x + 1, y + 7, x + 6, y + 7);
            graphics.DrawLine(&drawingPen, x + 3, y - 2, x + 7, y - 2);
            SetPixel(hDC, x + 8, y - 1, RGB(nRed, nGreen, nBlue));
            graphics.DrawLine(&drawingPen, x + 9, y, x + 9, y + 4);
        }
        else
        {
            graphics.DrawLine(&transparentPen, x, y, x + 9, y);
            graphics.DrawLine(&transparentPen, x, y, x, y + 9);
            graphics.DrawLine(&transparentPen, x + 9, y, x + 9, y + 9);
            graphics.DrawLine(&transparentPen, x, y + 9, x + 9, y + 9);

            // Drawing lines
            graphics.DrawLine(&drawingPen, x + 1, y, x + 8, y);
            graphics.DrawLine(&drawingPen, x, y + 1, x, y + 8);
            graphics.DrawLine(&drawingPen, x + 9, y + 1, x + 9, y + 8);
            graphics.DrawLine(&drawingPen, x + 1, y + 9, x + 8, y + 9);
        }
    }

    void Window::__DrawMinimizeButton(HDC hDC, RECT windowRect)
    {
        // Helps to create the minimize button.

        // Creating the compatible brush and pen for button.
        HBRUSH backgroundBrush;
        HPEN backgroundPen;

        bool bIsFocused = !!GetFocus();

        if (__bIsMinimizeButtonHover)
        {
            backgroundBrush = CreateSolidBrush(__windowTheme.windowTitleBarMinimizeButtonHoverBackgroundColor);
            backgroundPen = CreatePen(PS_SOLID, 1, __windowTheme.windowTitleBarMinimizeButtonHoverBackgroundColor);
        }
        else
        {
            if (bIsFocused)
            {
                backgroundBrush = CreateSolidBrush(__windowTheme.windowTitleBarMinimizeButtonFocusBackgroundColor);
                backgroundPen = CreatePen(PS_SOLID, 1, __windowTheme.windowTitleBarMinimizeButtonFocusBackgroundColor);
            }
            else
            {
                backgroundBrush = CreateSolidBrush(__windowTheme.windowTitleBarMinimizeButtonUnfocusBackgroundColor);
                backgroundPen = CreatePen(PS_SOLID, 1, __windowTheme.windowTitleBarMinimizeButtonUnfocusBackgroundColor);
            }
        }

        // Drawing the box for button.
        SelectObject(hDC, backgroundBrush);
        SelectObject(hDC, backgroundPen);
        Rectangle(hDC, windowRect.right - windowRect.left - 127 - __theme->__positionDifference, 1, windowRect.right - windowRect.left - 86 - __theme->__positionDifference, __nTitleBarButtonHeight - 1 + __theme->__positionDifference);
        DeleteObject(backgroundBrush);
        DeleteObject(backgroundPen);

        // Drawing the shape on the button.

        // Getting the accurate color
        int nRed, nGreen, nBlue;

        if (__bIsMinimizeButtonHover)
        {
            nRed = GetRValue(__windowTheme.windowTitleBarMinimizeButtonHoverTextColor);
            nGreen = GetGValue(__windowTheme.windowTitleBarMinimizeButtonHoverTextColor);
            nBlue = GetBValue(__windowTheme.windowTitleBarMinimizeButtonHoverTextColor);
        }
        else
        {
            if (bIsFocused)
            {
                nRed = GetRValue(__windowTheme.windowTitleBarMinimizeButtonFocusTextColor);
                nGreen = GetGValue(__windowTheme.windowTitleBarMinimizeButtonFocusTextColor);
                nBlue = GetBValue(__windowTheme.windowTitleBarMinimizeButtonFocusTextColor);
            }
            else
            {
                nRed = GetRValue(__windowTheme.windowTitleBarMinimizeButtonUnfocusTextColor);
                nGreen = GetGValue(__windowTheme.windowTitleBarMinimizeButtonUnfocusTextColor);
                nBlue = GetBValue(__windowTheme.windowTitleBarMinimizeButtonUnfocusTextColor);
            }
        }

        Gdiplus::Graphics graphics(hDC);

        Gdiplus::Pen drawingPen(Gdiplus::Color(255, nRed, nGreen, nBlue), 1);

        int x = windowRect.right - windowRect.left - __nTitleBarButtonWidth - 70 - __theme->__positionDifference;
        int y = __nTitleBarButtonHeight - 15 + __theme->__positionDifference;

        graphics.DrawLine(&drawingPen, x + 1, y, x + 10, y);
    }

    void Window::__DrawSettingsButton(HDC hDC, RECT windowRect)
    {
        // Helps to create the settings button.

        // Creating the compatible brush and pen for button.
        HBRUSH backgroundBrush;
        HPEN backgroundPen;

        bool bIsFocused = !!GetFocus();

        if (__bIsSettingButtonHover)
        {
            backgroundBrush = CreateSolidBrush(__windowTheme.windowTitleBarSettingButtonHoverBackgroundColor);
            backgroundPen = CreatePen(PS_SOLID, 1, __windowTheme.windowTitleBarSettingButtonHoverBackgroundColor);
        }
        else
        {
            if (bIsFocused)
            {
                backgroundBrush = CreateSolidBrush(__windowTheme.windowTitleBarSettingButtonFocusBackgroundColor);
                backgroundPen = CreatePen(PS_SOLID, 1, __windowTheme.windowTitleBarSettingButtonFocusBackgroundColor);
            }
            else
            {
                backgroundBrush = CreateSolidBrush(__windowTheme.windowTitleBarSettingButtonUnfocusBackgroundColor);
                backgroundPen = CreatePen(PS_SOLID, 1, __windowTheme.windowTitleBarSettingButtonUnfocusBackgroundColor);
            }
        }

        // Drawing the button box.
        SelectObject(hDC, backgroundBrush);
        SelectObject(hDC, backgroundPen);
        Rectangle(hDC, windowRect.right - windowRect.left - 169 - __theme->__positionDifference, 1, windowRect.right - windowRect.left - 128 - __theme->__positionDifference, __nTitleBarButtonHeight - 1 + __theme->__positionDifference);
        DeleteObject(backgroundBrush);
        DeleteObject(backgroundPen);

        // Drawing the shape of the button.

        // Getting the accurate color
        int nRed, nGreen, nBlue;

        if (__bIsSettingButtonHover)
        {
            nRed = GetRValue(__windowTheme.windowTitleBarSettingButtonHoverTextColor);
            nGreen = GetGValue(__windowTheme.windowTitleBarSettingButtonHoverTextColor);
            nBlue = GetBValue(__windowTheme.windowTitleBarSettingButtonHoverTextColor);
        }
        else
        {
            if (bIsFocused)
            {
                nRed = GetRValue(__windowTheme.windowTitleBarSettingButtonFocusTextColor);
                nGreen = GetGValue(__windowTheme.windowTitleBarSettingButtonFocusTextColor);
                nBlue = GetBValue(__windowTheme.windowTitleBarSettingButtonFocusTextColor);
            }
            else
            {
                nRed = GetRValue(__windowTheme.windowTitleBarSettingButtonUnfocusTextColor);
                nGreen = GetGValue(__windowTheme.windowTitleBarSettingButtonUnfocusTextColor);
                nBlue = GetBValue(__windowTheme.windowTitleBarSettingButtonUnfocusTextColor);
            }
        }

        Gdiplus::Graphics graphics(hDC);

        Gdiplus::Pen drawingPen(Gdiplus::Color(255, nRed, nGreen, nBlue), 1);

        int x = windowRect.right - windowRect.left - __nTitleBarButtonWidth - 112 - __theme->__positionDifference;
        int y = __nTitleBarButtonHeight - 20 + __theme->__positionDifference;

        graphics.DrawLine(&drawingPen, x, y, x + 11, y);
        graphics.DrawLine(&drawingPen, x, y + 5, x + 11, y + 5);
        graphics.DrawLine(&drawingPen, x, y + 10, x + 11, y + 10);
    }

    RECT Window::__GetButtonRect(RECT windowRect, int nRightSideMargin, int nLeftSideMargin)
    {
        // Helps to get the button rect for the hovering controls.

        RECT buttonRect;
        buttonRect.left = windowRect.right - windowRect.left - nRightSideMargin;
        buttonRect.right = windowRect.right - windowRect.left - 1 - nLeftSideMargin;
        buttonRect.top = 1;
        buttonRect.bottom = __nTitleBarButtonHeight;

        return buttonRect;
    }

    void Window::__LoadWindowThemeFromTheme()
    {
        __console.Log("LoadWindowThemeFromTheme", "Loading the window theme data from the original theme.");

        if (__windowTheme.windowBorderRadius == -1)
        {
            __windowTheme.windowBorderRadius = __theme->windowTheme.windowBorderRadius;
        }

        if (__windowTheme.windowBorderFocusColor == NULL)
        {
            __windowTheme.windowBorderFocusColor = __theme->windowTheme.windowBorderFocusColor;
        }

        if (__windowTheme.windowBorderUnfocusColor == NULL)
        {
            __windowTheme.windowBorderUnfocusColor = __theme->windowTheme.windowBorderUnfocusColor;
        }

        if (__windowTheme.windowBorderOpacity == -1)
        {
            __windowTheme.windowBorderOpacity = __theme->windowTheme.windowBorderOpacity;
        }

        if (__windowTheme.windowBackgroundColor == NULL)
        {
            __windowTheme.windowBackgroundColor = __theme->windowTheme.windowBackgroundColor;
        }

        if (__windowTheme.windowCursor == NULL)
        {
            __windowTheme.windowCursor = __theme->windowTheme.windowCursor;
        }

        if (__windowTheme.windowLeftResizeCursor == NULL)
        {
            __windowTheme.windowLeftResizeCursor = __theme->windowTheme.windowLeftResizeCursor;
        }

        if (__windowTheme.windowRightResizeCursor == NULL)
        {
            __windowTheme.windowRightResizeCursor = __theme->windowTheme.windowRightResizeCursor;
        }

        if (__windowTheme.windowTopResizeCursor == NULL)
        {
            __windowTheme.windowTopResizeCursor = __theme->windowTheme.windowTopResizeCursor;
        }

        if (__windowTheme.windowBottomResizeCursor == NULL)
        {
            __windowTheme.windowBottomResizeCursor = __theme->windowTheme.windowBottomResizeCursor;
        }

        if (__windowTheme.windowTopLeftResizeCursor == NULL)
        {
            __windowTheme.windowTopLeftResizeCursor = __theme->windowTheme.windowTopLeftResizeCursor;
        }

        if (__windowTheme.windowTopRightResizeCursor == NULL)
        {
            __windowTheme.windowTopRightResizeCursor = __theme->windowTheme.windowTopRightResizeCursor;
        }

        if (__windowTheme.windowBottomLeftResizeCursor == NULL)
        {
            __windowTheme.windowBottomLeftResizeCursor = __theme->windowTheme.windowBottomLeftResizeCursor;
        }

        if (__windowTheme.windowBottomRightResizeCursor == NULL)
        {
            __windowTheme.windowBottomRightResizeCursor = __theme->windowTheme.windowBottomRightResizeCursor;
        }

        if (__windowTheme.windowTitleBarBackgroundColor == NULL)
        {
            __windowTheme.windowTitleBarBackgroundColor = __theme->windowTheme.windowTitleBarBackgroundColor;
        }

        if (__windowTheme.windowTaskBarIcon == NULL)
        {
            __windowTheme.windowTaskBarIcon = __theme->windowTheme.windowTaskBarIcon;
        }

        if (__windowTheme.windowFocusIcon == NULL)
        {
            __windowTheme.windowFocusIcon = __theme->windowTheme.windowFocusIcon;
        }

        if (__windowTheme.windowUnfocusIcon == NULL)
        {
            __windowTheme.windowUnfocusIcon = __theme->windowTheme.windowUnfocusIcon;
        }

        if (__windowTheme.windowTitleBarTextFocusColor == NULL)
        {
            __windowTheme.windowTitleBarTextFocusColor = __theme->windowTheme.windowTitleBarTextFocusColor;
        }

        if (__windowTheme.windowTitleBarTextUnfocusColor == NULL)
        {
            __windowTheme.windowTitleBarTextUnfocusColor = __theme->windowTheme.windowTitleBarTextUnfocusColor;
        }

        if (__windowTheme.windowTitleBarCloseButtonHoverBackgroundColor == NULL)
        {
            __windowTheme.windowTitleBarCloseButtonHoverBackgroundColor = __theme->windowTheme.windowTitleBarCloseButtonHoverBackgroundColor;
        }

        if (__windowTheme.windowTitleBarCloseButtonFocusBackgroundColor == NULL)
        {
            __windowTheme.windowTitleBarCloseButtonFocusBackgroundColor = __theme->windowTheme.windowTitleBarCloseButtonFocusBackgroundColor;
        }

        if (__windowTheme.windowTitleBarCloseButtonUnfocusBackgroundColor == NULL)
        {
            __windowTheme.windowTitleBarCloseButtonUnfocusBackgroundColor = __theme->windowTheme.windowTitleBarCloseButtonUnfocusBackgroundColor;
        }

        if (__windowTheme.windowTitleBarCloseButtonHoverTextColor == NULL)
        {
            __windowTheme.windowTitleBarCloseButtonHoverTextColor = __theme->windowTheme.windowTitleBarCloseButtonHoverTextColor;
        }

        if (__windowTheme.windowTitleBarCloseButtonFocusTextColor == NULL)
        {
            __windowTheme.windowTitleBarCloseButtonFocusTextColor = __theme->windowTheme.windowTitleBarCloseButtonFocusTextColor;
        }

        if (__windowTheme.windowTitleBarCloseButtonUnfocusTextColor == NULL)
        {
            __windowTheme.windowTitleBarCloseButtonUnfocusTextColor = __theme->windowTheme.windowTitleBarCloseButtonUnfocusTextColor;
        }

        if (__windowTheme.windowTitleBarMaximizeButtonHoverBackgroundColor == NULL)
        {
            __windowTheme.windowTitleBarMaximizeButtonHoverBackgroundColor = __theme->windowTheme.windowTitleBarMaximizeButtonHoverBackgroundColor;
        }

        if (__windowTheme.windowTitleBarMaximizeButtonFocusBackgroundColor == NULL)
        {
            __windowTheme.windowTitleBarMaximizeButtonFocusBackgroundColor = __theme->windowTheme.windowTitleBarMaximizeButtonFocusBackgroundColor;
        }

        if (__windowTheme.windowTitleBarMaximizeButtonUnfocusBackgroundColor == NULL)
        {
            __windowTheme.windowTitleBarMaximizeButtonUnfocusBackgroundColor = __theme->windowTheme.windowTitleBarMaximizeButtonUnfocusBackgroundColor;
        }

        if (__windowTheme.windowTitleBarMaximizeButtonHoverTextColor == NULL)
        {
            __windowTheme.windowTitleBarMaximizeButtonHoverTextColor = __theme->windowTheme.windowTitleBarMaximizeButtonHoverTextColor;
        }

        if (__windowTheme.windowTitleBarMaximizeButtonFocusTextColor == NULL)
        {
            __windowTheme.windowTitleBarMaximizeButtonFocusTextColor = __theme->windowTheme.windowTitleBarMaximizeButtonFocusTextColor;
        }

        if (__windowTheme.windowTitleBarMaximizeButtonUnfocusTextColor == NULL)
        {
            __windowTheme.windowTitleBarMaximizeButtonUnfocusTextColor = __theme->windowTheme.windowTitleBarMaximizeButtonUnfocusTextColor;
        }

        if (__windowTheme.windowTitleBarMinimizeButtonHoverBackgroundColor == NULL)
        {
            __windowTheme.windowTitleBarMinimizeButtonHoverBackgroundColor = __theme->windowTheme.windowTitleBarMinimizeButtonHoverBackgroundColor;
        }

        if (__windowTheme.windowTitleBarMinimizeButtonFocusBackgroundColor == NULL)
        {
            __windowTheme.windowTitleBarMinimizeButtonFocusBackgroundColor = __theme->windowTheme.windowTitleBarMinimizeButtonFocusBackgroundColor;
        }

        if (__windowTheme.windowTitleBarMinimizeButtonUnfocusBackgroundColor == NULL)
        {
            __windowTheme.windowTitleBarMinimizeButtonUnfocusBackgroundColor = __theme->windowTheme.windowTitleBarMinimizeButtonUnfocusBackgroundColor;
        }

        if (__windowTheme.windowTitleBarMinimizeButtonHoverTextColor == NULL)
        {
            __windowTheme.windowTitleBarMinimizeButtonHoverTextColor = __theme->windowTheme.windowTitleBarMinimizeButtonHoverTextColor;
        }

        if (__windowTheme.windowTitleBarMinimizeButtonFocusTextColor == NULL)
        {
            __windowTheme.windowTitleBarMinimizeButtonFocusTextColor = __theme->windowTheme.windowTitleBarMinimizeButtonFocusTextColor;
        }

        if (__windowTheme.windowTitleBarMinimizeButtonUnfocusTextColor == NULL)
        {
            __windowTheme.windowTitleBarMinimizeButtonUnfocusTextColor = __theme->windowTheme.windowTitleBarMinimizeButtonUnfocusTextColor;
        }

        if (__windowTheme.windowTitleBarSettingButtonHoverBackgroundColor == NULL)
        {
            __windowTheme.windowTitleBarSettingButtonHoverBackgroundColor = __theme->windowTheme.windowTitleBarSettingButtonHoverBackgroundColor;
        }

        if (__windowTheme.windowTitleBarSettingButtonFocusBackgroundColor == NULL)
        {
            __windowTheme.windowTitleBarSettingButtonFocusBackgroundColor = __theme->windowTheme.windowTitleBarSettingButtonFocusBackgroundColor;
        }

        if (__windowTheme.windowTitleBarSettingButtonUnfocusBackgroundColor == NULL)
        {
            __windowTheme.windowTitleBarSettingButtonUnfocusBackgroundColor = __theme->windowTheme.windowTitleBarSettingButtonUnfocusBackgroundColor;
        }

        if (__windowTheme.windowTitleBarSettingButtonHoverTextColor == NULL)
        {
            __windowTheme.windowTitleBarSettingButtonHoverTextColor = __theme->windowTheme.windowTitleBarSettingButtonHoverTextColor;
        }

        if (__windowTheme.windowTitleBarSettingButtonFocusTextColor == NULL)
        {
            __windowTheme.windowTitleBarSettingButtonFocusTextColor = __theme->windowTheme.windowTitleBarSettingButtonFocusTextColor;
        }

        if (__windowTheme.windowTitleBarSettingButtonUnfocusTextColor == NULL)
        {
            __windowTheme.windowTitleBarSettingButtonUnfocusTextColor = __theme->windowTheme.windowTitleBarSettingButtonUnfocusTextColor;
        }

        if (__windowTheme.windowStatusBarBackgroundColor == NULL)
        {
            __windowTheme.windowStatusBarBackgroundColor = __theme->windowTheme.windowStatusBarBackgroundColor;
        }

        if (__windowTheme.windowStatusBarTextFocusColor == NULL)
        {
            __windowTheme.windowStatusBarTextFocusColor = __theme->windowTheme.windowStatusBarTextFocusColor;
        }

        if (__windowTheme.windowStatusBarTextUnfocusColor == NULL)
        {
            __windowTheme.windowStatusBarTextUnfocusColor = __theme->windowTheme.windowStatusBarTextUnfocusColor;
        }
    }
    // [ Ending ] - Private Functions.
}
