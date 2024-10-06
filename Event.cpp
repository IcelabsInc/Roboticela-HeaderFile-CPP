// Created by Muhammad Shahsawar.
// Company: Muhammad Technology.

// Including some important header files.
#include "Event.h"

// Using some important libraries.
#pragma comment(lib, "Build-Data\\Console.lib")

namespace __TkinterWindow
{
    void CallFunctions(std::vector<TkinterWindow::EVENTFUNCTION> array, TkinterWindow::EVENT eventHandle)
    {
        if (array.size() > 0)
        {
            for (int i = 0; i < array.size(); i++)
            {
                array.at(i)(eventHandle);
            }
        }
    }
}

namespace TkinterWindow
{
    // [ Starting ] - Public functions.
    bool Event::__InitializeEvents(TkinterWindow::Console *console)
    {
        // Helps to initialize the event class.

        __eventConsole = console;
        __eventConsole->Log("InitializeEvents", "Initializing the events for the window.");

        return true;
    }

    bool Event::__CheckEvents(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        // Helps to check all the events.
        EVENT eventInformation = {0};

        switch (message)
        {
        case WM_CLOSE:
        {
            __TkinterWindow::CallFunctions(__closeWindow, eventInformation);
            break;
        }

        case WM_SIZE:
        {
            if (wParam == SIZE_MAXIMIZED)
            {
                __TkinterWindow::CallFunctions(__maximizeWindow, eventInformation);
            }
            else if (wParam == SIZE_MINIMIZED)
            {
                __TkinterWindow::CallFunctions(__minimizeWindow, eventInformation);
            }
            break;
        }

        case WM_KEYDOWN:
        {
            eventInformation.keyboardKey = wParam;

            __TkinterWindow::CallFunctions(__keyboardKeyDown, eventInformation);
            break;
        }
        }

        return true;
    }

    // [ Starting ] - Binding and unbinding functions.
    bool Event::BindEvent(int nEventType, EVENTFUNCTION eventFunction)
    {
        if (nEventType == EVENT_CLOSEWINDOW)
        {
            __closeWindow.push_back(eventFunction);
        }
        else if (nEventType == EVENT_MAXIMIZEWINDOW)
        {
            __maximizeWindow.push_back(eventFunction);
        }
        else if (nEventType == EVENT_MINIMIZEWINDOW)
        {
            __minimizeWindow.push_back(eventFunction);
        }
        else if (nEventType == EVENT_KEYBOARDKEYDOWN)
        {
            __keyboardKeyDown.push_back(eventFunction);
        }

        return true;
    }

    bool Event::Bind(int nEventType, EVENTFUNCTION eventFunction)
    {
        // Same as BindEvent.
        return BindEvent(nEventType, eventFunction);
    }
    // [ Ending ] - Binding and unbinding functions.
    // [ Ending ] - Public functions.
}
