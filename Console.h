// Created by Muhammad Shahsawar.
// Company: Muhammad Technology.

#pragma once

// Including some header files.
#include "Common.h"

namespace TkinterWindow
{
    class EXPORTIMPORT Console
    {
    private:
        // [ Starting ] - Variables.
        int __nConsoleWidth, __nConsoleHeight;
        int __nConsoleXPosition, __nConsoleYPosition;
        HWND __consoleHandle;
        bool __isDebug = true;
        bool __isErrorCheck = true;
        std::string __sClassObject = "", __sClassName = "";
        // [ Ending ] - Variables.

        // [ Starting ] - Functions.
        bool __Log(std::string sFunctionName, std::string sText);
        bool __Log(std::string sFunctionName, const char *__format, ...);
        void __CheckWarning(std::string sFunctionName);
        // [ Ending ] - Functions.

    public:
        // [ Starting ] - Variables.
        // [ Ending ] - Variables.

        // [ Starting ] - Functions.

        // [ Starting ] - ConsoleClassInitializers.
        bool InitializeConsole(void);
        bool Initialize(void);
        // [ Ending ] - ConsoleClassInitializers.

        // [ Starting ] - ShowConsole.
        bool ShowConsole(void);
        bool Show(void);
        // [ Ending ] - ShowConsole.

        // [ Starting ] - HideConsole.
        bool HideConsole(void);
        bool Hide(void);
        // [ Ending ] - HideConsole.

        // [ Starting ] - SetConsoleTitle.
        bool SetConsoleTitle(std::string sTitle);
        bool SetTitle(std::string sTitle);

        bool SetConsoleCaption(std::string sCaption);
        bool SetCaption(std::string sCaption);
        // [ Ending ] - SetConsoleTitle.

        // [ Starting ] - SetConsoleSize.
        bool SetConsoleSize(int nWidth, int nHeight);
        bool SetSize(int nWidth, int nHeight);

        bool SetConsoleWidth(int nWidth);
        bool SetWidth(int nWidth);

        bool SetConsoleHeight(int nHeight);
        bool SetHeight(int nHeight);
        // [ Ending ] - SetConsoleSize.

        // [ Starting ] - SetConsolePosition.
        bool SetConsolePosition(int nHorizontalPosition, int nVerticalPosition);
        bool SetPosition(int nXPosition, int nYPosition);

        bool SetConsoleHorizontalPosition(int nHorizontalPosition);
        bool SetHorizontalPosition(int nHorizontalPosition);
        bool SetConsoleXPosition(int nXPosition);
        bool SetXPosition(int nXPosition);

        bool SetConsoleVerticalPosition(int nVerticalPosition);
        bool SetVerticalPosition(int nVerticalPosition);
        bool SetConsoleYPosition(int nYPosition);
        bool SetYPosition(int nYPosition);
        // [ Ending ] - SetConsolePosition.

        // [ Starting ] - StateControls.
        bool MaximizeConsoleWindow(void);
        bool MaximizeWindow(void);
        bool Maximize(void);

        bool MinimizeConsoleWindow(void);
        bool MinimizeWindow(void);
        bool Minimize(void);

        bool NormalConsoleWindow(void);
        bool NormalWindow(void);
        bool Normal(void);
        // [ Ending ] - StateControls.

        // [ Starting ] - Output on console.
        bool SetLoggerClassObject(std::string sClassObject);
        bool SetloggerClassName(std::string sClassName);
        bool Log(std::string sFunctionName, std::string sText);
        bool Log(std::string sFunctionName, const char *__format, ...);
        bool OpenStream(void);
        // [ Ending ] - Output on console.

        // [ Starting ] - Pausing the console.
        bool PauseConsole(void);
        bool Pause(void);
        // [ Ending ] - Pausing the console.

        // [ Starting ] - Debugger start and stop.
        bool EnableDebugger(void);
        bool DisableDebugger(void);
        bool DisableErrorCheck(void);
        // [ Ending ] - Debugger start and stop.

        // [ Ending ] - Functions.
    };
}
