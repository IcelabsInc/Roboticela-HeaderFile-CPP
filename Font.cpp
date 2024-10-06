// Company: Icelabs Inc.

// Including some important header files.
#include "Font.h"

// using some important libraries.
#pragma comment(lib, "Build-Data\\Console.lib")

namespace __TkinterWindow
{
    bool DeleteFontObjectF(HGDIOBJ object)
    {
        return DeleteObject(object);
    }
}

namespace TkinterWindow
{
    // [ Starting ] - Functions.

    // [ Starting ] - InitializeFont().
    bool Font::InitializeFont(std::string sClassName)
    {
        // Initializing the font.

        // Setting some variables.
        __sClassName = sClassName;

        __console.DisableErrorCheck();
        __console.SetLoggerClassObject("Font");
        __console.SetloggerClassName(sClassName);

        __console.Log("InitializeFont", "Initializing the font.");

        __bIsInitialized = true;

        return true;
    }

    bool Font::Initialize(std::string sClassName)
    {
        // Same as InitializeFont().
        return InitializeFont(sClassName);
    }
    // [ Ending ] - InitializeFont().

    // [ Starting ] - GetFontObject().
    HFONT Font::GetFontObject(HDC hDC)
    {
        // Helps to get the font object with extra information.
        SetGraphicsMode(hDC, GM_ADVANCED);

        GetFontObject();

        SelectObject(hDC, __hFont);

        return __hFont;
    }

    HFONT Font::GetFontObject(void)
    {
        __CheckWarning("GetFontObject");

        // Helps to get the font object.

        __hFont = CreateFontA(__nSizeFont, __nHeightFont, __nFontEscapement, __nFontOrientation, __nWeightFont, __bItalicFont, __bUnderLineFont, __bStrikeoutFont, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, (LPCSTR)__sStyleFont.c_str());
    
        return __hFont;
    }

    HFONT Font::GetObject(HDC hDC)
    {
        // Same as GetFontObject.
        return GetFontObject(hDC);
    }

    HFONT Font::GetObject(void)
    {
        // Same as GetFontObject.
        return GetFontObject();
    }
    // [ Ending ] - GetFontObject().

    // [ Starting ] - DeleteFontObject().
    bool Font::DeleteFontObject(void)
    {
        __CheckWarning("DeleteFontObject");

        // Helps to delete the font object that was created previous.

        return __TkinterWindow::DeleteFontObjectF(__hFont);
    }

    bool Font::DeleteObject(void)
    {
        // Same as DeleteFontObject.
        return DeleteFontObject();
    }
    // [ Ending ] - DeleteFontObject().

    // [ Starting ] - Font Styling.
    bool Font::SetFontItalicStyle(bool bItalicStyle)
    {
        __CheckWarning("SetFontItalicStyle");

        // Helps to set the italic style of the font.

        __console.Log("SetFontItalicStyle", "Setting the italic style of the font. Italic: %d.", bItalicStyle);
        __bItalicFont = bItalicStyle;

        return true;
    }

    bool Font::SetItalicStyle(bool bItalicStyle)
    {
        // Same as SetFontItalicStyle.
        return SetFontItalicStyle(bItalicStyle);
    }

    bool Font::SetFontUnderlineStyle(bool bUnderlineStyle)
    {
        __CheckWarning("SetFontUnderlineStyle");

        // Helps to set the underline style of the font.
        __console.Log("SetFontUnderlineStyle", "Setting the underline style of the font. Underline: %d.", bUnderlineStyle);

        __bUnderLineFont = bUnderlineStyle;

        return true;
    }

    bool Font::SetUnderlineStyle(bool bUnderlineStyle)
    {
        // Same as SetFontUnderlineStyle.
        return SetFontUnderlineStyle(bUnderlineStyle);
    }

    bool Font::SetFontStrikeoutStyle(bool bStrikeoutStyle)
    {
        __CheckWarning("SetFontStrikeoutStyle");

        // Helps to set the strikeout style of the font.

        __console.Log("SetFontStrikeoutStyle", "Setting the strikeout style of the font. Strikeout: %d.", bStrikeoutStyle);

        __bStrikeoutFont = bStrikeoutStyle;

        return true;
    }

    bool Font::SetStrikeoutStyle(bool bStrikeoutStyle)
    {
        // Same as SetFontStrikeoutStyle.
        return SetFontStrikeoutStyle(bStrikeoutStyle);
    }
    // [ Ending ] - Font Styling.

    // [ Starting ] - Font Size.
    bool Font::SetFontSize(int nFontSize)
    {
        __CheckWarning("SetFontSize");

        // Helps to set the font size of the font.
        __console.Log("SetFontSize", "Setting the font size. Size: %d.", nFontSize);
        
        __nHeightFont = 0;
        __nSizeFont = nFontSize;

        return true;
    }

    bool Font::SetSize(int nFontSize)
    {
        // Same as SetFontSize.
        return SetFontSize(nFontSize);
    }

    bool Font::SetFontHeight(int nFontHeight)
    {
        __CheckWarning("SetFontHeight");

        // Helps to set the font size of the font.
        __console.Log("SetFontHeight", "Setting the font height. Height: %d.", nFontHeight);
        
        __nHeightFont = nFontHeight;

        return true;
    }

    bool Font::SetHeight(int nFontHeight)
    {
        // Same as SetFontHeight.
        return SetFontHeight(nFontHeight);
    }

    bool Font::SetFontWidth(int nFontWidth)
    {
        __CheckWarning("SetFontWidth");

        // Helps to set the font size of the font.
        __console.Log("SetFontWidth", "Setting the font width. Width: %d.", nFontWidth);
        
        __nSizeFont = nFontWidth;

        return true;
    }

    bool Font::SetWidth(int nFontWidth)
    {
        // Same as SetFontWidth.
        return SetFontWidth(nFontWidth);
    }
    // [ Ending ] - Font Size.

    // [ Starting ] - Font family.
    bool Font::SetFontFamily(std::string sFontFamily)
    {
        __CheckWarning("SetFontFamily");

        // Helps to set the font family.
        __console.Log("SetFontFamily", "Setting the font family. Family: %s.", sFontFamily.c_str());

        __sStyleFont = sFontFamily;

        return true;
    }

    bool Font::SetFamily(std::string sFontFamily)
    {
        // Same as SetFontFamily.
        return SetFontFamily(sFontFamily);
    }

    bool Font::SetFontStyle(std::string sFontStyle)
    {
        // Same as SetFontFamily.
        return SetFontFamily(sFontStyle);
    }

    bool Font::SetStyle(std::string sFontStyle)
    {
        // Same as SetFontFamily.
        return SetFontFamily(sFontStyle);
    }
    // [ Ending ] - Font family.

    // [ Starting ] - Rotation controls.
    bool Font::SetFontEscapement(int nFontEscapement)
    {
        __CheckWarning("SetFontEscapement");

        // Helps to set the font escapement.
        __console.Log("SetFontEscapement", "Setting the font escapement. Escapement: %d.", nFontEscapement);

        __nFontEscapement = nFontEscapement;
        
        return true;
    }

    bool Font::SetEscapement(int nFontEscapement)
    {
        // Same as SetFontEscapement.
        return SetFontEscapement(nFontEscapement);
    }

    bool Font::SetFontOrientation(int nFontOrientation)
    {
        __CheckWarning("SetFontOrientation");

        // Helps to set the font escapement.
        __console.Log("SetFontOrientation", "Setting the font Orientation. Orientation: %d.", nFontOrientation);

        __nFontOrientation = nFontOrientation;
        
        return true;
    }

    bool Font::SetOrientation(int nFontOrientation)
    {
        // Same as SetFontOrientation.
        return SetFontOrientation(nFontOrientation);
    }
    // [ Starting ] - Rotation controls.

    // [ Starting ] - SetFontWeight.
    bool Font::SetFontWeight(int nFontWeight)
    {
        __CheckWarning("SetFontWeight");

        // Helps to set the font weight.
        __console.Log("SetFontWeight", "Setting the font weight. Weight: %d.", nFontWeight);

        __nWeightFont = nFontWeight;

        return true;
    }

    bool Font::SetWeight(int nFontWeight)
    {
        // Same as SetFontWeight.
        return SetFontWeight(nFontWeight);
    }
    // [ Ending ] - SetFontWeight.

    // [ Starting ] - debugger controls.
    bool Font::EnableDebugger(void)
    {
        // Helps to enable the debugger.
        return __console.EnableDebugger();
    }

    bool Font::DisableDebugger(void)
    {
        // Helps to disable the debugger.
        return __console.DisableDebugger();
    }
    // [ Ending ] - debugger controls.
    // [ Ending ] - Functions.

    // [ Starting ] - Private Functions.
    void Font::__CheckWarning(std::string sFunctionName)
    {
        if (!__bIsInitialized)
        {
            __console.Log(sFunctionName, "Warning: The function is called before the initalization. It can lead to some major problems.");
        }
    }
    // [ Ending ] - Private Functions.
}
