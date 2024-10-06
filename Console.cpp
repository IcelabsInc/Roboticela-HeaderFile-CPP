// Created by Muhammad Shahsawar.
// Company: Munammad Technology.

// Including the header files.
#include "Console.h"
#include <iostream>
#include <stdio.h>

namespace TkinterWindow
{
    // [ Starting ] - ConsoleClassInitializers.
    bool Console::InitializeConsole(void)
    {
        // Helps to setup the console for the application.
        if (!AllocConsole())
        {
            return false;
        }

        // Reading and writing to console.
        freopen("CONOUT$", "w", stdout);
        freopen("CONIN$", "r", stdin);

        __Log("InitializeConsole", "Console has been initialized.");

        // Gettting console handle.
        __consoleHandle = GetConsoleWindow();

        // Getting position and size.
        RECT consoleRect;
        if (!GetWindowRect(__consoleHandle, &consoleRect))
        {
            return false;
        }

        __nConsoleHeight = consoleRect.bottom - consoleRect.top;
        __nConsoleWidth = consoleRect.right - consoleRect.left;
        __nConsoleXPosition = consoleRect.left;
        __nConsoleYPosition = consoleRect.top;
        __Log("InitializeConsole", "The position and size for the console has been getted.");

        return true;
    }

    bool Console::Initialize(void)
    {
        // Same as InitializeConsole().
        return InitializeConsole();
    }
    // [ Ending ] - ConsoleClassInitializers.

    // [ Starting ] - ShowConsole.
    bool Console::ShowConsole(void)
    {
        __CheckWarning("ShowConsole");

        // Helps to show the console on the screen.
        __Log("ShowConsole", "Showing the console window.");
        return ShowWindow(__consoleHandle, SW_SHOW);
    }

    bool Console::Show(void)
    {
        // Same as ShowConsole().
        return ShowConsole();
    }
    // [ Ending ] - ShowConsole.

    // [ Starting ] - HideConsole.
    bool Console::HideConsole(void)
    {
        __CheckWarning("HideConsole");

        // Helps to hide the console window from the screen.
        __Log("HideConsole", "Hiding the console window.");
        return ShowWindow(__consoleHandle, SW_HIDE);
    }

    bool Console::Hide(void)
    {
        // Same as HideConsole().
        return HideConsole();
    }
    // [ Ending ] - HideConsole.

    // [ Starting ] - SetConsoleTitle.
    bool Console::SetConsoleTitle(std::string sTitle)
    {
        __CheckWarning("SetConsoleTitle");

        // Helps to set the title of the console window.
        __Log("SetConsoleTitle", "Setting the console window title. Title: %s", sTitle.c_str());
        return SetWindowTextA(__consoleHandle, sTitle.c_str());
    }

    bool Console::SetTitle(std::string sTitle)
    {
        // Same as SetConsoleTitle().
        return SetConsoleTitle(sTitle);
    }

    bool Console::SetConsoleCaption(std::string sCaption)
    {
        // Same as SetConsoleTitle().
        return SetConsoleTitle(sCaption);
    }

    bool Console::SetCaption(std::string sCaption)
    {
        // Same as SetConsoleTitle().
        return SetConsoleTitle(sCaption);
    }
    // [ Ending ] - SetConsoleTitle.

    // [ Starting ] - SetConsoleSize.
    bool Console::SetConsoleSize(int nWidth, int nHeight)
    {
        __CheckWarning("SetConsoleSize");

        // Helps to set the console window size.
        __Log("SetConsoleSize", "Setting the console window size. Width: %d, Height: %d.", nWidth, nHeight);

        __nConsoleHeight = nHeight;
        __nConsoleWidth = nWidth;

        return SetWindowPos(__consoleHandle, NULL, __nConsoleXPosition, __nConsoleYPosition, nWidth, nHeight, 0);
    }

    bool Console::SetSize(int nWidth, int nHeight)
    {
        // Same as SetConsoleSize()
        return SetConsoleSize(nWidth, nHeight);
    }

    bool Console::SetConsoleWidth(int nWidth)
    {
        // Same as SetConsoleSize except arguments.
        return SetConsoleSize(nWidth, __nConsoleHeight);
    }

    bool Console::SetWidth(int nWidth)
    {
        // Same as SetConsoleSize except arguments.
        return SetConsoleSize(nWidth, __nConsoleHeight);
    }

    bool Console::SetConsoleHeight(int nHeight)
    {
        // Same as SetConsoleSize except arguments.
        return SetConsoleSize(__nConsoleWidth, nHeight);
    }

    bool Console::SetHeight(int nHeight)
    {
        // Same as SetConsoleSize except arguments.
        return SetConsoleSize(__nConsoleWidth, nHeight);
    }
    // [ Ending ] - SetConsoleSize.

    // [ Starting ] - SetConsolePosition.
    bool Console::SetConsolePosition(int nHorizontalPosition, int nVerticalPosition)
    {
        __CheckWarning("SetConsolePosition");

        // Helps to set the console window position.
        __Log("SetConsolePosition", "Setting the position of console window. X: %d, Y: %d.", nHorizontalPosition, nVerticalPosition);

        __nConsoleXPosition = nHorizontalPosition;
        __nConsoleYPosition = nVerticalPosition;

        return SetWindowPos(__consoleHandle, NULL, __nConsoleXPosition, __nConsoleYPosition, __nConsoleWidth, __nConsoleHeight, 0);
    }

    bool Console::SetPosition(int nXPosition, int nYPosition)
    {
        // Same as SetConsolePosition().
        return SetConsolePosition(nXPosition, nYPosition);
    }

    bool Console::SetConsoleHorizontalPosition(int nHorizontalPosition)
    {
        // Same as SetConsolePosition().
        return SetConsolePosition(nHorizontalPosition, __nConsoleYPosition);
    }

    bool Console::SetHorizontalPosition(int nHorizontalPosition)
    {
        // Same as SetConsolePosition().
        return SetConsolePosition(nHorizontalPosition, __nConsoleYPosition);
    }

    bool Console::SetConsoleXPosition(int nXPosition)
    {
        // Same as SetConsolePosition().
        return SetConsolePosition(nXPosition, __nConsoleYPosition);
    }

    bool Console::SetXPosition(int nXPosition)
    {
        // Same as SetConsolePosition().
        return SetConsolePosition(nXPosition, __nConsoleYPosition);
    }

    bool Console::SetConsoleVerticalPosition(int nVerticalPosition)
    {
        // Same as SetConsolePosition().
        return SetConsolePosition(__nConsoleXPosition, nVerticalPosition);
    }

    bool Console::SetVerticalPosition(int nVerticalPosition)
    {
        // Same as SetConsolePosition().
        return SetConsolePosition(__nConsoleXPosition, nVerticalPosition);
    }

    bool Console::SetConsoleYPosition(int nYPosition)
    {
        // Same as SetConsolePosition().
        return SetConsolePosition(__nConsoleXPosition, nYPosition);
    }

    bool Console::SetYPosition(int nYPosition)
    {
        // Same as SetConsolePosition().
        return SetConsolePosition(__nConsoleXPosition, nYPosition);
    }
    // [ Ending ] - SetConsolePosition.

    // // [ Starting ] - StateControls.
    bool Console::MaximizeConsoleWindow(void)
    {
        __CheckWarning("MaximizeConsoleWindow");

        // Helps to maximize the console window.
        __Log("MaximizeConsoleWindow", "Maximizing the console window.");

        return ShowWindow(__consoleHandle, SW_MAXIMIZE);
    }

    bool Console::MaximizeWindow(void)
    {
        // Same as MaximizeConsoleWindow().
        return MaximizeConsoleWindow();
    }

    bool Console::Maximize(void)
    {
        // Same as MaximizeConsoleWindow().
        return MaximizeConsoleWindow();
    }

    bool Console::MinimizeConsoleWindow(void)
    {
        __CheckWarning("MinimizeConsoleWindow");

        // Helps to minimize the console window.
        __Log("MinimizeConsoleWindow", "Minimizing the console window.");

        return ShowWindow(__consoleHandle, SW_MINIMIZE);
    }

    bool Console::MinimizeWindow(void)
    {
        // Same as MinimizeConsoleWindow().
        return MinimizeConsoleWindow();
    }

    bool Console::Minimize(void)
    {
        // Same as MinimizeConsoleWindow().
        return MinimizeConsoleWindow();
    }

    bool Console::NormalConsoleWindow(void)
    {
        __CheckWarning("NormalConsoleWindow");

        // Helps to minimize the console window.
        __Log("NormalConsoleWindow", "Showing the console window in normal state.");

        return ShowWindow(__consoleHandle, SW_NORMAL);
    }

    bool Console::NormalWindow(void)
    {
        // Same as NormalConsoleWindow().
        return NormalConsoleWindow();
    }

    bool Console::Normal(void)
    {
        // Same as NormalConsoleWindow().
        return NormalConsoleWindow();
    }
    // // [ Ending ] - StateControls.

    // [ Starting ] - Output on console.
    bool Console::SetLoggerClassObject(std::string sClassObject)
    {
        __CheckWarning("SetLoggerClassObject");

        // Helps to set the class object of the debugger.
        __Log("SetLoggerClassObject", "Setting the debugger class object. ClassObject: %s", sClassObject.c_str());
        __sClassObject = sClassObject;

        return true;
    }

    bool Console::SetloggerClassName(std::string sClassName)
    {
        __CheckWarning("SetLoggerClassName");

        // Helps to set the class name of the debugger.
        __Log("SetLoggerClassName", "Setting the debugger class name. ClassName: %s", sClassName.c_str());
        __sClassName = sClassName;

        return true;
    }

    bool Console::Log(std::string sFunctionName, std::string sText)
    {
        __CheckWarning("Log");

        // Helps to write something on the console if the debugging is enabled.

        if (__isDebug)
        {
            if (GetConsoleWindow() != NULL)
            {
                // Reading and writing to console.
                freopen("CONIN$", "r", stdin);
                freopen("CONOUT$", "w", stdout);

                // outing the text on the console.
                std::cout << "[ " << __sClassObject << " ] { " << __sClassName << " } > [ " << sFunctionName << " ] --> " << sText << std::endl;
            }
        }

        return true;
    }

    bool Console::Log(std::string sFunctionName, const char *__format, ...)
    {
        __CheckWarning("Log");

        // Helps to write something on the console from arrays of string if the debugging is enabled.

        if (__isDebug)
        {
            // Reading and writing to console.
            if (GetConsoleWindow() != NULL)
            {
                freopen("CONIN$", "r", stdin);
                freopen("CONOUT$", "w", stdout);

                std::string sText;

                // outing the text on the console.
                std::cout << "[ " << __sClassObject << " ] { " << __sClassName << " } > [ " << sFunctionName << " ] --> ";
                va_list arg;

                va_start(arg, __format);
                vfprintf(stdout, __format, arg);
                va_end(arg);
                std::cout << std::endl;
            }
        }

        return true;
    }

    bool Console::OpenStream(void)
    {
        __CheckWarning("OpenStream");

        // Helps to open the stream for the reading and writing.
        __Log("OpenStream", "The reading and writing stream is openinig.");

        if (GetConsoleWindow() != NULL)
        {
            freopen("CONIN$", "r", stdin);
            freopen("CONOUT$", "w", stdout);
        }
        else
        {
            return false;
        }

        return true;
    }
    // [ Ending ] - Output on console.

    // [ Starting ] - Pausing the console.
    bool Console::PauseConsole(void)
    {
        __CheckWarning("PauseConsole");

        // Helps to pause the console for user keydown.
        OpenStream();
        std::cout << std::endl;
        system("pause");
        return true;
    }

    bool Console::Pause(void)
    {
        // Same as PauseConsole().
        return PauseConsole();
    }
    // [ Ending ] - Pausing the console.

    // [ Starting ] - Debugger start and stop.
    bool Console::EnableDebugger(void)
    {
        __CheckWarning("EnableDebugger");

        // Helps to enable the debugger.
        __isDebug = true;

        return true;
    }

    bool Console::DisableDebugger(void)
    {
        __CheckWarning("DisableDebugger");

        // Helps to disable the debugger.
        __isDebug = false;

        return true;
    }

    bool Console::DisableErrorCheck(void)
    {
        // Helps to disable the error check.
        __isErrorCheck = false;

        return true;
    }
    // [ Ending ] - Debugger start and stop.

    // [ Starting ] - Private Functions.
    bool Console::__Log(std::string sFunctionName, std::string sText)
    {
        // Helps to write something on the console if the debugging is enabled.

        if (__isDebug)
        {
            // Reading and writing to console.
            if (GetConsoleWindow() != NULL)
            {
                freopen("CONIN$", "r", stdin);
                freopen("CONOUT$", "w", stdout);

                // outing the text on the console.
                std::cout << "[ Console ] { } > [ " << sFunctionName << " ] --> " << sText << std::endl;
            }
        }

        return true;
    }

    bool Console::__Log(std::string sFunctionName, const char *__format, ...)
    {
        // Helps to write something on the console from arrays of string if the debugging is enabled.

        if (__isDebug)
        {
            // Reading and writing to console.
            if (GetConsoleWindow() != NULL)
            {
                freopen("CONIN$", "r", stdin);
                freopen("CONOUT$", "w", stdout);

                std::string sText;

                // outing the text on the console.
                std::cout << "[ Console ] { } > [ " << sFunctionName << " ] --> ";
                va_list arg;

                va_start(arg, __format);
                vfprintf(stdout, __format, arg);
                va_end(arg);

                std::cout << std::endl;
            }
        }

        return true;
    }

    void Console::__CheckWarning(std::string sFunctionName)
    {
        if (__isErrorCheck)
        {
            if (__consoleHandle == NULL)
            {
                __Log(sFunctionName, "Warning: The function is called before the initalization. It can lead to some major problems.");
            }
        }
    }
    // [ Ending ] - Private Functions.
}
