// Created by Muhammad Shahsawar.
// Company: Muhamamd Technology.

#pragma once

// Including some important header files.
#include "Common.h"
#include <vector>
#include "Console.h"

namespace TkinterWindow
{
    // Events.
    int EVENT_CLOSEWINDOW = 1000;
    int EVENT_MAXIMIZEWINDOW = 1001;
    int EVENT_MINIMIZEWINDOW = 1002;
    int EVENT_KEYBOARDKEYDOWN = 1003;

    // Keyboard Keys.
    int KEYBOARD_KEY_ESCAPE = 27;
    int KEYBOARD_KEY_F1 = 112;
    int KEYBOARD_KEY_F2 = 113;
    int KEYBOARD_KEY_F3 = 114;
    int KEYBOARD_KEY_F4 = 115;
    int KEYBOARD_KEY_F5 = 116;
    int KEYBOARD_KEY_F6 = 117;
    int KEYBOARD_KEY_F7 = 118;
    int KEYBOARD_KEY_F8 = 119;
    int KEYBOARD_KEY_F9 = 120;
    int KEYBOARD_KEY_F11 = 122;
    int KEYBOARD_KEY_F12 = 123;
    int KEYBOARD_KEY_SCROLLLOCK = 145;
    int KEYBOARD_KEY_TILDE = 192;
    int KEYBOARD_KEY_1 = 49;
    int KEYBOARD_KEY_2 = 50;
    int KEYBOARD_KEY_3 = 51;
    int KEYBOARD_KEY_4 = 52;
    int KEYBOARD_KEY_5 = 53;
    int KEYBOARD_KEY_6 = 54;
    int KEYBOARD_KEY_7 = 55;
    int KEYBOARD_KEY_8 = 56;
    int KEYBOARD_KEY_9 = 57;
    int KEYBOARD_KEY_0 = 58;
    int KEYBOARD_KEY_MINUS = 189;
    int KEYBOARD_KEY_PLUS = 187;
    int KEYBOARD_KEY_BACKSPACE = 8;
    int KEYBOARD_KEY_TAB = 9;
    int KEYBOARD_KEY_A = 65;
    int KEYBOARD_KEY_B = 66;
    int KEYBOARD_KEY_C = 67;
    int KEYBOARD_KEY_D = 68;
    int KEYBOARD_KEY_E = 69;
    int KEYBOARD_KEY_F = 70;
    int KEYBOARD_KEY_G = 71;
    int KEYBOARD_KEY_H = 72;
    int KEYBOARD_KEY_I = 73;
    int KEYBOARD_KEY_J = 74;
    int KEYBOARD_KEY_K = 75;
    int KEYBOARD_KEY_L = 76;
    int KEYBOARD_KEY_M = 77;
    int KEYBOARD_KEY_N = 78;
    int KEYBOARD_KEY_O = 79;
    int KEYBOARD_KEY_P = 80;
    int KEYBOARD_KEY_Q = 81;
    int KEYBOARD_KEY_R = 82;
    int KEYBOARD_KEY_S = 83;
    int KEYBOARD_KEY_T = 84;
    int KEYBOARD_KEY_U = 85;
    int KEYBOARD_KEY_V = 86;
    int KEYBOARD_KEY_W = 87;
    int KEYBOARD_KEY_X = 88;
    int KEYBOARD_KEY_Y = 89;
    int KEYBOARD_KEY_Z = 90;
    int KEYBOARD_KEY_SHIFT = 16;
    int KEYBOARD_KEY_CONTROL = 16;
    int KEYBOARD_KEY_LEFTWINDOW = 91;
    int KEYBOARD_KEY_VERTICALBAR = 226;
    int KEYBOARD_KEY_COMMA = 188;
    int KEYBOARD_KEY_DOT = 190;
    int KEYBOARD_KEY_FORWARDSLASH = 191;
    int KEYBOARD_KEY_RIGHTWINDOW = 92;
    int KEYBOARD_KEY_DESKTOP = 93;
    int KEYBOARD_KEY_INSERT = 45;
    int KEYBOARD_KEY_HOME = 36;
    int KEYBOARD_KEY_PAGEUP = 33;
    int KEYBOARD_KEY_PAGEDOWN = 34;
    int KEYBOARD_KEY_END = 35;
    int KEYBOARD_KEY_DELETE = 46;
    int KEYBOARD_KEY_LEFTARROW = 37;
    int KEYBOARD_KEY_RIGHTARROW = 39;
    int KEYBOARD_KEY_UPARROW = 38;
    int KEYBOARD_KEY_DOWNARROW = 40;
    int KEYBOARD_NUMPAD_KEY_NUMLOCK = 144;
    int KEYBOARD_NUMPAD_KEY_FORWARDSLASH = 111;
    int KEYBOARD_NUMPAD_KEY_ASTERISK = 106;
    int KEYBOARD_NUMPAD_KEY_MINUS = 109;
    int KEYBOARD_NUMPAD_KEY_PLUS = 107;
    int KEYBOARD_NUMPAD_KEY_DOT = 110;
    int KEYBOARD_NUMPAD_KEY_0 = 96;
    int KEYBOARD_NUMPAD_KEY_1 = 97;
    int KEYBOARD_NUMPAD_KEY_2 = 98;
    int KEYBOARD_NUMPAD_KEY_3 = 99;
    int KEYBOARD_NUMPAD_KEY_4 = 100;
    int KEYBOARD_NUMPAD_KEY_5 = 101;
    int KEYBOARD_NUMPAD_KEY_6 = 102;
    int KEYBOARD_NUMPAD_KEY_7 = 103;
    int KEYBOARD_NUMPAD_KEY_8 = 104;
    int KEYBOARD_NUMPAD_KEY_9 = 105;

    typedef struct
    {
        int keyboardKey;

    } EVENT;

    typedef void (*EVENTFUNCTION)(EVENT);

    class EXPORTIMPORT Event
    {
    private:
        // [ Starting ] - Events arrays.
        std::vector<EVENTFUNCTION> __closeWindow;
        std::vector<EVENTFUNCTION> __maximizeWindow;
        std::vector<EVENTFUNCTION> __minimizeWindow;
        std::vector<EVENTFUNCTION> __keyboardKeyDown;
        // [ Ending ] - Events arrays.

        // [ Starting ] - Variables.
        TkinterWindow::Console *__eventConsole;
        // [ Ending ] - Variables.
    public:
        // [ Starting ] - Public functions.
        bool __InitializeEvents(TkinterWindow::Console *console);
        bool __CheckEvents(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

        // [ Starting ] - Binding and unbinding functions.
        bool BindEvent(int nEventType, EVENTFUNCTION eventFunction);
        bool Bind(int nEventType, EVENTFUNCTION eventFunction);
        // [ Ending ] - Binding and unbinding functions.
        // [ Ending ] - Public functions.
    };
}
