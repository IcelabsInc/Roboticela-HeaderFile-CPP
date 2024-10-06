// Created by Muhammad Shahsawar.
// Company: Muhammad Technology.

#pragma once

// Including some important header files.
#include "Common.h"
#include "Console.h"

namespace TkinterWindow
{
    class EXPORTIMPORT Font
    {
    private:
        // [ Starting ] - Variables.
        HFONT __hFont = NULL;
        bool __bItalicFont = false;
        bool __bUnderLineFont = false;
        bool __bStrikeoutFont = false;
        int __nHeightFont = 0;
        int __nSizeFont = 15;
        int __nWeightFont = 0;
        int __nFontEscapement = 0;
        int __nFontOrientation = 0;
        std::string __sStyleFont = "Comicsans";
        TkinterWindow::Console __console;
        std::string __sClassName;
        bool __bIsInitialized = false;
        // [ Ending ] - Variables.

        // [ Starting ] - Functions.
        void __CheckWarning(std::string sFunctionName);
        // [ Ending ] - Functions.
        
    public:
        // [ Starting ] - Variables.
        // [ Ending ] - Variables.

        // [ Starting ] - Functions.

        // [ Starting ] - InitializeFont().
        bool InitializeFont(std::string sClassName);
        bool Initialize(std::string sClassName);
        // [ Ending ] - InitializeFont().

        // [ Starting ] - GetFontObject().
        HFONT GetFontObject(HDC hDC);
        HFONT GetFontObject(void);
        HFONT GetObject(HDC hDC);
        HFONT GetObject(void);
        // [ Ending ] - GetFontObject().

        // [ Starting ] - DeleteFontObject().
        bool DeleteFontObject(void);
        bool DeleteObject(void);
        // [ Ending ] - DeleteFontObject().

        // [ Starting ] - Font Styling.
        bool SetFontItalicStyle(bool bItalicStyle);
        bool SetItalicStyle(bool bItalicStyle);

        bool SetFontUnderlineStyle(bool bUnderlineStyle);
        bool SetUnderlineStyle(bool bUnderlineStyle);

        bool SetFontStrikeoutStyle(bool bStrikeoutStyle);
        bool SetStrikeoutStyle(bool bStrikeoutStyle);
        // [ Ending ] - Font Styling.

        // [ Starting ] - Font Size.
        bool SetFontSize(int nFontSize);
        bool SetSize(int nFontSize);

        bool SetFontHeight(int nFontHeight);
        bool SetHeight(int nFontHeight);

        bool SetFontWidth(int nFontWidth);
        bool SetWidth(int nFontWidth);
        // [ Ending ] - Font Size.

        // [ Starting ] - Font family.
        bool SetFontFamily(std::string sFontFamily);
        bool SetFamily(std::string sFontFamily);

        bool SetFontStyle(std::string sFontStyle);
        bool SetStyle(std::string sFontStyle);
        // [ Ending ] - Font family.

        // [ Starting ] - Rotation controls.
        bool SetFontEscapement(int nFontEscapement);
        bool SetEscapement(int nFontEscapement);

        bool SetFontOrientation(int nFontOrientation);
        bool SetOrientation(int nFontOrientation);
        // [ Starting ] - Rotation controls.

        // [ Starting ] - SetFontWeight.
        bool SetFontWeight(int nFontWeight);
        bool SetWeight(int nFontWeight);
        // [ Ending ] - SetFontWeight.

        // [ Starting ] - debugger controls.
        bool EnableDebugger(void);
        bool DisableDebugger(void);
        // [ Ending ] - debugger controls.
        // [ Ending ] - Functions.
    };
}
